#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void showScreen (void)
{
    int x, y;
    for (y = 0; y < 36; y++)
    {
        int start;
        int inc;
        switch (y)
        {
            case 0: start=0x3df; inc=-1; break;
            case 1: start=0x3ff; inc=-1; break;
            case 34: start=0x01f; inc=-1; break;
            case 35: start=0x03f; inc=-1; break;
            default: start=0x3a0+(y-2); inc=-32; break;
        }
        for (x = 0; x < 32; x++)
        {
            if ((y < 2 || y > 33) && (x < 2 || x > 29))
            {
                printf (" ");
            }
            else
            {
                char c = SCREEN[start];
                if (c >= 32 && c < 128)
                    printf ("%c", SCREEN[start]);
                else
                    printf (".");
                start += inc;
            }
        }
        printf("\n");
    }
}

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
void reset_0000 (void);
    videoInit (3);
    kbdOpen (NULL);
    reset_0000 ();
}

