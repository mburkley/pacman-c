/* Memory map table.  Starts at flat map but replace with specific locations as
 * they are discovered */

// Video : https://www.walkofmind.com/programming/pie/video_memory.htm



struct
{
    struct
    {
        uint8_t rom[0x4000]; // starts at 0x0000
        uint8_t video[0x400]; // starts at 0x4000
        uint8_t colour[0x400]; // starts at 0x4400
        uint8_t ram[0x7f0];  // starts at 0x4800
        uint8_t sprites[0x10];  // starts at 0x4ff0
    };
    union
    {
        struct
        {
            uint8_t in0[0x40]; // 0x5000-0x503f
            uint8_t in1[0x40]; // 0x5040-0x507f
            uint8_t dipSwitches[0x40]; // 0x5080-0x50bf
        } read;
        struct
        {
            uint8_t intEnable;  // 0x5000
            uint8_t soundEnable; // 0x5001
            uint8_t auxEnable; // 0x5002
            uint8_t flipScreen; // 0x5003
            uint8_t player1Start; // 0x5004
            uint8_t player2Start; // 0x5005
            uint8_t coinLockout; // 0x5006
            uint8_t coinCounter; // 0x5007
            uint8_t outputs[8]; // 0x5000-0x5007
            uint8_t __unused[0x38];
            uint8_t soundRegs[0x40]; // 0x5040
            uint8_t spriteCoords[0x10]; // 0x5060
            uint8_t watchdog[0x40]; // 0x50c0-0x50ff
        } write;
    } regs;
    uint8_t mem[0x5100];
}
memmap;

#define MEM memmap.mem.addr
#define RAM memory.mem.block.ram
#define VIDEO memory.mem.block.video
#define COLOUR memory.mem.block.colour
#define SOUND memory.regs.write.soundRegs
#define SPRITES memory.mem.block.sprites
#define INTENABLE memory.regs.write.outputs[0]; // 0x5000
#define COINCOUNTER memory.regs.write.coinCounter
#define COINLOCKOUT memory.regs.write.coinLockout
#define REGSWRITE memory.regs.write
#define SOUNDENABLE memory.regs.write.soundEnable

#define IN0_UP          (memory.regs.read.in0 & 0x01)
#define IN0_LEFT        (memory.regs.read.in0 & 0x02)
#define IN0_RIGHT       (memory.regs.read.in0 & 0x04)
#define IN0_DOWN        (memory.regs.read.in0 & 0x08)
#define IN0_TEST        (memory.regs.read.in0 & 0x10)
#define IN0_COIN1       (memory.regs.read.in0 & 0x20)
#define IN0_COIN2       (memory.regs.read.in0 & 0x40)
#define IN0_COIN3       (memory.regs.read.in0 & 0x80)

#define IN1_UP          (memory.regs.read.in0 & 0x01)
#define IN1_LEFT        (memory.regs.read.in0 & 0x02)
#define IN1_RIGHT       (memory.regs.read.in0 & 0x04)
#define IN1_DOWN        (memory.regs.read.in0 & 0x08)
#define IN1_SERVICE     (memory.regs.read.in0 & 0x10)
#define IN1_START1      (memory.regs.read.in0 & 0x20)
#define IN1_START2      (memory.regs.read.in0 & 0x40)
#define IN1_CABINET     (memory.regs.read.in0 & 0x80)

#define DIP_SWITCH_TEST (memmap.regs.read.in0 & 0x10)

#define BLINKY_SPRITE memmap.mem[0x4c02]
#define BLINKY_COLOUR memmap.mem[0x4c03]
#define PINKY_SPRITE memmap.mem[0x4c04]
#define PINKY_COLOUR memmap.mem[0x4c05]
#define INKY_SPRITE memmap.mem[0x4c06]
#define INKY_COLOUR memmap.mem[0x4c07]
#define CLYDE_SPRITE memmap.mem[0x4c08]
#define CLYDE_COLOUR memmap.mem[0x4c09]
#define PACMAN_SPRITE memmap.mem[0x4c0a]
#define PACMAN_COLOUR memmap.mem[0x4c0b]
#define FRUIT_SPRITE memmap.mem[0x4c0c]
#define FRUIT_COLOUR memmap.mem[0x4c0d]

#define SPRITE_POS ((uint8_t *)&memmap.mem[0x4c22])
#define SPRITE_DATA ((uint8_t *)&memmap.mem[0x4c32])

#define TASK_LIST_END (*(uint16_t*)&memmep.mem[0x4c80])
#define TASK_LIST_BEGIN (*(uint16_t*)&memmep.mem[0x4c82])

#define SOUND_COUNTER &memmap.mem[0x4c84]
#define TIMER_HUNDREDTHS memmap.mem[0x4c86]
#define TIMER_SECONDS memmap.mem[0x4c87]
#define TIMER_MINUTES memmap.mem[0x4c88]
#define TIMER_HOURS memmap.mem[0x4c89]
#define COUNTER_LIMITS_CHANGES memmap.mem[0x4c8a]

/*  ISR tasks are 3 bytes each and there are 16 entries */
#define ISR_TASKS (&memmap.mem[0x4c90])

/*  non-ISR tasks are 2 bytes each and there are 16 entries */
#define NONISR_TASKS (&memmap.mem[0x4cc0])

#define BLINKY_Y memmap.mem[0x4d00]
#define BLINKY_X memmap.mem[0x4d01]
#define PINKY_Y  memmap.mem[0x4d02]
#define PINKY_X  memmap.mem[0x4d03]
#define INKY_Y   memmap.mem[0x4d04]
#define INKY_X   memmap.mem[0x4d05]
#define CLYDE_Y  memmap.mem[0x4d06]
#define CLYDE_X  memmap.mem[0x4d07]
#define PACMAN_Y memmap.mem[0x4d08]
#define PACMAN_X memmap.mem[0x4d09]

#define BLINKY_Y_TILE memmap.mem[0x4d0a]
#define BLINKY_X_TILE memmap.mem[0x4d0b]
#define PINKY_Y_TILE  memmap.mem[0x4d0c]
#define PINKY_X_TILE  memmap.mem[0x4d0d]
#define INKY_Y_TILE   memmap.mem[0x4d0e]
#define INKY_X_TILE   memmap.mem[0x4d0f]
#define CLYDE_Y_TILE  memmap.mem[0x4d10]
#define CLYDE_X_TILE  memmap.mem[0x4d11]
#define PACMAN_Y_TILE memmap.mem[0x4d12]
#define PACMAN_X_TILE memmap.mem[0x4d13]

#define BLINKY_Y_TILE_CHANGE memmap.mem[0x4d14]
#define BLINKY_X_TILE_CHANGE memmap.mem[0x4d15]
#define PINKY_Y_TILE_CHANGE  memmap.mem[0x4d16]
#define PINKY_X_TILE_CHANGE  memmap.mem[0x4d17]
#define INKY_Y_TILE_CHANGE   memmap.mem[0x4d18]
#define INKY_X_TILE_CHANGE   memmap.mem[0x4d19]
#define CLYDE_Y_TILE_CHANGE  memmap.mem[0x4d1a]
#define CLYDE_X_TILE_CHANGE  memmap.mem[0x4d1b]
#define PACMAN_Y_TILE_CHANGE memmap.mem[0x4d1c]
#define PACMAN_X_TILE_CHANGE memmap.mem[0x4d1d]

#define BLINKY_Y_TILE_CHANGE2 memmap.mem[0x4d1e]
#define BLINKY_X_TILE_CHANGE2 memmap.mem[0x4d1f]
#define PINKY_Y_TILE_CHANGE2  memmap.mem[0x4d20]
#define PINKY_X_TILE_CHANGE2  memmap.mem[0x4d21]
#define INKY_Y_TILE_CHANGE2   memmap.mem[0x4d22]
#define INKY_X_TILE_CHANGE2   memmap.mem[0x4d23]
#define CLYDE_Y_TILE_CHANGE2  memmap.mem[0x4d24]
#define CLYDE_X_TILE_CHANGE2  memmap.mem[0x4d25]
#define PACMAN_Y_TILE_CHANGE2 memmap.mem[0x4d26]
#define PACMAN_X_TILE_CHANGE2 memmap.mem[0x4d27]

#define BLINKY_PREV_ORIENTATION memmap.mem[0x4d28]
#define PINKY_PREV_ORIENTATION  memmap.mem[0x4d29]
#define INKY_PREV_ORIENTATION   memmap.mem[0x4d2a]
#define CLYDE_PREV_ORIENTATION  memmap.mem[0x4d2b]

#define BLINKY_ORIENTATION memmap.mem[0x4d2c]
#define PINKY_ORIENTATION  memmap.mem[0x4d2d]
#define INKY_ORIENTATION   memmap.mem[0x4d2e]
#define CLYDE_ORIENTATION  memmap.mem[0x4d2f]

#define PACMAN_ORIENTATION  memmap.mem[0x4d30]

#define BLINKY_Y_TILE2 memmap.mem[0x4d31]
#define BLINKY_X_TILE2 memmap.mem[0x4d32]
#define PINKY_Y_TILE2  memmap.mem[0x4d33]
#define PINKY_X_TILE2  memmap.mem[0x4d34]
#define INKY_Y_TILE2   memmap.mem[0x4d35]
#define INKY_X_TILE2   memmap.mem[0x4d36]
#define CLYDE_Y_TILE2  memmap.mem[0x4d37]
#define CLYDE_X_TILE2  memmap.mem[0x4d38]
#define PACMAN_Y_TILE2 memmap.mem[0x4d39]
#define PACMAN_X_TILE2 memmap.mem[0x4d3a]

#define PACMAN_DESIRED_ORIENTATION  memmap.mem[0x4d3c]
#define GHOST_HOUSE_MOVE_COUNT      memmap.mem[0x4d94];

#define BLINKY_SUBSTATE             memmap.mem[0x4da0];
#define PINKY_SUBSTATE              memmap.mem[0x4da1];
#define INKY_SUBSTATE               memmap.mem[0x4da2];
#define CLYDE_SUBSTATE              memmap.mem[0x4da3];

#define KILLED_GHOST_INDEX     memmap.mem[0x4da4]
#define PILL_EFFECT            memmap.mem[0x4da6]

#define BLINKY_ORIENT_CHG_FLAG      memmap.mem[0x4db1];
#define PINKY_ORIENT_CHG_FLAG       memmap.mem[0x4db2];
#define INKY_ORIENT_CHG_FLAG        memmap.mem[0x4db3];
#define CLYDE_ORIENT_CHG_FLAG       memmap.mem[0x4db4];
#define PACMAN_ORIENT_CHG_FLAG      memmap.mem[0x4db5];

#define KILLED_COUNT           memmap.mem[0x4dd0]
#define KILLED_STATE           memmap.mem[0x4dd1]

#define FRUIT_POS ((uint8_t *)&memmap.mem[0x4dd2])

#define MAIN_STATE memmap.mem[0x4e00]
#define MAIN_STATE_SUB0 memmap.mem[0x4e01]
#define MAIN_STATE_SUB1 memmap.mem[0x4e02]
#define MAIN_STATE_SUB2 memmap.mem[0x4e03]

#define PLAYER memmap.mem[0x4e09]
#define CURR_DIFFICULTY (*(uint32_t*)&memmap.mem[0x4e0a])
#define LEVEL memmap.mem[0x4e13]
#define REAL_LIVES memmap.mem[0x4e14]
#define DISPLAY_LIVES memmap.mem[0x4e15]
#define PILL_ARRAY (&memmap.mem[0x4e16])                // 19 x 8 bits
#define BIG_PILL_ARRAY (&memmap.mem[0x4e34])            // 4 entries TODO stupid name
#define SERVICE1_DEBOUNCE memmap.mem[0x4e66]
#define COIN2_DEBOUNCE memmap.mem[0x4e67]
#define COIN1_DEBOUNCE memmap.mem[0x4e68]
#define COIN_COUNTER memmap.mem[0x4e69]
#define COIN_COUNTER_TIMEOUT memmap.mem[0x4e6a]
#define COINS_PER_CREDIT memmap.mem[0x4e6b]
#define PARTIAL_CREDIT memmap.mem[0x4e6c]
#define CREDITS_PER_COIN memmap.mem[0x4e6d]
#define CREDITS memmap.mem[0x4e6e]
#define LIVES_PER_GAME memmap.mem[0x4e6f]
#define TWO_PLAYERS memmap.mem[0x4e70]
#define COCKTAIL_MODE memmap.mem[0x4e72]
#define GHOST_NAMES_MODE memmap.mem[0x4e75]
#define P1_SCORE (*(uint32_t*)&memmap.mem[0x4e80])
#define P2_SCORE (*(uint32_t*)&memmap.mem[0x4e84])
#define HIGH_SCORE (*(uint32_t*)&memmap.mem[0x4e88])

#define SWAP16(int addr1, int addr2)\
{ \
    uint8_t tmp1, tmp2; \
    tmp1 = MEM(addr1); tmp2 = MEM(addr1+1); \
    MEM(addr1) = MEM(addr2); MEM(addr1+1) = MEM(addr2+1); \
    MEM(addr2) = tmp1; MEM(addr2+1) = tmp2; \
}

