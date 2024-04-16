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

// #include "p5e.h"
// #include "p5f.h"

#define VIDEO_XSIZE 256
#define VIDEO_YSIZE 288

uint8_t charset[0x2000];

static uint8_t videoScreen[VIDEO_XSIZE][VIDEO_YSIZE];
static bool videoInitialised = false;
static bool videoRefreshNeeded = false;
static bool videoSpritesEnabled = false;

/*  The framebuffer is a 2D array of pixels with 4 bytes per pixel.  The first 3
 *  bytes of each pixel are r, g, b respectively and the 4th is not
 *  used.  The framebuffer is increased in size by the pixel magnification
 *  factor and also if a status pane is displayed.  Since these are
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
static void videoPlot (int x, int y, int col)
{
    int i, j;

    if (x < 0 || y < 0 || 
        x >= VIDEO_XSIZE || 
        y >= VIDEO_YSIZE)
    {
        fprintf (stderr,"VIDEO coords out of range\n");
        exit(1);
    }

    /*  Draw a square block of pixels of size (scale x scale) */
    for (i = 0; i < frameBufferScale; i++)
        for (j = 0; j < frameBufferScale; j++)
            videoPlotRaw (x*frameBufferScale+i, y*frameBufferScale+j, col);
}

/*  Draw an 8x8 character on screen.  cx and cy are the column (0 to 31) and row
 *  (0 to 23).  ch is the character index (0 to 255).  Values are multiplied by
 *  8 (<< 3) to convert to pixel coords.  bits is 6 or 8 for text or graphics.
 *
 *  https://www.walkofmind.com/programming/pie/char_defs.htm
 */
static void videoDrawChar (int cx, int cy, int ch, int col)
{
    int x, y;

    printf ("[%d;%d]", ch, col);
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            int z = ch * 16;
            z += (4-(y&4)) * 2;
            z += (7-x);
            char c = charset[z];
            col &= 0x3f;
            col |= (c & (0x01 << (y&3))) ? 0x40 : 0;
            col |= (c & (0x10 << (y&3))) ? 0x80 : 0;

            videoPlot ((cx << 3) + x, (cy << 3) + y, col);
        }
    }
}
                     
#if 0
static void videoDrawByte (int data, int x, int y, int col, int sprite)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            if (x+i < 0 || y < 0 || 
                x+i >= VIDEO_XSIZE || 
                y >= VIDEO_YSIZE)
            {
                /*  This pixel of the sprite is not visible */
                continue;
            }

            videoPlot (x + i, y, col);
        }

        data <<= 1;
    }
}
#endif

#if 0
static void videoDrawByteMagnified (int data, int x, int y, int col, int sprite)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
        {
            if (x+i*2 < 0 || y < 0 || 
                x+i*2 >= VIDEO_XSIZE-1 || 
                y >= VIDEO_YSIZE)
            {
                /*  This pixel of the sprite is not visible */
                continue;
            }

            if (videoSpriteCoinc[x+i*2][y] || videoSpriteCoinc[x+i*2+1][y])
                video.st |= VIDEO_SPRITE_COINC;

            videoSpriteCoinc[x+i*2][y] = true;
            videoSpriteCoinc[x+i*2+1][y] = true;

            videoPlot (x+i*2, y, col);
            videoPlot (x+i*2+1, y, col);
        }

        data <<= 1;
    }
}
#endif

#if 0
static void videoDrawSprites8x8 (int x, int y, int p, int c, int sprite)
{
    int i;

    mprintf (LVL_VIDEO, "Draw sprite pat 8x8 0x%x at %d,%d\n", p, x, y);
    for (i = 0; i < 8; i++)
    {
        videoDrawByte (video.ram[p+i], x, y + i, c & 0x0F, sprite);
    }
}
#endif

#if 0
static void videoDrawSprites16x16 (int x, int y, int p, int c, int sprite)
{
    int i, col;

    mprintf (LVL_VIDEO, "Draw sprite pat 16x16 0x%x at %d,%d\n", p, x, y);

    for (i = 0; i < 16; i++)
    {
        if (maxSpritesPerLine (y+i, sprite))
            continue;

        for (col = 0; col < 16; col += 8)
        {
            videoDrawByte (video.ram[p+i+col*2], x + col, y + i, c & 0x0F, sprite);
        }
    }
}

static void videoDrawSprites8x8Mag (int x, int y, int p, int c, int sprite)
{
    int i;

    mprintf (LVL_VIDEO, "Draw sprite 8x8 mag pat 0x%x at %d,%d\n", p, x, y);

    for (i = 0; i < 8; i++)
    {
        if (maxSpritesPerLine (y+i*2, sprite))
            continue;

        videoDrawByteMagnified (video.ram[p+i], x, y + i*2, c & 0x0F, sprite);

        if (maxSpritesPerLine (y+i*2+1, sprite))
            continue;

        videoDrawByteMagnified (video.ram[p+i], x, y + i*2+1, c & 0x0F, sprite);
    }
}

static void videoDrawSprites16x16Mag (int x, int y, int p, int c, int sprite)
{
    int i, col;

    mprintf (LVL_VIDEO, "Draw sprite 16x16 mag pat 0x%x at %d,%d\n", p, x, y);

    for (i = 0; i < 16; i++)
    {
        for (col = 0; col < 16; col += 8)
        {
            if (maxSpritesPerLine (y+i*2, sprite))
                continue;

            videoDrawByteMagnified (video.ram[p+i+col*2], x + col, y + i*2, c & 0x0F, sprite);

            if (maxSpritesPerLine (y+i*2+1, sprite))
                continue;

            videoDrawByteMagnified (video.ram[p+i+col*2], x + col, y + i*2+1, c & 0x0F, sprite);
        }
    }
}

static void videoDrawSprites (void)
{
    int size;
    int i;
    int x, y, p, c;
    int attr = VIDEO_SPRITEATTR_TAB;
    int entrySize = 8;

    video.st &= ~VIDEO_SPRITE_COINC;
    memset (videoSpriteCoinc, 0, VIDEO_XSIZE * VIDEO_YSIZE * sizeof (bool));

    size = (VIDEO_SPRITESIZE ? 1 : 0);
    size |= (VIDEO_SPRITEMAG ? 2 : 0);

    for (i = 0; i < VIDEO_YSIZE; i++)
        videoSpritesPerLine[i] = 0;

    for (i = 0; i < 32; i++)
    {
        y = video.ram[attr + i*4] + 1;
        x = video.ram[attr + i*4 + 1];
        p = video.ram[attr + i*4 + 2] * entrySize + VIDEO_SPRITEPAT_TAB;
        c = video.ram[attr + i*4 + 3];

        if (y == 0xD1)
        {
            mprintf (LVL_VIDEO, "Sprite %d switched off\n", y);
            return;
        }

        if (c & 0x80)
            x -= 32;

        mprintf (LVL_VIDEO, "Draw sprite %d @ %d,%d pat=%d, colour=%d\n", i, x, y, p, c);

        statusSpriteUpdate (i, x, y, p, c);

        #if 0
        /*  Transparent sprites don't get drawn */
        if (c == 0)
            continue;
        #endif

        switch (size)
        {
        case 0: videoDrawSprites8x8 (x, y, p, c, i); break;
        case 1: videoDrawSprites16x16 (x, y, p, c, i); break;
        case 2: videoDrawSprites8x8Mag (x, y, p, c, i); break;
        case 3: videoDrawSprites16x16Mag (x, y, p, c, i); break;
        }
    }
}
#endif

void videoRefresh (void)
{
    int sc;

    #if 0
    if (VIDEO_INT_ENABLE)
    {
        /*
         *  Clear bit 2 to indicate VIDEO interrupt
         */
        mprintf (LVL_VIDEO, "IRQ_VIDEO lowered\n");
        // cruBitInput (0, IRQ_VIDEO, 0);
        // video.st |= VIDEO_VERT_RETRACE;
    }
    #endif

    // if (!videoRefreshNeeded || !videoInitialised)
    //     return;

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
            default: pos=0x3a0+(y-2); inc=-32; break;
        }
        for (x = 0; x < 28; x++)
        {
            videoDrawChar (x, y, VIDEO[pos], COLOUR[pos]);
            pos += inc;
        }
    }

    // if (videoSpritesEnabled)
    //     videoDrawSprites ();

    videoScreenUpdate();
}

static bool videoThreadRunning = false;
static pthread_t thVideoThread;

static void *videoThread (void *arg)
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

    frameBufferXSize = VIDEO_XSIZE * scale;
    frameBufferYSize = VIDEO_YSIZE * scale;
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

