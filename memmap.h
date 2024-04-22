/* Memory map table.  Starts at flat map but replace with specific locations as
 * they are discovered */

// Video : https://www.walkofmind.com/programming/pie/video_memory.htm

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    struct
    {
        uint8_t rom[0x4000]; // starts at 0x0000
        uint8_t video[0x400]; // starts at 0x4000
        uint8_t colour[0x400]; // starts at 0x4400
        uint8_t ram[0x7f0];  // starts at 0x4800
        uint8_t spriteAttrib[0x10];  // starts at 0x4ff0
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
            uint8_t __unused1[0x38];
            uint8_t soundRegs[0x20]; // 0x5040
            uint8_t spriteCoords[0x10]; // 0x5060
            uint8_t __unused2[0x50];
            uint8_t watchdog[0x40]; // 0x50c0-0x50ff
        } write;
    } regs;
    uint8_t mem[0x5100];
}
CPU_MEMMAP;

extern CPU_MEMMAP memmap;
extern uint8_t charset[];
extern uint8_t input0;
extern uint8_t input1;
extern uint8_t dipSwitches;

#define ROM memmap.rom
#define MEM memmap.mem
#define RAM memmap.ram
#define SCREEN memmap.video
#define COLOUR memmap.colour
#define SOUND memmap.regs.write.soundRegs
#define SPRITEATTRIB memmap.spriteAttrib
#define SPRITECOORDS memmap.regs.write.spriteCoords
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
#define INPUT_ANYCOIN   0xe0
#define INPUT_ANYSTART  0x60

/*  Inputs and outputs share the same memory space but as we implement them with
 *  RAM for now, map the inputs to unused outputs.  Fix this sometime TODO */
#if 0
#define IO_INPUT0       memmap.regs.read.in0[0x30]
#define IO_INPUT1       memmap.regs.read.in1[0x30]
#define DIP_INPUT       memmap.regs.read.dipSwitches[0x30]
#else
#define IO_INPUT0       input0
#define IO_INPUT1       input1
#define DIP_INPUT       dipSwitches
#endif

#define IN0_UP          (IO_INPUT0 & INPUT_UP)
#define IN0_LEFT        (IO_INPUT0 & INPUT_LEFT)
#define IN0_RIGHT       (IO_INPUT0 & INPUT_RIGHT)
#define IN0_DOWN        (IO_INPUT0 & INPUT_DOWN)
#define IN0_RACKADV     (IO_INPUT0 & 0x10)
#define IN0_COIN1       (IO_INPUT0 & 0x20)
#define IN0_COIN2       (IO_INPUT0 & 0x40)
#define IN0_CREDIT      (IO_INPUT0 & 0x80)

#define IN1_UP          (IO_INPUT1 & INPUT_UP)
#define IN1_LEFT        (IO_INPUT1 & INPUT_LEFT)
#define IN1_RIGHT       (IO_INPUT1 & INPUT_RIGHT)
#define IN1_DOWN        (IO_INPUT1 & INPUT_DOWN)
#define IN1_SERVICE     (IO_INPUT1 & 0x10)
#define IN1_START1      (IO_INPUT1 & 0x20)
#define IN1_START2      (IO_INPUT1 & 0x40)
#define IN1_CABINET     (IO_INPUT1 & 0x80)

/* 0=free 1=1-coin=1-game 2=1-coin=2-games 3=2-coins=1-game */
#define DIP_SWITCH_COINS        (memmap.regs.read.in0[0] & 0x03)

/* 0=1-life 1=2-lives 2=3-lives 3=5-lives */
#define DIP_SWITCH_LIVES        ((memmap.regs.read.in0[0] & 0x0c) >> 2)

/* 0=10000 1=15000 2=20000 3=none */
#define DIP_SWITCH_BONUS        ((memmap.regs.read.in0[0] & 0x30) >> 4)

/* 0=hard 1=normal */
#define DIP_SWITCH_DIFFICULTY   ((memmap.regs.read.in0[0] & 0x40) >> 6)

/* 0=alternate 1=normal */
#define DIP_SWITCH_NAMES        ((memmap.regs.read.in0[0] & 0x80) >> 7)

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

#define SOUND_COUNTER                   &memmap.mem[0x4c84]
#define TIMER_HUNDREDTHS                memmap.mem[0x4c86]
#define TIMER_SECONDS                   memmap.mem[0x4c87]
#define TIMER_MINUTES                   memmap.mem[0x4c88]
#define TIMER_HOURS                     memmap.mem[0x4c89]
#define COUNTER_LIMITS_CHANGES          memmap.mem[0x4c8a]
#define RND_NUM_GEN1                    memmap.mem[0x4c8b]
#define RND_NUM_GEN2                    memmap.mem[0x4c8c]

/*  ISR tasks are 3 bytes each and there are 16 entries */
#define ISR_TASKS (&memmap.mem[0x4c90])

/*  non-ISR tasks are 2 bytes each and there are 16 entries */
#define NONISR_TASKS (&memmap.mem[0x4cc0])

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
#define PACMAN_DEMO_TILE     (*(XYPOS*)(&memmap.mem[0x4d12]))
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
#define PACMAN_DEMO_TILE2 (*(XYPOS*)(&memmap.mem[0x4d39]))

#define BEST_ORIENTATION_FOUND memmap.mem[0x4d3b]
#define PACMAN_DESIRED_ORIENTATION      memmap.mem[0x4d3c]
#define OPPOSITE_ORIENTATION memmap.mem[0x4d3d]
#define CURRENT_TILE_POS (*(XYPOS*)(&memmap.mem[0x4d3e]))
#define DEST_TILE_POS (*(XYPOS*)(&memmap.mem[0x4d40]))
#define TMP_RESULT_POS (*(XYPOS*)(&memmap.mem[0x4d42]))
#define MIN_DISTANCE_FOUND              (*(uint16_t*)&memmap.mem[0x4d44])
#define PACMAN_MOVE_PAT_NORMAL1         (*(uint16_t*)&memmap.mem[0x4d46])
#define PACMAN_MOVE_PAT_NORMAL2         (*(uint16_t*)&memmap.mem[0x4d48])
#define PACMAN_MOVE_PAT_POWERUP1        (*(uint16_t*)&memmap.mem[0x4d4a])
#define PACMAN_MOVE_PAT_POWERUP2        (*(uint16_t*)&memmap.mem[0x4d4c])
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
#define PACMAN_POWEREDUP                memmap.mem[0x4da6]
#define BLINKY_EDIBLE                   memmap.mem[0x4da7]
#define PINKY_EDIBLE                    memmap.mem[0x4da8]
#define INKY_EDIBLE                     memmap.mem[0x4da9]
#define CLYDE_EDIBLE                    memmap.mem[0x4daa]
#define GHOST_STATE                     memmap.mem[0x4dab]
#define BLINKY_STATE                    memmap.mem[0x4dac]
#define PINKY_STATE                     memmap.mem[0x4dad]
#define INKY_STATE                      memmap.mem[0x4dae]
#define CLYDE_STATE                     memmap.mem[0x4daf]

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

#define P1_CURR_DIFFICULTY              (*(uint16_t*)&memmap.mem[0x4e0a])
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
#define SND_CH1_EFF_CUR                 memmap.mem[0x4e9e]
#define SND_CH1_EFF_TABLE               (&memmap.mem[0x4e9f])
#define SND_CH2_EFF_NUM                 memmap.mem[0x4eac]
#define SND_CH2_EFF_CUR                 memmap.mem[0x4eae]
#define SND_CH2_EFF_TABLE               (&memmap.mem[0x4eaf])
#define SND_CH3_EFF_NUM                 memmap.mem[0x4ebc]
#define SND_CH3_EFF_CUR                 memmap.mem[0x4ebe]
#define SND_CH3_EFF_TABLE               (&memmap.mem[0x4ebf])
#define SND_CH1_WAV_NUM                 memmap.mem[0x4ecc]
#define SND_CH1_WAV_CUR                 memmap.mem[0x4ece]
#define SND_CH1_WAV_SEL                 memmap.mem[0x4ecf]
#define SND_CH2_WAV_NUM                 memmap.mem[0x4edc]
#define SND_CH2_WAV_CUR                 memmap.mem[0x4ede]
#define SND_CH2_WAV_SEL                 memmap.mem[0x4edf]
#define SND_CH3_WAV_NUM                 memmap.mem[0x4eec]
#define SND_CH3_WAV_CUR                 memmap.mem[0x4eee]
#define SND_CH3_WAV_SEL                 memmap.mem[0x4eef]

static inline void swap16 (uint8_t *a, uint8_t *b)
{
    uint8_t tmp;
    tmp = a[0]; a[0] = b[0]; b[0] = tmp;
    tmp = a[1]; a[1] = b[1]; b[1] = tmp;
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

static inline void assert (bool cond, char *file, int line)
{
    if (!cond)
    {
        fprintf (stderr, "ASSERT %s:%d\n", file, line);
        exit(1);
    }
}

#define ASSERT(cond) assert(cond,__FILE__,__LINE__)
