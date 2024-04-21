#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "video.h"
#include "kbd.h"
#include "memmap.h"

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

/*  TODO pend on cond var set up interrupt */
void interruptHalt (void)
{
    usleep(10000);
    static bool inInterrupt;
    if (!inInterrupt && intVector)
    {
        inInterrupt = true;
        intVector();
    }
    inInterrupt = false;
// void showScreen (void);
// showScreen();
    videoRefresh();
    kbdPoll();

    printf ("sprite-at: ");
    for (int i = 0; i < 16; i++)
        printf ("%02x ", SPRITEATTRIB[i]);
    printf ("\nsprite-co: ");
    for (int i = 0; i < 16; i++)
        printf ("%02x ", SPRITECOORDS[i]);
    printf ("\n\n=====\n");
}

void interruptVector (void (*func) (void))
{
    intVector = func;
}

void kickWatchdog (void)
{
}
