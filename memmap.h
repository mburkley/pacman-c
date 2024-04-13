/* Memory map table.  Starts at flat map but replace with specific locations as
 * they are discovered */

// Video : https://www.walkofmind.com/programming/pie/video_memory.htm

#include <stdint.h>
#include <stdbool.h>

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

#define ROM memmap.rom
#define MEM memmap.mem
#define RAM memmap.ram
#define VIDEO memmap.video
#define COLOUR memmap.colour
#define SOUND memmap.regs.write.soundRegs
#define SPRITES memmap.sprites
#define INTENABLE memmap.regs.write.intEnable
#define SOUNDENABLE memmap.regs.write.soundEnable
#define AUXENABLE memmap.regs.write.auxEnable
#define FLIPSCREEN memmap.regs.write.flipScreen
#define P1START memmap.regs.write.player1Start
#define P2START memmap.regs.write.player2Start
#define COINLOCKOUT memmap.regs.write.coinLockout
#define COINCOUNTER memmap.regs.write.coinCounter
#define REGSWRITE memmap.regs.write

#define INPUT_UP        0x01
#define INPUT_LEFT      0x02
#define INPUT_RIGHT     0x04
#define INPUT_DOWN      0x08

#define IO_INPUT0       memmap.regs.read.in0[0]
#define IO_INPUT1       memmap.regs.read.in1[0]

#define IN0_UP          (IO_INPUT0 & INPUT_UP)
#define IN0_LEFT        (IO_INPUT0 & INPUT_LEFT)
#define IN0_RIGHT       (IO_INPUT0 & INPUT_RIGHT)
#define IN0_DOWN        (IO_INPUT0 & INPUT_DOWN)
#define IN0_TEST        (IO_INPUT0 & 0x10)
#define IN0_COIN1       (IO_INPUT0 & 0x20)
#define IN0_COIN2       (IO_INPUT0 & 0x40)
#define IN0_COIN3       (IO_INPUT0 & 0x80)

#define IN1_UP          (IO_INPUT1 & INPUT_UP)
#define IN1_LEFT        (IO_INPUT1 & INPUT_LEFT)
#define IN1_RIGHT       (IO_INPUT1 & INPUT_RIGHT)
#define IN1_DOWN        (IO_INPUT1 & INPUT_DOWN)
#define IN1_SERVICE     (IO_INPUT1 & 0x10)
#define IN1_START1      (IO_INPUT1 & 0x20)
#define IN1_START2      (IO_INPUT1 & 0x40)
#define IN1_CABINET     (IO_INPUT1 & 0x80)

#define DIP_SWITCH_FREE (memmap.regs.read.in0[0] & 0x03)
#define DIP_SWITCH_TEST (memmap.regs.read.in0[0] & 0x10)
#define DIP_SWITCH_BONUS (memmap.regs.read.in0[0] & 0x30)

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

#define ISRTASK_INC_LEVEL_STATE        0
#define ISRTASK_INC_MAIN_SUB2        1
#define ISRTASK_INC_MAIN_SUB1        2
#define ISRTASK_INC_KILLED_STATE        3
#define ISRTASK_RESET_FRUIT     4
#define ISRTASK_DISPLAY_READY         6
#define ISRTASK_INC_SCENE1_STATE         7
#define ISRTASK_INC_SCENE2_STATE         8
#define ISRTASK_INC_SCENE3_STATE         9

/*  non-ISR tasks are 2 bytes each and there are 16 entries */
#define NONISR_TASKS (&memmap.mem[0x4cc0])

#define TASK_CLEAR_SCREEN       0x00
#define TASK_FLASH_MAZE         0x01  // ???? TODO
#define TASK_DRAW_MAZE         0x02
#define TASK_DRAW_PILLS         0x03
#define TASK_INIT_POSITIONS         0x04
#define TASK_BLINKY_SUBSTATE 0x05
#define TASK_CLEAR_COLOUR         0x06
#define TASK_RESET_GAME_STATE         0x07
#define TASK_TILE_CHANGE_PINKY 0x09
#define TASK_CLEAR_PILLS 0x12
#define TASK_UPDATE_PILLS 0x15
#define TASK_DISPLAY_MSG 0x1c
#define TASK_DISPLAY_CREDITS 0x1d
#define TASK_RESET_POSITIONS 0x1e
#define TASK_SHOW_BONUS_LIFE_SCORE 0x1f

#define MSG_HIGHSCORE   0
#define MSG_CREDIT      1
#define MSG_FREEPLAY    2
#define MSG_PLAYER1     3
#define MSG_PLAYER2     4
#define MSG_GAMEOVER    5
#define MSG_READY       6
#define MSG_BADROMRAM    0x24
#define MSG_PACMAN       0x29
#define MSG_BONUS_NONE   0x2a
#define MSG_BONUS        0x2b
#define MSG_TABLE        0x2c
#define MSG_000          0x2e

/*  X and Y coords are frequently stored together and accessed as a single 16-
 *  bit value (e.g. through the hl reg).  To simplify C code, declare a union of
 *  y and x byte values with a 16 bit hl reg */
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

#define BLINKY_POS      (*(XYPOS*)(&memmap.mem[0x4d00]))
// #define BLINKY_Y memmap.mem[0x4d00]
// #define BLINKY_X memmap.mem[0x4d01]
#define PINKY_POS       (*(XYPOS*)(&memmap.mem[0x4d02]))
// #define PINKY_Y  memmap.mem[0x4d02]
// #define PINKY_X  memmap.mem[0x4d03]
#define INKY_POS        (*(XYPOS*)(&memmap.mem[0x4d04]))
#define CLYDE_POS       (*(XYPOS*)(&memmap.mem[0x4d06]))
#define PACMAN_POS      (*(XYPOS*)(&memmap.mem[0x4d08]))
// #define PACMAN_Y memmap.mem[0x4d08]
// #define PACMAN_X memmap.mem[0x4d09]

#define BLINKY_TILE     (*(XYPOS*)(&memmap.mem[0x4d0a]))
#define PINKY_TILE      (*(XYPOS*)(&memmap.mem[0x4d0c]))
#define INKY_TILE       (*(XYPOS*)(&memmap.mem[0x4d0e]))
#define CLYDE_TILE      (*(XYPOS*)(&memmap.mem[0x4d10]))
#define PACMAN_TILE        (*(XYPOS*)(&memmap.mem[0x4d12]))
// #define PACMAN_X_TILE memmap.mem[0x4d13]

#define BLINKY_TILE_CHANGE (*(XYPOS*)(&memmap.mem[0x4d14]))
#define PINKY_TILE_CHANGE  (*(XYPOS*)(&memmap.mem[0x4d16]))
#define INKY_TILE_CHANGE   (*(XYPOS*)(&memmap.mem[0x4d18]))
#define CLYDE_TILE_CHANGE  (*(XYPOS*)(&memmap.mem[0x4d1a]))
#define PACMAN_TILE_CHANGE (*(XYPOS*)(&memmap.mem[0x4d1c]))

#define BLINKY_TILE_CHANGE2 (*(XYPOS*)(&memmap.mem[0x4d1e]))
#define PINKY_TILE_CHANGE2  (*(XYPOS*)(&memmap.mem[0x4d20]))
#define INKY_TILE_CHANGE2   (*(XYPOS*)(&memmap.mem[0x4d22]))
#define CLYDE_TILE_CHANGE2  (*(XYPOS*)(&memmap.mem[0x4d24]))
#define PACMAN_TILE_CHANGE2 (*(XYPOS*)(&memmap.mem[0x4d26]))

#define BLINKY_PREV_ORIENTATION memmap.mem[0x4d28]
#define PINKY_PREV_ORIENTATION  memmap.mem[0x4d29]
#define INKY_PREV_ORIENTATION   memmap.mem[0x4d2a]
#define CLYDE_PREV_ORIENTATION  memmap.mem[0x4d2b]

#define BLINKY_ORIENTATION memmap.mem[0x4d2c]
#define PINKY_ORIENTATION  memmap.mem[0x4d2d]
#define INKY_ORIENTATION   memmap.mem[0x4d2e]
#define CLYDE_ORIENTATION  memmap.mem[0x4d2f]

#define PACMAN_ORIENTATION  memmap.mem[0x4d30]

#define BLINKY_TILE2 (*(XYPOS*)(&memmap.mem[0x4d31]))
#define PINKY_TILE2  (*(XYPOS*)(&memmap.mem[0x4d33]))
#define INKY_TILE2   (*(XYPOS*)(&memmap.mem[0x4d35]))
#define CLYDE_TILE2  (*(XYPOS*)(&memmap.mem[0x4d37]))
#define PACMAN_TILE2 (*(XYPOS*)(&memmap.mem[0x4d39]))

#define BEST_ORIENTATION_FOUND memmap.mem[0x4d3b]
#define PACMAN_DESIRED_ORIENTATION      memmap.mem[0x4d3c]
#define OPPOSITE_ORIENTATION memmap.mem[0x4d3d]
#define CURRENT_TILE_POS (*(XYPOS*)(&memmap.mem[0x4d3e]))
#define DEST_TILE_POS (*(XYPOS*)(&memmap.mem[0x4d40]))
#define TMP_RESULT_POS (*(XYPOS*)(&memmap.mem[0x4d42]))
#define MIN_DISTANCE_FOUND              (*(uint16_t*)&memmap.mem[0x4d44])
#define PACMAN_MOVE_PAT_NORMAL1         memmap.mem[0x4d46]
#define PACMAN_MOVE_PAT_NORMAL2         memmap.mem[0x4d48]
#define PACMAN_MOVE_PAT_POWERUP1        memmap.mem[0x4d4a]
#define PACMAN_MOVE_PAT_POWERUP2        memmap.mem[0x4d4c]
#define PACMAN_MOVE_PAT_DIFF2_1         (*(uint16_t*)&memmap.mem[0x4d4e])
#define PACMAN_MOVE_PAT_DIFF2_2         (*(uint16_t*)&memmap.mem[0x4d50])
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
#define DIFFICULTY_TABLE                ((uint16_t*)&memmap.mem[0x4d86])

#define GHOST_HOUSE_MOVE_COUNT          memmap.mem[0x4d94]
#define UNITS_B4_GHOST_LEAVES_HOME      (*(uint16_t*)&memmap.mem[0x4d95])
#define UNITS_INACTIVITY_COUNTER        (*(uint16_t*)&memmap.mem[0x4d97])
#define BLINKY_AUX_POS                  memmap.mem[0x4d99]
#define PINKY_AUX_POS                  memmap.mem[0x4d9a]
#define INKY_AUX_POS                  memmap.mem[0x4d9b]
#define CLYDE_AUX_POS                  memmap.mem[0x4d9c]
#define PACMAN_MOVE_DELAY               memmap.mem[0x4d9d]
#define EATEN_SINCE_MOVE                memmap.mem[0x4d9e]
#define EATEN_PILLS_COUNT               memmap.mem[0x4d9f]

#define BLINKY_SUBSTATE                 memmap.mem[0x4da0]
#define PINKY_SUBSTATE                  memmap.mem[0x4da1]
#define INKY_SUBSTATE                   memmap.mem[0x4da2]
#define CLYDE_SUBSTATE                  memmap.mem[0x4da3]

#define KILLED_GHOST_INDEX              memmap.mem[0x4da4]
#define PAC_DEAD_ANIM_STATE             memmap.mem[0x4da5]
#define PILL_EFFECT                     memmap.mem[0x4da6]
#define BLINKY_EDIBLE                   memmap.mem[0x4da7]
#define PINKY_EDIBLE                    memmap.mem[0x4da8]
#define INKY_EDIBLE                     memmap.mem[0x4da9]
#define CLYDE_EDIBLE                    memmap.mem[0x4daa]
#define GHOST_STATE                     memmap.mem[0x4dab]
#define BLINKY_STATE                    memmap.mem[0x4dac]
#define PINKY_STATE                     memmap.mem[0x4dad]
#define INKY_STATE                      memmap.mem[0x4dae]
#define CLYDE_STATE                     memmap.mem[0x4daf]

#define GHOST_ALIVE     0
#define GHOST_DEAD      1

#define REL_DIFF                        memmap.mem[0x4db0]
#define BLINKY_ORIENT_CHG_FLAG          memmap.mem[0x4db1]
#define PINKY_ORIENT_CHG_FLAG           memmap.mem[0x4db2]
#define INKY_ORIENT_CHG_FLAG            memmap.mem[0x4db3]
#define CLYDE_ORIENT_CHG_FLAG           memmap.mem[0x4db4]
#define PACMAN_ORIENT_CHG_FLAG          memmap.mem[0x4db5]
#define DIFF_FLAG_1                     memmap.mem[0x4db6]
#define DIFF_FLAG_2                     memmap.mem[0x4db7]
#define PINKY_LEAVE_HOME_COUNTER        memmap.mem[0x4db8]
#define INKY_LEAVE_HOME_COUNTER         memmap.mem[0x4db9]
#define CLYDE_LEAVE_HOME_COUNTER        memmap.mem[0x4dba]
#define PILLS_REM_DIFF_1                memmap.mem[0x4dbb]
#define PILLS_REM_DIFF_2                memmap.mem[0x4dbc]
#define GHOST_EDIBLE_TIME               (*(uint16_t*)&memmap.mem[0x4dbd])
#define PACMAN_ENTERING_TUNNEL          memmap.mem[0x4dbf]

#define GHOST_ANIMATION                 memmap.mem[0x4dc0]
#define NONRANDOM_MOVEMENT              memmap.mem[0x4dc1]
#define ORIENTATION_CHANGE_COUNT        (*(uint16_t*)&memmap.mem[0x4dc2])
#define COUNTER_TO_8                    memmap.mem[0x4dc4]
#define COUNT_SINCE_PAC_KILLED          (*(uint16_t*)&memmap.mem[0x4dc5])
#define TRIAL_ORIENTATION               memmap.mem[0x4dc7]
#define GHOST_COL_POWERUP_COUNTER       memmap.mem[0x4dc8]
#define RND_VAL_PTR                     (*(uint16_t*)&memmap.mem[0x4dc9])
#define EDIBLE_REMAIN_COUNT             (*(uint16_t*)&memmap.mem[0x4dcb])
#define COIN_TIMER                      memmap.mem[0x4dce]

#define PILL_CHANGE_COUNTER             memmap.mem[0x4dcf]
#define KILLED_COUNT                    memmap.mem[0x4dd0]
#define KILLED_STATE                    memmap.mem[0x4dd1]
#define FRUIT_POS                       (*(XYPOS *)(&memmap.mem[0x4dd2]))

#define FRUIT_POINTS                    memmap.mem[0x4dd4]
#define WAIT_START_BUTTON               memmap.mem[0x4dd6]

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
#define P1_SCORE                        (&memmap.mem[0x4e80])
#define P2_SCORE                        (&memmap.mem[0x4e84])
#define HIGH_SCORE                      (&memmap.mem[0x4e88])

#define CH1_FREQ0       memmap.mem[0x4e8c]   // 20 bits
#define CH1_FREQ1       memmap.mem[0x4e8d]
#define CH1_FREQ2       memmap.mem[0x4e8e]
#define CH1_FREQ3       memmap.mem[0x4e8f]
#define CH1_FREQ4       memmap.mem[0x4e90]
#define CH1_VOL         memmap.mem[0x4e91]
#define CH2_FREQ1       memmap.mem[0x4e92]   // 16 bits
#define CH2_FREQ2       memmap.mem[0x4e93]
#define CH2_FREQ3       memmap.mem[0x4e94]
#define CH2_FREQ4       memmap.mem[0x4e95]
#define CH2_VOL         memmap.mem[0x4e96]
#define CH3_FREQ1       memmap.mem[0x4e97]   // 16 bits
#define CH3_FREQ2       memmap.mem[0x4e98]
#define CH3_FREQ3       memmap.mem[0x4e99]
#define CH3_FREQ4       memmap.mem[0x4e9a]
#define CH3_VOL         memmap.mem[0x4e9b]

#define SND_CH1_EFF_NUM                 memmap.mem[0x4e9c]
#define SND_CH2_EFF_NUM                 memmap.mem[0x4eac]
#define SND_CH3_EFF_NUM                 memmap.mem[0x4ebc]
#define SND_CH1_WAV_NUM                 memmap.mem[0x4ecc]
#define SND_CH2_WAV_NUM                 memmap.mem[0x4edc]
#define SND_CH3_WAV_NUM                 memmap.mem[0x4eec]

#define ORIENT_RIGHT    0
#define ORIENT_DOWN     1
#define ORIENT_LEFT     2
#define ORIENT_UP       3

#define SWAP16(addr1,addr2)\
{ \
    uint8_t tmp1, tmp2; \
    tmp1 = MEM(addr1); tmp2 = MEM(addr1+1); \
    MEM(addr1) = MEM(addr2); MEM(addr1+1) = MEM(addr2+1); \
    MEM(addr2) = tmp1; MEM(addr2+1) = tmp2; \
}

/*  Function to emulate the Z80 daa instruction.  Convert a value to BCD by
 *  examining each nybble.  If low nybble is higher than 9 then add 6 to carry
 *  to the higher nybble.  If the higher nyblle is higher than 9 then substract
 *  0xa0 and return true to indicate carry to next byte */
static inline int bcdAdjust (uint8_t *value)
{
    if ((*value & 0xf) > 9)
        *value += 6;

    if ((*value & 0xf0) > 0x90)
    {
        *value -= 0xa0;
        return 1;
    }

    return 0;
}


void func_01dc();
void dispatchISRTasks_0221();
void checkCoinInput_0267 ();
void func_02ad();
void func_039d (void);
void func_03dc (void);
void func_03fe();
void func_045f();
void func_0471();
void func_047f(void );
void func_048b();
void func_0499();
void func_049f();
void func_04a5();
void func_04b3();
void func_04b9();
void func_04bf();
void func_04cd();
void func_04d3();
void func_04d8();
void func_04e0();
void func_051c();
void func_0524 (uint8_t *hl, int b, int a);
void func_052c();
void func_054b();
void func_0556();
void func_0561();
void func_056c();
void func_057c();
void func_0580(int c);
void func_0585(int c);
void func_0593(int c);
XYPOS func_05a5 (void);
void func_05bf (int hl, int a);
void func_05e5 (void);
void func_0485(void );
void func_05f3(void );
void func_0674(void );
void func_0899(void );
void func_0a2c (void);
void func_06a8();
void func_06be();
void func_070e(int b);
void setupMovePat_0814(uint8_t *hl);
void func_08cd();
void func_0940();
void func_0972();
void func_0988 ();
void func_09d2();
void func_09d8();
void func_09e8();
void func_09fe();
void func_0a02();
void func_0a04();
void func_0a06();
void func_0a08();
void func_0a0a();
void func_0a0c();
void func_0a0e();
void func_0a7c();
void func_0aa0();
void func_0aa3();
void func_0aa6();
void func_0ac3();
void func_0c0d();
void func_0c42();
void toggleGhostAnimation_0e23();
void func_0e36 ();
void func_0ead();
void resetFruit_1000();
void func_100b();
void func_1017 ();
void func_1066();
void func_1094();
void func_109e();
void func_10a8();
void func_10b4();
void func_10c0();
void func_10d2();
void func_1101();
void func_1118();
void func_112a();
void func_116e();
void func_118f();
void func_11c9();
void func_11db();
void func_11fc();
void func_1235();
void func_12cb();
void func_12f9();
void func_1306();
void func_130e();
void func_1316();
void func_131e();
void func_1326();
void func_132e();
void func_1336();
void func_133e();
void func_1346();
void decrementLives_1353();
void func_1376();
void func_141f (void);
void func_1490();
void func_14fe();
void func_1562();
void func_15e6();
void func_162d();
void func_16d6();
void func_16f7();
void checkPacmanGhostCoincidence_171d();
void func_1763 (int b);
void func_1789 ();
void updatePacmanVector_1806 (void);
void func_18e4 (int b);
void func_1985(XYPOS pos);
void func_1a19 ();
void func_1a6a ();
void func_1a70 ();
void updateBlinkyMovePat_1b36();
void func_1c4b ();
void func_1d22();
void func_1df9();
bool func_1ed0(int ghost);
void reverseBlinky_1efe (void);
void func_1f25();
void func_1f4c();
void func_1f73();
uint16_t getScreenOffset_202d (XYPOS hl);
void func_205a(XYPOS pos, uint8_t *aux);
void func_208c();
void func_20af();
void func_2108();
void func_211a();
void func_2130();
void func_2136();
void func_2140();
void func_214b();
void func_2170();
void func_217b();
void func_2186();
void func_219e();
void func_21c2(uint16_t iy);
void func_21e1(uint16_t iy);
void func_21f5(uint16_t iy);
void func_220c(uint16_t iy);
void func_2237();
void func_2244(uint16_t iy);
void func_225d(uint16_t iy);
void func_226a(uint16_t iy);
void func_2286(uint16_t iy);
void func_228d(uint16_t iy);
void func_2297();
void func_22be();
void func_22dd();
void func_22e4();
void func_22f5();
void func_22fe();
void start_230b ();
void clearScreen_23f3 (void);
void clearMaze_2400 (void);
void clearColour_240d (int param);
void drawMazeTBD_2419 (int param);
void drawPills_2448(int param);
void clearPills_24c9();
void blinkySubstateTBD_268b(int param);
void func_26a2();
void tileChangePinky_276c (int param);
void tileChangeInky_27a9 (int param);
void tileChangeClyde_27f1 (int param);
void func_28e3();
void func_2a35();
void addToScore_2a5a(int b);
void func_2ae0();
uint8_t* getPlayerScorePtr_2b0b (void);
void drawBlankSquare_2b7e(uint8_t *hl);
void drawCharSquare_2b80 (uint8_t *hl, int a);
void drawFruit_2b8f (uint8_t *hl, int a);
void func_2b6a();
void func_2c44(uint8_t a);
void func_2cc1 (void);
void displayMsg_2c5e (int b);
uint8_t func_2d44(uint8_t *ix, uint8_t *iy, uint8_t data[]);
void func_2da5(int a);
uint8_t func_2df4(uint8_t *ix, uint8_t *iy);
uint8_t func_2e1b (uint8_t *ix, uint8_t *iy, uint8_t *hl, uint8_t c);
uint8_t func_2f22 (uint8_t *ix);
uint8_t func_2f26 (uint8_t *ix);
uint8_t func_2f2b (uint8_t *ix);
uint8_t func_2f30 (uint8_t *ix, uint8_t a);
uint8_t func_2f34 (uint8_t *ix, uint8_t a);
uint8_t func_2f3c (uint8_t *ix);
uint8_t func_2f43 (uint8_t *ix);
uint8_t func_2f55 (uint8_t *ix, uint8_t *iy);
uint8_t func_2f65 (uint8_t *ix, uint8_t *iy);
uint8_t func_2f77 (uint8_t *ix, uint8_t *iy);
uint8_t func_2f89 (uint8_t *ix, uint8_t *iy);
uint8_t func_2f9b (uint8_t *ix, uint8_t *iy);
uint8_t func_2fad (uint8_t *ix, uint8_t *iy);

    void kickWatchdog();
void advanceGameState  ();
int main (void);
void addISRTask(uint8_t *ptr, int count, uint8_t* data);
void addTask (uint8_t task, uint8_t param);
void advanceGameState  ();
void advanceStartState();
void checkStartButtons ();
void displayCredits ();
void drawPlayerScore_2aaf (uint8_t *score);
void drawScore_2abe (uint8_t *screenLoc, uint8_t *score, int blanks);
void extraLife_2b33(int de);
void fillScreenArea_2bcd (int addr, int ch, int cols, int rows);
void incLevelStateSubr_0894();
void incMainSub2_06a3();
void initLeaveHomeCounters_083a(uint8_t *hl);
void isr();
void jumpClearScreen_23ed(int param);
void nothing (void);
void oneBlank (uint8_t *ix);
void oneUp (uint8_t *ix);
void pacmanDeadAnimation_12d6(int ch, int count);
void playerDied_090d();
void playerUp ();
uint8_t random_2a23 (void);
void resetGameState_2698();
void resetGhostPosition_267e (int y, int x);
void resetPlayerParams_0879();
void resetPositions_2675();
void schedISRTask (uint8_t time, uint8_t routine, uint8_t param);
void schedTask (int b, int c);
void selectPacmanLeftSprite_168c (void);
void selectPacmanDownSprite_16b1 (void);
void selectPacmanRightSprite_16d6 (void);
void selectPacmanUpSprite_16f7 (void);
void setConfig_26d0();
void setGhostColour_0bd6();
void setMemory (int addr, int count, uint8_t value);
void showBonusLifeScore_26b2();
void start_230b ();
void tableCall (void (*func[])(), uint8_t index, uint8_t param);
void tileChangeBlinky_283b();
void tileChangeClyde_28b9();
void tileChangeInky_288f();
void tileChangePinky_2865();
void twoBlank (uint8_t *iy);
void twoUp (uint8_t *iy);
void updatePillsFromScreen_2487 (int param);
void waitForever (void);
void func_02fd (void);
void func_2d0c (void);
void interruptEnable ();
void interruptDisable();
void interruptMode (int mode);
void interruptVector (int vector);
bool interruptActive (void);
void incMainStateSub1_058e(void);
void addTask_0042 (uint8_t task, uint8_t param);
void addISRTask_0051(uint8_t *ptr, int count, uint8_t* data);
void incKilledState_1272 (void);
void displayReady_0263 (void);
void incScene1State_212b (void);
void incScene2State_212b (void);
bool checkCoinCredit_02df (void);
void advanceScene3State_22b9 (void);
void selectFruit_0ead (void);
void func_2bea (int param);
void func_13dd (void);
void func_0e6c (void);
void func_0a6f (void);
XYPOS addXYOffset_2000 (XYPOS ix, XYPOS iy);
void func_1f2e (void);
void func_1f55 (void);
void func_1f7c (void);
void pacmanDeadAnimState_1291 (void);
void func_2069 (void);
void func_115c(void);
void func_1bd8 (void);
void func_1caf (void);
void func_1d86 (void);
void func_1e5d (void);
void func_123f (void);
void func_12b7 (void);
void func_1652 (void);
void func_1940 (int b);
void func_1950 (void);
void pacmanOrientLeft_1ac9 (void);
void pacmanOrientRight_1ad9 (void);
void pacmanOrientUp_1ae8 (void);
void pacmanOrientDown_1af8 (void);
uint8_t getScreenCharPosOffset_200f (XYPOS offset, XYPOS pos);
XYPOS pixelToTile_2018 (XYPOS pos);
void resetFruitState_1004 (void);
void func_1b08 (void);
void func_1a5c (void);
void func_20d7 (void);
uint16_t getColourOffset_2052 (XYPOS pos);
void func_0506 (void);
void func_221e (uint16_t param);
void func_22a7 (void);
void startGame_234b (void);
void func_24d7(int param);
void initialisePositions_25d3 (int param);
void func_2730 (int param);
void func_23e8 (int param);
XYPOS findBestOrientation_2966 (XYPOS hl, XYPOS de, uint8_t *a);
uint16_t computeDistance_29ea(XYPOS ix, XYPOS iy);
XYPOS randomDirection_291e (XYPOS hl, uint8_t *orientation);
uint16_t calcSquare_2a12(uint8_t a);
uint16_t scoreTable_2b17[];
int drawDigit_2ace(uint8_t **screenLoc, int digit, int blanks);
uint16_t displayLives_2b4a (int lives);
uint8_t func_2dee (uint8_t *ix, uint8_t *iy, uint8_t *hl);
void func_2dd7 (void);
uint8_t func_2ee8 (uint8_t *ix, uint8_t *iy, uint16_t val);
uint8_t func_2f4a (uint8_t *ix);
void func_32ed (void);
void func_3af4 (void);

#define DATA_0219 (&ROM[0x0219])
#define DATA_3445 &ROM[0x3445]
#define DATA_35b5 (&ROM[0x35b5])
#define BONUS_LIFE_DATA (&ROM[0x2728])
#define DIFFICULTY_DATA ((uint16_t*)(&ROM[0x272c]))
#define DATA_3b80 (&ROM[0x3b80])
#define DATA_3b30 (&ROM[0x3b30])
#define DATA_3b40 (&ROM[0x3b40])
#define FRUIT_DATA (&ROM[0x0efd])
#define FRUIT_TABLE (&ROM[0x3b08])
#define DATA_MSG_TABLE ((uint16_t*)(&ROM[0x36a5]))
#define DATA_3bc8 (&ROM[0x3bc8])
#define DATA_3bb0 (&ROM[0x3bb0])
#define DATA_3bb8 (&ROM[0x3bb8])
#define DATA_3bcc (&ROM[0x3bcc])
#define DATA_3bd0 (&ROM[0x3bd0])
#define DATA_0796 (&ROM[0x0796])
#define MOVE_VECTOR_DATA ((XYPOS*)(&ROM[0x32ff]))
#define MOVE_VECTOR_RIGHT ((XYPOS*)(&ROM[0x32ff]))
#define MOVE_VECTOR_DOWN ((XYPOS*)(&ROM[0x3301]))
#define MOVE_VECTOR_LEFT ((XYPOS*)(&ROM[0x3303]))
#define MOVE_VECTOR_UP ((XYPOS*)(&ROM[0x3305]))
#define MOVE_DATA (&ROM[0x330f])
#define DATA_0843 (&ROM[0x0843])
#define DATA_084f (&ROM[0x084f])
#define DATA_0861 (&ROM[0x0861])
#define DATA_0873 (&ROM[0x0873])
