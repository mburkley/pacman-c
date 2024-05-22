#ifndef __STRUCTS_H
#define __STRUCTS_H

/*  X and Y coords are frequently stored together and accessed as a single 16-
 *  bit value (e.g. through the hl reg).  To simplify C code, declare a union of
 *  y and x byte values with a 16 bit hl reg */
typedef struct // union
{
    uint8_t y; // l
    uint8_t x; // h
}
XYPOS;

typedef struct
{
    uint8_t timer;
    uint8_t func;
    uint8_t param;
}
TASK;

typedef struct
{
    uint8_t mask;
    uint8_t __unused_1;
    uint8_t current;
    uint8_t selected;           // high nybble = freq scale, low nyb = sound effect
    uint8_t frequencyInitial;   // diff mean in song and effect?  use union?  song=scale
    uint8_t frequencyDelta;
    // uint8_t offsetLo;   // also &7f = duraction, &80 = ??
    // uint8_t offsetHi;   // also freq delta
    uint16_t offset;
    uint8_t repeat;  // 8
    uint8_t volumeInitial; // 9
    uint8_t volumeDelta;   // a
    uint8_t type;          // b
    uint8_t duration;      // c
    uint8_t dir;           // d
    uint8_t frequency;     // e 
    uint8_t volume;        // f
}
SOUND_EFFECT;

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

#endif
