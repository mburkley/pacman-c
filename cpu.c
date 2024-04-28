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
 * Some support functions for Z80 CPU
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "video.h"
#include "kbd.h"
#include "memmap.h"
#include "structs.h"

static void (*intVector) (void);

void interruptEnable ()
{
}

void interruptDisable()
{
}

void interruptMode (int mode)
{
}

static bool paused;
/*  TODO pend on cond var set up interrupt */
void interruptHalt (void)
{
    usleep(20000);
    static bool inInterrupt;
    if (!inInterrupt && !paused && intVector)
    {
        inInterrupt = true;
        intVector();
    }
    inInterrupt = false;
    kbdPoll(&paused);

    printf ("sprite-at: ");
    for (int i = 0; i < 16; i++)
        printf ("%02x ", SPRITEATTRIB[i]);
    printf ("\nsprite-co: ");
    for (int i = 0; i < 16; i++)
        printf ("%02x ", SPRITECOORDS[i]);
    printf ("\nstates: main=%d 0=%d intro=%d 2=%d l=%d s1=%d s2=%d s3=%d\n",
            MAIN_STATE, MAIN_STATE_SUB0, 
            INTRO_STATE, MAIN_STATE_SUB2, 
            LEVEL_STATE_SUBR,
            SCENE1_STATE,
            SCENE2_STATE,
            SCENE3_STATE);
    printf ("ghost states: b=%d p=%d i=%d c=%d\n",
            BLINKY_STATE,
            PINKY_STATE,
            INKY_STATE,
            CLYDE_STATE);
    printf ("ghost sub-states: %d %d %d %d\n",
            BLINKY_SUBSTATE,
            PINKY_SUBSTATE,
            INKY_SUBSTATE,
            CLYDE_SUBSTATE);
    printf ("pacman-tile %d,%d blinky-tile %d,%d\n",
            PACMAN_TILE2.x,
            PACMAN_TILE2.y,
            BLINKY_TILE2.x,
            BLINKY_TILE2.y);
    printf ("\n\n=====\n");
}

void interruptVector (void (*func) (void))
{
    intVector = func;
}

void kickWatchdog (void)
{
// usleep(50000);
}
