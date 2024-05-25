/*
 * Copyright (c) 204 Mark Burkley.
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

#ifndef __VIDEO_H
#define __VIDEO_H

#include <stdint.h>

typedef struct _pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t unused;
}
pixel;

void videoInit (int xsize, int ysize, int scale);
void videoDrawSprite (unsigned px, unsigned py, int shape, int mode, int colour);
void videoDrawChar (unsigned cx, unsigned cy, int chr, int chrCol);
void videoPlot (unsigned x, unsigned y, pixel p);
pixel videoColourLookup (uint8_t col);

#endif

