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

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>

#include "kbd.h"
#include "memmap.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

static int kbdFd;
static char kbdDevice[256];

static struct _keyCode
{
    int code;
    int input;
    int bit;
}
keyCode[] =
{
    { 110, 0, 0x20 },  // Ins = coin
    { 111, 1, 0x20 },  // Del = start
    {  75, 0, 0x02 },  // numpad 4 = left
    {  77, 0, 0x04 },  // numpad 6 = right
    {  80, 0, 0x08 },  // numpad 2 = down
    {  72, 0, 0x01 }   // numpad 8 = up
};

#define NUM_KEY 6

static void kbdReopen (void)
{
    if (kbdFd != -1)
        close (kbdFd);

    kbdFd = open (kbdDevice, O_RDONLY);

    if (kbdFd == -1)
    {
        printf ("%s failed to open device %s error %s\n", __func__,
              kbdDevice, strerror (errno));
        fprintf (stderr, "!! check keyboard input device");
        exit(1);
    }
}

static void decodeEvent (struct input_event ev)
{
    int i;
    bool mapped = false;

    if (ev.type == EV_KEY && ev.value < 2)
    {
        for (i = 0; i < NUM_KEY; i++)
            if (keyCode[i].code == ev.code)
            {
                printf ("%s KEY %d %s -> (%d)\n",
                         __func__,
                         ev.code,
                         ev.value == 0 ? "UP" : "DOWN",
                         i);

                uint8_t *input = keyCode[i].input ? &IO_INPUT1 : &IO_INPUT0;

                if (ev.value)
                    *input &= ~keyCode[i].bit;
                else
                    *input |= keyCode[i].bit;
                mapped = true;
            }

        if (!mapped)
            printf ("%s unknown KEY %s not mapped c=%d\n", __func__,
                   ev.value == 0 ? "UP" : "DOWN", ev.code);
    }
}

#define PROC_FILE "/proc/bus/input/devices"
#define HANDLERS "H: Handlers="
#define EVENTS "B: EV="

void kbdFindInputDevice (void)
{
    FILE *fp;
    unsigned events = 0;
    char handlers[256] = "";
    char s[256];
    bool found = false;

    if ((fp = fopen ("/proc/bus/input/devices", "r")) == NULL)
    {
        fprintf (stderr, "!! Open /proc/bus/input/devices");
        exit(1);
    }

    while (!feof (fp))
    {
        if (fgets (s, sizeof s, fp) == NULL)
            break;

        if (!strncmp (s, HANDLERS, strlen (HANDLERS)))
            strcpy (handlers, s+strlen (HANDLERS));
        else if (!strncmp (s, EVENTS, strlen (EVENTS)))
            events=strtoul (s+strlen (EVENTS), NULL, 16);

        if ((events & 0x120013) == 0x120013)
        {
            break;
        }
    }

    fclose (fp);

    if (!events)
    {
        fprintf (stderr, "!! no events");
        exit(1);
    }

    char *tok = handlers;

    tok = strtok (tok, " ");

    while (tok)
    {
        if (!strncmp (tok, "event", 5))
        {
            sprintf (kbdDevice, "/dev/input/%s", tok);
            printf ("Found kbd input dev %s\n", kbdDevice);
            found = true;
        }

        tok = strtok (NULL, " ");
    }

    if (!found)
    {
        fprintf (stderr, "!! Can't find keyboard");
        exit(1);
    }
}

void kbdPoll (void)
{
    struct input_event ev;
    struct pollfd pfds[2];
    int n;
    int ret;

    pfds[0].fd = 0;
    pfds[0].events = POLLIN;
    pfds[1].fd = kbdFd;
    pfds[1].events = POLLIN;
    ret = poll(pfds, 2, 0);

    if (ret < 1)
        return;

    if (!(pfds[1].revents & POLLIN))
        return;

    n = read (kbdFd, &ev, sizeof (ev));

    if (n < 0)
    {
        printf ("problem reading from device %s: %s\n",
                kbdDevice, strerror (errno));
        kbdReopen ();
        return;
    }

    if (n < (int) sizeof (ev))
    {
        printf ("Partial read of HID device, got %d / %lu bytes ", n,
          sizeof (struct input_event));
        return;
    }

    decodeEvent (ev);
}

void kbdClose (void)
{
    if (kbdFd != -1)
    {
        printf ("%s closing\n", __func__);
        close (kbdFd);
        kbdFd = -1;
    }
}

void kbdOpen (const char *device)
{
    if (device)
        strcpy (kbdDevice, device);
    else
        kbdFindInputDevice ();

    kbdFd = -1;
    kbdReopen ();

    printf ("%s dev %s opened as fd %d\n", __func__, kbdDevice, kbdFd);

}

