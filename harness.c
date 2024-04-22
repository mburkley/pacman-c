#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "memmap.h"
#include "video.h"
#include "kbd.h"

#include "p5e.h"
#include "p5f.h"

#include "p6e.h"
#include "p6f.h"
#include "p6h.h"
#include "p6j.h"

CPU_MEMMAP memmap;
uint8_t input0;
uint8_t input1;
uint8_t dipSwitches;

int main (void)
{
    memcpy (&charset[0x0000], rom_pacman_5e, 0x1000);
    memcpy (&charset[0x1000], rom_pacman_5f, 0x1000);

    memcpy (&ROM[0x0000], rom_pacman_6e, 0x1000);
    memcpy (&ROM[0x1000], rom_pacman_6f, 0x1000);
    memcpy (&ROM[0x2000], rom_pacman_6h, 0x1000);
    memcpy (&ROM[0x3000], rom_pacman_6j, 0x1000);

    /*  Input switches are active low */
    IO_INPUT0 = 0xff;
    IO_INPUT1 = 0xff;
    DIP_INPUT = 0xff;
    printf ("IN0=%02x\n", IO_INPUT0);

void reset_0000 (void);
    videoInit (3);
    kbdOpen (NULL);

    #if 1
    reset_0000 ();
    #else
    for (int i = 0; i < 0x400; i++)
        COLOUR[i]=1;
    for (int i = 0; i < 0x400; i++)
        SCREEN[i]=i;
    videoRefresh();
    usleep (100000000);
    #endif
}

