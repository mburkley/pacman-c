/*
 * Copyright (c) 2024 Mark Burkley.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Implements https://www.walkofmind.com/programming/pie/video_memory.htm */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "structs.h"
#include "memmap.h"
#include "video.h"

// 82s123.7f = colour palette.  16 bytes.  Each byte is BBGGGRRR (3-3-2 RGB)

// 82s126.4a = colour table.  32 x 16-bit entries.  each 16-bit entry is 4x4 bit
//             palette entries.

#include "82s123.7f.h"
#include "82s126.4a.h"

uint8_t charset[0x2000];

/*  The framebuffer is a 2D array of pixels with 4 bytes per pixel.  The first 3
 *  bytes of each pixel are r, g, b respectively and the 4th is not
 *  used.  The framebuffer is increased in size by the pixel magnification
 *  factor.  Since this is
 *  configurable, the framebuffer is allocated at runtime.
 */
static pixel *frameBuffer;

static int screenXSize;
static int screenYSize;

static int frameBufferXSize;
static int frameBufferYSize;
static int frameBufferScale;

bool redrawEnable = true;
bool drawTargetEnable = false;

/*  Raw plot, doesn't do any scaling, expects absolute coords */
static void videoPlotRaw (int x, int y, pixel p)
{
    y = frameBufferYSize - y - 1;
    frameBuffer[y*frameBufferXSize+x] = p;
}

pixel videoColourLookup (uint8_t col)
{
    /*  Lookup the colour in the 128-entry colour table to find the 4-bit colour */
    #if 0
    if (col == (0x1a<<2))
        col = 0xf;
    else if (col == (0x1b<<2))
        col = 0xe;
    // else if (col == (0x10<<2))
    //     col = 0xd;
    else
    #endif
    col = rom_82s126_4a[col & 0x7f];

    /*  Lookup the least significant 4 bits in the RGB colour in the 16-entry colour palette */
    col = rom_82s123_7f[col & 0xf];

    pixel p;
    // p.r = (col & 0x07) << 5;
    // p.g = (col & 0x31) << 2;
    // p.b = (col & 0xc0);
    p.r = (col & 7) * 36;
    p.g = ((col >> 3) & 7) * 36;
    p.b = (col >> 6) * 85;
    return p;
}

/*  Scaling plot, scales up x and y and draws a square of pixels */
void videoPlot (unsigned x, unsigned y, pixel p)
{
    int i, j;

    if (x >= screenXSize || 
        y >= screenYSize)
    {
        // fprintf (stderr,"!! SCREEN coords %d,%d out of range\n", x, y);
        // exit(1);
    }

    /*  Draw a square block of pixels of size (scale x scale) */
    for (i = 0; i < frameBufferScale; i++)
        for (j = 0; j < frameBufferScale; j++)
            videoPlotRaw (x*frameBufferScale+i, y*frameBufferScale+j, p);
}

/*  Draw an 8x8 character on screen.  cx and cy are the column (0 to 27) and row
 *  (0 to 35).  ch is the character index (0 to 255).  Values are multiplied by
 *  8 (<< 3) to convert to pixel coords.
 *
 *  Mapping of charset to pixels is a bit weird.  see here:
 *
 *      https://www.walkofmind.com/programming/pie/char_defs.htm
 *
 *  and colour info here:
 *
 *      https://aarongiles.com/old/mamemem/part3.html
 */
void videoDrawChar (unsigned cx, unsigned cy, int chr, int chrCol)
{
    unsigned x, y;

    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            int z = chr * 16;
            z += (4-(y&4)) << 1;
            z += (7-x);
            uint8_t pixelData = charset[z];
            uint8_t col = chrCol << 2;
            col |= (pixelData & (0x08 >> (y&3))) ? 0x01 : 0;
            col |= (pixelData & (0x80 >> (y&3))) ? 0x02 : 0;

            // TODO flipscreen
            pixel p = videoColourLookup (col);
            videoPlot ((cx << 3) + x, (cy << 3) + y, p);
        }
    }
}

void videoDrawSprite (unsigned px, unsigned py, int shape, int mode, int colour)
{
    unsigned x, y;

    /*  x==0 is RHS of screen, screen is over-sized 256 pixels */
    px = 256 - px;

    /*  Sprites are not visible if too far left */
    if (px < 0x12)
        return;

    /*  sprite coords are upside down */
    py = screenYSize - py;

    /*  Origin of sprite is bottom right.  Found these values by trial and error */
    px -= 0x12;
    py -= 0xf;

    for (y = 0; y < 16; y++)
    {
        for (x = 0; x < 16; x++)
        {
            /*  Found how to deal with x&8 and y&8 pretty much by trial and
             *  error but seems to yield correct results */
            int z = shape * 64;
            z += ((y+4)&0xc) << 1;
            z += (7-(x&7));
            if ((x&8) == 0)
                z += 32;
            uint8_t pixelData = charset[z + 0x1000];
            uint8_t col = colour << 2;
            col |= (pixelData & (0x08 >> (y&3))) ? 0x01 : 0;
            col |= (pixelData & (0x80 >> (y&3))) ? 0x02 : 0;
            pixel p = videoColourLookup (col);

            /*  Black sprite pixels are transparent, so only plot if any component is
             *  non zero */
            if (p.r > 0 || p.g > 0 || p.b > 0)
            {
                if (px+x >= screenXSize || 
                    py+y >= screenYSize)
                {
                    // fprintf (stderr,"SPRITE coords (%d,%d) out of range\n", px+x, py+y);
                }
                else
                {
                    int dx = x;
                    int dy = y;

                    /* Mirror */
                    if (mode & 2)
                        dx = 15-dx;

                    /* Invert */
                    if (mode & 1)
                        dy = 15-dy;

                    videoPlot (px + dx, py + dy, p);
                }
            }
        }
    }
}

static struct
{
    GLint vertex[4];
    int col;
}
targets[5];

void showTarget (XYPOS a, XYPOS b, int ghost)
{
    /*  Translate tile to pixel and scale */
    targets[ghost-1].vertex[0] = (476 - a.x * 8) * frameBufferScale;
    targets[ghost-1].vertex[1] = (524 - a.y * 8) * frameBufferScale;
    targets[ghost-1].vertex[2] = (476 - b.x * 8) * frameBufferScale;
    targets[ghost-1].vertex[3] = (524 - b.y * 8) * frameBufferScale;

    /*  Draw the line the colour of the ghost which is 1,3,5,7 or 9.  Shift
     *  right by 2 and or with 3 to ensure it gets the highest colour of the
     *  palette */
    targets[ghost-1].col = (((ghost*2-1) << 2) | 3);
}

static void videoRedraw (void)
{
    int x, y;
    for (y = 0; y < 36; y++)
    {
        int pos;
        int inc;
        switch (y)
        {
            case 0: pos=0x3dd; inc=-1; break;
            case 1: pos=0x3fd; inc=-1; break;
            case 34: pos=0x01d; inc=-1; break;
            case 35: pos=0x03d; inc=-1; break;
            default: pos=0x3a0+y-2; inc=-32; break;
        }
        for (x = 0; x < 28; x++)
        {
            videoDrawChar (x, y, SCREEN[pos], COLOUR[pos]);
            pos += inc;
        }
    }

    for (int sprite = 7; sprite >= 0; sprite--)
    {
        videoDrawSprite (SPRITECOORDS[sprite * 2], SPRITECOORDS[sprite * 2 + 1],
                         SPRITEATTRIB[sprite * 2] >> 2, SPRITEATTRIB[sprite * 2] & 3,
                         SPRITEATTRIB[sprite * 2 + 1]);
    }
}

static void drawTargets (void)
{
    for (int i = 0; i < 5; i++)
    {
        glLineWidth(4);

        /*  Use the ghost colour but at half intensity so instead of div 255 we
         *  div 511 */
        pixel p = videoColourLookup (targets[i].col);
        glColor4f (p.r / 511.0, p.g / 511.0, p.b / 511.0, 0.1);

        glBegin(GL_LINE_LOOP);
        glVertex2iv(&targets[i].vertex[0]);
        glVertex2iv(&targets[i].vertex[2]);
        glEnd();
    }
}

static void displayFunc (void)
{
    if (redrawEnable)
        videoRedraw ();

    glDrawPixels (frameBufferXSize, frameBufferYSize, GL_RGBA, GL_UNSIGNED_BYTE, frameBuffer);

    if (drawTargetEnable)
        drawTargets ();

    glFlush();
    glutSwapBuffers();
}

static bool videoThreadRunning = false;
static pthread_t thVideoThread;

static void *videoThread (void *arg)
{
    int argc=1;
    char *argv[] = { "foo" };
    glutInit(&argc, argv);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutInitWindowSize(frameBufferXSize, frameBufferYSize);
    #define VERSION "0.7"
    glutCreateWindow("Pacman-c v" VERSION);
    glViewport(0, 0, frameBufferXSize, frameBufferYSize);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, frameBufferXSize, 0, frameBufferYSize, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    #if 0
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    #endif

    glutDisplayFunc(displayFunc);
    glutIdleFunc(glutPostRedisplay); // keep redrawing
    glutMainLoop(); 

    return NULL;
}

void videoInit (int xsize, int ysize, int scale)
{
    screenXSize = xsize;
    screenYSize = ysize;

    frameBufferXSize = screenXSize * scale;
    frameBufferYSize = screenYSize * scale;
    frameBufferScale = scale;

    frameBuffer = calloc (frameBufferXSize * frameBufferYSize,
                          sizeof (pixel));

    if (frameBuffer == NULL)
    {
        fprintf (stderr, "!! allocated frame buffer");
        exit (1);
    }

    printf ("FB size is %d x %d\n", frameBufferXSize, frameBufferYSize);

    videoThreadRunning = true;
    if (pthread_create (&thVideoThread, NULL, videoThread, NULL) != 0)
    {
        fprintf (stderr, "!! thread\n");
        exit (1);
    }
}

