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

#include "memmap.h"
#include "video.h"

// 82s123.7f = colour palette.  16 bytes.  Each byte is BBGGGRRR (3-3-2 RGB)

// 82s126.4a = colour table.  32 x 16-bit entries.  each 16-bit entry is 4x4 bit
//             palette entries.

#include "82s123.7f.h"
#include "82s126.4a.h"

#define SCREEN_XSIZE 224
#define SCREEN_YSIZE 288

uint8_t charset[0x2000];

// static uint8_t videoScreen[SCREEN_XSIZE][SCREEN_YSIZE];
static bool videoInitialised = false;
static bool videoRefreshNeeded = false;
// static bool videoSpritesEnabled = false;

/*  The framebuffer is a 2D array of pixels with 4 bytes per pixel.  The first 3
 *  bytes of each pixel are r, g, b respectively and the 4th is not
 *  used.  The framebuffer is increased in size by the pixel magnification
 *  factor.  Since this is
 *  configurable, the framebuffer is allocated at runtime.
 */
static struct _frameBuffer
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t unused;
}
*frameBuffer;

static int frameBufferXSize;
static int frameBufferYSize;
static int frameBufferScale;

static inline struct _frameBuffer* pixel (int x, int y)
{
    return &frameBuffer[y*frameBufferXSize+x];
}

static void videoScreenUpdate (void)
{
    glDrawPixels (frameBufferXSize, frameBufferYSize, GL_RGBA, GL_UNSIGNED_BYTE, frameBuffer);
    glutSwapBuffers();
}

/*  Raw plot, doesn't do any scaling, expects absolute coords */
void videoPlotRaw (int x, int y, int col)
{
    y = frameBufferYSize - y - 1;

    pixel (x, y)->r = (col & 0x07) << 5;
    pixel (x, y)->g = (col & 0x31) << 2;
    pixel (x, y)->b = (col & 0xc0);
}

/*  Scaling plot, scales up x and y and draws a square of pixels */
static void videoPlot (unsigned x, unsigned y, int col, bool noBlack)
{
    int i, j;

    /*  Lookup the colour in the 128-entry colour table to find the 4-bit colour */
    col = rom_82s126_4a[col & 0x7f];

    /*  Lookup the least significant 4 bits in the RGB colour in the 16-entry colour palette */
    col = rom_82s123_7f[col & 0xf];

    if (// x < 0 || y < 0 || 
        x >= SCREEN_XSIZE || 
        y >= SCREEN_YSIZE)
    {
        fprintf (stderr,"SCREEN coords out of range\n");
        exit(1);
    }

    if (col == 0 && noBlack)
        return;

    /*  Draw a square block of pixels of size (scale x scale) */
    for (i = 0; i < frameBufferScale; i++)
        for (j = 0; j < frameBufferScale; j++)
            videoPlotRaw (x*frameBufferScale+i, y*frameBufferScale+j, col);
}

/*  Draw an 8x8 character on screen.  cx and cy are the column (0 to 27) and row
 *  (0 to 35).  ch is the character index (0 to 255).  Values are multiplied by
 *  8 (<< 3) to convert to pixel coords.
 *
 *  Mapping of charset to pixels is a bit weird.  see here:
 *
 *      https://www.walkofmind.com/programming/pie/char_defs.htm
 *
 *  and colour info here: https://aarongiles.com/old/mamemem/part3.html
 */
static void videoDrawChar (unsigned cx, unsigned cy, int chr, int chrCol)
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

            videoPlot ((cx << 3) + x, (cy << 3) + y, col, false);
        }
    }
}

static void videoDrawSprite (unsigned px, unsigned py, int shape, int mode, int colour)
{
    unsigned x, y;

    /*  x==0 is RHS of screen, screen is over-sized 256 pixels */
    px = 256 - px;

    /*  sprite coords are upside down */
    py = SCREEN_YSIZE - py;

    /*  Origin of sprite is bottom right */
    px -= 0x12;
    py -= 0xf;

    /*  TODO invert and mirror */
    for (y = 0; y < 16; y++)
    {
        for (x = 0; x < 16; x++)
        {
            int z = shape * 64;
            z += ((y+4)&0xc) << 1;
            z += (7-(x&7));
            if ((x&8) == 0)
                z += 32;
            uint8_t pixelData = charset[z + 0x1000];
            uint8_t col = colour << 2;
            col |= (pixelData & (0x08 >> (y&3))) ? 0x01 : 0;
            col |= (pixelData & (0x80 >> (y&3))) ? 0x02 : 0;

            if (px+x >= SCREEN_XSIZE || 
                py+y >= SCREEN_YSIZE)
            {
                // fprintf (stderr,"SPRITE coords (%d,%d) out of range\n", px+x, py+y);
            }
            else if (col > 0)
            {
                int dx = x;
                int dy = y;

                /* Mirror */
                if (mode & 2)
                    dx = 15-dx;

                /* Invert */
                if (mode & 1)
                    dy = 15-dy;

                videoPlot (px + dx, py + dy, col, true);
            }
        }
    }
}
                     

void videoRefresh (void)
{
    videoRefreshNeeded = false;

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

    // if (videoSpritesEnabled)
    //     videoDrawSprites ();

    videoScreenUpdate();
}

static bool videoThreadRunning = false;
// static pthread_t thVideoThread;

void *videoThread (void *arg)
{
    while (videoThreadRunning)
    {
        usleep (16667);
        printf ("vid refr\n");
        videoRefresh ();
    }

    return NULL;
}

void videoInit (int scale)
{
    int argc=1;
    char *argv[] = { "foo" };
    glutInit(&argc, argv);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    frameBufferXSize = SCREEN_XSIZE * scale;
    frameBufferYSize = SCREEN_YSIZE * scale;
    frameBufferScale = scale;

    frameBuffer = calloc (frameBufferXSize * frameBufferYSize,
                          sizeof (struct _frameBuffer));

    if (frameBuffer == NULL)
    {
        fprintf (stderr, "allocated frame buffer");
        exit (1);
    }

    printf ("FB size is %d x %d\n", frameBufferXSize, frameBufferYSize);
    glutInitWindowSize(frameBufferXSize, frameBufferYSize);
    #define VERSION "0.7"
    glutCreateWindow("Pacman-c v" VERSION);

    videoInitialised = true;

    #if 0
    videoThreadRunning = true;
    if (pthread_create (&thVideoThread, NULL, videoThread, NULL) != 0)
    {
        // halt ("create video thread");
        fprintf (stderr, "thread\n");
        exit (1);
    }
    #endif
}

