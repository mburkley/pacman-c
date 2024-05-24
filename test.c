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
 *
 * I/O for pacman
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "memmap.h"
#include "video.h"
#include "sound.h"
#include "kbd.h"

#include "pacman.5e.h"
#include "pacman.5f.h"

#include "pacman.6e.h"
#include "pacman.6f.h"
#include "pacman.6h.h"
#include "pacman.6j.h"

#include "namcopac.6e.h"
#include "namcopac.6f.h"
#include "namcopac.6h.h"
#include "namcopac.6j.h"

CPU_MEMMAP memmap;
uint8_t input0;
uint8_t input1;
uint8_t dipSwitches;

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf (stderr, "Please provide test pattern (1-3)\n");
        exit (1);
    }

    memcpy (&charset[0x0000], rom_pacman_5e, 0x1000);
    memcpy (&charset[0x1000], rom_pacman_5f, 0x1000);

    #if 1
    memcpy (&ROM[0x0000], rom_pacman_6e, 0x1000);
    memcpy (&ROM[0x1000], rom_pacman_6f, 0x1000);
    memcpy (&ROM[0x2000], rom_pacman_6h, 0x1000);
    memcpy (&ROM[0x3000], rom_pacman_6j, 0x1000);
    #else
    memcpy (&ROM[0x0000], rom_namcopac_6e, 0x1000);
    memcpy (&ROM[0x1000], rom_namcopac_6f, 0x1000);
    memcpy (&ROM[0x2000], rom_namcopac_6h, 0x1000);
    memcpy (&ROM[0x3000], rom_namcopac_6j, 0x1000);
    #endif

    extern bool redrawEnable;
    redrawEnable = false;
    videoInit (300, 300, 3); // 32 x 8 + 8

    switch (argv[1][0])
    {
    case '1':
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                // SCREEN[0x380+i*2-(0x20*j)] = (i*16)+j;
                // COLOUR[0x380+i*2-(0x20*j)] = 0x1;
                int col = 0x1f;
                if (j>5) col = 1;
                if (j>8) col = 0x14;
                if (j>0xa) col = 0x1;
                if (j>0xb) col = 0x10;

                videoDrawChar (1+i*2, 1+j*2, j*16+i, col);
            }
        }
        break;
    case '2':
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                videoDrawSprite (i*24 + 8, j*24 + 8, j*8+i, 0, 1);
            }
        }
        break;
    case '3':
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                pixel p = videoColourLookup ((j << 2) | i);
                for (int x = 0; x < 8; x++)
                {
                    for (int y = 0; y < 8; y++)
                    {
                        videoPlot (8+i*9+x, 8+j*9+y, p);
                    }
                }
            }
        }
        break;
    }


    usleep (100000000);
}

