/* Memory map table.  Starts at flat map but replace with specific locations as
 * they are discovered */

// Video : https://www.walkofmind.com/programming/pie/video_memory.htm

#include <stdint.h>

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

#define MEM memmap.mem
#define RAM memmap.ram
#define VIDEO memmap.video
#define COLOUR memmap.colour
#define SOUND memmap.regs.write.soundRegs
#define SPRITES memmap.mem.block.sprites
#define INTENABLE memmap.regs.write.outputs[0] // 0x5000
#define COINCOUNTER memmap.regs.write.coinCounter
#define COINLOCKOUT memmap.regs.write.coinLockout
#define REGSWRITE memmap.regs.write
#define SOUNDENABLE memmap.regs.write.soundEnable

#define INPUT_UP        0x01
#define INPUT_LEFT      0x02
#define INPUT_RIGHT     0x04
#define INPUT_DOWN      0x08

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

#define TASK_LIST_END (*(uint16_t*)&memmap.mem[0x4c80])
#define TASK_LIST_BEGIN (*(uint16_t*)&memmap.mem[0x4c82])

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

#define TASK_CLEAR_SCREEN       0x00
#define TASK_FLASH_MAZE         0x01  // ????
#define TASK_DRAW_MAZE         0x02
#define TASK_DRAW_PILLS         0x03
#define TASK_INIT_POSITIONS         0x04
#define TASK_BLINKY_SUBSTATE 0x05
#define TASK_CLEAR_COLOUR         0x06
#define TASK_RESET_GAME_STATE         0x07
#define TASK_CLEAR_PILLS 0x12
#define TASK_UPDATE_PILLS 0x15
#define TASK_DISPLAY_MSG 0x1c
#define TASK_DISPLAY_CREDITS 0x1d
#define TASK_RESET_POSITIONS 0x1e
#define TASK_SHOW_BONUS_LIFE_SCORE 0x1f

/*  X and Y coords are frequently stored together and accessed as a single 16-
 *  bit value (e.g. through the hl reg).  To simplify C code, declare a union of
 *  y and x byte values with a 16 bit hl reg */
typedef union
{
    struct
    {
        uint8_t y; // l
        uint8_t x; // h
    }
    uint16_t hl;
}
XYPOS;

#define BLINKY_POS (XYPOS*)(&memmap.mem[0x4d00])
// #define BLINKY_X memmap.mem[0x4d01]
#define PINKY_POS (XYPOS*)(&memmap.mem[0x4d02])
// #define PINKY_Y  memmap.mem[0x4d02]
#define PINKY_X  memmap.mem[0x4d03]
#define INKY_Y   memmap.mem[0x4d04]
#define INKY_X   memmap.mem[0x4d05]
#define CLYDE_Y  memmap.mem[0x4d06]
#define CLYDE_X  memmap.mem[0x4d07]
#define PACMAN_POS (XYPOS*)(&memmap.mem[0x4d08])
// #define PACMAN_Y memmap.mem[0x4d08]
// #define PACMAN_X memmap.mem[0x4d09]

#define BLINKY_Y_TILE memmap.mem[0x4d0a]
#define BLINKY_X_TILE memmap.mem[0x4d0b]
#define PINKY_Y_TILE  memmap.mem[0x4d0c]
#define PINKY_X_TILE  memmap.mem[0x4d0d]
#define INKY_Y_TILE   memmap.mem[0x4d0e]
#define INKY_X_TILE   memmap.mem[0x4d0f]
#define CLYDE_Y_TILE  memmap.mem[0x4d10]
#define CLYDE_X_TILE  memmap.mem[0x4d11]
#define PACMAN_DEMO_TILE memmap.mem[0x4d12]
// #define PACMAN_X_TILE memmap.mem[0x4d13]

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
#define PACMAN_TILE2 (XYPOS*)(&memmap.mem[0x4d39])

#define BEST_ORIENTATION_FOUND memmap.mem[0x4d3b]
#define PACMAN_DESIRED_ORIENTATION      memmap.mem[0x4d3c]
#define OPPOSITE_ORIENTATION memmap.mem[0x4d3d]
#define CURRENT_TILE_POS (XYPOS*)(&memmap.mem[0x4d3e])
#define DEST_TILE_POS (XYPOS*)(&memmap.mem[0x4d40])
#define PACMAN_MOVE_PAT_NORMAL1        memmap.mem[0x4d46]
#define PACMAN_MOVE_PAT_NORMAL2        memmap.mem[0x4d48]
#define PACMAN_MOVE_PAT_BIG_PILL1        memmap.mem[0x4d4a]
#define PACMAN_MOVE_PAT_BIG_PILL2        memmap.mem[0x4d4c]
#define PACMAN_MOVE_PAT_DIFF2_1         memmap.mem[0x4d4e]
#define PACMAN_MOVE_PAT_DIFF2_2         memmap.mem[0x4d50]
#define PACMAN_MOVE_PAT_DIFF1_1         memmap.mem[0x4d52]
#define PACMAN_MOVE_PAT_DIFF1_2         memmap.mem[0x4d54]
#define BLINKY_MOVE_PAT_NORMAL1         memmap.mem[0x4d56]
#define BLINKY_MOVE_PAT_NORMAL2         memmap.mem[0x4d58]
#define BLINKY_MOVE_PAT_EDIBLE1         memmap.mem[0x4d5a]
#define BLINKY_MOVE_PAT_EDIBLE2         memmap.mem[0x4d5c]
#define BLINKY_MOVE_PAT_TUNNEL1         memmap.mem[0x4d5e]
#define BLINKY_MOVE_PAT_TUNNEL2         memmap.mem[0x4d60]
#define PINKY_MOVE_PAT_NORMAL1         memmap.mem[0x4d62]
#define PINKY_MOVE_PAT_NORMAL2         memmap.mem[0x4d64]
#define PINKY_MOVE_PAT_EDIBLE1         memmap.mem[0x4d66]
#define PINKY_MOVE_PAT_EDIBLE2         memmap.mem[0x4d68]
#define PINKY_MOVE_PAT_TUNNEL1         memmap.mem[0x4d6a]
#define PINKY_MOVE_PAT_TUNNEL2         memmap.mem[0x4d6c]
#define INKY_MOVE_PAT_NORMAL1         memmap.mem[0x4d6e]
#define INKY_MOVE_PAT_NORMAL2         memmap.mem[0x4d70]
#define INKY_MOVE_PAT_EDIBLE1         memmap.mem[0x4d72]
#define INKY_MOVE_PAT_EDIBLE2         memmap.mem[0x4d74]
#define INKY_MOVE_PAT_TUNNEL1         memmap.mem[0x4d76]
#define INKY_MOVE_PAT_TUNNEL2         memmap.mem[0x4d78]
#define CLYDE_MOVE_PAT_NORMAL1         memmap.mem[0x4d7a]
#define CLYDE_MOVE_PAT_NORMAL2         memmap.mem[0x4d7c]
#define CLYDE_MOVE_PAT_EDIBLE1         memmap.mem[0x4d7e]
#define CLYDE_MOVE_PAT_EDIBLE2         memmap.mem[0x4d80]
#define CLYDE_MOVE_PAT_TUNNEL1         memmap.mem[0x4d82]
#define CLYDE_MOVE_PAT_TUNNEL2         memmap.mem[0x4d84]
#define DIFFICULTY_TABLE                (*(uint16_t*)&memmap.mem[0x4d86])

#define GHOST_HOUSE_MOVE_COUNT          memmap.mem[0x4d94];
#define UNITS_B4_GHOST_LEAVES_HOME      (*(uint16_t*)&memmap.mem[0x4d95])
#define UNITS_INACTIVITY_COUNTER        (*(uint16_t*)&memmap.mem[0x4d97])
#define BLINKY_AUX_POS                  memmap.mem[0x4d99];
#define PINKY_AUX_POS                  memmap.mem[0x4d9a];
#define INKY_AUX_POS                  memmap.mem[0x4d9b];
#define CLYDE_AUX_POS                  memmap.mem[0x4d9c];
#define PACMAN_MOVE_DELAY               memmap.mem[0x4d9d];
#define EATEN_SINCE_MOVE                memmap.mem[0x4d9e];
#define EATEN_PILLS_COUNT               memmap.mem[0x4d9f];

#define BLINKY_SUBSTATE                 memmap.mem[0x4da0];
#define PINKY_SUBSTATE                  memmap.mem[0x4da1];
#define INKY_SUBSTATE                   memmap.mem[0x4da2];
#define CLYDE_SUBSTATE                  memmap.mem[0x4da3];

#define KILLED_GHOST_INDEX              memmap.mem[0x4da4]
#define PAC_DEAD_ANIM_STATE             memmap.mem[0x4da5]
#define PILL_EFFECT                     memmap.mem[0x4da6]
#define BLINKY_EDIBLE                   memmap.mem[0x4da7];
#define PINKY_EDIBLE                    memmap.mem[0x4da8];
#define INKY_EDIBLE                     memmap.mem[0x4da9];
#define CLYDE_EDIBLE                    memmap.mem[0x4daa];
#define GHOST_STATE                     memmap.mem[0x4dab];
#define BLINKY_STATE                    memmap.mem[0x4dac]
#define PINKY_STATE                     memmap.mem[0x4dad]
#define INKY_STATE                      memmap.mem[0x4dae]
#define CLYDE_STATE                     memmap.mem[0x4daf]

#define GHOST_ALIVE     0
#define GHOST_DEAD      1

#define REL_DIFF                        memmap.mem[0x4db0];
#define BLINKY_ORIENT_CHG_FLAG          memmap.mem[0x4db1];
#define PINKY_ORIENT_CHG_FLAG           memmap.mem[0x4db2];
#define INKY_ORIENT_CHG_FLAG            memmap.mem[0x4db3];
#define CLYDE_ORIENT_CHG_FLAG           memmap.mem[0x4db4];
#define PACMAN_ORIENT_CHG_FLAG          memmap.mem[0x4db5];
#define DIFF_FLAG_1                     memmap.mem[0x4db6];
#define DIFF_FLAG_2                     memmap.mem[0x4db7];
#define PINKY_LEAVE_HOME_COUNTER        memmap.mem[0x4db8];
#define INKY_LEAVE_HOME_COUNTER         memmap.mem[0x4db9];
#define CLYDE_LEAVE_HOME_COUNTER        memmap.mem[0x4dba];
#define PILLS_REM_DIFF_1                memmap.mem[0x4dbb];
#define PILLS_REM_DIFF_2                memmap.mem[0x4dbc];
#define GHOST_EDIBLE_TIME               (*(uint16_t*)&memmap.mem[0x4dbd])
#define PACMAN_ENTERING_TUNNEL          memmap.mem[0x4dbf];

#define GHOST_ANIMATION                 memmap.mem[0x4dc0]
#define NONRANDOM_MOVEMENT              memmap.mem[0x4dc1]
#define ORIENTATION_CHANGE_COUNT        (*(uint16_t*)&memmap.mem[0x4dc2])
#define COUNTER_TO_8                    memmap.mem[0x4dc4]
#define COUNT_SINCE_PAC_KILLED          (*(uint16_t*)&memmap.mem[0x4dc5])
#define GHOST_COL_POWERUP_COUNTER       memmap.mem[0x4dc8]
#define EDIBLE_REMAIN_COUNT             (*(uint16_t*)&memmap.mem[0x4dcb])

#define PILL_CHANGE_COUNTER             memmap.mem[0x4dcf]
#define KILLED_COUNT                    memmap.mem[0x4dd0]
#define KILLED_STATE                    memmap.mem[0x4dd1]
#define FRUIT_POS                       (XYPOS *)(&memmap.mem[0x4dd2])

#define FRUIT_POINTS                    memmap.mem[0x4dd4]

#define MAIN_STATE                      memmap.mem[0x4e00]
#define MAIN_STATE_SUB0                 memmap.mem[0x4e01]
#define MAIN_STATE_SUB1                 memmap.mem[0x4e02]
#define MAIN_STATE_SUB2                 memmap.mem[0x4e03]
#define LEVEL_STATE_SUBR                memmap.mem[0x4e04]
#define SCENE1_STATE                    memmap.mem[0x4e06]
#define SCENE2_STATE                    memmap.mem[0x4e07]
#define SCENE3_STATE                    memmap.mem[0x4e08]

#define PLAYER memmap.mem[0x4e09]

#define P1_CURR_DIFFICULTY               (*(uint16_t*)&memmap.mem[0x4e0a])
#define P1_FIRST_FRUIT                  memmap.mem[0x4e0c]
#define P1_SECOND_FRUIT                 memmap.mem[0x4e0d]
#define P1_PILLS_EATEN_LEVEL            memmap.mem[0x4e0e]
#define P1_PINKY_LEAVE_HOME_COUNTER     memmap.mem[0x4e0f]
#define P1_INKY_LEAVE_HOME_COUNTER      memmap.mem[0x4e10]
#define P1_CLYDE_LEAVE_HOME_COUNTER     memmap.mem[0x4e11]
#define P1_DIED_IN_LEVEL                memmap.mem[0x4e12]
#define P1_LEVEL                        memmap.mem[0x4e13]
#define P1_REAL_LIVES                   memmap.mem[0x4e14]
#define P1_DISPLAY_LIVES                memmap.mem[0x4e15]
#define P1_PILL_ARRAY                   (&memmap.mem[0x4e16])      // 19 x 8 bits
#define P1_POWERUP_ARRAY                (&memmap.mem[0x4e34])      // 4 entries 

// 4e38-4e65 is P2 copy of 4e0a-4e37 (45 bytes)

#define P2_CURR_DIFFICULTY              (*(uint16_t*)&memmap.mem[0x4e38])
#define P2_FIRST_FRUIT                  memmap.mem[0x4e3a]
#define P2_SECOND_FRUIT                 memmap.mem[0x4e3b]
#define P2_PILLS_EATEN_LEVEL            memmap.mem[0x4e3c]
#define P2_PINKY_LEAVE_HOME_COUNTER     memmap.mem[0x4e3d]
#define P2_INKY_LEAVE_HOME_COUNTER      memmap.mem[0x4e3e]
#define P2_CLYDE_LEAVE_HOME_COUNTER     memmap.mem[0x4e3f]
#define P2_DIED_IN_LEVEL                memmap.mem[0x4e40]
#define P2_LEVEL                        memmap.mem[0x4e41]
#define P2_REAL_LIVES                   memmap.mem[0x4e42]
#define P2_DISPLAY_LIVES                memmap.mem[0x4e43]
#define P2_PILL_ARRAY                   (&memmap.mem[0x4e44])     // 19 x 8 bits
#define P2_POWERUP_ARRAY                (&memmap.mem[0x4e42])     // 4 entries 

#define SERVICE1_DEBOUNCE               memmap.mem[0x4e66]
#define COIN2_DEBOUNCE                  memmap.mem[0x4e67]
#define COIN1_DEBOUNCE                  memmap.mem[0x4e68]
#define COIN_COUNTER                    memmap.mem[0x4e69]
#define COIN_COUNTER_TIMEOUT            memmap.mem[0x4e6a]
#define COINS_PER_CREDIT                memmap.mem[0x4e6b]
#define PARTIAL_CREDIT                  memmap.mem[0x4e6c]
#define CREDITS_PER_COIN                memmap.mem[0x4e6d]
#define CREDITS                         memmap.mem[0x4e6e]
#define LIVES_PER_GAME                  memmap.mem[0x4e6f]
#define TWO_PLAYERS                     memmap.mem[0x4e70]
#define BONUS_LIFE                      memmap.mem[0x4e71]
#define COCKTAIL_MODE                   memmap.mem[0x4e72]
#define DIFFICULTY_PTR                  (*(uint16_t*)&memmap.mem[0x4e73])
#define GHOST_NAMES_MODE                memmap.mem[0x4e75]
#define P1_SCORE                        (*(uint32_t*)&memmap.mem[0x4e80])
#define P2_SCORE                        (*(uint32_t*)&memmap.mem[0x4e84])
#define HIGH_SCORE                      (*(uint32_t*)&memmap.mem[0x4e88])

#define SND_CH1_EFF_NUM                 memmap.mem[0x4e9c];
#define SND_CH2_EFF_NUM                 memmap.mem[0x4eac];
#define SND_CH3_EFF_NUM                 memmap.mem[0x4ebc];
#define SND_CH1_WAV_NUM                 memmap.mem[0x4ecc];
#define SND_CH2_WAV_NUM                 memmap.mem[0x4edc];
#define SND_CH3_WAV_NUM                 memmap.mem[0x4eec];

#define SWAP16(addr1,addr2)\
{ \
    uint8_t tmp1, tmp2; \
    tmp1 = MEM(addr1); tmp2 = MEM(addr1+1); \
    MEM(addr1) = MEM(addr2); MEM(addr1+1) = MEM(addr2+1); \
    MEM(addr2) = tmp1; MEM(addr2+1) = tmp2; \
}

