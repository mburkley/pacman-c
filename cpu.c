#include <stdbool.h>
#include <unistd.h>

#include "video.h"
#include "kbd.h"

void interruptEnable ()
{
}

void interruptDisable()
{
}

void interruptMode (int mode)
{
}

void interruptVector (int vector)
{
}

void interruptHalt (void)
{
void isr_008d (void);
    usleep(100000);
    isr_008d ();
// void showScreen (void);
// showScreen();
    videoRefresh();
    kbdPoll();
}

void kickWatchdog (void)
{
}
