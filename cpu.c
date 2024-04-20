#include <stdbool.h>
#include <unistd.h>

#include "video.h"
#include "kbd.h"

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
    usleep(100000);
    if (intVector)
        intVector();
// void showScreen (void);
// showScreen();
    videoRefresh();
    kbdPoll();
}

void interruptVector (void (*func) (void))
{
    intVector = func;
}

void kickWatchdog (void)
{
}
