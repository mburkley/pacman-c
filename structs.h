/*  X and Y coords are frequently stored together and accessed as a single 16-
 *  bit value (e.g. through the hl reg).  To simplify C code, declare a union of
 *  y and x byte values with a 16 bit hl reg */

#ifndef __STRUCTS_H
#define __STRUCTS_H

typedef struct // union
{
    // struct
    // {
        uint8_t y; // l
        uint8_t x; // h
    // };
    // uint16_t hl;
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

#endif
