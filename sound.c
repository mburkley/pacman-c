/*
 * Copyright (c) 2004-2023 Mark Burkley.
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

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <pulse/simple.h>

#include "memmap.h"

/* TODO is audio rom 1 needed?  Highest waveform (32B) I've seen is 6 */

#include "82s126.1m.h"  // audio rom 0
#include "82s126.3m.h"  // audio rom 1

uint8_t soundRom[0x200];

/*  The frequency at which we are playing samples to pulse audio */
#define AUDIO_FREQUENCY 96000

/* Generate 10ms of samples at a time */
#define SAMPLE_COUNT (AUDIO_FREQUENCY / 100)

static short generateTone (uint8_t *freqCountPtr, uint8_t *freqPtr, uint8_t volume,
                           uint8_t waveForm, int bytes)
{
    short sample;
    int freq = 0;
    int freqCounter = 0;

    /*  Shift nybbles into a 16 or 20 bit word */
    for (int i = bytes - 1; i >= 0; i--)
    {
        freq <<= 4;
        freqCounter <<= 4;

        freq |= (freqPtr[i] & 0xf);
        freqCounter |= (freqCountPtr[i] & 0xf);
    }

    freqCounter += freq;

    /* soundRom has 512 bytes: 2 x 256 = 32 x 16 waveforms */
    waveForm &= 0xf;

    /*  Fetch the highest 5 bits of the 16 or 20 bit freq counter */
    int ix;
    if (bytes == 5)
        ix = (freqCounter>>15) & 0x1f;
    else
        ix = (freqCounter>>11) & 0x1f;

    /*  Select the waveform */
    ix |= (waveForm << 5);

    sample = soundRom[ix];

    for (int i = 0; i < bytes; i++)
    {
        freqCountPtr[i] = freqCounter & 0xf;
        freqCounter >>= 4;
    }

    sample = (sample - 8) * volume * 68;
    /*  Convert 0-225 to -8192 to +8191 */
    return sample; //  * 72 - 8192;
}

#define TEST_SMP 1600 // generate a 60hz wave @ 96kHz
#define TEST_AMP 32 // 32 / 32768 = 1/2^10 = -30dB 
static short testWave (void)
{
    static int counter;

    double angle = (2 * M_PI * counter++) / TEST_SMP;
    counter %= TEST_SMP;
    return TEST_AMP * sin (angle);
}

static short generateSample (void)
{
    short sample = 0;
    SOUNDREGS *sound = (SOUNDREGS*) SOUND;

    sample = generateTone (sound->v1FreqCount, sound->v1Frequency,
        sound->v1Volume, sound->v1WaveForm, 5);
    sample += generateTone (sound->v2FreqCount, sound->v2Frequency,
        sound->v2Volume, sound->v2WaveForm, 4);
    sample += generateTone (sound->v3FreqCount, sound->v3Frequency,
        sound->v3Volume, sound->v3WaveForm, 4);
    sample += testWave();

    return sample;
}

/*  Every 10 msec, generate data to feed pulse audio device using a combination
 *  from currently active tone and noise generators.
 */
static void soundUpdate (pa_simple *pulseAudioHandle)
{
    int i;

    /*  Create an array of samples to play to pulse audio.    The values are
     *  signed 16-bit so for one channels we have 2 bytes for sample.
     */
    int16_t sampleData[SAMPLE_COUNT];

    for (i = 0; i < SAMPLE_COUNT; i++)
        sampleData[i] = generateSample ();

    pa_simple_write (pulseAudioHandle, sampleData, 2*SAMPLE_COUNT, NULL);
}

static bool soundThreadRunning = false;
static pthread_t audioThread;

static void *soundThread (void *arg)
{
    pa_simple *pulseAudioHandle = (pa_simple*) arg;

    while (soundThreadRunning)
        soundUpdate (pulseAudioHandle);

    return NULL;
}

void soundInit (void)
{
    pa_simple *pulseAudioHandle;
    static pa_sample_spec pulseAudioSpec;

    pulseAudioSpec.format = PA_SAMPLE_S16NE;
    pulseAudioSpec.channels = 1;
    pulseAudioSpec.rate = AUDIO_FREQUENCY;

    memcpy (&soundRom[0x0000], rom_82s126_1m, 0x100);
    memcpy (&soundRom[0x0100], rom_82s126_3m, 0x100);

    pulseAudioHandle = pa_simple_new(NULL,               // Use the default server.
                      "Pacman-C",           // Our application's name.
                      PA_STREAM_PLAYBACK,
                      NULL,               // Use the default device.
                      "Games",            // Description of our stream.
                      &pulseAudioSpec,                // Our sample format.
                      NULL,               // Use default channel map
                      NULL,               // Use default buffering attributes.
                      NULL               // Ignore error code.
                      );

    if (pulseAudioHandle == NULL)
    {
        fprintf (stderr, "pulse audio handle new fail\n");
        exit (1);
    }

    soundThreadRunning = true;

    if (pthread_create (&audioThread, NULL, soundThread, pulseAudioHandle) != 0)
    {
        fprintf (stderr, "can't create sound thread\n");
        exit (1);
    }
}

void soundClose (void)
{
    soundThreadRunning = false;
    pthread_join (audioThread, NULL);
}

