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
bool paused;

int main (int argc, char *argv[])
{
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

    /*  Input switches are active low */
    IO_INPUT0 = 0xef;
    IO_INPUT1 = 0x6f;
    IO_INPUT0 |= 0x10; // remove for rack advance
     IO_INPUT1 |= 0x10; // remove for service
    IO_INPUT1 |= 0x80; // upright mode, remove for cabinet
    // DIP_INPUT = 0xff; default, 5 lives, 2 coins per game, etc
    DIP_INPUT = 0x49; 
    DIP_INPUT |= 0x80; // remove for alt names
    printf ("IN0=%02x\n", IO_INPUT0);
    if (argc > 1)
        DIP_INPUT = atoi (argv[1]);

    void reset_0000 (void);
    videoInit (3);
    soundInit ();
    keyboardInit (&paused);

    #if 1
    reset_0000 ();
    #else

    /*  Test code to display all chars (or all sprites) on screen */
    for (int i = 0; i < 0x400; i++)
        COLOUR[i]=1;
    for (int i = 0; i < 0x400; i++)
        SCREEN[i]=i;
    memcpy (&charset[0x0000], rom_pacman_5f, 0x1000);
    usleep (100000000);
    #endif
}

