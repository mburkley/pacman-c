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

#endif
