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

// 82s126.1m = audio data
// 82s126.3m = audio data

#include "82s126.1m.h"
#include "82s126.3m.h"

uint8_t soundRom[0x200];

/*  The frequency at which we are playing samples to pulse audio
 */
#define AUDIO_FREQUENCY 48000

/* At 44,100Hz we need to generate 480 samples per call as we are called every
 * 20msec.
 */
#define SAMPLE_COUNT 480
// #define SAMPLE_COUNT 1

/*  Move to memmap? */
typedef struct
{
    uint8_t v1FreqCount[5];             // 0x5040
    uint8_t v1WaveForm;                 // 0x5045
    uint8_t v2FreqCount[4];             // 0x5046
    uint8_t v2WaveForm;                 // 0x504a
    uint8_t v3FreqCount[4];             // 0x504b
    uint8_t v3WaveForm;                 // 0x504f
    uint8_t v1Frequency[5];             // 0x5050
    uint8_t v1Volume;                   // 0x5055
    uint8_t v2Frequency[4];             // 0x5056
    uint8_t v2Volume;                   // 0x505a
    uint8_t v3Frequency[4];             // 0x505b
    uint8_t v3Volume;                   // 0x505f
}
SOUNDREGS;

static short generateTone (uint8_t *freqCountPtr, uint8_t *freqPtr, uint8_t volume,
uint8_t waveForm, int bytes)
{
    short sample;
    int freq = 0;
    int freqCounter = 0;

    /*  Right shift nybbles into a 16 or 20 bit word */
    for (int i = 0; i < 5; i++)
    {
        freq >>= 4;
        freqCounter >>= 4;

        if (i < bytes)
        {
            freq |= (freqPtr[i] & 0xf) << 16;
            // printf ("%s AUD nyb=%d out=%x\n", __func__, freqPtr[i]&0xf, freq);
            freqCounter |= (freqCountPtr[i] & 0xf) << 16;
        }
    }

    /*  To avoid pops in the audio, we only make changes to amplitude at the
     *  beginning or end of a cycle.  If a change in amplitude or frequency have
     *  been requested, do this only when counter is zero so we don't do it in
     *  the middle of a cycle
     */
    #if 0
    if (tone->counter == 0)
    {
        tone->amplitude = tone->requestedAmplitude;
        tone->period = tone->requestedPeriod;
    }
    #endif

    // if (volume == 0 || freq == 0)
    //     return 0;

    // double angle = (2 * M_PI * tone->counter) / tone->period;

    freqCounter += freq;
    freqCounter &= 0xfffff;

    /*  soundRom has 512 bytes.  32B x 16 */
    waveForm&=0xf;
    sample = soundRom[(freqCounter>>15) | (waveForm << 5)];
    // printf ("%s AUD v=%d w=%d f=%d fc=%d[%d] smp=%d\n", __func__, volume,
    // waveForm, freq, freqCounter, freqCounter>>15, sample);

    for (int i = 0; i < 5; i++)
    {
        if (bytes == 5 || i > 0)
            freqCountPtr[i] = freqCounter & 0xf;

        freqCounter >>= 4;
    }

    sample = (sample - 8) * volume * 68;
    /*  Convert 0-225 to -8192 to +8191 */
    return sample; //  * 72 - 8192;
}

#if 0
static bool updateActiveToneGenerators (toneInfo *tone)
{
    if (tone->requestedAmplitude == 0 && tone->amplitude == 0)
        return false;

    return true;
}
#endif

#define TEST_SMP 192 // generate a 250hz wave (48khz => 192 samples)
#define TEST_AMP 128 // 128 / 32768 = 1/2^8 = -24dB ?
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

static void dump16 (uint8_t *data)
{
    for (int i = 0; i < 16; i++)
        printf ("%02x ", data[i]);
}

/*  Every 10 msec, generate data to feed pulse audio device using a combination
 *  from currently active tone and noise generators.
 */
static bool soundUpdate (pa_simple *pulseAudioHandle)
{
    int i;
    #if 0
    bool anyActive = false;

    for (i = 0; i < 3; i++)
    {
        anyActive = updateActiveToneGenerators (&tones[i]) || anyActive;
    }

    if (!anyActive)
    {
        return false;
    }
    #endif

    /*  Create an array of samples to play to pulse audio.    The values are
     *  signed 16-bit so for one channels we have 2 bytes for sample.
     */
    int16_t sampleData[SAMPLE_COUNT];
    printf ("%s AUDX REG= ", __func__); dump16 (&SOUND[16]); printf ("\n");
    // printf ("%s AUDX gen %d samps\n", __func__, SAMPLE_COUNT);
    for (i = 0; i < SAMPLE_COUNT; i++)
    {
        int16_t sample;

        sample = generateSample ();

        sampleData[i] = sample;
    }
    // return false; // delete me

    pa_simple_write (pulseAudioHandle, sampleData, 2*SAMPLE_COUNT, NULL);

    return true;
}

static bool soundThreadRunning = false;
static pthread_t audioThread;

static void *soundThread (void *arg)
{
    pa_simple *pulseAudioHandle = (pa_simple*) arg;

    while (soundThreadRunning)
    {
        if (!soundUpdate (pulseAudioHandle))
            usleep (10000);
    }

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


