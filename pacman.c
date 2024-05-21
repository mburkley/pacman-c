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
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "memmap.h"
#include "protos.h"
#include "consts.h"
#include "structs.h"
#include "cpu.h"

// TODO prototypes are here temporarily to make find-and-replace easier */

void updateCounters_01dc (void);
void dispatchISRTasks_0221 (void);
void checkCoinInput_0267 (void);
void checkCoinCounterTimeout_02ad (void);
void func_039d (void);
void initResetGame_03dc (void);
void introStateMachine_03fe (void);
void introStart_045f (void);
void introduceBlinky_0471 (void);
void introduceShadow_047f (void);
void introducePinky_048b (void);
void introduceSpeedy_0499 (void);
void introducePinky_049f (void);
void introduceInky_04a5 (void);
void introduceBashful_04b3 (void);
void introduceBlinky_0485 (void);
void introduceInky_04b9 (void);
void introduceClyde_04bf (void);
void introduceClyde_04cd (void);
void selectDisplayClydeName_04d3 (void);
void introducePoints_04d8 (void);
void introSceneSetup_04e0 (void);
void introStartMoveBlinky_051c (void);
void introAdvanceState_0524 (uint8_t *hl, int b, int a);
void introMain_052c (void);
void introStartMovePinky_054b (void);
void introStartMoveInky_0556 (void);
void introStartMoveClyde_0561 (void);
void introCheckAllGhostsEaten_056c (void);
void introFinalTBD_057c (void);
void selectDisplayGhostName_0580(int c);
void displayIntroMsg_0585(int c);
void introduceGhost_0593(int c);
XYPOS pacmanReverse_05a5 (void);
void drawGhost_05bf (int hl, int a);
void coinInsertedStateMachine_05e5 (void);
void pushStartMsg_05f3 (void);
void player1ReadyMsg_0674 (void);
void creditStateReset_06a8 (void);
void playGameStateMachine_06be (void);
void setupGhostTimers_070e(int b);
void setupMovePat_0814(uint8_t *hl);
void levelStatePlayerReady_0899 (void);
void playGameMain_08cd (void);
void switchPlayers_0940 (void);
void stateDemoInit_0972 (void);
void gameOverOrNextPlayer_0988 (void);
void mazeColour_09ea (int param);
void advanceToLevelStatePlayGame_09d2 (void);
void playGameSoundOff_09d8 (void);
void mazeColourWhite_09e8 (void);
void mazeColourBlue_09fe (void);
void mazeColourWhite_0a02 (void);
void mazeColourBlue_0a04 (void);
void mazeColourWhite_0a06 (void);
void mazeColourBlue_0a08 (void);
void mazeColourWhite_0a0a (void);
void mazeColourBlue_0a0c (void);
void mazeReset_0a0e (void);
void nextLevelStateMachine_0a2c (void);
void nextLevel_0a7c (void);
void gameOverOrNextPlayer_0aa0 (void);
void advanceToLevelStatePlayGame_0aa3 (void);
void swapP1P2Difficulty_0aa6 (void);
void ghostsFlashBecomingInedible_0ac3 (void);
void flashPowerups_0c0d (void);
void ghostsLeaveHouse_0c42 (void);
void toggleGhostAnimation_0e23 (void);
void ghostsChangeOrientation_0e36 (void);
void resetFruit_1000 (void);
void func_100b (void);
void updateGhostStates_1017 (void);
void selectGhostState_1066 (void);
void blinkyStateMachine_1094 (void);
void pinkyStateMachine_109e (void);
void inkyStateMachine_10a8 (void);
void clydeStateMachine_10b4 (void);
void blinkyStateDead_10c0 (void);
void blinkyStateEnterHouse_10d2 (void);
void ghostsAnyDeadSoundOff_1101 (void);
void pinkyStateDead_1118 (void);
void pinkyStateEnterHouse_112a (void);
void inkyStateEnterHouse_116e (void);
void inkyStateHouseMoveAside_118f (void);
void clydeStateDead_11c9 (void);
void clydeStateEnterHouse_11db (void);
void clydeStateHouseMoveAside_11fc (void);
void ghostKilledState_1235 (void);
void pacmanDeadAnimState5_12cb (void);
void pacmanDeadAnimState6_12f9 (void);
void pacmanDeadAnimState7_1306 (void);
void pacmanDeadAnimState8_130e (void);
void pacmanDeadAnimState9_1316 (void);
void pacmanDeadAnimState10_131e (void);
void pacmanDeadAnimState11_1326 (void);
void pacmanDeadAnimState12_132e (void);
void pacmanDeadAnimState13_1336 (void);
void pacmanDeadAnimState14_133e (void);
void pacmanDeadAnimState15_1346 (void);
void decrementLives_1353 (void);
void powerupOver_1376 (void);
void spriteAnimationUpright_141f (void);
void spriteAnimationCocktail_1490 (void);
void spriteAnimation_14fe (bool invert);
void ghostsCocktailMode_15b4 (bool invert);
void scene1Animation_15e6 (void);
void scene2Animation_162d (void);
void pacmanCheckGhostCoincidence_171d (void);
void pacmanGhostCoincide_1763 (int b);
void pacmanCheckEatGhost_1789 (void);
void pacmanUpdateMovePat_1806 (void);
void pacmanCheckMoveClear_18e4 (int b);
void pacmanUpdatePos_1985(XYPOS pos);
void pacmanMoveTile_1a19 (void);
void checkGhostsBecomeEdible_1a6a (void);
void ghostsBecomeEdible_1a70 (void);
void blinkyUpdateMovePat_1b36 (void);
void pinkyUpdateMovePat_1c4b (void);
void inkyUpdateMovePat_1d22 (void);
void clydeUpdateMovePat_1df9 (void);
bool checkTunnelTBD_1ed0(int ghost);
void blinkyCheckReverse_1efe (void);
void pinkyCheckReverse_1f25 (void);
void inkyCheckReverse_1f4c (void);
void clydeCheckReverse_1f73 (void);
uint16_t getScreenOffset_202d (XYPOS hl);
void checkGhostEnterTunnel_205a (XYPOS pos, uint8_t *aux);
void inkyCheckLeaveHouse_208c (void);
void clydeCheckLeaveHouse_20af (void);
void scene1StateMachine_2108 (void);
void scene1State0_211a (void);
void updateMoveVectorPacmanBlinky_2130 (void);
void updateMoveVectorBlinky_2136 (void);
void scene1State1_2140 (void);
void scene1State2_214b (void);
void scene1State4_2170 (void);
void scene1State5_217b (void);
void scene1State6_2186 (void);
void scene2StateMachine_219e (void);
void scene2State0_21c2(uint16_t iy);
void scene2State2_21e1(uint16_t iy);
void scene2State3_21f5(uint16_t iy);
void scene2State4_220c(uint16_t iy);
void updateMoveVector_2237 (void);
void scene2State6_2244(uint16_t iy);
void scene2State7_225d(uint16_t iy);
void scene2State9_226a(uint16_t iy);
void scene2State11_2286(uint16_t iy);
void scene2State13_228d(uint16_t iy);
void scene3StateMachine_2297 (void);
void scene3State1_22be (void);
void scene3State3_22dd (void);
void scene3FruitPos_22e4 (void);
void scene3State4_22f5 (void);
void scene3State5_22fe (void);
void initSelfTest_230b (void);
void clearScreen_23f3 (void);
void clearScreenMazeOnly_2400 (void);
void clearColour_240d (int param);
void drawMaze_2419 (int param);
void drawPills_2448(int param);
void clearPillArrays_24c9 ();
void blinkySubstateTBD_268b(int param);
void clearGhostState_26a2 ();
void pinkyScatterOrChase_276c (int param);
void inkyScatterOrChase_27a9 (int param);
void clydeScatterOrChase_27f1 (int param);
void pacmanOrientationDemo_28e3 ();
void clearPillsScreen_2a35 ();
void addToScore_2a5a(int b);
void clearScores_2ae0 ();
uint8_t* getPlayerScorePtr_2b0b (void);
void drawBlankSquare_2b7e(uint8_t *hl);
void drawCharSquare_2b80 (uint8_t *hl, int a);
void drawFruit_2b8f (uint8_t *hl, int a);
void bottomTextColourAndDisplayLives_2b6a (int unused);
void displayFruitHistory_2bfd (uint8_t *table, int level);
void func_2c44(uint8_t a);
void playSongsAllChannels_2cc1 (void);
void displayMsg_2c5e (int b);
uint8_t playSongOneChannel_2d44 (SOUND_EFFECT *effect, uint8_t *frequency, uint8_t *table);
uint8_t soundEffectClear_2df4 (SOUND_EFFECT *effect, uint8_t *frequency);
uint8_t soundEffectProcess_2e1b (SOUND_EFFECT *effect, uint8_t *frequency,
uint8_t *table, int chan);
uint8_t frequencyScaledWithVolume_2ee4 (SOUND_EFFECT *effect, uint8_t *frequency, uint16_t frequencyValue, uint8_t a);
uint8_t volumeDecayNone_2f22 (SOUND_EFFECT *effect);
uint8_t volumeDecay_2f26 (SOUND_EFFECT *effect);
uint8_t volumeDecayHalfTime_2f2b (SOUND_EFFECT *effect);
uint8_t volumeDecreaseConditional_2f30 (SOUND_EFFECT *effect, int condition);
uint8_t volumeDecrease_2f34 (SOUND_EFFECT *effect, uint8_t a);
uint8_t volumeDecayQuarterTime_2f3c (SOUND_EFFECT *effect);
uint8_t volumeDecayEighthTime_2f43 (SOUND_EFFECT *effect);
void soundEffectIndirect_2f55 (SOUND_EFFECT *effect, uint8_t *frequency);
void soundEffectSelect_2f65 (SOUND_EFFECT *effect, uint8_t *frequency);
void soundEffectInitialFrequency_2f77 (SOUND_EFFECT *effect, uint8_t *frequency);
void soundEffectInitialVolume_2f89 (SOUND_EFFECT *effect, uint8_t *frequency);
void soundEffectType_2f9b (SOUND_EFFECT *effect, uint8_t *frequency);
void soundEffectMarkDone_2fad (SOUND_EFFECT *effect, uint8_t *frequency);

void kickWatchdog (void);
void mainStateMachine_03c8  (void);
// void addISRTask(uint8_t *ptr, int count, uint8_t* data);
void addTask (uint8_t task, uint8_t param);
void mainStateMachine_03c8  (void);
void resetStateMachine_03d4 (void);
void checkStartButtons (void);
void displayCredits_2ba1 ();
void drawPlayerScore_2aaf (uint8_t *score);
void drawScore_2abe (uint16_t screenLoc, uint8_t *score, int blanks);
void extraLife_2b33 (uint8_t *score);
void fillScreenArea_2bcd (int addr, int ch, int cols, int rows);
void incLevelStateSubr_0894 (void);
void incMainSub2_06a3 (void);
void initLeaveHouseCounters_083a(uint8_t *hl);
void isr_008d (void);
void jumpClearScreen_23ed(int param);
void nothing (void);
void oneBlank_0383 (uint8_t *ix);
void oneUp_0369 (uint8_t *ix);
void pacmanDeadAnimation_12d6(int ch, int count);
void playerDied_090d (void);
void playerUp (void);
uint8_t random_2a23 (void);
void resetGameState_2698 ();
void setGhostPosition_267e (int y, int x);
void resetPlayerParams_0879 (void);
void resetPositions_2675 ();
void schedISRTask (uint8_t time, uint8_t routine, uint8_t param);
void schedTask (int b, int c);
void selectPacmanLeftSprite_168c (void);
void selectPacmanDownSprite_16b1 (void);
void selectPacmanRightSprite_16d6 (void);
void selectPacmanUpSprite_16f7 (void);
void configureGame_26d0 (int unused);
void setGhostColour_0bd6 (void);
void setMemory (int addr, int count, uint8_t value);
void showBonusLifeScore_26b2 ();
void tableCall (void (*func[])(), uint8_t index, uint8_t param);
void homeOrRandomBlinky_283b ();
void homeOrRandomClyde_28b9 ();
void homeOrRandomInky_288f ();
void homeOrRandomPinky_2865 ();
void twoBlank_0390 (uint8_t *iy);
void twoUp_0376 (uint8_t *iy);
void updatePillsFromScreen_2487 (int param);
void waitForever (void);
void showStartNumPlayers_02fd (void);
void soundEffectsAllChannels_2d0c (void);
void incMainStateIntro_058e(void);
void addTask_0042 (uint8_t task, uint8_t param);
void addISRTask_0051(uint8_t *ptr, int count, uint8_t* data);
void incKilledState_1272 (void);
void displayReady_0263 (void);
void incScene1State_212b (void);
void incScene2State_212b (void);
void checkCoinCredit_02df (void);
void incScene3State_22b9 (void);
void selectFruit_0ead (void);
void fruitHistoryLevelCheck_2bea (int param);
void checkInactivityCounter_13dd (void);
void updatePillsEatenSoundEffect_0e6c (void);
void incLevelState_0a6f (void);
XYPOS addXYOffset_2000 (XYPOS ix, XYPOS iy);
void pinkyReverse_1f2e (void);
void inkyReverse_1f55 (void);
void clydeReverse_1f7c (void);
void pacmanDeadAnimState_1291 (void);
void pinkyCheckLeaveHouse_2069 (void);
void inkyStateDead_115c(void);
void blinkyUpdatePosition_1bd8 (void);
void pinkyUpdatePosition_1caf (void);
void inkyUpdatePosition_1d86 (void);
void clydeUpdatePosition_1e5d (void);
void showKillPoints_123f (void);
void pacmanDeadAnimState1To4_12b7 (void);
void scene3Animation_1652 (void);
void pacmanHitMazeWall_1940 (int b);
void pacmanMove_1950 (void);
void pacmanOrientLeft_1ac9 (void);
void pacmanOrientRight_1ad9 (void);
void pacmanOrientUp_1ae8 (void);
void pacmanOrientDown_1af8 (void);
uint8_t getScreenCharPosOffset_200f (XYPOS offset, XYPOS pos);
XYPOS pixelToTile_2018 (XYPOS pos);
void resetFruitState_1004 (void);
void updateLeaveHouseCounters_1b08 (void);
void pacmanMove_1a5c (void);
void updateDifficultyTBD_20d7 (void);
uint16_t getColourOffset_2052 (XYPOS pos);
void demoMazeHorizontal_0506 (void);
void scene2State5_221e (uint16_t param);
void scene3State0_22a7 (void);
void mainTaskLoop_234b (void);
void advanceLevelState_23e8 (int param);
void mazeColours_24d7(int param);
void initialisePositions_25d3 (int param);
void blinkyScatterOrChase_2730 (int param);
XYPOS findBestOrientation_2966 (XYPOS hl, XYPOS de, uint8_t *a);
uint16_t computeDistance_29ea(XYPOS ix, XYPOS iy);
XYPOS randomDirection_291e (XYPOS hl, uint8_t *orientation);
uint16_t calcSquare_2a12(uint8_t a);
uint16_t scoreTable_2b17[];
int drawDigit_2ace(uint16_t *screenLoc, int digit, int blanks);
uint16_t displayLives_2b4a (int lives);
void fruitHistoryLevelHigherThan8_2c2e (int level);
uint8_t soundEffectOneChannel_2dee (SOUND_EFFECT *effect, uint8_t *frequency,
uint8_t *table, int chan);
void func_2dd7 (void);
uint8_t frequencyWithVolume_2ee8 (SOUND_EFFECT *effect, uint8_t *frequency, uint16_t frequencyValue);
uint8_t soundEffectDoNothing_2f4a (SOUND_EFFECT *effect);
void isr_3000 (void);
void romChecksumBad_3031 (uint8_t h, uint8_t checksum);
void ramTest_3042 (void);
void badRam_30b5 (uint8_t e, uint8_t checksum);
void testResultRamRom (int e, uint8_t checksum, int b);
void badRomOrRamMessage_30fb (int e, int h, uint8_t checksum);
void serviceModeOrStartGame_3174 (void);
void delay_32ed (void);
void madeByNamco_3af4 (void);

#define DATA_0219 (&ROM[0x0219])
#define DATA_0796 (&ROM[0x0796])
#define DATA_0843 (&ROM[0x0843])
#define DATA_084f (&ROM[0x084f])
#define DATA_0861 (&ROM[0x0861])
#define DATA_0873 (&ROM[0x0873])
#define FRUIT_DATA (&ROM[0x0efd])
#define BONUS_LIFE_DATA (&ROM[0x2728])
#define DIFFICULTY_DATA ((uint16_t*)(&ROM[0x272c]))
#define MOVE_VECTOR_DATA ((XYPOS*)(&ROM[0x32ff]))
#define MOVE_VECTOR_RIGHT ((XYPOS*)(&ROM[0x32ff]))
#define MOVE_VECTOR_DOWN ((XYPOS*)(&ROM[0x3301]))
#define MOVE_VECTOR_LEFT ((XYPOS*)(&ROM[0x3303]))
#define MOVE_VECTOR_UP ((XYPOS*)(&ROM[0x3305]))
#define MOVE_DATA_330f (&ROM[0x330f])
#define DATA_3435 &ROM[0x3435]
#define DATA_35b5 (&ROM[0x35b5])
#define EFFECT_TABLE_CH3_3b80 (&ROM[0x3b80])
#define EFFECT_TABLE_CH1_3b30 (&ROM[0x3b30])
#define EFFECT_TABLE_CH2_3b40 (&ROM[0x3b40])
#define FRUIT_TABLE (&ROM[0x3b08])
#define DATA_MSG_TABLE (&ROM[0x36a5])
#define SONG_TABLE_CH1_3bc8 (&ROM[0x3bc8])
#define POWER_OF_2_3bb0 (&ROM[0x3bb0])
#define FREQ_TABLE_3bb8 (&ROM[0x3bb8])
#define SONG_TABLE_CH2_3bcc (&ROM[0x3bcc])
#define SONG_TABLE_CH3_3bd0 (&ROM[0x3bd0])
#define DATA_3154 ((uint16_t *)(&ROM[0x3154]))
#define BAD_ROM_316c (&ROM[0x316c])
#define BAD_W_RAM_316e (&ROM[0x316e])
#define BAD_V_RAM_3170 (&ROM[0x3170])
#define BAD_C_RAM_3172 (&ROM[0x3172])
#define DATA_32f9 (&ROM[0x32f9])
#define DATA_3ae2 ((uint16_t *)(&ROM[0x3ae2]))

void reset_0000 (void)
{
    //-------------------------------
    // 0000  f3        di			; Disable interrupts
    // 0001  3e3f      ld      a,#3f
    // 0003  ed47      ld      i,a		; Interrupt page = 0x3f
    // 0005  c30b23    jp      #230b		; Run startup tests
    //-------------------------------
    interruptDisable ();
    initSelfTest_230b();
}

/* Fill "hl" to "hl+b" with "a" */
void setMemory_0008 (uint8_t *hl, uint8_t b, uint8_t a)
{
    //-------------------------------
    // 0008  77        ld      (hl),a
    // 0009  23        inc     hl
    // 000a  10fc      djnz    #0008           ; (-4)
    // 000c  c9        ret     
    //-------------------------------
    memset (hl, a, b);
}

/*  Memory location 000c is referenced in several tables.  It is just a return
 *  so define an empty function to add to the jump tables */
void nothing_000c ()
{
}

/*  Same as above but takes a parameter */
void nothingParam_000c (uint16_t unused)
{
}

/*  Same as above but takes a parameter and returns a uint8 */
uint8_t nothingReturnParam_000c (SOUND_EFFECT *unused1, uint8_t *unused2)
{
    return 0;
}

void setupGhostTimers_000d (int param)
{
    //-------------------------------
    // 000d  c30e07    jp      #070e
    //-------------------------------
    setupGhostTimers_070e(param);
}

/*  Add b to hl, fetch return the byte at *(hl+b).  hl is also modified */
uint8_t fetchOffset_0010 (uint8_t **hl, uint8_t b)
{
    //-------------------------------
    // 	;; hl = hl + a, (hl) -> a
    // 0010  85        add     a,l		
    // 0011  6f        ld      l,a		
    // 0012  3e00      ld      a,#00
    // 0014  8c        adc     a,h		
    // 0015  67        ld      h,a
    // 0016  7e        ld      a,(hl)
    // 0017  c9        ret     
    //-------------------------------
    (*hl) += b;
    return **hl;
}

/*  Do a table lookup using b as an offset.  Fetch a byte value into de and
 *  return.
 *
 *  hl = hl + 2*b,  (hl) -> e, (++hl) -> d, de -> hl */
uint16_t tableLookup_0018 (uint8_t *hl, uint8_t b)
{
    //-------------------------------
    // 0018  78        ld      a,b		; b -> a 
    // 0019  87        add     a,a		; 2*a -> a 
    // 001a  d7        rst     #10
    // 001b  5f        ld      e,a
    // 001c  23        inc     hl
    // 001d  56        ld      d,(hl)
    // 001e  eb        ex      de,hl
    // 001f  c9        ret     
    //-------------------------------
    int e = fetchOffset_0010(&hl, b*2);
    hl++;
    int d = *hl;
    return e | (d << 8);
}

/*  Lookup a function address in a table pointed to by the return address.  The
 *  number of function addresses is variable.  This function calls functions
 *  that have a void parameter list.  When calling functions that need
 *  parameters, this method isn't used and the functions are called by directly
 *  indexing the array.  */
void tableCall_0020 (void (*func[])(), uint8_t a)
{
    //-------------------------------
    // 0020  e1        pop     hl
    // 0021  87        add     a,a
    // 0022  d7        rst     #10
    // 0023  5f        ld      e,a
    // 0024  23        inc     hl
    // 0025  56        ld      d,(hl)
    // 0026  eb        ex      de,hl
    // 0027  e9        jp      (hl)
    //-------------------------------
    func[a]();
}

/*  Fetches two bytes following caller return address and places in a ring.  The
 *  C implementation doesn't need to retrieve from stack, so is just a wrapper
 *  */
void schedTask (int b, int c)
{
    //-------------------------------
    // 0028  e1        pop     hl              ; retrieve return addr
    // 0029  46        ld      b,(hl)          ; fetch byte following rst call
    // 002a  23        inc     hl              
    // 002b  4e        ld      c,(hl)          ; fetch next byte
    // 002c  23        inc     hl              ; inc again
    // 002d  e5        push    hl              ; put ret addr+2 on stack to skip // data
    // 002e  1812      jr      #0042           ; (18)
    //-------------------------------
    // printf("%s t = %d p=%d\n", __func__, b, c);
    addTask_0042 (b, c);
}

/*  Fetches 3 bytes and stores them to a free location starting at 0x4c90.  In C
 *  we pass the bytes as params.  Task list starts at 0x4c90 and has 16 entries  */
void schedISRTask (uint8_t time, uint8_t routine, uint8_t param)
{
    //-------------------------------
    // 0030  11904c    ld      de,#4c90
    // 0033  0610      ld      b,#10
    // 0035  c35100    jp      #0051
    //-------------------------------
    TASK task;
    task.timer = time;
    task.func = routine;
    task.param = param;
    // printf ("%s t = %d f=%d p=%d\n", __func__, time, routine, param);
    addISRTask_0051 (ISR_TASKS, 0x10, (uint8_t*)&task);
}

/* Loop forever with interrupts disabled.  Continuously reset interrupt enable
 * and coin counter */
void waitForever_0038 (void)
{
    //-------------------------------
    // 0038  af        xor     a
    // 0039  320050    ld      (#5000),a
    // 003c  320750    ld      (#5007),a
    // 003f  c33800    jp      #0038
    //-------------------------------
    while (1)
    {
        INTENABLE = 0;
        COINCOUNTER = 0;
    }
}

/*  The task list is from 0x4cc0-0x4cff.  High byte doesn't change so only
 *  increment l.  If the low byte is 00 then we have hit the end so we need to
 *  wrap around to 0x4cc0 again. */
void addTask_0042 (uint8_t task, uint8_t param)
{
    //-------------------------------
    // 0042  2a804c    ld      hl,(#4c80)       ; task list start value
    // 0045  70        ld      (hl),b
    // 0046  2c        inc     l
    // 0047  71        ld      (hl),c
    // 0048  2c        inc     l
    // 0049  2002      jr      nz,#004d        ; (2)
    // 004b  2ec0      ld      l,#c0            ; if l = 0x00 then reset to 0xc0
    // 004d  22804c    ld      (#4c80),hl
    // 0050  c9        ret     
    //-------------------------------
    MEM[TASK_LIST_END++] = task; 
    MEM[TASK_LIST_END++] = param; 

    if (TASK_LIST_END == 0x4d00)
        TASK_LIST_END = 0x4cc0;
}

/*  Called from rst #30.  Adds a task to the ISR task queue */
void addISRTask_0051(uint8_t *ptr, int count, uint8_t* data)
{
    //-------------------------------
    // 	;; Jump from rst 0x30
    // 0051  1a        ld      a,(de)
    // 0052  a7        and     a
    // 0053  2806      jr      z,#005b         ; (6)
    // 0055  1c        inc     e
    // 0056  1c        inc     e
    // 0057  1c        inc     e
    // 0058  10f7      djnz    #0051           ; (-9)
    //-------------------------------
    int i;
    for (i = 0; i < count; i++)
    {
        if (*ptr == 0)
            break;

        ptr += 3;
    }
    //-------------------------------
    // 005a  c9        ret     
    //-------------------------------
    if (i == count)
        return;

    //-------------------------------
    // 005b  e1        pop     hl           ; retrieve return address
    // 005c  0603      ld      b,#03
    //-------------------------------
    for (i = 0; i < 3; i++)
    {
        //-------------------------------
        // 005e  7e        ld      a,(hl)   ; fetch a byte from return addr
        // 005f  12        ld      (de),a   ; store byte to task entry
        // 0060  23        inc     hl
        // 0061  1c        inc     e
        // 0062  10fa      djnz    #005e           ; (-6)
        //-------------------------------
        *ptr++= *data++;
    }

    //-------------------------------
    // 0064  e9        jp      (hl)
    //-------------------------------
}

uint16_t getScreenOffset_0065(XYPOS pos)
{
    //-------------------------------
    // 0065  c32d20    jp      #202d
    //-------------------------------
    return getScreenOffset_202d(pos);
}

    /*  Difficulty data.  Two sets, easy or hard.  Hard ramps up more quickly.
     *  Each level is more difficult until max difficulty which is 0x14 */

    //-------------------------------
    // 0068                           00 01 02 03 04 05 06 07
    // 0070  08 09 0a 0b 0c 0d 0e 0f  10 11 12 13 14 
    //-------------------------------
    //-------------------------------
    // 007d                                          01 03 04
    // 0080  06 07 08 09 0a 0b 0c 0d  0e 0f 10 11 14         
    //-------------------------------


void isr_008d (void)
{
    //-------------------------------
    // 	;; Non-test mode interrupt routine
    // 008d  f5        push    af
    // 008e  32c050    ld      (#50c0),a	; Kick watchdog 
    // 0091  af        xor     a
    // 0092  320050    ld      (#5000),a	; Disable interrupts (hardware) 
    // 0095  f3        di			; Disable interrupts (CPU) 
    // 0096  c5        push    bc
    // 0097  d5        push    de
    // 0098  e5        push    hl
    // 0099  dde5      push    ix
    // 009b  fde5      push    iy
    //-------------------------------
    kickWatchdog();
    INTENABLE = 0;
    interruptDisable();

    //-------------------------------
    // 009d  218c4e    ld      hl,#4e8c	; Write freq/volume for sound regs 
    // 00a0  115050    ld      de,#5050
    // 00a3  011000    ld      bc,#0010
    // 00a6  edb0      ldir
    //-------------------------------
    memcpy (&SOUND[0x10], &CH1_FREQ0, 0x10);

    //-------------------------------
    // 00a8  3acc4e    ld      a,(#4ecc)
    // 00ab  a7        and     a
    // 
    // 	;; Write sound waveforms
    // 00ac  3acf4e    ld      a,(#4ecf)
    // 00af  2003      jr      nz,#00b4        ; (3)
    // 00b1  3a9f4e    ld      a,(#4e9f)
    // 00b4  324550    ld      (#5045),a
    //-------------------------------
    int a;

    if (CH1_SOUND_WAVE->mask != 0)
        a = CH1_SOUND_WAVE->selected;
    else
        a = CH1_SOUND_EFFECT->selected;

    SOUND[5] = a; // voice 1 wave form

    //-------------------------------
    // 00b7  3adc4e    ld      a,(#4edc)
    // 00ba  a7        and     a
    // 00bb  3adf4e    ld      a,(#4edf)
    // 00be  2003      jr      nz,#00c3        ; (3)
    // 00c0  3aaf4e    ld      a,(#4eaf)
    // 00c3  324a50    ld      (#504a),a
    //-------------------------------

    if (CH2_SOUND_WAVE->mask != 0)
        a = CH2_SOUND_WAVE->selected;
    else
        a = CH2_SOUND_EFFECT->selected;

    SOUND[0xa] = a; // voice 2 wave form

    //-------------------------------
    // 00c6  3aec4e    ld      a,(#4eec)
    // 00c9  a7        and     a
    // 00ca  3aef4e    ld      a,(#4eef)
    // 00cd  2003      jr      nz,#00d2        ; (3)
    // 00cf  3abf4e    ld      a,(#4ebf)
    // 00d2  324f50    ld      (#504f),a
    //-------------------------------

    if (CH3_SOUND_WAVE->mask != 0)
        a = CH3_SOUND_WAVE->selected;
    else
        a = CH3_SOUND_EFFECT->selected;

    SOUND[0xf] = a; // voice 3 wave form

    //-------------------------------
    // 00d5  21024c    ld      hl,#4c02
    // 00d8  11224c    ld      de,#4c22
    // 00db  011c00    ld      bc,#001c
    // 00de  edb0      ldir
    //-------------------------------
    memcpy (SPRITE_POS, &BLINKY_SPRITE, 0x1c);

    //-------------------------------
    // 00e0  dd21204c  ld      ix,#4c20
    // 00e4  dd7e02    ld      a,(ix+#02)
    // 00e7  07        rlca    
    // 00e8  07        rlca    
    // 00e9  dd7702    ld      (ix+#02),a
    // 00ec  dd7e04    ld      a,(ix+#04)
    // 00ef  07        rlca    
    // 00f0  07        rlca    
    // 00f1  dd7704    ld      (ix+#04),a
    // 00f4  dd7e06    ld      a,(ix+#06)
    // 00f7  07        rlca    
    // 00f8  07        rlca    
    // 00f9  dd7706    ld      (ix+#06),a
    // 00fc  dd7e08    ld      a,(ix+#08)
    // 00ff  07        rlca    
    // 0100  07        rlca    
    // 0101  dd7708    ld      (ix+#08),a
    // 0104  dd7e0a    ld      a,(ix+#0a)
    // 0107  07        rlca    
    // 0108  07        rlca    
    // 0109  dd770a    ld      (ix+#0a),a
    // 010c  dd7e0c    ld      a,(ix+#0c)
    // 010f  07        rlca    
    // 0110  07        rlca    
    // 0111  dd770c    ld      (ix+#0c),a
    //-------------------------------

    /*  Move the least significant 2 bits (mirror and invert) to the most
     *  significant posititions.  Why didn't they just put them in the MSB to
     *  begin with?  Maybe easier to work with sprite shape numbers that are not
     *  times 4 */

    rotate8 (&SPRITE_POS[0], 2);
    rotate8 (&SPRITE_POS[2], 2);
    rotate8 (&SPRITE_POS[4], 2);
    rotate8 (&SPRITE_POS[6], 2);
    rotate8 (&SPRITE_POS[8], 2);
    rotate8 (&SPRITE_POS[10], 2);

    //-------------------------------
    // 0114  3ad14d    ld      a,(#4dd1)
    // 0117  fe01      cp      #01
    // 0119  2038      jr      nz,#0153        ; (56)
    //-------------------------------
    if (KILLED_STATE == 1)
    {
        //-------------------------------
        // 011b  dd21204c  ld      ix,#4c20
        // 011f  3aa44d    ld      a,(#4da4)
        // 0122  87        add     a,a
        // 0123  5f        ld      e,a
        // 0124  1600      ld      d,#00
        // 0126  dd19      add     ix,de
        // 0128  2a244c    ld      hl,(#4c24)
        // 012b  ed5b344c  ld      de,(#4c34)
        // 012f  dd7e00    ld      a,(ix+#00)
        // 0131  32244c    ld      (#4c24),a
        // 0135  dd7e01    ld      a,(ix+#01)
        // 0138  32254c    ld      (#4c25),a
        // 013b  dd7e10    ld      a,(ix+#10)
        // 013e  32344c    ld      (#4c34),a
        // 0141  dd7e11    ld      a,(ix+#11)
        // 0144  32354c    ld      (#4c35),a
        // 0147  dd7500    ld      (ix+#00),l
        // 014a  dd7401    ld      (ix+#01),h
        // 014d  dd7310    ld      (ix+#10),e
        // 0150  dd7211    ld      (ix+#11),d
        //-------------------------------

        /*  If a ghost has been eaten, then make that sprite the highest
         *  priority by swapping it with blinky.  I presume this is to ensure
         *  the points aren't hidden behind any other ghost
         *  sprites.*/

        swap16 (&SPRITE_POS[2], &SPRITE_POS[KILLED_GHOST_INDEX*2]);
        swap16 (&SPRITE_DATA[2], &SPRITE_POS[KILLED_GHOST_INDEX*2 + 0x10]);
    }

    //-------------------------------
    // 0153  3aa64d    ld      a,(#4da6)
    // 0156  a7        and     a
    // 0157  ca7601    jp      z,#0176
    //-------------------------------
    if (PACMAN_POWEREDUP != 0)
    {
        //-------------------------------
        // 015a  ed4b224c  ld      bc,(#4c22)
        // 015e  ed5b324c  ld      de,(#4c32)
        // 0162  2a2a4c    ld      hl,(#4c2a)
        // 0165  22224c    ld      (#4c22),hl
        // 0168  2a3a4c    ld      hl,(#4c3a)
        // 016b  22324c    ld      (#4c32),hl
        // 016e  ed432a4c  ld      (#4c2a),bc
        // 0172  ed533a4c  ld      (#4c3a),de
        //-------------------------------

        /*  If pacman is powered up then the pacman sprite appears on top of all
         *  other sprites so swap the position with blinky's position */

        swap16 (SPRITE_POS, &SPRITE_POS[8]);
        swap16 (SPRITE_DATA, &SPRITE_DATA[8]);
    }

    //-------------------------------
    // 0176  21224c    ld      hl,#4c22
    // 0179  11f24f    ld      de,#4ff2
    // 017c  010c00    ld      bc,#000c
    // 017f  edb0      ldir    
    //-------------------------------
    // TODO looks backwards, positions and attributes
    memcpy (SPRITEATTRIB+2, SPRITE_POS, 0xc);

    //-------------------------------
    // 0181  21324c    ld      hl,#4c32
    // 0184  116250    ld      de,#5062
    // 0187  010c00    ld      bc,#000c
    // 018a  edb0      ldir    
    //-------------------------------
    memcpy (SPRITECOORDS+2, SPRITE_DATA, 0xc);

    //-------------------------------
    // 018c  cddc01    call    #01dc
    // 018f  cd2102    call    #0221
    // 0192  cdc803    call    #03c8
    //-------------------------------
    updateCounters_01dc();
    dispatchISRTasks_0221();
    mainStateMachine_03c8 ();

    //-------------------------------
    // 0195  3a004e    ld      a,(#4e00)
    // 0198  a7        and     a
    // 0199  2812      jr      z,#01ad         ; (18)
    // 019b  cd9d03    call    #039d
    // 019e  cd9014    call    #1490
    // 01a1  cd1f14    call    #141f
    // 01a4  cd6702    call    #0267
    // 01a7  cdad02    call    #02ad
    // 01aa  cdfd02    call    #02fd
    //-------------------------------
    if (MAIN_STATE != MAIN_STATE_INIT)
    {
        // printf ("ISR: MAIN != 0\n");
        func_039d();
        spriteAnimationCocktail_1490();
        spriteAnimationUpright_141f();
        checkCoinInput_0267();
        checkCoinCounterTimeout_02ad();
        showStartNumPlayers_02fd();
    }

    //-------------------------------
    // 01ad  3a004e    ld      a,(#4e00)
    // 01b0  3d        dec     a
    // 01b1  2006      jr      nz,#01b9        ; (6)
    //-------------------------------
    if (MAIN_STATE == MAIN_STATE_DEMO)
    {
        //-------------------------------
        // 01b3  32ac4e    ld      (#4eac),a
        // 01b6  32bc4e    ld      (#4ebc),a
        //-------------------------------
        CH2_SOUND_EFFECT->mask = 0;
        CH3_SOUND_EFFECT->mask = 0;
    }

    //-------------------------------
    // 01b9  cd0c2d    call    #2d0c
    // 01bc  cdc12c    call    #2cc1
    // 01bf  fde1      pop     iy
    // 01c1  dde1      pop     ix
    // 01c3  e1        pop     hl
    // 01c4  d1        pop     de
    // 01c5  c1        pop     bc
    //-------------------------------
    soundEffectsAllChannels_2d0c();
    playSongsAllChannels_2cc1();
    printf ("2cc1 done\n");

    //-------------------------------
    // 01c6  3a004e    ld      a,(#4e00)
    // 01c9  a7        and     a
    // 01ca  2808      jr      z,#01d4         ; (8)
    // 01cc  3a4050    ld      a,(#5040)	; Check test switch 
    // 01cf  e610      and     #10
    // 01d1  ca0000    jp      z,#0000		; Reset if test
    // 01d4  3e01      ld      a,#01		; Enable interrupts (hardware) 
    // 01d6  320050    ld      (#5000),a
    // 01d9  fb        ei			; Enable interrupts (CPU) 
    // 01da  f1        pop     af
    // 01db  c9        ret     
    //-------------------------------

    if (MAIN_STATE != MAIN_STATE_INIT && IN0_RACKADV == 0)
    {
        // reset();
        printf ("!! main state != 0 and test DIP sel\n");
        exit(1);
    }

    INTENABLE = 1;
    interruptEnable ();
}

void updateCounters_01dc (void)
{
    printf("%s\n", __func__);
    //-------------------------------
    // 01dc  21844c    ld      hl,#4c84
    // 01df  34        inc     (hl)
    // 01e0  23        inc     hl
    // 01e1  35        dec     (hl)
    // 01e2  23        inc     hl
    //-------------------------------
    uint8_t *counter = SOUND_COUNTER;
    printf ("%s Counters %d,%d\n", __func__, counter[0], counter[1]);
    counter[0]++;
    counter[1]--;
    counter = TIMER_SIXTIETHS;

    //-------------------------------
    // 01e3  111902    ld      de,#0219
    // 01e6  010104    ld      bc,#0401
    //-------------------------------
    uint8_t *limit = DATA_0219;
    int c = 1;

    /*  Walk through 4 BCD bytes which hold timer info.  Each increasing byte is
     *  a clock order of magnitude, sixtieths, seconds, minutes and hours.  Do
     *  two comparisons for each byte, high nybble and low nybble.  If a nybble
     *  doesn't match the limit, break, otherwise increment the next digit.  The value c
     *  counts how many digits have changed.  This gives us counter limits of
     *
     *  every 6/60ths (0.1 seconds)
     *  every 60/60ths (1 second)
     *  every 10 seconds
     *  every minute
     *  evert 10 minutes
     *  every hour
     *  every 10 hours
     *
     *  The counter is 4 bytes but the limits are 8 bytes.  Presumably because
     *  RAM space is expensive but ROM not as much */
    for (int b = 0; b < 4; b++)
    {
        //-------------------------------
        // 01e9  34        inc     (hl)
        //-------------------------------
        counter[b]++;

        //-------------------------------
        // 01ea  7e        ld      a,(hl)
        // 01eb  e60f      and     #0f
        // 01ed  eb        ex      de,hl
        // 01ee  be        cp      (hl)
        // 01ef  2013      jr      nz,#0204        ; (19)
        //-------------------------------
        printf ("%s digit=%d a=%02x cmp=%02x\n", __func__, b, counter[b], *limit);
        if ((counter[b] & 0x0f) != *limit)
            break;

        //-------------------------------
        // 01f1  0c        inc     c
        // 01f2  1a        ld      a,(de)
        // 01f3  c610      add     a,#10
        // 01f5  e6f0      and     #f0
        // 01f7  12        ld      (de),a
        //-------------------------------
        c++;
        counter[b] = (counter[b] + 0x10) & 0xf0;

        //-------------------------------
        // 01f8  23        inc     hl
        // 01f9  be        cp      (hl)
        // 01fa  2008      jr      nz,#0204        ; (8)
        //-------------------------------
        limit++;
        printf ("%s digit=%d a=%02x cmp=%02x\n", __func__, b, counter[b], *limit);
        if ((counter[b] & 0xf0) != *limit)
            break;

        //-------------------------------
        // 01fc  0c        inc     c
        // 01fd  eb        ex      de,hl
        // 01fe  3600      ld      (hl),#00
        // 0200  23        inc     hl
        // 0201  13        inc     de
        // 0202  10e5      djnz    #01e9           ; (-27)
        //-------------------------------
        c++;
        counter[b] = 0;
        limit++;
    }

    //-------------------------------
    // 0204  218a4c    ld      hl,#4c8a
    // 0207  71        ld      (hl),c
    //-------------------------------
    printf ("%s %d digits updated\n", __func__, c);
    COUNTER_LIMITS_CHANGES = c;

    //-------------------------------
    // 0208  2c        inc     l
    // 0209  7e        ld      a,(hl)
    // 020a  87        add     a,a
    // 020b  87        add     a,a
    // 020c  86        add     a,(hl)
    // 020d  3c        inc     a
    // 020e  77        ld      (hl),a
    //-------------------------------
    RND_NUM_GEN1 = RND_NUM_GEN1 * 5 + 1;

    //-------------------------------
    // 020f  2c        inc     l
    // 0210  7e        ld      a,(hl)
    // 0211  87        add     a,a
    // 0212  86        add     a,(hl)
    // 0213  87        add     a,a
    // 0214  87        add     a,a
    // 0215  86        add     a,(hl)
    // 0216  3c        inc     a
    // 0217  77        ld      (hl),a
    // 0218  c9        ret     
    //-------------------------------
    RND_NUM_GEN2 = RND_NUM_GEN2 * 5 + 1;
}
 
    /*  Data related to timer counts, sixtieths of a second, seconds, minutes, hours */ 

    //-------------------------------
    // 0219  06 a0 0a 60 0a 60 0a a0 
    //-------------------------------

/*  Dispatch tasks in the queue once their timer expires.  The time value is the
 *  lower 6 bits of the delay value.  The upper 2 bits are the units
 *  (tenths of a second, seconds, 10 seconds or 1 minute) */
void dispatchISRTasks_0221 (void)
{
    //-------------------------------
    // 0221  21904c    ld      hl,#4c90
    // 0224  3a8a4c    ld      a,(#4c8a)
    // 0227  4f        ld      c,a
    // 0228  0610      ld      b,#10
    //-------------------------------
    TASK *task = (TASK*) ISR_TASKS;

    for (int b = 0; b < 0x10; b++)
    {
        //-------------------------------
        // 022a  7e        ld      a,(hl)
        // 022b  a7        and     a
        // 022c  282f      jr      z,#025d         ; (47)
        //-------------------------------
        if (task->timer != 0)
        {
            //-------------------------------
            // 022e  e6c0      and     #c0
            // 0230  07        rlca    
            // 0231  07        rlca    
            // 0232  b9        cp      c
            // 0233  3028      jr      nc,#025d        ; (40)
            //-------------------------------
            if ((task->timer >> 6) < COUNTER_LIMITS_CHANGES)
            {
                //-------------------------------
                // 0235  35        dec     (hl)
                // 0236  7e        ld      a,(hl)
                // 0237  e63f      and     #3f
                // 0239  2022      jr      nz,#025d        ; (34)
                //-------------------------------
                printf ("%s task=%d limits=%d timer=%d units=%d\n", __func__,
                        task->func, COUNTER_LIMITS_CHANGES, task->timer & 0x3f, task->timer >> 6);
                task->timer--;
                if ((task->timer & 0x3f) == 0)
                {
                    //-------------------------------
                    // 023b  77        ld      (hl),a
                    // 023c  c5        push    bc
                    // 023d  e5        push    hl
                    // 023e  2c        inc     l
                    // 023f  7e        ld      a,(hl)
                    // 0240  2c        inc     l
                    // 0241  46        ld      b,(hl)
                    // 0242  215b02    ld      hl,#025b         ; return to 025b
                    // 0245  e5        push    hl
                    //-------------------------------
                    /*  The parameter byte is fetched into register b but it
                     *  doesn't look like any of the dispatchable tasks look at
                     *  the value of b and it is never set to anything other
                     *  than 0x00 anyway so I'm ignoring it */
                    task->timer = 0;

                    //-------------------------------
                    // 0246  e7        rst     #20
                    //
                    // 0247  94 08 a3 06 8e 05 72 12 
                    // 024f  00 10 0b 10 63 02 2b 21
                    //       f0 21 b9 22
                    //
                    // 025b  e1        pop     hl
                    // 025c  c1        pop     bc
                    //-------------------------------
                    printf("%s disp tsk %d\n", __func__, task->func);
                    ASSERT (task->func < 10);
                    void (*func[])() = 
                    {
                        incLevelStateSubr_0894,
                        incMainSub2_06a3,
                        incMainStateIntro_058e,
                        incKilledState_1272,      // 3 ISRTASK_INC_KILLED_STATE
                        resetFruit_1000,
                        func_100b,
                        displayReady_0263,
                        incScene1State_212b,
                        incScene2State_212b,
                        incScene3State_22b9
                    };
                    tableCall_0020 (func, task->func);
                    /*  No return as this addr was pushed as ret addr */
                }
            }
        }

        //-------------------------------
        // 025d  2c        inc     l
        // 025e  2c        inc     l
        // 025f  2c        inc     l
        // 0260  10c8      djnz    #022a           ; (-56)
        //-------------------------------
        task++;
    }
    //-------------------------------
    // 0262  c9        ret     
    //-------------------------------
}

void displayReady_0263 (void)
{
    //-------------------------------
    // 0263  ef        rst     #28
    // 0264  1c86
    // 0266  c9        ret     
    //-------------------------------
    schedTask(TASK_DISPLAY_MSG, 0x80 | MSG_READY);
}

/*  Check/debounce coin inputs */
void checkCoinInput_0267 (void)
{
    //-------------------------------
    // 0267  3a6e4e    ld      a,(#4e6e)
    // 026a  fe99      cp      #99
    // 026c  17        rla     
    // 026d  320650    ld      (#5006),a
    // 0270  1f        rra     
    // 0271  d0        ret     nc
    //-------------------------------
    COINLOCKOUT = CREDITS<<1;

    if (CREDITS >= 99)
        return;

    //-------------------------------
    // 0272  3a0050    ld      a,(#5000)            ; read IN0
    // 0275  47        ld      b,a
    // 0276  cb00      rlc     b                    ; Move MSB (CREDIT) to carry flag
    // 0278  3a664e    ld      a,(#4e66)
    // 027b  17        rla                          ; Rotate carry flag to LSB
    // 027c  e60f      and     #0f
    // 027e  32664e    ld      (#4e66),a
    //-------------------------------
    SERVICE1_DEBOUNCE = ((SERVICE1_DEBOUNCE<<1) & 0x0f) | (IN0_CREDIT?1:0);

    //-------------------------------
    // 0281  d60c      sub     #0c
    // 0283  ccdf02    call    z,#02df		; Add Coin
    //-------------------------------
    if (SERVICE1_DEBOUNCE ==12)
        checkCoinCredit_02df();

    //-------------------------------
    // 0286  cb00      rlc     b                    ; Move MSB (COIN2) to carry flag
    // 0288  3a674e    ld      a,(#4e67)
    // 028b  17        rla     
    // 028c  e60f      and     #0f
    // 028e  32674e    ld      (#4e67),a
    //-------------------------------
    COIN2_DEBOUNCE = ((COIN2_DEBOUNCE<<1)&0x0f) | (IN0_COIN2?1:0);

    //-------------------------------
    // 0291  d60c      sub     #0c
    // 0293  c29a02    jp      nz,#029a
    // 0296  21694e    ld      hl,#4e69
    // 0299  34        inc     (hl)
    //-------------------------------
    if (COIN2_DEBOUNCE == 0xc)
        COIN_COUNTER++;

    //-------------------------------
    // 029a  cb00      rlc     b                    ; Move MSB (COIN1) to carry flag
    // 029c  3a684e    ld      a,(#4e68)
    // 029f  17        rla     
    // 02a0  e60f      and     #0f
    //-------------------------------
    COIN1_DEBOUNCE = ((COIN1_DEBOUNCE<<1)&0x0f) | (IN0_COIN1?1:0);

    //-------------------------------
    // 02a2  32684e    ld      (#4e68),a
    // 02a5  d60c      sub     #0c
    // 02a7  c0        ret     nz
    //-------------------------------
    if (COIN1_DEBOUNCE != 0xc)
        return;

    //-------------------------------
    // 02a8  21694e    ld      hl,#4e69
    // 02ab  34        inc     (hl)
    // 02ac  c9        ret     
    //-------------------------------
    printf ("** coin added\n");
    COIN_COUNTER++;
}

void checkCoinCounterTimeout_02ad (void)
{
    //-------------------------------
    // 02ad  3a694e    ld      a,(#4e69)
    // 02b0  a7        and     a
    // 02b1  c8        ret     z
    //-------------------------------
    if (COIN_COUNTER == 0)
        return;

    //-------------------------------
    // 02b2  47        ld      b,a
    // 02b3  3a6a4e    ld      a,(#4e6a)
    // 02b6  5f        ld      e,a
    // 02b7  fe00      cp      #00
    // 02b9  c2c402    jp      nz,#02c4
    //-------------------------------
    if (COIN_COUNTER_TIMEOUT == 0)
    {
        //-------------------------------
        // 02bc  3e01      ld      a,#01
        // 02be  320750    ld      (#5007),a    ; coin counter = 1
        // 02c1  cddf02    call    #02df
        //-------------------------------
        COIN_COUNTER = 1;
        checkCoinCredit_02df ();
    }

    //-------------------------------
    // 02c4  7b        ld      a,e
    // 02c5  fe08      cp      #08
    // 02c7  c2ce02    jp      nz,#02ce
    //-------------------------------
    if (COIN_COUNTER_TIMEOUT == 8)
    {
        //-------------------------------
        // 02ca  af        xor     a
        // 02cb  320750    ld      (#5007),a    ; zero coin counter
        //-------------------------------
        COINCOUNTER = 0;
    }

    //-------------------------------
    // 02ce  1c        inc     e
    // 02cf  7b        ld      a,e
    // 02d0  326a4e    ld      (#4e6a),a
    //-------------------------------
    COIN_COUNTER_TIMEOUT++;

    //-------------------------------
    // 02d3  d610      sub     #10
    // 02d5  c0        ret     nz
    //-------------------------------
    if (COIN_COUNTER_TIMEOUT != 0x10)
        return;

    //-------------------------------
    // 02d6  326a4e    ld      (#4e6a),a
    // 02d9  05        dec     b
    // 02da  78        ld      a,b
    // 02db  32694e    ld      (#4e69),a
    // 02de  c9        ret     
    //-------------------------------
    COIN_COUNTER_TIMEOUT -= 0x10;
    COIN_COUNTER--;
}

/* Coins -> credits routine */
void checkCoinCredit_02df (void)
{
    //-------------------------------
    // 02df  3a6b4e    ld      a,(#4e6b)		; #coins per #credits 
    // 02e2  216c4e    ld      hl,#4e6c		; #leftover coins 
    // 02e5  34        inc     (hl)			; add 1 
    // 02e6  96        sub     (hl)
    // 02e7  c0        ret     nz			; not enough coins for credit 
    // 02e8  77        ld      (hl),a		; store leftover coins 
    //-------------------------------
    if (++PARTIAL_CREDIT < COINS_PER_CREDIT)
        return;

    PARTIAL_CREDIT -= COINS_PER_CREDIT;

    //-------------------------------
    // 02e9  3a6d4e    ld      a,(#CREDITS_PER_COIN)		; #credits per #coins 
    // 02ec  216e4e    ld      hl,#4e6e	; #credits 
    // 02ef  86        add     a,(hl)		; add # credits 
    // 02f0  27        daa     
    // 02f1  d2f602    jp      nc,#02f6
    // 02f4  3e99      ld      a,#99
    // 02f6  77        ld      (hl),a		; store #credits, max 99 
    //-------------------------------
    CREDITS += CREDITS_PER_COIN;

    if (CREDITS > 99)
        CREDITS = 99;

    //-------------------------------
    // 02f7  219c4e    ld      hl,#4e9c
    // 02fa  cbce      set     1,(hl)		; set bit 1 of 4e9c 
    // 02fc  c9        ret     
    //-------------------------------
    CH1_SOUND_EFFECT->mask |= 2;
}

void showStartNumPlayers_02fd (void)
{
    //-------------------------------
    // 02fd  21ce4d    ld      hl,#4dce
    // 0300  34        inc     (hl)
    // 0301  7e        ld      a,(hl)
    // 0302  e60f      and     #0f
    // 0304  201f      jr      nz,#0325        ; (31)
    //-------------------------------
    int a = COIN_TIMER++;

    if ((a & 0xf) == 0)
    {
        //-------------------------------
        // 0306  7e        ld      a,(hl)
        // 0307  0f        rrca    
        // 0308  0f        rrca    
        // 0309  0f        rrca    
        // 030a  0f        rrca    
        //-------------------------------
        int b = (a>>4) | ((a&0xf)<<4);

        //-------------------------------
        // 030b  47        ld      b,a
        // 030c  3ad64d    ld      a,(#4dd6)
        // 030f  2f        cpl     
        // 0310  b0        or      b
        //-------------------------------
        b |= ~WAIT_START_BUTTON;

        //-------------------------------
        // 0311  4f        ld      c,a
        // 0312  3a6e4e    ld      a,(#4e6e)
        // 0315  d601      sub     #01
        // 0317  3002      jr      nc,#031b        ; (2)
        //-------------------------------
        int c = b;

        if (CREDITS < 1)
        {
            //-------------------------------
            // 0319  af        xor     a
            // 031a  4f        ld      c,a
            a = c = 0;
        }
        // 031b  2801      jr      z,#031e         ; (1)
        // 031d  79        ld      a,c
        //-------------------------------
        else if (CREDITS != 1)
        {
            a = c;
        }
        //-------------------------------
        // 031e  320550    ld      (#5005),a
        // 0321  79        ld      a,c
        // 0322  320450    ld      (#5004),a
        //-------------------------------
        P1START = a;
        P2START = c;
    }

    //-------------------------------
    // 0325  dd21d843  ld      ix,#43d8
    // 0329  fd21c543  ld      iy,#43c5
    // 032d  3a004e    ld      a,(#4e00)
    // 0330  fe03      cp      #03
    // 0332  ca4403    jp      z,#0344
    //-------------------------------
    uint8_t *ix = &SCREEN[0x3d8];
    uint8_t *iy = &SCREEN[0x3c5];
    if (MAIN_STATE != MAIN_STATE_PLAY)
    {
        //-------------------------------
        // 0335  3a034e    ld      a,(#4e03)
        // 0338  fe02      cp      #02
        // 033a  d24403    jp      nc,#0344
        //-------------------------------
        if (CREDIT_STATE < CREDIT_STATE_PLAYER1_READY)
        {
            //-------------------------------
            // 033d  cd6903    call    #0369
            // 0340  cd7603    call    #0376
            // 0343  c9        ret     
            //-------------------------------
            oneUp_0369 (ix);
            twoUp_0376 (iy);
            return;
        }
    }

    //-------------------------------
    // 0344  3a094e    ld      a,(#4e09)
    // 0347  a7        and     a
    // 0348  3ace4d    ld      a,(#4dce)
    // 034b  c25903    jp      nz,#0359
    //-------------------------------
    if (PLAYER == 0)
    {
        //-------------------------------
        // 034e  cb67      bit     4,a
        // 0350  cc6903    call    z,#0369
        // 0353  c48303    call    nz,#0383
        // 0356  c36103    jp      #0361
        //-------------------------------
        if ((COIN_TIMER & 0x10) == 0)
            oneUp_0369 (ix);
        else
            oneBlank_0383 (ix);
    }
    else
    {
        //-------------------------------
        // 0359  cb67      bit     4,a
        // 035b  cc7603    call    z,#0376
        // 035e  c49003    call    nz,#0390
        //-------------------------------
        if ((COIN_TIMER & 0x10) == 0)
            twoUp_0376 (iy);
        else
            twoBlank_0390 (iy);
    }

    //-------------------------------
    // 0361  3a704e    ld      a,(#4e70)
    // 0364  a7        and     a
    // 0365  cc9003    call    z,#0390
    // 0368  c9        ret     
    //-------------------------------
    if (!TWO_PLAYERS)
        twoBlank_0390 (iy);
}

/* Display "1UP" */
void oneUp_0369 (uint8_t *ix)
{
    //-------------------------------
    // 0369  dd360050  ld      (ix+#00),#50
    // 036d  dd360155  ld      (ix+#01),#55
    // 0371  dd360231  ld      (ix+#02),#31
    // 0375  c9        ret     
    //-------------------------------
    *ix = 0x50;
    *(ix+1) = 0x55;
    *(ix+2) = 0x31;
}

/* Display "2UP" */
void twoUp_0376 (uint8_t *iy)
{
    //-------------------------------
    // 0376  fd360050  ld      (iy+#00),#50
    // 037a  fd360155  ld      (iy+#01),#55
    // 037e  fd360232  ld      (iy+#02),#32
    // 0382  c9        ret     
    //-------------------------------
    *iy = 0x50;
    *(iy+1) = 0x55;
    *(iy+2) = 0x31;
}

void oneBlank_0383 (uint8_t *ix)
{
    //-------------------------------
    // 0383  dd360040  ld      (ix+#00),#40
    // 0387  dd360140  ld      (ix+#01),#40
    // 038b  dd360240  ld      (ix+#02),#40
    // 038f  c9        ret     
    //-------------------------------
    *ix = *(ix+1) = *(ix+2) = 0x40;
}

void twoBlank_0390 (uint8_t *iy)
{
    //-------------------------------
    // 0390  fd360040  ld      (iy+#00),#40
    // 0394  fd360140  ld      (iy+#01),#40
    // 0398  fd360240  ld      (iy+#02),#40
    // 039c  c9        ret     
    //-------------------------------
    *iy = *(iy+1) = *(iy+2) = 0x40;
}

void func_039d (void)
{
    //-------------------------------
    // 039d  3a064e    ld      a,(#4e06)
    // 03a0  d605      sub     #05
    // 03a2  d8        ret     c
    //-------------------------------
    if (SCENE1_STATE < 5)
        return;

    //-------------------------------
    // 03a3  2a084d    ld      hl,(#4d08)
    // 03a6  0608      ld      b,#08
    // 03a8  0e10      ld      c,#10
    // 03aa  7d        ld      a,l
    // 03ab  32064d    ld      (#4d06),a
    // 03ae  32d24d    ld      (#4dd2),a
    //-------------------------------
    CLYDE_POS.y = 
    FRUIT_POS.y = PACMAN_POS.y;

    //-------------------------------
    // 03b1  91        sub     c
    // 03b2  32024d    ld      (#4d02),a
    // 03b5  32044d    ld      (#4d04),a
    //-------------------------------
    PINKY_POS.y = 
    INKY_POS.y = PACMAN_POS.y - 16;

    //-------------------------------
    // 03b8  7c        ld      a,h
    // 03b9  80        add     a,b
    // 03ba  32034d    ld      (#4d03),a
    // 03bd  32074d    ld      (#4d07),a
    //-------------------------------
    PINKY_POS.x = 
    CLYDE_POS.x = PACMAN_POS.x + 8;

    //-------------------------------
    // 03c0  91        sub     c
    // 03c1  32054d    ld      (#4d05),a
    // 03c4  32d34d    ld      (#4dd3),a
    // 03c7  c9        ret     
    //-------------------------------
    INKY_POS.x = 
    FRUIT_POS.x = PACMAN_POS.x - 8;
}

/*  MAIN_STATE has 4 states.  Call a func for the state */
void mainStateMachine_03c8 (void)
{
    //-------------------------------
    // 03c8  3a004e    ld      a,(#4e00)
    // 03cb  e7        rst     #20
    //
    // 03cc  d403
    // 03ce  fe03
    // 03d0  e505
    // 03d2  be06
    //-------------------------------
    void (*func[])() = 
    {
        resetStateMachine_03d4,
        introStateMachine_03fe,
        coinInsertedStateMachine_05e5,
        playGameStateMachine_06be
    };
    tableCall_0020 (func, MAIN_STATE);
}

/*  4e00 ==0, switch 4e01 */
void resetStateMachine_03d4 (void)
{
    //-------------------------------
    // 03d4  3a014e    ld      a,(#4e01) 
    // 03d7  e7        rst     #20
    //
    // 03d8  dc03
    // 03da  0c00
    //-------------------------------
    void (*func[])() = 
    {
        initResetGame_03dc,
        nothing_000c
    };
    tableCall_0020 (func, RESET_STATE);
}

/*  4e00 ==0 && 4e01 == 0 => 4e01=1 */
void initResetGame_03dc (void)
{
    //-------------------------------
    // 03dc  ef        rst     #28
    // 03dd  0000
    // 03df  ef        rst     #28
    // 03e0  0600
    // 03e2  ef        rst     #28
    // 03e3  0100
    // 03e5  ef        rst     #28
    // 03e6  1400
    // 03e8  ef        rst     #28
    // 03e9  1800
    // 03eb  ef        rst     #28
    // 03ec  0400
    // 03ee  ef        rst     #28
    // 03ef  1e00
    // 03f1  ef        rst     #28
    // 03f2  0700
    //-------------------------------
    schedTask (TASK_CLEAR_SCREEN, 0);
    schedTask (TASK_CLEAR_COLOUR, 0);
    schedTask (TASK_MAZE_COLOURS, 0);
    schedTask (TASK_CONFIGURE_GAME, 0);
    schedTask (TASK_CLEAR_SCORES, 0);
    schedTask (TASK_INIT_POSITIONS, 0);
    schedTask (TASK_RESET_POSITIONS, 0);
    schedTask (TASK_RESET_GAME_STATE, 0);

    //-------------------------------
    // 03f4  21014e    ld      hl,#4e01
    // 03f7  34        inc     (hl)
    // 03f8  210150    ld      hl,#5001
    // 03fb  3601      ld      (hl),#01
    // 03fd  c9        ret     
    //-------------------------------
    RESET_STATE++;
    SOUNDENABLE = 1;
}

void introStateMachine_03fe (void)
{
    //-------------------------------
    // 03fe  cda12b    call    #2ba1			; Write # credits on screen
    //-------------------------------
    displayCredits_2ba1();

    //-------------------------------
    // 0401  3a6e4e    ld      a,(#4e6e)
    // 0404  a7        and     a
    // 0405  280c      jr      z,#0413			; No credits -> 0x13
    //-------------------------------
    if (CREDITS != 0)
    {
        //-------------------------------
        // 0407  af        xor     a
        // 0408  32044e    ld      (#4e04),a
        // 040b  32024e    ld      (#4e02),a
        // 040e  21004e    ld      hl,#4e00
        // 0411  34        inc     (hl)
        // 0412  c9        ret     
        //-------------------------------

        INTRO_STATE = LEVEL_STATE = 0;
        MAIN_STATE++;
        return;
    }

    //-------------------------------
    // 0413  3a024e    ld      a,(#4e02)
    // 0416  e7        rst     #20
    //
    // 0417                       5f  04 0c 00 71 04 0c 00 7f
    // 0420  04 0c 00 85 04 0c 00 8b  04 0c 00 99 04 0c 00 9f
    // 0430  04 0c 00 a5 04 0c 00 b3  04 0c 00 b9 04 0c 00 bf
    // 0440  04 0c 00 cd 04 0c 00 d3  04 0c 00 d8 04 0c 00 e0
    // 0450  04 0c 00 1c 05 4b 05 56  05 61 05 6c 05 7c 05 
    //-------------------------------
    void (*func[])() = 
    {
        introStart_045f, nothing_000c,
        introduceBlinky_0471, nothing_000c,   // state 2
        introduceShadow_047f, nothing_000c,
        introduceBlinky_0485, nothing_000c,   // 6
        introducePinky_048b, nothing_000c,
        introduceSpeedy_0499, nothing_000c,   // 10
        introducePinky_049f, nothing_000c,    // 12
        introduceInky_04a5, nothing_000c,
        introduceBashful_04b3, nothing_000c,
        introduceInky_04b9, nothing_000c,
        introduceClyde_04bf, nothing_000c,    // 20
        introduceClyde_04cd, nothing_000c,    // 22
        selectDisplayClydeName_04d3, nothing_000c,
        introducePoints_04d8, nothing_000c,
        introSceneSetup_04e0, nothing_000c,              // 28
        introStartMoveBlinky_051c,            // 30
        introStartMovePinky_054b,             // 31
        introStartMoveInky_0556,              // 32
        introStartMoveClyde_0561,             // 33
        introCheckAllGhostsEaten_056c,
        introFinalTBD_057c
    };
    tableCall_0020 (func, INTRO_STATE);
}

void introStart_045f (void)
{
    //-------------------------------
    // 045f  ef        rst     #28
    // 0460  0001
    //       ef        rst     #28
    //       0100
    // 0465  ef        rst     #28
    // 0466  0400
    // 0468  ef        rst     #28
    // 0469  1e00
    //-------------------------------
    schedTask (TASK_CLEAR_SCREEN, 1);
    schedTask (TASK_MAZE_COLOURS, 0);
    schedTask (TASK_INIT_POSITIONS, 0);
    schedTask (TASK_RESET_POSITIONS, 0);

    //-------------------------------
    // 046b  0e0c      ld      c,#0c
    // 046d  cd8505    call    #0585
    // 0470  c9        ret     
    //-------------------------------
    displayIntroMsg_0585 (MSG_NICKNAME);
}

void introduceBlinky_0471 (void)
{
    //-------------------------------
    // 0471  210443    ld      hl,#4304
    // 0474  3e01      ld      a,#01
    // 0476  cdbf05    call    #05bf
    // 0479  0e0c      ld      c,#0c
    // 047b  cd8505    call    #0585
    // 047e  c9        ret     
    //-------------------------------
    drawGhost_05bf(0x304, 1);
    displayIntroMsg_0585 (MSG_NICKNAME);
}

void introduceShadow_047f (void)
{
    //-------------------------------
    // 047f  0e14      ld      c,#14
    // 0481  cd9305    call    #0593
    // 0484  c9        ret     
    //-------------------------------
    introduceGhost_0593(0x14);
}

void introduceBlinky_0485 (void)
{
    //-------------------------------
    // 0485  0e0d      ld      c,#0d
    // 0487  cd9305    call    #0593
    // 048a  c9        ret     
    //-------------------------------
    introduceGhost_0593(0xd);
}

void introducePinky_048b (void)
{
    //-------------------------------
    // 048b  210743    ld      hl,#4307
    // 048e  3e03      ld      a,#03
    // 0490  cdbf05    call    #05bf
    // 0493  0e0c      ld      c,#0c
    // 0495  cd8505    call    #0585
    // 0498  c9        ret     
    //-------------------------------
    drawGhost_05bf(0x307, 3);
    displayIntroMsg_0585 (MSG_NICKNAME);
}

void introduceSpeedy_0499 (void)
{ 
    //-------------------------------
    // 0499  0e16      ld      c,#16
    // 049b  cd9305    call    #0593
    // 049e  c9        ret     
    //-------------------------------
    introduceGhost_0593(0x16);
}

void introducePinky_049f (void)
{
    //-------------------------------
    // 049f  0e0f      ld      c,#0f
    // 04a1  cd9305    call    #0593
    // 04a4  c9        ret     
    //-------------------------------
    introduceGhost_0593(0xf);
}

void introduceInky_04a5 (void)
{
    //-------------------------------
    // 04a5  210a43    ld      hl,#430a
    // 04a8  3e05      ld      a,#05
    // 04aa  cdbf05    call    #05bf
    // 04ad  0e0c      ld      c,#0c
    // 04af  cd8505    call    #0585
    // 04b2  c9        ret     
    //-------------------------------
    drawGhost_05bf(0x30a,5);
    displayIntroMsg_0585 (MSG_NICKNAME);
}

void introduceBashful_04b3 (void)
{
    //-------------------------------
    // 04b3  0e33      ld      c,#33
    // 04b5  cd9305    call    #0593
    // 04b8  c9        ret     
    //-------------------------------
    introduceGhost_0593(0x33);
}

void introduceInky_04b9 (void)
{
    //-------------------------------
    // 04b9  0e2f      ld      c,#2f
    // 04bb  cd9305    call    #0593
    // 04be  c9        ret     
    //-------------------------------
    introduceGhost_0593(0x2f);
}

void introduceClyde_04bf (void)
{
    //-------------------------------
    // 04bf  210d43    ld      hl,#430d
    // 04c2  3e07      ld      a,#07
    // 04c4  cdbf05    call    #05bf
    // 04c7  0e0c      ld      c,#0c
    // 04c9  cd8505    call    #0585
    // 04cc  c9        ret     
    //-------------------------------
    drawGhost_05bf(0x30d,7);
    displayIntroMsg_0585 (MSG_NICKNAME);
}

void introduceClyde_04cd (void)
{
    //-------------------------------
    // 04cd  0e35      ld      c,#35
    // 04cf  cd9305    call    #0593
    // 04d2  c9        ret     
    //-------------------------------
    introduceGhost_0593(0x35);
}

void selectDisplayClydeName_04d3 (void)
{
    //-------------------------------
    // 04d3  0e31      ld      c,#31
    // 04d5  c38005    jp      #0580
    //-------------------------------
    selectDisplayGhostName_0580(0x31);
}

void introducePoints_04d8 (void)
{
    //-------------------------------
    // 04d8  ef        rst     #28
    // 04d9  1c11
    //-------------------------------
    schedTask (TASK_DISPLAY_MSG, MSG_10PTS);

    //-------------------------------
    //       0e12      ld      c,0x12
    // 04dd  c38505    jp      #0585
    //-------------------------------
    displayIntroMsg_0585 (MSG_50PTS);
}

void introSceneSetup_04e0 (void)
{
    //-------------------------------
    // 04e0  0e13      ld      c,#13
    // 04e2  cd8505    call    #0585
    //-------------------------------
    displayIntroMsg_0585 (MSG_COPYRIGHT2);

    //-------------------------------
    // 04e5  cd7908    call    #0879
    // 04e8  35        dec     (hl)
    //-------------------------------
    resetPlayerParams_0879();
    LEVEL_STATE--;

    //-------------------------------
    // 04e9  ef        rst     #28
    // 04ea  1100
    // 04ec  ef        rst     #28
    // 04ed  0501
    // 04ef  ef        rst     #28
    // 04f0  1014
    // 04f2  ef        rst     #28
    // 04f3  0401
    //-------------------------------
    schedTask (TASK_CLEAR_GHOST_STATE, 0);
    schedTask (TASK_BLINKY_SUBSTATE, SUBSTATE_CHASE);
    schedTask (TASK_SETUP_GHOST_TIMERS, 20);
    schedTask (TASK_INIT_POSITIONS, 1);

    //-------------------------------
    // 04f5  3e01      ld      a,#01
    // 04f7  32144e    ld      (#4e14),a
    // 04fa  af        xor     a
    // 04fb  32704e    ld      (#4e70),a
    // 04fe  32154e    ld      (#4e15),a
    //-------------------------------
    P1_REAL_LIVES = 0;
    TWO_PLAYERS = 0;
    P1_DISPLAY_LIVES = 0;

    //-------------------------------
    // 0501  213243    ld      hl,#4332
    // 0504  3614      ld      (hl),#14
    //-------------------------------
    SCREEN[0x332] = CHAR_POWERUP;
    demoMazeHorizontal_0506();
}

/*  Create a hidden (no colour) horizontal maze pair at rows 0x11 and 0x13 to
 *  guide pacman and the ghosts along row 0x12 for the intro demo */
void demoMazeHorizontal_0506 (void)
{
    //-------------------------------
    // 0506  3efc      ld      a,#fc
    // 0508  112000    ld      de,#0020
    // 050b  061c      ld      b,#1c
    // 050d  dd214040  ld      ix,#4040
    //-------------------------------
    int ix = 0x40;
    for (int b = 0; b < 0x1c; b++)
    {
        //-------------------------------
        // 0511  dd7711    ld      (ix+#11),a
        // 0514  dd7713    ld      (ix+#13),a
        // 0517  dd19      add     ix,de
        // 0519  10f6      djnz    #0511           ; (-10)
        //-------------------------------
        SCREEN[ix+0x11] = 0xfc;
        SCREEN[ix+0x13] = 0xfc;
        ix+= 0x20;
    }
    //-------------------------------
    // 051b  c9        ret     
    //-------------------------------
}

void introStartMoveBlinky_051c (void)
{
    //-------------------------------
    // 051c  21a04d    ld      hl,#4da0
    // 051f  0621      ld      b,#21
    // 0521  3a3a4d    ld      a,(#4d3a)
    //-------------------------------
    introAdvanceState_0524 (&BLINKY_SUBSTATE, 0x21, PACMAN_TILE2.x);
}

/*  Advance the intro state and update the ghost substate to chase when a ghost
 *  (or pacman) reaches a specified x tile. */
void introAdvanceState_0524 (uint8_t *ghostSubstate, int target, int tile)
{
    //-------------------------------
    // 0524  90        sub     b
    // 0525  2005      jr      nz,#052c        ; (5)
    // 0527  3601      ld      (hl),#01
    // 0529  c38e05    jp      #058e
    //-------------------------------
    // printf ("%s a = %d b=%d\n", __func__, a, b);
    if (tile != target)
    {
        introMain_052c();
        return;
    }

    // printf ("%s %04lx = 1\n", __func__, hl-MEM);
    *ghostSubstate = SUBSTATE_CHASE;
    incMainStateIntro_058e();
    return;
}

void introMain_052c (void)
{
    //-------------------------------
    // 052c  cd1710    call    #1017
    // 052f  cd1710    call    #1017
    // 0532  cd230e    call    #0e23
    // 0535  cd0d0c    call    #0c0d
    // 0538  cdd60b    call    #0bd6
    // 053b  cda505    call    #05a5
    // 053e  cdfe1e    call    #1efe
    // 0541  cd251f    call    #1f25
    // 0544  cd4c1f    call    #1f4c
    // 0547  cd731f    call    #1f73
    // 054a  c9        ret     
    //-------------------------------
    updateGhostStates_1017(); 
    updateGhostStates_1017(); 
    toggleGhostAnimation_0e23();
    flashPowerups_0c0d();
    setGhostColour_0bd6();
    pacmanReverse_05a5();
    blinkyCheckReverse_1efe();
    pinkyCheckReverse_1f25();
    inkyCheckReverse_1f4c();
    clydeCheckReverse_1f73();
}

void introStartMovePinky_054b (void)
{
    //-------------------------------
    // 054b  21a14d    ld      hl,#4da1
    // 054e  0620      ld      b,#20
    // 0550  3a324d    ld      a,(#4d32)
    // 0553  c32405    jp      #0524
    //-------------------------------
    introAdvanceState_0524 (&PINKY_SUBSTATE, 0x20, BLINKY_TILE2.x);
}

void introStartMoveInky_0556 (void)
{
    //-------------------------------
    // 0556  21a24d    ld      hl,#4da2
    // 0559  0622      ld      b,#22
    // 055b  3a324d    ld      a,(#4d32)
    // 055e  c32405    jp      #0524
    //-------------------------------
    introAdvanceState_0524 (&INKY_SUBSTATE, 0x22, BLINKY_TILE2.x);
}

void introStartMoveClyde_0561 (void)
{
    //-------------------------------
    // 0561  21a34d    ld      hl,#4da3
    // 0564  0624      ld      b,#24
    // 0566  3a324d    ld      a,(#4d32)
    // 0569  c32405    jp      #0524
    //-------------------------------
    introAdvanceState_0524 (&CLYDE_SUBSTATE, 0x24, BLINKY_TILE2.x);
}

void introCheckAllGhostsEaten_056c (void)
{
    //-------------------------------
    // 056c  3ad04d    ld      a,(#4dd0)
    // 056f  47        ld      b,a
    // 0570  3ad14d    ld      a,(#4dd1)
    // 0573  80        add     a,b
    // 0574  fe06      cp      #06
    // 0576  ca8e05    jp      z,#058e
    //-------------------------------
    if (KILLED_COUNT + KILLED_STATE == 6)
    {
        incMainStateIntro_058e();
        return;
    }

    //-------------------------------
    // 0579  c32c05    jp      #052c
    //-------------------------------
    introMain_052c();
}

void introFinalTBD_057c (void)
{
    printf ("%s lss=%d\n", __func__, LEVEL_STATE);
    //-------------------------------
    // 057c  cdbe06    call    #06be
    // 057f  c9        ret     
    //-------------------------------
    playGameStateMachine_06be();
}

void selectDisplayGhostName_0580(int c)
{
    //-------------------------------
    // 0580  3a754e    ld      a,(#4e75)
    // 0583  81        add     a,c
    // 0584  4f        ld      c,a
    //-------------------------------
    c += GHOST_NAMES_MODE;

    /*  Asm continues on but 585 is also called as a function, so we also define
     *  as a function and call it */
    displayIntroMsg_0585(c);
}

void displayIntroMsg_0585(int c)
{
    //-------------------------------
    // 0585  061c      ld      b,#1c
    // 0587  cd4200    call    #0042
    //-------------------------------
    addTask_0042 (TASK_DISPLAY_MSG, c);

    //-------------------------------
    // 058a  f7        rst     #30
    // 058b  4a0200
    //-------------------------------
    schedISRTask (0x4a, ISRTASK_INC_INTRO_STATE, 0x00);

    incMainStateIntro_058e();
}

void incMainStateIntro_058e(void)
{
    //-------------------------------
    // 058e  21024e    ld      hl,#4e02
    // 0591  34        inc     (hl)
    // 0592  c9        ret     
    //-------------------------------
    INTRO_STATE++;
}

void introduceGhost_0593 (int c)
{
    //-------------------------------
    // 0593  3a754e    ld      a,(#4e75)
    // 0596  81        add     a,c
    // 0597  4f        ld      c,a
    // 0598  061c      ld      b,#1c
    // 059a  cd4200    call    #0042
    //-------------------------------
    addTask_0042 (TASK_DISPLAY_MSG, c+GHOST_NAMES_MODE);

    //-------------------------------
    // 059d  f7        rst     #30
    // 059e  450200
    // 05a1  cd8e05    call    #058e
    // 05a4  c9        ret     
    //-------------------------------
    schedISRTask (0x45, ISRTASK_INC_INTRO_STATE, 0x00);
    incMainStateIntro_058e();
}

XYPOS pacmanReverse_05a5 (void)
{
    printf ("%s \n", __func__);
    //-------------------------------
    // 05a5  3ab54d    ld      a,(#4db5)
    // 05a8  a7        and     a
    // 05a9  c8        ret     z
    //-------------------------------
    XYPOS vector = { 0, 0 };

    printf ("%s orient chg = %d\n", __func__, PACMAN_ORIENT_CHG_FLAG);
    if (PACMAN_ORIENT_CHG_FLAG == 0)
        return vector;

    //-------------------------------
    // 05aa  af        xor     a
    // 05ab  32b54d    ld      (#4db5),a
    //-------------------------------
    PACMAN_ORIENT_CHG_FLAG = 0;

    //-------------------------------
    // 05ae  3a304d    ld      a,(#4d30)
    // 05b1  ee02      xor     #02
    // 05b3  323c4d    ld      (#4d3c),a
    //-------------------------------
    PACMAN_DESIRED_ORIENTATION = PACMAN_ORIENTATION ^ 2;

    //-------------------------------
    // 05b6  47        ld      b,a
    // 05b7  21ff32    ld      hl,#32ff
    // 05ba  df        rst     #18
    // 05bb  22264d    ld      (#4d26),hl
    // 05be  c9        ret     
    //-------------------------------
    vector = MOVE_VECTOR_DATA[PACMAN_DESIRED_ORIENTATION];
    PACMAN_VECTOR2 = vector;
    return vector;
}

/*  Draws the ghosts on the intro screen.  Same characters are used for each
 *  ghost but the colour varies.
 *
 *  hl = offset into video buffer, a = colour */
void drawGhost_05bf (int hl, int a)
{
    //-------------------------------
    // 05bf  36b1      ld      (hl),#b1
    // 05c1  2c        inc     l
    // 05c2  36b3      ld      (hl),#b3
    // 05c4  2c        inc     l
    // 05c5  36b5      ld      (hl),#b5
    //-------------------------------
    SCREEN[hl++] = 0xb1;
    SCREEN[hl++] = 0xb3;
    SCREEN[hl] = 0xb5;

    //-------------------------------
    // 05c7  011e00    ld      bc,#001e
    // 05ca  09        add     hl,bc
    //-------------------------------
    hl += 0x1e;

    //-------------------------------
    // 05cb  36b0      ld      (hl),#b0
    // 05cd  2c        inc     l
    // 05ce  36b2      ld      (hl),#b2
    // 05d0  2c        inc     l
    // 05d1  36b4      ld      (hl),#b4
    //-------------------------------
    SCREEN[hl++] = 0xb0;
    SCREEN[hl++] = 0xb2;
    SCREEN[hl] = 0xb4;

    //-------------------------------
    // 05d3  110004    ld      de,#0400
    // 05d6  19        add     hl,de
    // 05d7  77        ld      (hl),a
    // 05d8  2d        dec     l
    // 05d9  77        ld      (hl),a
    // 05da  2d        dec     l
    // 05db  77        ld      (hl),a
    //-------------------------------
    /*  ASM adds 0x400 to move to colour table, we just used it is an array */
    COLOUR[hl--] = a;
    COLOUR[hl--] = a;
    COLOUR[hl] = a;

    //-------------------------------
    // 05dc  a7        and     a
    // 05dd  ed42      sbc     hl,bc
    //-------------------------------
    hl -= 0x1e;

    //-------------------------------
    // 05df  77        ld      (hl),a
    // 05e0  2d        dec     l
    // 05e1  77        ld      (hl),a
    // 05e2  2d        dec     l
    // 05e3  77        ld      (hl),a
    // 05e4  c9        ret     
    //-------------------------------
    COLOUR[hl--] = a;
    COLOUR[hl--] = a;
    COLOUR[hl] = a;
}

void coinInsertedStateMachine_05e5 (void)
{
    //-------------------------------
    // 05e5  3a034e    ld      a,(#4e03)
    // 05e8  e7        rst     #20
    //
    // 05e9  f305 1b06 7406 0c00
    // 05f1  a806
    //-------------------------------
    void (*func[])() =
    {
        pushStartMsg_05f3,
        checkStartButtons,
        player1ReadyMsg_0674,
        nothing_000c,
        creditStateReset_06a8
    };
    tableCall_0020 (func, CREDIT_STATE);
}

void pushStartMsg_05f3 (void)
{
    //-------------------------------
    // 05f3  cda12b    call    #2ba1
    //-------------------------------
    displayCredits_2ba1();

    //-------------------------------
    // 05f6  ef        rst     #28
    // 05f7  0001
    //       ef        rst     #28
    //       0100
    // 05fc  ef        rst     #28
    // 05fd  1c07
    // 05ff  ef        rst     #28
    // 0600  1c0b
    // 0602  ef        rst     #28
    // 0603  1e00
    //-------------------------------
    schedTask (TASK_CLEAR_SCREEN, 1);
    schedTask (TASK_MAZE_COLOURS, 0);
    schedTask (TASK_DISPLAY_MSG, MSG_PUSHSTART);
    schedTask (TASK_DISPLAY_MSG, MSG_COPYRIGHT1);
    schedTask (TASK_RESET_POSITIONS, 0);

    //-------------------------------
    // 0605  21034e    ld      hl,#4e03
    // 0608  34        inc     (hl)
    // 0609  3e01      ld      a,#01
    // 060b  32d64d    ld      (#4dd6),a
    //-------------------------------
    CREDIT_STATE++;
    WAIT_START_BUTTON = 1;

    //-------------------------------
    // 060e  3a714e    ld      a,(#4e71)
    // 0611  feff      cp      #ff
    // 0613  c8        ret     z
    //-------------------------------
    if (BONUS_LIFE == 0xff)
        return;

    //-------------------------------
    // 0614  ef        rst     #28
    // 0615  1c0a
    // 0617  ef        rst     #28
    // 0618  1f00
    // 061a  c9        ret     
    //-------------------------------
    schedTask (TASK_DISPLAY_MSG, MSG_BONUS_PACMAN);
    schedTask (TASK_SHOW_BONUS_LIFE_SCORE, 0x00);
}

/*  4e00 ==0 && 4e03==1, if start pushed, 4e03=2 */
void checkStartButtons (void)
{
    //-------------------------------
    // 	;; Display 1/2 player and check start buttons
    // 061b  cda12b    call    #2ba1
    //-------------------------------
    displayCredits_2ba1();
    //-------------------------------
    // 061e  3a6e4e    ld      a,(#4e6e)	; Credits
    // 0621  fe01      cp      #01
    // 0623  0609      ld      b,#09		; MSG #9
    // 0625  2002      jr      nz,#0629	; >2 credits
    // 0627  0608      ld      b,#08		; MSG #8
    // 0629  cd5e2c    call    #2c5e
    //-------------------------------
    if (CREDITS == 1)
        displayMsg_2c5e (MSG_ONEPLAYER);
    else
        displayMsg_2c5e (MSG_ONEORTWOPLAYER);

    //-------------------------------
    // 062c  3a6e4e    ld      a,(#4e6e)
    // 062f  fe01      cp      #01
    // 0631  3a4050    ld      a,(#5040)
    // 0634  280c      jr      z,#0642         ; Don't check P2 w/ 1 credit
    // 0636  cb77      bit     6,a
    // 0638  2008      jr      nz,#0642        ; (8)
    // 063a  3e01      ld      a,#01
    // 063c  32704e    ld      (#4e70),a
    // 063f  c34906    jp      #0649
    //-------------------------------
    if (CREDITS!= 1 && !IN1_START2)
        TWO_PLAYERS = 1;

    //-------------------------------
    // 0642  cb6f      bit     5,a
    // 0644  c0        ret     nz
    //-------------------------------
    else if (IN1_START1)
        return;
 
    //-------------------------------
    // 0645  af        xor     a
    // 0646  32704e    ld      (#4e70),a
    //-------------------------------
    else
        TWO_PLAYERS = 0;

    //-------------------------------
    // 0649  3a6b4e    ld      a,(#4e6b)       ; credits
    // 064c  a7        and     a
    // 064d  2815      jr      z,#0664         ; (21)
    //-------------------------------

    /*  Seems to be a redundant check.  We couldn't be here if we have no credit */
    if (CREDITS!= 0)
    {
        //-------------------------------
        // 064f  3a704e    ld      a,(#4e70)            ; two players
        // 0652  a7        and     a
        // 0653  3a6e4e    ld      a,(#4e6e)
        // 0656  2803      jr      z,#065b         ; (3)
        //-------------------------------

        /*  Note - to maintain BCD encoding, if lowest digit is zero,
         *  subtract 7 instead of 1 to make 0x10 become 0x09.  Do this twice
         *  if TWO_PLAYERS.  We use a for loop where original used a jump TODO
         *  use bcd function */
        for (int i = 0; i <= TWO_PLAYERS; i++)
        {
            //-------------------------------
            // 0658  c699      add     a,#99
            // 065a  27        daa     
            // 065b  c699      add     a,#99
            // 065d  27        daa     
            //-------------------------------

            if ((CREDITS & 0x0f) ==0)
                CREDITS-= 7;
            else
                CREDITS--;
        }

        //-------------------------------
        // 065e  326e4e    ld      (#4e6e),a
        // 0661  cda12b    call    #2ba1
        //-------------------------------
        displayCredits_2ba1();
    }
    //-------------------------------
    // 0664  21034e    ld      hl,#4e03
    // 0667  34        inc     (hl)
    //-------------------------------
    CREDIT_STATE++;

    //-------------------------------
    // 0668  af        xor     a
    // 0669  32d64d    ld      (#4dd6),a
    // 066c  3c        inc     a
    // 066d  32cc4e    ld      (#4ecc),a
    // 0670  32dc4e    ld      (#4edc),a
    // 0673  c9        ret     
    //-------------------------------
    WAIT_START_BUTTON = 0;
    CH1_SOUND_WAVE->mask = 
    CH2_SOUND_WAVE->mask = 1;
}

void player1ReadyMsg_0674 (void)
{
    //-------------------------------
    // 0674  ef        rst     #28
    // 0675  0001
    //       ef        rst     #28
    //       0101
    //       ef        rst     #28
    //       0200
    // 067d  ef        rst     #28
    // 067e  1200
    // 0680  ef        rst     #28
    // 0681  0300
    // 0683  ef        rst     #28
    // 0684  1c03
    // 0686  ef        rst     #28
    // 0687  1c06
    //       ef        rst     #28
    // 068a  1800
    // 068c  ef        rst     #28
    // 068d  1b00
    //-------------------------------
    schedTask (TASK_CLEAR_SCREEN, 1);
    schedTask (TASK_MAZE_COLOURS, 1);
    schedTask (TASK_DRAW_MAZE, 0);
    schedTask (TASK_CLEAR_PILLS, 0);
    schedTask (TASK_DRAW_PILLS, 0);
    schedTask (TASK_DISPLAY_MSG, MSG_PLAYER1);
    schedTask (TASK_DISPLAY_MSG, MSG_READY);
    schedTask (TASK_CLEAR_SCORES, 0);
    schedTask (TASK_FRUIT_HISTORY, 0);

    //-------------------------------
    // 068f  af        xor     a
    // 0690  32134e    ld      (#4e13),a
    // 0693  3a6f4e    ld      a,(#4e6f)
    // 0696  32144e    ld      (#4e14),a
    // 0699  32154e    ld      (#4e15),a
    //-------------------------------
    P1_LEVEL = 0;
    P1_REAL_LIVES = P1_DISPLAY_LIVES = LIVES_PER_GAME;

    //-------------------------------
    // 069c  ef        rst     #28
    // 069d  1a00
    //-------------------------------
    schedTask (TASK_BOTTOM_COLOUR, 0x00);

    //-------------------------------
    // 069f  f7        rst     #30
    // 06a0  570100
    //-------------------------------
    schedISRTask (0x57, ISRTASK_INC_MAIN_SUB2, 0x00);
    incMainSub2_06a3();
}

void incMainSub2_06a3 (void)
{
    //-------------------------------
    // 06a3  21034e    ld      hl,#4e03
    // 06a6  34        inc     (hl)
    // 06a7  c9        ret     
    //-------------------------------
    CREDIT_STATE++;
}

void creditStateReset_06a8 (void)
{
    //-------------------------------
    // 06a8  21154e    ld      hl,#4e15
    // 06ab  35        dec     (hl)
    // 06ac  cd6a2b    call    #2b6a
    //-------------------------------
    P1_DISPLAY_LIVES--;
    bottomTextColourAndDisplayLives_2b6a (0);

    //-------------------------------
    // 06af  af        xor     a
    // 06b0  32034e    ld      (#4e03),a
    // 06b3  32024e    ld      (#4e02),a
    // 06b6  32044e    ld      (#4e04),a
    // 06b9  21004e    ld      hl,#4e00
    // 06bc  34        inc     (hl)
    // 06bd  c9        ret     
    //-------------------------------
    INTRO_STATE = 
    CREDIT_STATE = 
    LEVEL_STATE = 0;
    MAIN_STATE++;
}

/*  called if MAIN_STATE_PLAY */
void playGameStateMachine_06be (void)
{
    //-------------------------------
    // 06be  3a044e    ld      a,(#4e04)
    // 06c1  e7        rst     #20
    //
    // 06c2        79 08 99 08 0c 00  cd 08 0d 09 0c 00 40 09 
    // 06d0  0c 00 72 09 88 09 0c 00  d2 09 d8 09 0c 00 e8 09 
    // 06e0  0c 00 fe 09 0c 00 02 0a  0c 00 04 0a 0c 00 06 0a 
    // 06f0  0c 00 08 0a 0c 00 0a 0a  0c 00 0c 0a 0c 00 0e 0a 
    // 0700  0c 00 2c 0a 0c 00 7c 0a  a0 0a 0c 00 a3 0a      
    //-------------------------------
    void (*func[])() = 
    {
        resetPlayerParams_0879,
        levelStatePlayerReady_0899, nothing_000c,
        playGameMain_08cd,
        playerDied_090d, nothing_000c,
        switchPlayers_0940, nothing_000c,
        stateDemoInit_0972,
        gameOverOrNextPlayer_0988, nothing_000c,
        advanceToLevelStatePlayGame_09d2,
        playGameSoundOff_09d8, nothing_000c,
        mazeColourWhite_09e8, nothing_000c,     
        mazeColourBlue_09fe, nothing_000c,
        mazeColourWhite_0a02, nothing_000c,
        mazeColourBlue_0a04, nothing_000c,
        mazeColourWhite_0a06, nothing_000c,
        mazeColourBlue_0a08, nothing_000c,
        mazeColourWhite_0a0a, nothing_000c,
        mazeColourBlue_0a0c, nothing_000c,
        mazeReset_0a0e, nothing_000c,
        nextLevelStateMachine_0a2c, nothing_000c,
        nextLevel_0a7c,
        gameOverOrNextPlayer_0aa0, nothing_000c,
        advanceToLevelStatePlayGame_0aa3
    };
    tableCall_0020 (func, LEVEL_STATE);
}

void setupGhostTimers_070e (int b)
{
    //-------------------------------
    // 070e  78        ld      a,b
    // 070f  a7        and     a
    // 0710  2004      jr      nz,#0716        ; (4)
    // 0712  2a0a4e    ld      hl,(#4e0a)
    // 0715  7e        ld      a,(hl)
    //-------------------------------
    printf ("%s diff = %d\n", __func__, b);

    if (b == 0)
    {
        b = ROM[P1_CURR_DIFFICULTY];
        printf ("%s ROM read diff = %d\n", __func__, b);
    }

    //-------------------------------
    // 0716  dd219607  ld      ix,#0796
    // 071a  47        ld      b,a
    // 071b  87        add     a,a
    // 071c  87        add     a,a
    // 071d  80        add     a,b
    // 071e  80        add     a,b
    // 071f  5f        ld      e,a
    // 0720  1600      ld      d,#00
    // 0722  dd19      add     ix,de
    //-------------------------------
    uint8_t *ix = DATA_0796 + b * 6;
    printf ("%s data = %lx\n", __func__, ix-ROM);

    //-------------------------------
    // 0724  dd7e00    ld      a,(ix+#00)
    // 0727  87        add     a,a              ; a*2
    // 0728  47        ld      b,a
    // 0729  87        add     a,a
    // 072a  87        add     a,a
    // 072b  4f        ld      c,a              ; c = a*8
    // 072c  87        add     a,a
    // 072d  87        add     a,a              ; a*4
    // 072e  81        add     a,c              ; + a*32
    // 072f  80        add     a,b              ; + a*2
    // 0730  5f        ld      e,a              ; e = a*32 + a*8 + a*2 = a*42
    // 0731  1600      ld      d,#00
    // 0733  210f33    ld      hl,#330f
    // 0736  19        add     hl,de
    // 0737  cd1408    call    #0814
    //-------------------------------
    uint8_t a = ix[0] * 0x2a;
    uint8_t *hl = MOVE_DATA_330f + a;
    printf ("%s movedata %d = %lx\n", __func__, a, hl-ROM);
    setupMovePat_0814(hl);

    //-------------------------------
    // 073a  dd7e01    ld      a,(ix+#01)
    // 073d  32b04d    ld      (#4db0),a
    //-------------------------------
    REL_DIFF = ix[1];
    printf ("%s REL_DIFF=%d\n", __func__, REL_DIFF);

    //-------------------------------
    // 0740  dd7e02    ld      a,(ix+#02)
    // 0743  47        ld      b,a
    // 0744  87        add     a,a
    // 0745  80        add     a,b   
    // 0746  5f        ld      e,a              ; e = a*3
    // 0747  1600      ld      d,#00
    // 0749  214308    ld      hl,#0843
    // 074c  19        add     hl,de
    // 074d  cd3a08    call    #083a
    //-------------------------------
    hl = DATA_0843+3*ix[2];
    printf ("%s leave home counter=%lx\n", __func__, hl-ROM);
    initLeaveHouseCounters_083a(hl);

    //-------------------------------
    // 0750  dd7e03    ld      a,(ix+#03)
    // 0753  87        add     a,a
    // 0754  5f        ld      e,a
    // 0755  1600      ld      d,#00
    // 0757  fd214f08  ld      iy,#084f
    // 075b  fd19      add     iy,de
    //-------------------------------
    uint8_t *iy = DATA_084f+2*ix[3];

    //-------------------------------
    // 075d  fd6e00    ld      l,(iy+#00)
    // 0760  fd6601    ld      h,(iy+#01)
    // 0763  22bb4d    ld      (#4dbb),hl
    //-------------------------------
    printf ("%s pills rem diff=%lx\n", __func__, iy-ROM);
    PILLS_REM_DIFF_1 = iy[0];
    PILLS_REM_DIFF_2 = iy[1];

    //-------------------------------
    // 0766  dd7e04    ld      a,(ix+#04)
    // 0769  87        add     a,a
    // 076a  5f        ld      e,a
    // 076b  1600      ld      d,#00
    // 076d  fd216108  ld      iy,#0861
    // 0771  fd19      add     iy,de
    //-------------------------------
    iy = DATA_0861+2*ix[4];

    //-------------------------------
    // 0773  fd6e00    ld      l,(iy+#00)
    // 0776  fd6601    ld      h,(iy+#01)
    // 0779  22bd4d    ld      (#4dbd),hl
    //-------------------------------
    printf ("%s ghost edible time=[%lx]=%04x\n", __func__, iy-ROM, *(uint16_t*)iy);
    GHOST_EDIBLE_TIME = *(uint16_t*)iy;

    //-------------------------------
    // 077c  dd7e05    ld      a,(ix+#05)
    // 077f  87        add     a,a
    // 0780  5f        ld      e,a
    // 0781  1600      ld      d,#00
    // 0783  fd217308  ld      iy,#0873
    // 0787  fd19      add     iy,de
    //-------------------------------
    iy = DATA_0873+2*ix[5];
    printf ("%s leave home units data=%04lx\n", __func__, iy-ROM);

    //-------------------------------
    // 0789  fd6e00    ld      l,(iy+#00)
    // 078c  fd6601    ld      h,(iy+#01)
    // 078f  22954d    ld      (#4d95),hl
    //-------------------------------
    printf ("%s leave home units=%04x\n", __func__, *(uint16_t*)iy);
    UNITS_B4_GHOST_LEAVES_HOME = *(uint16_t*)iy;

    //-------------------------------
    // 0792  cdea2b    call    #2bea
    // 0795  c9        ret     
    //-------------------------------
    fruitHistoryLevelCheck_2bea (b);
}

    /* Table of values used to initialise ghost timers.  Groups of 6 bytes.  21
     * entries.  Index is difficulty of current level (0 thru 20) */

    //-------------------------------
    // 0796  03 01 01 00 02 00
    // 079c  04 01 02 01 03 00
    // 07a2  04 01 03 02 04 01
    // 07a8  04 02 03 02 05 01
    // 07ae  05 00 03 02 06 02
    // 07b4  05 01 03 03 03 02
    // 07ba  05 02 03 03 06 02
    // 07c0  05 02 03 03 06 02
    // 07c6  05 00 03 04 07 02
    // 07cc  05 01 03 04 03 02
    // 07d2  05 02 03 04 06 02
    // 07d8  05 02 03 05 07 02
    // 07de  05 00 03 05 07 02
    // 07e4  05 02 03 05 05 02
    // 07ea  05 01 03 06 07 02
    // 07f0  05 02 03 06 07 02
    // 07f6  05 02 03 06 08 02
    // 07fc  05 02 03 06 07 02
    // 0802  05 02 03 07 08 02
    // 0808  05 02 03 07 08 02
    // 080e  06 02 03 07 08 02
    //-------------------------------

void setupMovePat_0814(uint8_t *hl)
{
    //-------------------------------
    // 0814  11464d    ld      de,#4d46
    // 0817  011c00    ld      bc,#001c
    // 081a  edb0      ldir    
    //-------------------------------

    /*  Copy move patterns for pacman (4 x 4 = 0x10) and for Blinky (3 x 4 =
     *  0xc) */
    memcpy (&PACMAN_MOVE_PAT_NORMAL, hl, 0x1c);

    //-------------------------------
    // 081c  010c00    ld      bc,#000c
    // 081f  a7        and     a
    // 0820  ed42      sbc     hl,bc
    // 0822  edb0      ldir    
    //-------------------------------

    /*  move pattern table + 0x1c is from PACMAN to PINKY but subtract 0xc from
     *  hl causes data for BLINKY to be reused for PINKY */
    memcpy (&PINKY_MOVE_PAT_NORMAL, &hl[0x10], 0xc);

    //-------------------------------
    // 0824  010c00    ld      bc,#000c
    // 0827  a7        and     a
    // 0828  ed42      sbc     hl,bc
    // 082a  edb0      ldir    
    //-------------------------------

    /*  Reuse move data for INKY */
    memcpy (&INKY_MOVE_PAT_NORMAL, &hl[0x10], 0xc);

    //-------------------------------
    // 082c  010c00    ld      bc,#000c
    // 082f  a7        and     a
    // 0830  ed42      sbc     hl,bc
    // 0832  edb0      ldir    
    //-------------------------------

    /*  Reuse move data for CLYDE */
    memcpy (&CLYDE_MOVE_PAT_NORMAL, &hl[0x10], 0xc);

    //-------------------------------
    // 0834  010e00    ld      bc,#000e
    // 0837  edb0      ldir    
    // 0839  c9        ret     
    //-------------------------------
    memcpy (DIFFICULTY_TABLE, &hl[0x1c], 0xe);
}

/*  Sets the leave home counters for pinky, inky and clyde */
void initLeaveHouseCounters_083a(uint8_t *hl)
{
    //-------------------------------
    // 083a  11b84d    ld      de,#4db8
    // 083d  010300    ld      bc,#0003
    // 0840  edb0      ldir    
    // 0842  c9        ret     
    //-------------------------------
    memcpy (&PINKY_LEAVE_HOME_COUNTER, hl, 3);
}

    /*  Leave home counter data, groups of 3 bytes */

    //-------------------------------
    // 0843           14 1e 46 00 1e  3c 00 00 32 00 00 00 14
    // 0850  0a 1e 0f 28 14 32 19 3c  1e 50 28 64 32 78 3c 8c
    // 0860  46 c0 03 48 03 d0 02 58  02 e0 01 68 01 f0 00 78
    // 0870  00 01 00 f0 00 f0 00 b4  00                    
    //-------------------------------

/*  side-effect: Sets HL to 0x4e04 */
void resetPlayerParams_0879 (void)
{
    //-------------------------------
    // 0879  21094e    ld      hl,#4e09
    // 087c  af        xor     a
    // 087d  060b      ld      b,#0b
    // 087f  cf        rst     #8
    //-------------------------------
    memset (&PLAYER, 0, 11); // clear P1 params excluding pills

    //-------------------------------
    // 0880  cdc924    call    #24c9
    // 0883  2a734e    ld      hl,(#4e73)
    // 0886  220a4e    ld      (#4e0a),hl
    //-------------------------------
    clearPillArrays_24c9();
    P1_CURR_DIFFICULTY = DIFFICULTY_PTR;
    printf ("P1DIFF = %04x\n", P1_CURR_DIFFICULTY);

    //-------------------------------
    // 0889  210a4e    ld      hl,#4e0a
    // 088c  11384e    ld      de,#4e38
    // 088f  012e00    ld      bc,#002e
    // 0892  edb0      ldir    
    //-------------------------------
    memcpy (&P2_CURR_DIFFICULTY, &P1_CURR_DIFFICULTY, 0x2e);
    incLevelStateSubr_0894();
}

void incLevelStateSubr_0894 (void)
{
    //-------------------------------
    // 0894  21044e    ld      hl,#4e04
    // 0897  34        inc     (hl)
    // 0898  c9        ret     
    //-------------------------------
    LEVEL_STATE++;
}

void levelStatePlayerReady_0899 (void)
{
    //-------------------------------
    // 0899  3a004e    ld      a,(#4e00)
    // 089c  3d        dec     a
    // 089d  2006      jr      nz,#08a5        ; (6)
    // 089f  3e09      ld      a,#09
    // 08a1  32044e    ld      (#4e04),a
    // 08a4  c9        ret     
    //-------------------------------
    if (MAIN_STATE == MAIN_STATE_DEMO)
    {
         LEVEL_STATE = LEVEL_STATE_GAME_OVER;
         return;
    }

    //-------------------------------
    // 08a5  ef        rst     #28
    // 08a6  1100
    // 08a8  ef        rst     #28
    // 08a9  1c83
    // 08ab  ef        rst     #28
    // 08ac  0400
    // 08ae  ef        rst     #28
    // 08af  0500
    // 08b1  ef        rst     #28
    // 08b2  1000
    // 08b4  ef        rst     #28
    // 08b5  1a00
    //-------------------------------
    schedTask (TASK_CLEAR_GHOST_STATE, 0);
    schedTask (TASK_DISPLAY_MSG, 0x80 | MSG_PLAYER1);
    schedTask (TASK_INIT_POSITIONS, 0);
    schedTask (TASK_BLINKY_SUBSTATE, SUBSTATE_IN_HOUSE);
    schedTask (TASK_SETUP_GHOST_TIMERS, 0);
    schedTask (TASK_BOTTOM_COLOUR, 0);

    //-------------------------------
    // 08b7  f7        rst     #30
    // 08b8  540000
    // 08bb  f7        rst     #30
    // 08bc  540600
    //-------------------------------
    schedISRTask (0x54, ISRTASK_INC_LEVEL_STATE, 0x00);
    schedISRTask (0x54, ISRTASK_DISPLAY_READY, 0x00);

    //-------------------------------
    // 08bf  3a724e    ld      a,(#4e72)
    // 08c2  47        ld      b,a
    // 08c3  3a094e    ld      a,(#4e09)
    // 08c6  a0        and     b
    // 08c7  320350    ld      (#5003),a
    // 08ca  c39408    jp      #0894
    //-------------------------------
    FLIPSCREEN = (COCKTAIL_MODE & PLAYER);
    incLevelStateSubr_0894();
}

void playGameMain_08cd (void)
{
    //-------------------------------
    // 08cd  3a0050    ld      a,(#5000)
    // 08d0  cb67      bit     4,a
    // 08d2  c2de08    jp      nz,#08de
    //-------------------------------
    if (IN0_RACKADV == 0)
    {
        //-------------------------------
        // 08d5  21044e    ld      hl,#4e04
        // 08d8  360e      ld      (hl),#0e
        // 08da  ef        rst     #28
        // 08db  1300
        // 08dd  c9        ret     
        //-------------------------------
        LEVEL_STATE = 0x0e;
        schedTask (TASK_CLEAR_PILLS_SCREEN, 0x00);
        return;
    }
 
    //-------------------------------
    // 08de  3a0e4e    ld      a,(#4e0e)
    // 08e1  fef4      cp      #f4
    // 08e3  2006      jr      nz,#08eb        ; (6)
    //-------------------------------
    if (P1_PILLS_EATEN_LEVEL == 0xf4)
    {
        //-------------------------------
        // 08e5  21044e    ld      hl,#4e04
        // 08e8  360c      ld      (hl),#0c
        // 08ea  c9        ret     
        //-------------------------------
        LEVEL_STATE = 0x0c;
        return;
    }

    //-------------------------------
    // 08eb  cd1710    call    #1017
    // 08ee  cd1710    call    #1017
    // 08f1  cddd13    call    #13dd
    // 08f4  cd420c    call    #0c42
    // 08f7  cd230e    call    #0e23
    // 08fa  cd360e    call    #0e36
    // 08fd  cdc30a    call    #0ac3
    // 0900  cdd60b    call    #0bd6
    // 0903  cd0d0c    call    #0c0d
    // 0906  cd6c0e    call    #0e6c
    // 0909  cdad0e    call    #0ead
    // 090c  c9        ret     
    //-------------------------------
    updateGhostStates_1017();
    updateGhostStates_1017();
    checkInactivityCounter_13dd();
    ghostsLeaveHouse_0c42();
    toggleGhostAnimation_0e23();
    ghostsChangeOrientation_0e36();
    ghostsFlashBecomingInedible_0ac3();
    setGhostColour_0bd6();
    flashPowerups_0c0d();
    updatePillsEatenSoundEffect_0e6c();
    selectFruit_0ead();
}

void playerDied_090d (void)
{
    //-------------------------------
    // 090d  3e01      ld      a,#01
    // 090f  32124e    ld      (#4e12),a
    // 0912  cd8724    call    #2487
    //-------------------------------
    P1_DIED_IN_LEVEL = 1;
    updatePillsFromScreen_2487(0);

    //-------------------------------
    // 0915  21044e    ld      hl,#4e04
    // 0918  34        inc     (hl)
    //-------------------------------
    LEVEL_STATE++;

    //-------------------------------
    // 0919  3a144e    ld      a,(#4e14)
    // 091c  a7        and     a
    // 091d  201f      jr      nz,#093e        ; (31)
    //-------------------------------
    if (P1_REAL_LIVES == 0)
    {
        //-------------------------------
        // 091f  3a704e    ld      a,(#4e70)
        // 0922  a7        and     a
        // 0923  2819      jr      z,#093e         ; (25)
        //-------------------------------
        if (TWO_PLAYERS)
        {
            //-------------------------------
            // 0925  3a424e    ld      a,(#4e42)
            // 0928  a7        and     a
            // 0929  2813      jr      z,#093e         ; (19)
            //-------------------------------
            if (P2_REAL_LIVES != 0)
            {
                //-------------------------------
                // 092b  3a094e    ld      a,(#4e09)
                // 092e  c603      add     a,#03
                // 0930  4f        ld      c,a
                // 0931  061c      ld      b,#1c
                // 0933  cd4200    call    #0042
                //-------------------------------
                addTask_0042 (TASK_DISPLAY_MSG, PLAYER+3); // player one or two

                //-------------------------------
                // 0936  ef        rst     #28
                // 0937  1c05
                // 0939  f7        rst     #30
                // 093a  540000
                // 093d  c9        ret     
                //-------------------------------
                schedTask (TASK_DISPLAY_MSG, MSG_GAMEOVER);
                schedISRTask (0x54, ISRTASK_INC_LEVEL_STATE, 0x00);
                return;
            }
        }
    }

    //-------------------------------
    // 093e  34        inc     (hl)
    // 093f  c9        ret     
    //-------------------------------
    LEVEL_STATE++;
}

void switchPlayers_0940 (void)
{
    //-------------------------------
    // 0940  3a704e    ld      a,(#4e70)
    // 0943  a7        and     a
    // 0944  2806      jr      z,#094c         ; (6)
    // 0946  3a424e    ld      a,(#4e42)
    // 0949  a7        and     a
    // 094a  2015      jr      nz,#0961        ; (21)
    //-------------------------------
    if (TWO_PLAYERS == 0 || P2_REAL_LIVES == 0)
    {
        //-------------------------------
        // 094c  3a144e    ld      a,(#4e14)
        // 094f  a7        and     a
        // 0950  201a      jr      nz,#096c        ; (26)
        //-------------------------------
        if (P1_REAL_LIVES == 0)
        {
            //-------------------------------
            // 0952  cda12b    call    #2ba1
            // 0955  ef        rst     #28
            // 0956  1c05
            // 0958  f7        rst     #30
            // 0959  540000
            //-------------------------------
            displayCredits_2ba1();
            schedTask (TASK_DISPLAY_MSG, MSG_GAMEOVER);
            schedISRTask (0x54, ISRTASK_INC_LEVEL_STATE, 0x00);

            //-------------------------------
            // 095c  21044e    ld      hl,#4e04
            // 095f  34        inc     (hl)
            // 0960  c9        ret     
            //-------------------------------
            LEVEL_STATE++;
            return;
        }
    }
    else
    {
        //-------------------------------
        // 0961  cda60a    call    #0aa6
        //-------------------------------
        swapP1P2Difficulty_0aa6();

        //-------------------------------
        // 0964  3a094e    ld      a,(#4e09)
        // 0967  ee01      xor     #01
        // 0969  32094e    ld      (#4e09),a
        //-------------------------------
        PLAYER ^= 1;
    }

    //-------------------------------
    // 096c  3e09      ld      a,#09
    // 096e  32044e    ld      (#4e04),a
    // 0971  c9        ret     
    //-------------------------------
    LEVEL_STATE = LEVEL_STATE_GAME_OVER;
}

void stateDemoInit_0972 (void)
{
    //-------------------------------
    // 0972  af        xor     a
    // 0973  32024e    ld      (#4e02),a
    // 0976  32044e    ld      (#4e04),a
    // 0979  32704e    ld      (#4e70),a
    // 097c  32094e    ld      (#4e09),a
    // 097f  320350    ld      (#5003),a
    //-------------------------------
    INTRO_STATE = 
    LEVEL_STATE = 
    TWO_PLAYERS = 
    PLAYER = 0;
    FLIPSCREEN = 0;

    //-------------------------------
    // 0982  3e01      ld      a,#01
    // 0984  32004e    ld      (#4e00),a
    // 0987  c9        ret     
    //-------------------------------
    MAIN_STATE = MAIN_STATE_DEMO;
}

void gameOverOrNextPlayer_0988 (void)
{
    //-------------------------------
    // 0988  ef        rst     #28
    // 0989  0001
    //       ef        rst     #28
    //       0101
    //       ef        rst     #28
    //       0200
    // 0991  ef        rst     #28
    // 0992  1100
    //       ef        rst     #28
    // 0995  1300
    // 0997  ef        rst     #28
    // 0998  0300
    // 099a  ef        rst     #28
    // 099b  0400
    // 099d  ef        rst     #28
    // 099e  0500
    // 09a0  ef        rst     #28
    // 09a1  1000
    // 09a3  ef        rst     #28
    // 09a4  1a00
    // 09a6  ef        rst     #28
    // 09a7  1c06 
    //-------------------------------
    schedTask (TASK_CLEAR_SCREEN, 1);
    schedTask (TASK_MAZE_COLOURS, 1);
    schedTask (TASK_DRAW_MAZE, 0);
    schedTask (TASK_CLEAR_GHOST_STATE, 0);
    schedTask (TASK_CLEAR_PILLS_SCREEN, 0);
    schedTask (TASK_DRAW_PILLS, 0);
    schedTask (TASK_INIT_POSITIONS, 0);
    schedTask (TASK_BLINKY_SUBSTATE, SUBSTATE_IN_HOUSE);
    schedTask (TASK_SETUP_GHOST_TIMERS, 0);
    schedTask (TASK_BOTTOM_COLOUR, 0);
    schedTask (TASK_DISPLAY_MSG, MSG_READY);

    //-------------------------------
    //       3a004e    ld      a,(#4e00)
    // 09ac  fe03      cp      #03
    // 09ae  2806      jr      z,#09b6         ; (6)
    //-------------------------------
    if (MAIN_STATE != MAIN_STATE_PLAY)
    {
        //-------------------------------
        // 09b0  ef        rst     #28
        // 09b1  1c05
        // 09b3  ef        rst     #28
        // 09b4  1d00
        //-------------------------------
        schedTask (TASK_DISPLAY_MSG, MSG_GAMEOVER);
        schedTask (TASK_DISPLAY_CREDITS, 0);
    }

    //-------------------------------
    // 09b6  f7        rst     #30
    // 09b7  540000
    //-------------------------------
    schedISRTask (0x54, ISRTASK_INC_LEVEL_STATE, 0);

    //-------------------------------
    // 09ba  3a004e    ld      a,(#4e00)
    // 09bd  3d        dec     a
    // 09be  2804      jr      z,#09c4         ; (4)
    //-------------------------------
    if (MAIN_STATE != MAIN_STATE_DEMO)
    {
        //-------------------------------
        // 09c0  f7        rst     #30
        // 09c1  540600 
        //-------------------------------
        schedISRTask (0x54, ISRTASK_DISPLAY_READY, 0);
    }

    //-------------------------------
    // 09c4  3a724e    ld      a,(#4e72)
    // 09c7  47        ld      b,a
    // 09c8  3a094e    ld      a,(#4e09)
    // 09cb  a0        and     b
    // 09cc  320350    ld      (#5003),a
    // 09cf  c39408    jp      #0894
    //-------------------------------
    FLIPSCREEN = (COCKTAIL_MODE & PLAYER);
    incLevelStateSubr_0894();
}

void advanceToLevelStatePlayGame_09d2 (void)
{
    //-------------------------------
    // 09d2  3e03      ld      a,#03
    // 09d4  32044e    ld      (#4e04),a
    // 09d7  c9        ret     
    //-------------------------------
    LEVEL_STATE = LEVEL_STATE_PLAY_GAME;
}

void playGameSoundOff_09d8 (void)
{
    //-------------------------------
    // 09d8  f7        rst     #30
    // 09d9  540000
    // 09dc  21044e    ld      hl,#4e04
    // 09df  34        inc     (hl)
    //-------------------------------
    schedISRTask (0x54, ISRTASK_INC_LEVEL_STATE, 0x00);
    LEVEL_STATE++;

    //-------------------------------
    // 09e0  af        xor     a
    // 09e1  32ac4e    ld      (#4eac),a
    // 09e4  32bc4e    ld      (#4ebc),a
    // 09e7  c9        ret     
    //-------------------------------
    CH2_SOUND_EFFECT->mask = 
    CH3_SOUND_EFFECT->mask = 0;
}

void mazeColourWhite_09e8 (void)
{
    //-------------------------------
    // 09e8  0e02      ld      c,#02
    //-------------------------------
    mazeColour_09ea (2);
}

void mazeColour_09ea (int param)
{
    //-------------------------------
    // 09ea  0601      ld      b,#01
    // 09ec  cd4200    call    #0042
    //-------------------------------
    addTask_0042 (TASK_MAZE_COLOURS, param);

    //-------------------------------
    // 09ef  f7        rst     #30
    // 09f0  420000
    // 09f3  210000    ld      hl,#0000
    // 09f6  cd7e26    call    #267e
    //-------------------------------
    schedISRTask (0x42, ISRTASK_INC_LEVEL_STATE, 0x00);
    setGhostPosition_267e (0, 0);

    //-------------------------------
    // 09f9  21044e    ld      hl,#4e04
    // 09fc  34        inc     (hl)
    // 09fd  c9        ret     
    //-------------------------------
    LEVEL_STATE++;
}

void mazeColourBlue_09fe (void)
{
    //-------------------------------
    // 09fe  0e00      ld      c,#00
    // 0a00  18e8      jr      #09ea           ; (-24)
    //-------------------------------
    mazeColour_09ea (0);
}

void mazeColourWhite_0a02 (void)
{
    //-------------------------------
    // 0a02  18e4      jr      #09e8           ; (-28)
    //-------------------------------
    mazeColourWhite_09e8();
}

void mazeColourBlue_0a04 (void)
{
    //-------------------------------
    // 0a04  18f8      jr      #09fe           ; (-8)
    //-------------------------------
    mazeColourBlue_09fe();
}

void mazeColourWhite_0a06 (void)
{
    //-------------------------------
    // 0a06  18e0      jr      #09e8           ; (-32)
    //-------------------------------
    mazeColourWhite_09e8();
}

void mazeColourBlue_0a08 (void)
{
    //-------------------------------
    // 0a08  18f4      jr      #09fe           ; (-12)
    //-------------------------------
    mazeColourBlue_09fe();
}

void mazeColourWhite_0a0a (void)
{
    //-------------------------------
    // 0a0a  18dc      jr      #09e8           ; (-36)
    //-------------------------------
    mazeColourWhite_09e8();
}

void mazeColourBlue_0a0c (void)
{
    //-------------------------------
    // 0a0c  18f0      jr      #09fe           ; (-16)
    //-------------------------------
    mazeColourBlue_09fe();
}

void mazeReset_0a0e (void)
{
    //-------------------------------
    // 0a0e  ef        rst     #28
    // 0a0f  0001
    //       ef        rst     #28
    //       0600 
    // 0a14  ef        rst     #28
    // 0a15  1100
    //       ef        rst     #28
    // 0a18  1300
    // 0a1a  ef        rst     #28
    // 0a1b  0401
    //       ef        rst     #28
    //       0501
    //       ef        rst     #28
    //       1013      
    // 0a23  f7        rst     #30
    // 0a24  430000
    //-------------------------------
    schedTask (TASK_CLEAR_SCREEN, 1);
    schedTask (TASK_CLEAR_COLOUR, 0);
    schedTask (TASK_CLEAR_GHOST_STATE, 0);
    schedTask (TASK_CLEAR_PILLS_SCREEN, 0);
    schedTask (TASK_INIT_POSITIONS, 1);
    schedTask (TASK_BLINKY_SUBSTATE, SUBSTATE_CHASE);
    schedTask (TASK_SETUP_GHOST_TIMERS, 19);
    schedISRTask (0x43, ISRTASK_INC_LEVEL_STATE, 0);

    //-------------------------------
    // 0a27  21044e    ld      hl,#4e04
    // 0a2a  34        inc     (hl)
    // 0a2b  c9        ret     
    //-------------------------------
    LEVEL_STATE++;
}

/*  State machine for levels.  After level 2, play scene1, after level 5 play
 *  scene2 and after level 9 play scene3.  Replay scene3 after every 4th level
 *  up to max level 20 */
void nextLevelStateMachine_0a2c (void)
{
    //-------------------------------
    // 0a2c  af        xor     a
    // 0a2d  32ac4e    ld      (#4eac),a
    // 0a30  32bc4e    ld      (#4ebc),a
    //-------------------------------
    CH2_SOUND_EFFECT->mask = 
    CH3_SOUND_EFFECT->mask = 0;

    //-------------------------------
    // 0a33  3e02      ld      a,#02
    // 0a35  32cc4e    ld      (#4ecc),a
    // 0a38  32dc4e    ld      (#4edc),a
    //-------------------------------
    CH1_SOUND_WAVE->mask = 
    CH2_SOUND_WAVE->mask = 2;

    //-------------------------------
    // 0a3b  3a134e    ld      a,(#4e13)
    // 0a3e  fe14      cp      #14
    // 0a40  3802      jr      c,#0a44         ; (2)
    // 0a42  3e14      ld      a,#14
    //-------------------------------
    int a = P1_LEVEL;
    if (a >= 20)
        a = 20;

    //-------------------------------
    // 0a44  e7        rst     #20
    //
    // 0a45                 6f 0a 08  21 6f 0a 6f 0a 9e 21 6f
    // 0a50  0a 6f 0a 6f 0a 97 22 6f  0a 6f 0a 6f 0a 97 22 6f
    // 0a60  0a 6f 0a 6f 0a 97 22 6f  0a 6f 0a 6f 0a 6f 0a  
    //-------------------------------
    void (*func[])() =
    {
        scene3StateMachine_2297,
        incLevelState_0a6f,
        // scene1StateMachine_2108,
        incLevelState_0a6f,
        incLevelState_0a6f,
        scene2StateMachine_219e,
        incLevelState_0a6f,
        incLevelState_0a6f,
        incLevelState_0a6f,
        scene3StateMachine_2297,
        incLevelState_0a6f,
        incLevelState_0a6f,
        incLevelState_0a6f,
        scene3StateMachine_2297,
        incLevelState_0a6f,
        incLevelState_0a6f,
        incLevelState_0a6f,
        scene3StateMachine_2297,
        incLevelState_0a6f,
        incLevelState_0a6f,
        incLevelState_0a6f,
        incLevelState_0a6f
    };
    tableCall_0020 (func, a);
}

/*  Increment level state by 2 and mute sound */
void incLevelState_0a6f (void)
{
    //-------------------------------
    // 0a6f  21044e    ld      hl,#4e04
    // 0a72  34        inc     (hl)
    // 0a73  34        inc     (hl)
    // 0a74  af        xor     a
    // 0a75  32cc4e    ld      (#4ecc),a
    // 0a78  32dc4e    ld      (#4edc),a
    // 0a7b  c9        ret     
    //-------------------------------
    LEVEL_STATE += 2;
    CH1_SOUND_WAVE->mask = 
    CH2_SOUND_WAVE->mask = 0;
}

void nextLevel_0a7c(void)
{
    //-------------------------------
    // 0a7c  af        xor     a
    // 0a7d  32cc4e    ld      (#4ecc),a
    // 0a80  32dc4e    ld      (#4edc),a
    //-------------------------------
    clearPillArrays_24c9();
    CH1_SOUND_WAVE->mask = 
    CH2_SOUND_WAVE->mask = 0;

    //-------------------------------
    // 0a83  0607      ld      b,#07
    // 0a85  210c4e    ld      hl,#4e0c
    // 0a88  cf        rst     #8
    //-------------------------------
    memset (&P1_FIRST_FRUIT, 0, 7);

    //-------------------------------
    // 0a89  cdc924    call    #24c9
    // 0a8c  21044e    ld      hl,#4e04
    // 0a8f  34        inc     (hl)
    //-------------------------------
    clearPillArrays_24c9();
    LEVEL_STATE++;

    //-------------------------------
    // 0a90  21134e    ld      hl,#4e13
    // 0a93  34        inc     (hl)
    //-------------------------------
    P1_LEVEL++;

    //-------------------------------
    // 0a94  2a0a4e    ld      hl,(#4e0a)
    // 0a97  7e        ld      a,(hl)
    // 0a98  fe14      cp      #14
    // 0a9a  c8        ret     z
    //-------------------------------
    if (ROM[P1_CURR_DIFFICULTY] == 0x14)
        return;

    //-------------------------------
    // 0a9b  23        inc     hl
    // 0a9c  220a4e    ld      (#4e0a),hl
    // 0a9f  c9        ret     
    //-------------------------------
    P1_CURR_DIFFICULTY++;
}

void gameOverOrNextPlayer_0aa0 (void)
{
    //-------------------------------
    // 0aa0  c38809    jp      #0988
    //-------------------------------
    gameOverOrNextPlayer_0988();
}

void advanceToLevelStatePlayGame_0aa3 (void)
{
    //-------------------------------
    // 0aa3  c3d209    jp      #09d2
    //-------------------------------
    advanceToLevelStatePlayGame_09d2();
}

void swapP1P2Difficulty_0aa6 (void)
{
    //-------------------------------
    // 0aa6  062e      ld      b,#2e
    // 0aa8  dd210a4e  ld      ix,#4e0a
    // 0aac  fd21384e  ld      iy,#4e38
    //-------------------------------
    uint8_t *ix = (uint8_t*)&P1_CURR_DIFFICULTY;
    uint8_t *iy = (uint8_t*)&P2_CURR_DIFFICULTY;
    for (int i = 0; i < 0x2e; i++)
    {
        //-------------------------------
        // 0ab0  dd5600    ld      d,(ix+#00)
        // 0ab3  fd5e00    ld      e,(iy+#00)
        // 0ab6  fd7200    ld      (iy+#00),d
        // 0ab9  dd7300    ld      (ix+#00),e
        // 0abc  dd23      inc     ix
        // 0abe  fd23      inc     iy
        // 0ac0  10ee      djnz    #0ab0           ; (-18)
        //-------------------------------
        uint8_t d = *ix;
        uint8_t e = *iy;
        *iy++= d;
        *ix++= e;
    }
    //-------------------------------
    // 0ac2  c9        ret     
    //-------------------------------
}

void ghostsFlashBecomingInedible_0ac3 (void)
{
    //-------------------------------
    // 0ac3  3aa44d    ld      a,(#4da4)
    // 0ac6  a7        and     a
    // 0ac7  c0        ret     nz
    //-------------------------------
    if (KILLED_GHOST_INDEX != 0)
        return;

    //-------------------------------
    // 0ac8  dd21004c  ld      ix,#4c00
    // 0acc  fd21c84d  ld      iy,#4dc8
    // 0ad0  110001    ld      de,#0100
    // 0ad3  fdbe00    cp      (iy+#00)
    // 0ad6  c2d20b    jp      nz,#0bd2
    //-------------------------------
    if (GHOST_COL_POWERUP_COUNTER == 0)
    {
        //-------------------------------
        // 0ad9  fd36000e  ld      (iy+#00),#0e
        // 0add  3aa64d    ld      a,(#4da6)
        // 0ae0  a7        and     a
        // 0ae1  281b      jr      z,#0afe         ; (27)
        //-------------------------------
        GHOST_COL_POWERUP_COUNTER = 0xe;
        if (PACMAN_POWEREDUP != 0)
        {
            //-------------------------------
            // 0ae3  2acb4d    ld      hl,(#4dcb)
            // 0ae6  a7        and     a
            // 0ae7  ed52      sbc     hl,de
            // 0ae9  3013      jr      nc,#0afe        ; (19)
            //-------------------------------
            if (EDIBLE_REMAIN_COUNT < 0x100)
            {
                //-------------------------------
                // 0aeb  21ac4e    ld      hl,#4eac
                // 0aee  cbfe      set     7,(hl)
                // 0af0  3e09      ld      a,#09
                // 0af2  ddbe0b    cp      (ix+#0b)
                // 0af5  2004      jr      nz,#0afb        ; (4)
                //-------------------------------
                CH2_SOUND_EFFECT->mask |= 0x80;
                if (PACMAN_COLOUR == 9)
                {
                    //-------------------------------
                    // 0af7  cbbe      res     7,(hl)
                    // 0af9  3e09      ld      a,#09
                    //-------------------------------
                    CH2_SOUND_EFFECT->mask &= ~0x80;
                }

                //-------------------------------
                // 0afb  320b4c    ld      (#4c0b),a
                //-------------------------------
                PACMAN_COLOUR = 9;
            }
        }

        //-------------------------------
        // 0afe  3aa74d    ld      a,(#4da7)
        // 0b01  a7        and     a
        // 0b02  281d      jr      z,#0b21         ; (29)
        //-------------------------------
        if (BLINKY_EDIBLE)
        {
            //-------------------------------
            // 0b04  2acb4d    ld      hl,(#4dcb)
            // 0b07  a7        and     a
            // 0b08  ed52      sbc     hl,de
            // 0b0a  3027      jr      nc,#0b33        ; (39)
            //-------------------------------
            if (EDIBLE_REMAIN_COUNT < 0x100)
            {
                //-------------------------------
                // 0b0c  3e11      ld      a,#11
                // 0b0e  ddbe03    cp      (ix+#03)
                // 0b11  2807      jr      z,#0b1a         ; (7)
                //-------------------------------
                if (BLINKY_COLOUR != 0x11)
                {
                    //-------------------------------
                    // 0b13  dd360311  ld      (ix+#03),#11
                    // 0b17  c3330b    jp      #0b33
                    //-------------------------------
                    BLINKY_COLOUR = 0x11;
                }
                else
                {
                    //-------------------------------
                    // 0b1a  dd360312  ld      (ix+#03),#12
                    // 0b1e  c3330b    jp      #0b33
                    //-------------------------------
                    BLINKY_COLOUR = 0x12;
                }
            }
        }
        else
        {
            //-------------------------------
            // 0b21  3e01      ld      a,#01
            // 0b23  ddbe03    cp      (ix+#03)
            // 0b26  2807      jr      z,#0b2f         ; (7)
            //-------------------------------
            if (BLINKY_COLOUR != 3)
            {
                //-------------------------------
                // 0b28  dd360301  ld      (ix+#03),#01
                // 0b2c  c3330b    jp      #0b33
                //-------------------------------
                BLINKY_COLOUR = 1;
            }
            else
            {
                //-------------------------------
                // 0b2f  dd360301  ld      (ix+#03),#01
                //-------------------------------
                BLINKY_COLOUR = 1;
            }
        }

        //-------------------------------
        // 0b33  3aa84d    ld      a,(#4da8)
        // 0b36  a7        and     a
        // 0b37  281d      jr      z,#0b56         ; (29)
        //-------------------------------
        if (PINKY_EDIBLE!= 0)
        {
            //-------------------------------
            // 0b39  2acb4d    ld      hl,(#4dcb)
            // 0b3c  a7        and     a
            // 0b3d  ed52      sbc     hl,de
            // 0b3f  3027      jr      nc,#0b68        ; (39)
            //-------------------------------
            if (EDIBLE_REMAIN_COUNT < 0x100)
            {
                //-------------------------------
                // 0b41  3e11      ld      a,#11
                // 0b43  ddbe05    cp      (ix+#05)
                // 0b46  2807      jr      z,#0b4f         ; (7)
                //-------------------------------
                if (PINKY_COLOUR != 0x11)
                {
                    //-------------------------------
                    // 0b48  dd360511  ld      (ix+#05),#11
                    // 0b4c  c3680b    jp      #0b68
                    //-------------------------------
                    PINKY_COLOUR = 0x11;
                }
                else
                {
                    //-------------------------------
                    // 0b4f  dd360512  ld      (ix+#05),#12
                    // 0b53  c3680b    jp      #0b68
                    //-------------------------------
                    PINKY_COLOUR = 0x12;
                }
            }
        }
        else
        {
            //-------------------------------
            // 0b56  3e03      ld      a,#03
            // 0b58  ddbe05    cp      (ix+#05)
            // 0b5b  2807      jr      z,#0b64         ; (7)
            //-------------------------------
            if (PINKY_COLOUR != 0x03)
            {
                //-------------------------------
                // 0b5d  dd360503  ld      (ix+#05),#03
                // 0b61  c3680b    jp      #0b68
                //-------------------------------
                PINKY_COLOUR = 0x3;
            }
            else
            {
                //-------------------------------
                // 0b64  dd360503  ld      (ix+#05),#03
                //-------------------------------
                PINKY_COLOUR = 0x3;
            }
        }

        //-------------------------------
        // 0b68  3aa94d    ld      a,(#4da9)
        // 0b6b  a7        and     a
        // 0b6c  281d      jr      z,#0b8b         ; (29)
        //-------------------------------
        if (INKY_EDIBLE)
        {
            //-------------------------------
            // 0b6e  2acb4d    ld      hl,(#4dcb)
            // 0b71  a7        and     a
            // 0b72  ed52      sbc     hl,de
            // 0b74  3027      jr      nc,#0b9d        ; (39)
            //-------------------------------
            if (EDIBLE_REMAIN_COUNT < 0x100)
            {
                //-------------------------------
                // 0b76  3e11      ld      a,#11
                // 0b78  ddbe07    cp      (ix+#07)
                // 0b7b  2807      jr      z,#0b84         ; (7)
                //-------------------------------
                if (INKY_COLOUR != 0x11)
                {
                    //-------------------------------
                    // 0b7d  dd360711  ld      (ix+#07),#11
                    // 0b81  c39d0b    jp      #0b9d
                    //-------------------------------
                    INKY_COLOUR = 0x11;
                }
                else
                {
                    //-------------------------------
                    // 0b84  dd360712  ld      (ix+#07),#12
                    // 0b88  c39d0b    jp      #0b9d
                    //-------------------------------
                    INKY_COLOUR = 0x12;
                }
            }
        }
        else
        {
            //-------------------------------
            // 0b8b  3e05      ld      a,#05
            // 0b8d  ddbe07    cp      (ix+#07)
            // 0b90  2807      jr      z,#0b99         ; (7)
            //-------------------------------
            if (INKY_COLOUR != 5)
            {
                //-------------------------------
                // 0b92  dd360705  ld      (ix+#07),#05
                // 0b96  c39d0b    jp      #0b9d
                //-------------------------------
                INKY_COLOUR = 5;
            }
            else
            {
                //-------------------------------
                // 0b99  dd360705  ld      (ix+#07),#05
                //-------------------------------
                INKY_COLOUR = 5;
            }
        }

        //-------------------------------
        // 0b9d  3aaa4d    ld      a,(#4daa)
        // 0ba0  a7        and     a
        // 0ba1  281d      jr      z,#0bc0         ; (29)
        //-------------------------------
        if (CLYDE_EDIBLE != 0)
        {
            //-------------------------------
            // 0ba3  2acb4d    ld      hl,(#4dcb)
            // 0ba6  a7        and     a
            // 0ba7  ed52      sbc     hl,de
            // 0ba9  3027      jr      nc,#0bd2        ; (39)
            //-------------------------------
            if (EDIBLE_REMAIN_COUNT < 0x100)
            {
                //-------------------------------
                // 0bab  3e11      ld      a,#11
                // 0bad  ddbe09    cp      (ix+#09)
                // 0bb0  2807      jr      z,#0bb9         ; (7)
                //-------------------------------
                if (CLYDE_COLOUR != 0x11)
                {
                    //-------------------------------
                    // 0bb2  dd360911  ld      (ix+#09),#11
                    // 0bb6  c3d20b    jp      #0bd2
                    //-------------------------------
                    CLYDE_COLOUR = 0x11;
                }
                else
                {
                    //-------------------------------
                    // 0bb9  dd360912  ld      (ix+#09),#12
                    // 0bbd  c3d20b    jp      #0bd2
                    //-------------------------------
                    CLYDE_COLOUR = 0x12;
                }
            }
        }
        else
        {
            //-------------------------------
            // 0bc0  3e07      ld      a,#07
            // 0bc2  ddbe09    cp      (ix+#09)
            // 0bc5  2807      jr      z,#0bce         ; (7)
            //-------------------------------
            if (CLYDE_COLOUR != 7)
            {
                //-------------------------------
                // 0bc7  dd360907  ld      (ix+#09),#07
                // 0bcb  c3d20b    jp      #0bd2
                //-------------------------------
                CLYDE_COLOUR = 7;
            }
            else
            {
                //-------------------------------
                // 0bce  dd360907  ld      (ix+#09),#07
                //-------------------------------
                CLYDE_COLOUR = 7;
            }
        }
    }

    //-------------------------------
    // 0bd2  fd3500    dec     (iy+#00)
    // 0bd5  c9        ret     
    //-------------------------------
    GHOST_COL_POWERUP_COUNTER--;
}

void setGhostColour_0bd6 (void)
{
    //-------------------------------
    // 0bd6  0619      ld      b,#19
    // 0bd8  3a024e    ld      a,(#4e02)
    // 0bdb  fe22      cp      #22
    // 0bdd  c2e20b    jp      nz,#0be2
    //-------------------------------
    int b = 0x19;
    if (INTRO_STATE == 0x22)
    {
        //-------------------------------
        // 0be0  0600      ld      b,#00
        //-------------------------------
        b = 0;
    }

    //-------------------------------
    // 0be2  dd21004c  ld      ix,#4c00
    // 0be6  3aac4d    ld      a,(#4dac)
    // 0be9  a7        and     a
    // 0bea  caf00b    jp      z,#0bf0
    //-------------------------------
    if (BLINKY_STATE)
    {
        //-------------------------------
        // 0bed  dd7003    ld      (ix+#03),b
        //-------------------------------
        BLINKY_COLOUR = b;
    }

    //-------------------------------
    // 0bf0  3aad4d    ld      a,(#4dad)
    // 0bf3  a7        and     a
    // 0bf4  cafa0b    jp      z,#0bfa
    //-------------------------------
    if (PINKY_STATE)
    {
        //-------------------------------
        // 0bf7  dd7005    ld      (ix+#05),b
        //-------------------------------
        PINKY_COLOUR = b;
    }

    //-------------------------------
    // 0bfa  3aae4d    ld      a,(#4dae)
    // 0bfd  a7        and     a
    // 0bfe  ca040c    jp      z,#0c04
    //-------------------------------
    if (INKY_STATE)
    {
        //-------------------------------
        // 0c01  dd7007    ld      (ix+#07),b
        //-------------------------------
        INKY_COLOUR = b;
    }

    //-------------------------------
    // 0c04  3aaf4d    ld      a,(#4daf)
    // 0c07  a7        and     a
    // 0c08  c8        ret     z
    //-------------------------------
    if (CLYDE_STATE)
    {
        //-------------------------------
        // 0c09  dd7009    ld      (ix+#09),b
        // 0c0c  c9        ret     
        //-------------------------------
        CLYDE_COLOUR = b;
    }
}

/*  Toggle the colour of the powers to black and back again.  If level subr is 3
 *  then normal, all 4 pills.  Otherwise presume demo mode (?) and flash only 3
 *  pills.  These must be in consistent locations in the demo scenes? */
void flashPowerups_0c0d (void)
{
    //-------------------------------
    // 0c0d  21cf4d    ld      hl,#4dcf
    // 0c10  34        inc     (hl)
    // 0c11  3e0a      ld      a,#0a
    // 0c13  be        cp      (hl)
    // 0c14  c0        ret     nz
    //-------------------------------
    if (++PILL_CHANGE_COUNTER != 0xa)
        return;

    //-------------------------------
    // 0c15  3600      ld      (hl),#00
    //-------------------------------
    PILL_CHANGE_COUNTER = 0;

    //-------------------------------
    // 0c17  3a044e    ld      a,(#4e04)
    // 0c1a  fe03      cp      #03
    // 0c1c  2015      jr      nz,#0c33        ; (21)
    //-------------------------------
    if (LEVEL_STATE == 3)
    {
        //-------------------------------
        // 0c1e  216444    ld      hl,#4464
        // 0c21  3e10      ld      a,#10
        //-------------------------------
        int a = 0x10;
        // 0c23  be        cp      (hl)
        // 0c24  2002      jr      nz,#0c28        ; (2)
        // 0c26  3e00      ld      a,#00
        //-------------------------------
        if (COLOUR[0x64] == a)
            a = 0;

        //-------------------------------
        // 0c28  77        ld      (hl),a
        //-------------------------------
        COLOUR[0x64] = a;

        //-------------------------------
        // 0c29  327844    ld      (#4478),a
        // 0c2c  328447    ld      (#4784),a
        // 0c2f  329847    ld      (#4798),a
        // 0c32  c9        ret     
        //-------------------------------
        COLOUR[0x78] = a;
        COLOUR[0x384] = a;
        COLOUR[0x398] = a;
        return;
    }
    else
    {
        //-------------------------------
        // 0c33  213247    ld      hl,#4732
        // 0c36  3e10      ld      a,#10
        //-------------------------------
        int a = 0x10;

        //-------------------------------
        // 0c38  be        cp      (hl)
        // 0c39  2002      jr      nz,#0c3d        ; (2)
        // 0c3b  3e00      ld      a,#00
        //-------------------------------
        if (COLOUR[0x332] == 0x10)
            a = 0;

        //-------------------------------
        // 0c3d  77        ld      (hl),a
        // 0c3e  327846    ld      (#4678),a
        // 0c41  c9        ret     
        //-------------------------------
        COLOUR[0x332] = a;
        COLOUR[0x278] = a;
    }
}

void ghostsLeaveHouse_0c42 (void)
{
    //-------------------------------
    // 0c42  3aa44d    ld      a,(#4da4)
    // 0c45  a7        and     a
    // 0c46  c0        ret     nz
    //-------------------------------
    // printf ("%s killed = %d\n", __func__, KILLED_GHOST_INDEX);
    if (KILLED_GHOST_INDEX != 0)
        return;

    //-------------------------------
    // 0c47  3a944d    ld      a,(#4d94)
    // 0c4a  07        rlca    
    // 0c4b  32944d    ld      (#4d94),a
    // 0c4e  d0        ret     nc
    //-------------------------------
    // printf ("%s count = %02x\n", __func__, GHOST_HOUSE_MOVE_COUNT);
    rotate8 (&GHOST_HOUSE_MOVE_COUNT, 1);

    if ((GHOST_HOUSE_MOVE_COUNT & 0x01) == 0)
        return;

    //-------------------------------
    // 0c4f  3aa04d    ld      a,(#4da0)
    // 0c52  a7        and     a
    // 0c53  c2900c    jp      nz,#0c90
    //-------------------------------
    // printf ("%s blinky-sub = %d\n", __func__, BLINKY_SUBSTATE);
    if (BLINKY_SUBSTATE == SUBSTATE_IN_HOUSE)
    {
        //-------------------------------
        // 0c56  dd210533  ld      ix,#3305
        // 0c5a  fd21004d  ld      iy,#4d00
        // 0c5e  cd0020    call    #2000
        // 0c61  22004d    ld      (#4d00),hl
        //-------------------------------
        BLINKY_POS = addXYOffset_2000 (*MOVE_VECTOR_UP, BLINKY_POS);

        //-------------------------------
        // 0c64  3e03      ld      a,#03
        // 0c66  32284d    ld      (#4d28),a
        // 0c69  322c4d    ld      (#4d2c),a
        //-------------------------------
        BLINKY_ORIENTATION = BLINKY_PREV_ORIENTATION = ORIENT_UP;

        //-------------------------------
        // 0c6c  3a004d    ld      a,(#4d00)
        // 0c6f  fe64      cp      #64
        // 0c71  c2900c    jp      nz,#0c90
        //-------------------------------

        /*  Once blinky has moved upwards enough to clear the house, he turns
         *  left and his substate advances to 1 */
        if (BLINKY_POS.y == 0x64)
        {
            //-------------------------------
            // 0c74  212c2e    ld      hl,#2e2c
            // 0c77  220a4d    ld      (#4d0a),hl
            //-------------------------------
            BLINKY_TILE.y = 0x2c;
            BLINKY_TILE.x = 0x2e;

            //-------------------------------
            // 0c7a  210001    ld      hl,#0100
            // 0c7d  22144d    ld      (#4d14),hl
            // 0c80  221e4d    ld      (#4d1e),hl
            //-------------------------------
            BLINKY_VECTOR.y = BLINKY_VECTOR2.y = 0x00;
            BLINKY_VECTOR.x = BLINKY_VECTOR2.x = 0x01;

            //-------------------------------
            // 0c83  3e02      ld      a,#02
            // 0c85  32284d    ld      (#4d28),a
            // 0c88  322c4d    ld      (#4d2c),a
            //-------------------------------
            BLINKY_ORIENTATION = BLINKY_PREV_ORIENTATION = ORIENT_LEFT;

            //-------------------------------
            // 0c8b  3e01      ld      a,#01
            // 0c8d  32a04d    ld      (#4da0),a
            //-------------------------------
            BLINKY_SUBSTATE = SUBSTATE_CHASE;
        }
    }

    //-------------------------------
    // 0c90  3aa14d    ld      a,(#4da1)
    // 0c93  fe01      cp      #01
    // 0c95  cafb0c    jp      z,#0cfb
    //-------------------------------
    // printf ("%s pinky-sub = %d\n", __func__, PINKY_SUBSTATE);
    if (PINKY_SUBSTATE != SUBSTATE_CHASE)
    {
        // printf ("pinky-y=%02x\n",PINKY_POS.y);
        //-------------------------------
        // 0c98  fe00      cp      #00
        // 0c9a  c2c10c    jp      nz,#0cc1
        //-------------------------------
        if (PINKY_SUBSTATE == SUBSTATE_IN_HOUSE)
        {
            //-------------------------------
            // 0c9d  3a024d    ld      a,(#4d02)
            // 0ca0  fe78      cp      #78
            // 0ca2  cc2e1f    call    z,#1f2e
            // 0ca5  fe80      cp      #80
            // 0ca7  cc2e1f    call    z,#1f2e
            //-------------------------------

            /*  Pinky is still in the house.  He just moves up and down so
             *  reverse his direction when he gets to top or bottom of house */

            if (PINKY_POS.y == 0x78 || PINKY_POS.y == 0x80)
                pinkyReverse_1f2e ();

            //-------------------------------
            // 0caa  3a2d4d    ld      a,(#4d2d)
            // 0cad  32294d    ld      (#4d29),a
            //-------------------------------
            PINKY_PREV_ORIENTATION = PINKY_ORIENTATION;
            //-------------------------------
            // 0cb0  dd21204d  ld      ix,#4d20
            // 0cb4  fd21024d  ld      iy,#4d02
            // 0cb8  cd0020    call    #2000
            // 0cbb  22024d    ld      (#4d02),hl
            // 0cbe  c3fb0c    jp      #0cfb
            //-------------------------------
            PINKY_POS = addXYOffset_2000 (PINKY_VECTOR2, PINKY_POS);
        }
        else
        {
            //-------------------------------
            // 0cc1  dd210533  ld      ix,#3305
            // 0cc5  fd21024d  ld      iy,#4d02
            // 0cc9  cd0020    call    #2000
            // 0ccc  22024d    ld      (#4d02),hl
            //-------------------------------
            PINKY_POS = addXYOffset_2000 (*MOVE_VECTOR_UP, PINKY_POS);

            //-------------------------------
            // 0ccf  3e03      ld      a,#03
            // 0cd1  322d4d    ld      (#4d2d),a
            // 0cd4  32294d    ld      (#4d29),a
            //-------------------------------
            PINKY_PREV_ORIENTATION = PINKY_ORIENTATION = ORIENT_UP;

            //-------------------------------
            // 0cd7  3a024d    ld      a,(#4d02)
            // 0cda  fe64      cp      #64
            // 0cdc  c2fb0c    jp      nz,#0cfb
            //-------------------------------
            if (PINKY_POS.y == 0x64)
            {
                //-------------------------------
                // 0cdf  212c2e    ld      hl,#2e2c
                // 0ce2  220c4d    ld      (#4d0c),hl
                //-------------------------------
                PINKY_TILE.y = 0x2c;
                PINKY_TILE.x = 0x2e;

                //-------------------------------
                // 0ce5  210001    ld      hl,#0100
                // 0ce8  22164d    ld      (#4d16),hl
                // 0ceb  22204d    ld      (#4d20),hl
                //-------------------------------
                PINKY_VECTOR.y = PINKY_VECTOR2.y = 0x00;
                PINKY_VECTOR.x = PINKY_VECTOR2.x = 0x01;

                //-------------------------------
                // 0cee  3e02      ld      a,#02
                // 0cf0  32294d    ld      (#4d29),a
                // 0cf3  322d4d    ld      (#4d2d),a
                //-------------------------------
                PINKY_PREV_ORIENTATION = PINKY_ORIENTATION = ORIENT_LEFT;

                //-------------------------------
                // 0cf6  3e01      ld      a,#01
                // 0cf8  32a14d    ld      (#4da1),a
                //-------------------------------
                PINKY_SUBSTATE = SUBSTATE_CHASE;
            }
        }
    }

    //-------------------------------
    // 0cfb  3aa24d    ld      a,(#4da2)
    // 0cfe  fe01      cp      #01
    // 0d00  ca930d    jp      z,#0d93
    //-------------------------------
    // printf ("%s inky-sub = %d\n", __func__, INKY_SUBSTATE);
    if (INKY_SUBSTATE != SUBSTATE_CHASE)
    {
        // printf ("%s inky-y=%02x\n", __func__, INKY_POS.y);
        //-------------------------------
        // 0d03  fe00      cp      #00
        // 0d05  c22c0d    jp      nz,#0d2c
        //-------------------------------
        if (INKY_SUBSTATE == SUBSTATE_IN_HOUSE)
        {
            //-------------------------------
            // 0d08  3a044d    ld      a,(#4d04)
            // 0d0b  fe78      cp      #78
            // 0d0d  cc551f    call    z,#1f55
            // 0d10  fe80      cp      #80
            // 0d12  cc551f    call    z,#1f55
            //-------------------------------
            if (INKY_POS.y == 0x78 || INKY_POS.y == 0x80)
                inkyReverse_1f55();

            //-------------------------------
            // 0d15  3a2e4d    ld      a,(#4d2e)
            // 0d18  322a4d    ld      (#4d2a),a
            //-------------------------------
            INKY_PREV_ORIENTATION = INKY_ORIENTATION;

            //-------------------------------
            // 0d1b  dd21224d  ld      ix,#4d22
            // 0d1f  fd21044d  ld      iy,#4d04
            // 0d23  cd0020    call    #2000
            // 0d26  22044d    ld      (#4d04),hl
            //-------------------------------
            // printf ("%s inky tile-ch=%d,%d\n", __func__,
            // INKY_VECTOR2.x,INKY_VECTOR2.y);

            INKY_POS = addXYOffset_2000 (INKY_VECTOR2, INKY_POS);

            //-------------------------------
            // 0d29  c3930d    jp      #0d93
            //-------------------------------
        }
        else
        {
            //-------------------------------
            // 0d2c  3aa24d    ld      a,(#4da2)
            // 0d2f  fe03      cp      #03
            // 0d31  c2590d    jp      nz,#0d59
            //-------------------------------
            if (INKY_SUBSTATE == SUBSTATE_HOUSE_MOVE)
            {
                //-------------------------------
                // 0d34  dd21ff32  ld      ix,#32ff
                // 0d38  fd21044d  ld      iy,#4d04
                // 0d3c  cd0020    call    #2000
                // 0d3f  22044d    ld      (#4d04),hl
                //-------------------------------
                INKY_POS = addXYOffset_2000 (*MOVE_VECTOR_RIGHT, INKY_POS);

                //-------------------------------
                // 0d42  af        xor     a
                // 0d43  322a4d    ld      (#4d2a),a
                // 0d46  322e4d    ld      (#4d2e),a
                //-------------------------------
                INKY_PREV_ORIENTATION = INKY_ORIENTATION = ORIENT_RIGHT;

                //-------------------------------
                // 0d49  3a054d    ld      a,(#4d05)
                // 0d4c  fe80      cp      #80
                // 0d4e  c2930d    jp      nz,#0d93
                //-------------------------------
                if (INKY_POS.x == 0x80)
                {
                    //-------------------------------
                    // 0d51  3e02      ld      a,#02
                    // 0d53  32a24d    ld      (#4da2),a
                    // 0d56  c3930d    jp      #0d93
                    //-------------------------------
                    INKY_SUBSTATE = SUBSTATE_LEAVING_HOUSE;
                }
            }
            else
            {
                //-------------------------------
                // 0d59  dd210533  ld      ix,#3305
                // 0d5d  fd21044d  ld      iy,#4d04
                // 0d61  cd0020    call    #2000
                // 0d64  22044d    ld      (#4d04),hl
                //-------------------------------
                INKY_POS = addXYOffset_2000 (*MOVE_VECTOR_UP, INKY_POS);

                //-------------------------------
                // 0d67  3e03      ld      a,#03
                // 0d69  322a4d    ld      (#4d2a),a
                // 0d6c  322e4d    ld      (#4d2e),a
                //-------------------------------
                INKY_PREV_ORIENTATION = INKY_ORIENTATION = ORIENT_UP;

                //-------------------------------
                // 0d6f  3a044d    ld      a,(#4d04)
                // 0d72  fe64      cp      #64
                // 0d74  c2930d    jp      nz,#0d93
                //-------------------------------

                /*  Has inky finished his upward move to exit the house?  If so,
                 *  set his vector to left and mode to chase */

                if (INKY_POS.y == 0x64)
                {
                    //-------------------------------
                    // 0d77  212c2e    ld      hl,#2e2c
                    // 0d7a  220e4d    ld      (#4d0e),hl
                    //-------------------------------
                    INKY_TILE.y = 0x2c;
                    INKY_TILE.x = 0x2e;

                    //-------------------------------
                    // 0d7d  210001    ld      hl,#0100
                    // 0d80  22184d    ld      (#4d18),hl
                    // 0d83  22224d    ld      (#4d22),hl
                    //-------------------------------
                    INKY_VECTOR.y = INKY_VECTOR2.y = 0x00;
                    INKY_VECTOR.x = INKY_VECTOR2.x = 0x01;

                    //-------------------------------
                    // 0d86  3e02      ld      a,#02
                    // 0d88  322a4d    ld      (#4d2a),a
                    // 0d8b  322e4d    ld      (#4d2e),a
                    //-------------------------------
                    INKY_PREV_ORIENTATION = INKY_ORIENTATION = ORIENT_LEFT;

                    //-------------------------------
                    // 0d8e  3e01      ld      a,#01
                    // 0d90  32a24d    ld      (#4da2),a
                    //-------------------------------
                    INKY_SUBSTATE = SUBSTATE_CHASE;
                }
            }
        }
    }
    //-------------------------------
    // 0d93  3aa34d    ld      a,(#4da3)
    // 0d96  fe01      cp      #01
    // 0d98  c8        ret     z
    //-------------------------------
    if (CLYDE_SUBSTATE == SUBSTATE_CHASE)
        return;

    //-------------------------------
    // 0d99  fe00      cp      #00
    // 0d9b  c2c00d    jp      nz,#0dc0
    //-------------------------------
    if (CLYDE_SUBSTATE == SUBSTATE_IN_HOUSE)
    {
        //-------------------------------
        // 0d9e  3a064d    ld      a,(#4d06)
        // 0da1  fe78      cp      #78
        // 0da3  cc7c1f    call    z,#1f7c
        // 0da6  fe80      cp      #80
        // 0da8  cc7c1f    call    z,#1f7c
        //-------------------------------
        if (CLYDE_POS.y == 0x78 || CLYDE_POS.y == 0x80)
            clydeReverse_1f7c();

        //-------------------------------
        // 0dab  3a2f4d    ld      a,(#4d2f)
        // 0dae  322b4d    ld      (#4d2b),a
        //-------------------------------
        CLYDE_PREV_ORIENTATION = CLYDE_ORIENTATION;

        //-------------------------------
        // 0db1  dd21244d  ld      ix,#4d24
        // 0db5  fd21064d  ld      iy,#4d06
        // 0db9  cd0020    call    #2000
        // 0dbc  22064d    ld      (#4d06),hl
        // 0dbf  c9        ret     
        //-------------------------------
        CLYDE_POS = addXYOffset_2000 (CLYDE_VECTOR2, CLYDE_POS);
        return;
    }
    //-------------------------------
    // 0dc0  3aa34d    ld      a,(#4da3)
    // 0dc3  fe03      cp      #03
    // 0dc5  c2ea0d    jp      nz,#0dea
    //-------------------------------
    if (CLYDE_SUBSTATE == GHOST_STATE_HOUSE_MOVE)
    {
        //-------------------------------
        // 0dc8  dd210333  ld      ix,#3303
        // 0dcc  fd21064d  ld      iy,#4d06
        // 0dd0  cd0020    call    #2000
        // 0dd3  22064d    ld      (#4d06),hl
        //-------------------------------
        CLYDE_POS = addXYOffset_2000 (*MOVE_VECTOR_LEFT, CLYDE_POS);

        //-------------------------------
        // 0dd6  3e02      ld      a,#02
        // 0dd8  322b4d    ld      (#4d2b),a
        // 0ddb  322f4d    ld      (#4d2f),a
        //-------------------------------
        CLYDE_PREV_ORIENTATION = CLYDE_ORIENTATION = ORIENT_LEFT;

        //-------------------------------
        // 0dde  3a074d    ld      a,(#4d07)
        // 0de1  fe80      cp      #80
        // 0de3  c0        ret     nz
        //-------------------------------
        if (CLYDE_POS.x != 0x80)
            return;

        //-------------------------------
        // 0de4  3e02      ld      a,#02
        // 0de6  32a34d    ld      (#4da3),a
        // 0de9  c9        ret     
        //-------------------------------
        CLYDE_SUBSTATE = SUBSTATE_LEAVING_HOUSE;
        return;
    }

    //-------------------------------
    // 0dea  dd210533  ld      ix,#3305
    // 0dee  fd21064d  ld      iy,#4d06
    // 0df2  cd0020    call    #2000
    // 0df5  22064d    ld      (#4d06),hl
    //-------------------------------
    CLYDE_POS = addXYOffset_2000 (*MOVE_VECTOR_UP, CLYDE_POS);

    //-------------------------------
    // 0df8  3e03      ld      a,#03
    // 0dfa  322b4d    ld      (#4d2b),a
    // 0dfd  322f4d    ld      (#4d2f),a
    //-------------------------------
    CLYDE_PREV_ORIENTATION = CLYDE_ORIENTATION = ORIENT_UP;

    //-------------------------------
    // 0e00  3a064d    ld      a,(#4d06)
    // 0e03  fe64      cp      #64
    // 0e05  c0        ret     nz
    //-------------------------------
    if (CLYDE_POS.y != 0x64)
        return;

    //-------------------------------
    // 0e06  212c2e    ld      hl,#2e2c
    // 0e09  22104d    ld      (#4d10),hl
    //-------------------------------
    CLYDE_TILE.y = 0x2c;
    CLYDE_TILE.x = 0x2e;

    //-------------------------------
    // 0e0c  210001    ld      hl,#0100
    // 0e0f  221a4d    ld      (#4d1a),hl
    // 0e12  22244d    ld      (#4d24),hl
    //-------------------------------
    CLYDE_VECTOR.y = CLYDE_VECTOR2.y = 0x00;
    CLYDE_VECTOR.x = CLYDE_VECTOR2.x = 0x01;

    //-------------------------------
    // 0e15  3e02      ld      a,#02
    // 0e17  322b4d    ld      (#4d2b),a
    // 0e1a  322f4d    ld      (#4d2f),a
    //-------------------------------
    CLYDE_PREV_ORIENTATION = CLYDE_ORIENTATION = ORIENT_LEFT;

    //-------------------------------
    // 0e1d  3e01      ld      a,#01
    // 0e1f  32a34d    ld      (#4da3),a
    // 0e22  c9        ret     
    //-------------------------------
    CLYDE_SUBSTATE = SUBSTATE_CHASE;
}

void toggleGhostAnimation_0e23 (void)
{
    //-------------------------------
    // 0e23  21c44d    ld      hl,#4dc4
    // 0e26  34        inc     (hl)
    // 0e27  3e08      ld      a,#08
    // 0e29  be        cp      (hl)
    // 0e2a  c0        ret     nz
    //-------------------------------
    // printf ("%s count = %d\n", __func__, COUNTER_TO_8);
    if (COUNTER_TO_8++ != 8)
        return;
    //-------------------------------
    // 0e2b  3600      ld      (hl),#00
    //-------------------------------
    COUNTER_TO_8 = 0;

    //-------------------------------
    // 0e2d  3ac04d    ld      a,(#4dc0)
    // 0e30  ee01      xor     #01
    // 0e32  32c04d    ld      (#4dc0),a
    // 0e35  c9        ret     
    //-------------------------------
    // printf ("%s ghost anim = %d\n", __func__, GHOST_ANIMATION);
    GHOST_ANIMATION ^= 1;
}

void ghostsChangeOrientation_0e36 (void)
{
    //-------------------------------
    // 0e36  3aa64d    ld      a,(#4da6)
    // 0e39  a7        and     a
    // 0e3a  c0        ret     nz
    //-------------------------------
    if (PACMAN_POWEREDUP)
        return;

    //-------------------------------
    // 0e3b  3ac14d    ld      a,(#4dc1)
    // 0e3e  fe07      cp      #07
    // 0e40  c8        ret     z
    //-------------------------------
    if (NONRANDOM_MOVEMENT == 7)
        return;

    //-------------------------------
    // 0e41  87        add     a,a
    // 0e42  2ac24d    ld      hl,(#4dc2)
    // 0e45  23        inc     hl
    // 0e46  22c24d    ld      (#4dc2),hl
    //-------------------------------
    ORIENTATION_CHANGE_COUNT++;

    //-------------------------------
    // 0e49  5f        ld      e,a
    // 0e4a  1600      ld      d,#00
    // 0e4c  dd21864d  ld      ix,#4d86
    // 0e50  dd19      add     ix,de
    // 0e52  dd5e00    ld      e,(ix+#00)
    // 0e55  dd5601    ld      d,(ix+#01)
    // 0e58  a7        and     a
    // 0e59  ed52      sbc     hl,de
    // 0e5b  c0        ret     nz
    //-------------------------------
    /*  Note there is no need to double a and srl it after since our table is a
     *  16-bit ptr */
    if (ORIENTATION_CHANGE_COUNT != DIFFICULTY_TABLE[NONRANDOM_MOVEMENT])
        return;

    //-------------------------------
    // 0e5c  cb3f      srl     a
    // 0e5e  3c        inc     a
    // 0e5f  32c14d    ld      (#4dc1),a
    //-------------------------------
    NONRANDOM_MOVEMENT++;

    //-------------------------------
    // 0e62  210101    ld      hl,#0101
    // 0e65  22b14d    ld      (#4db1),hl
    // 0e68  22b34d    ld      (#4db3),hl
    // 0e6b  c9        ret     
    //-------------------------------
    BLINKY_ORIENT_CHG_FLAG = 
    PINKY_ORIENT_CHG_FLAG = 
    INKY_ORIENT_CHG_FLAG = 
    CLYDE_ORIENT_CHG_FLAG = 1;
}

void updatePillsEatenSoundEffect_0e6c (void)
{
    //-------------------------------
    // 0e6c  3aa54d    ld      a,(#4da5)
    // 0e6f  a7        and     a
    // 0e70  2805      jr      z,#0e77         ; (5)
    //-------------------------------
    if (PAC_DEAD_ANIM_STATE != 0)
    {
        //-------------------------------
        // 0e72  af        xor     a
        // 0e73  32ac4e    ld      (#4eac),a
        // 0e76  c9        ret     
        //-------------------------------
        CH2_SOUND_EFFECT->mask = 0;
        return;
    }

    //-------------------------------
    // 0e77  21ac4e    ld      hl,#4eac
    // 0e7a  06e0      ld      b,#e0
    // 0e7c  3a0e4e    ld      a,(#4e0e)
    // 0e7f  fee4      cp      #e4
    // 0e81  3806      jr      c,#0e89         ; (6)
    //-------------------------------
    if (P1_PILLS_EATEN_LEVEL >= 0xe4)
    {
        //-------------------------------
        // 0e83  78        ld      a,b
        // 0e84  a6        and     (hl)
        // 0e85  cbe7      set     4,a
        // 0e87  77        ld      (hl),a
        // 0e88  c9        ret     
        //-------------------------------
        CH2_SOUND_EFFECT->mask = (CH2_SOUND_EFFECT->mask & 0xe0) | 0x10;
        return;
    }

    //-------------------------------
    // 0e89  fed4      cp      #d4
    // 0e8b  3806      jr      c,#0e93         ; (6)
    //-------------------------------
    if (P1_PILLS_EATEN_LEVEL >= 0xd4)
    {
        //-------------------------------
        // 0e8d  78        ld      a,b
        // 0e8e  a6        and     (hl)
        // 0e8f  cbdf      set     3,a
        // 0e91  77        ld      (hl),a
        // 0e92  c9        ret     
        //-------------------------------
        CH2_SOUND_EFFECT->mask = (CH2_SOUND_EFFECT->mask & 0xe0) | 0x08;
        return;
    }

    //-------------------------------
    // 0e93  feb4      cp      #b4
    // 0e95  3806      jr      c,#0e9d         ; (6)
    //-------------------------------
    if (P1_PILLS_EATEN_LEVEL >= 0xb4)
    {
        //-------------------------------
        // 0e97  78        ld      a,b
        // 0e98  a6        and     (hl)
        // 0e99  cbd7      set     2,a
        // 0e9b  77        ld      (hl),a
        // 0e9c  c9        ret     
        //-------------------------------
        CH2_SOUND_EFFECT->mask = (CH2_SOUND_EFFECT->mask & 0xe0) | 0x04;
        return;
    }

    //-------------------------------
    // 0e9d  fe74      cp      #74
    // 0e9f  3806      jr      c,#0ea7         ; (6)
    //-------------------------------
    if (P1_PILLS_EATEN_LEVEL >= 0x74)
    {
        //-------------------------------
        // 0ea1  78        ld      a,b
        // 0ea2  a6        and     (hl)
        // 0ea3  cbcf      set     1,a
        // 0ea5  77        ld      (hl),a
        // 0ea6  c9        ret     
        //-------------------------------
        CH2_SOUND_EFFECT->mask = (CH2_SOUND_EFFECT->mask & 0xe0) | 0x02;
        return;
    }

    //-------------------------------
    // 0ea7  78        ld      a,b
    // 0ea8  a6        and     (hl)
    // 0ea9  cbc7      set     0,a
    // 0eab  77        ld      (hl),a
    // 0eac  c9        ret     
    //-------------------------------
    CH2_SOUND_EFFECT->mask = (CH2_SOUND_EFFECT->mask & 0xe0) | 0x01;
}

void selectFruit_0ead (void)
{
    //-------------------------------
    // 0ead  3aa54d    ld      a,(#4da5)
    // 0eb0  a7        and     a
    // 0eb1  c0        ret     nz
    //-------------------------------
    if (PAC_DEAD_ANIM_STATE != 0)
        return;

    //-------------------------------
    // 0eb2  3ad44d    ld      a,(#4dd4)
    // 0eb5  a7        and     a
    // 0eb6  c0        ret     nz
    //-------------------------------
    if (FRUIT_POINTS != 0)
        return;

    //-------------------------------
    // 0eb7  3a0e4e    ld      a,(#4e0e)
    // 0eba  fe46      cp      #46
    // 0ebc  280e      jr      z,#0ecc         ; (14)
    //-------------------------------
    if (P1_PILLS_EATEN_LEVEL != 0x46)
    {
        //-------------------------------
        // 0ebe  feaa      cp      #aa
        // 0ec0  c0        ret     nz
        //-------------------------------
        if (P1_PILLS_EATEN_LEVEL != 0xaa)
            return;

        //-------------------------------
        // 0ec1  3a0d4e    ld      a,(#4e0d)
        // 0ec4  a7        and     a
        // 0ec5  c0        ret     nz
        //-------------------------------
        if (P1_SECOND_FRUIT != 0)
            return;

        //-------------------------------
        // 0ec6  210d4e    ld      hl,#4e0d
        // 0ec9  34        inc     (hl)
        //-------------------------------
        P1_SECOND_FRUIT++;

        //-------------------------------
        // 0eca  1809      jr      #0ed5           ; (9)
        //-------------------------------
    }
    //-------------------------------
    // 0ecc  3a0c4e    ld      a,(#4e0c)
    // 0ecf  a7        and     a
    // 0ed0  c0        ret     nz
    //-------------------------------
    if (P1_FIRST_FRUIT != 0)
        return;

    //-------------------------------
    // 0ed1  210c4e    ld      hl,#4e0c
    // 0ed4  34        inc     (hl)
    //-------------------------------
    P1_FIRST_FRUIT++;

    //-------------------------------
    // 0ed5  219480    ld      hl,#8094
    // 0ed8  22d24d    ld      (#4dd2),hl
    //-------------------------------
    FRUIT_POS.x = 0x80;
    FRUIT_POS.y = 0x94;

    //-------------------------------
    // 0edb  21fd0e    ld      hl,#0efd
    // 0ede  3a134e    ld      a,(#4e13)
    //-------------------------------
    int a = P1_LEVEL;

    //-------------------------------
    // 0ee1  fe14      cp      #14
    // 0ee3  3802      jr      c,#0ee7         ; (2)
    // 0ee5  3e14      ld      a,#14
    //-------------------------------
    if (a > 20) a = 20;

    //-------------------------------
    // 0ee7  47        ld      b,a
    // 0ee8  87        add     a,a
    // 0ee9  80        add     a,b
    //-------------------------------
    a *= 3;

    //-------------------------------
    // 0eea  d7        rst     #10
    // 0eeb  320c4c    ld      (#4c0c),a
    //-------------------------------
    uint8_t *hl = FRUIT_DATA;
    FRUIT_SPRITE = fetchOffset_0010 (&hl, a);

    //-------------------------------
    // 0eee  23        inc     hl
    // 0eef  7e        ld      a,(hl)
    // 0ef0  320d4c    ld      (#4c0d),a
    //-------------------------------
    FRUIT_COLOUR = *hl++;

    //-------------------------------
    // 0ef3  23        inc     hl
    // 0ef4  7e        ld      a,(hl)
    // 0ef5  32d44d    ld      (#4dd4),a
    //-------------------------------
    FRUIT_POINTS = *hl;

    //-------------------------------
    // 0ef8  f7        rst     #30
    // 0ef9  8a0400
    //-------------------------------
    schedISRTask (0x8a, ISRTASK_RESET_FRUIT, 0);

    //-------------------------------
    // 0efc  c9        ret     
    //-------------------------------
}

    /*  Fruit data.  3 byte sets contains sprite, colour and points */

    // 0efd                                          00 14 06
    // 0f00  01 0f 07 02 15 08 02 15  08 04 14 09 04 14 09 05
    // 0f10  17 0a 05 17 0a 06 09 0b  06 09 0b 03 16 0c 03 16
    // 0f20  0c 07 16 0d 07 16 0d 07  16 0d 07 16 0d 07 16 0d
    // 0f30  07 16 0d 07 16 0d 07 16  0d 07 16 0d 00 00 00 00
    // 0f40  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0f50  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0f60  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0f70  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0f80  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0f90  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0fa0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0fb0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0fc0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0fd0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0fe0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 0ff0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 48 36

void resetFruit_1000 (void)
{
    //-------------------------------
    // 1000  af        xor     a
    // 1001  32d44d    ld      (#4dd4),a
    //-------------------------------
    FRUIT_POINTS = 0;
    resetFruitState_1004 ();
}

void resetFruitState_1004 (void)
{
    //-------------------------------
    // 1004  210000    ld      hl,#0000
    // 1007  22d24d    ld      (#4dd2),hl
    // 100a  c9        ret     
    //-------------------------------
    FRUIT_POS.y = 
    FRUIT_POS.x = 0;
}

void func_100b (void)
{
    //-------------------------------
    // 100b  ef        rst     #28
    // 100c  1c9b
    //-------------------------------
    schedTask (TASK_DISPLAY_MSG, 0x80 | MSG_100PTS);

    //-------------------------------
    // 100e  3a004e    ld      a,(#4e00)
    // 1011  3d        dec     a
    // 1012  c8        ret     z
    //-------------------------------
    if (MAIN_STATE == MAIN_STATE_DEMO)
        return;

    //-------------------------------
    // 1013  ef        rst     #28
    // 1014  1ca2
    // 1016  c9        ret     
    //-------------------------------
    schedTask (TASK_DISPLAY_MSG, 0x80 | MSG_5000PTS);
}

void updateGhostStates_1017 (void)
{
    //-------------------------------
    // 1017  cd9112    call    #1291
    // 101a  3aa54d    ld      a,(#4da5)
    // 101d  a7        and     a
    // 101e  c0        ret     nz
    //-------------------------------
    pacmanDeadAnimState_1291();

    printf ("%s dead = %d\n", __func__, PAC_DEAD_ANIM_STATE);
    if (PAC_DEAD_ANIM_STATE != 0)
        return;

    //-------------------------------
    // 101f  cd6610    call    #1066
    // 1022  cd9410    call    #1094
    // 1025  cd9e10    call    #109e
    // 1028  cda810    call    #10a8
    // 102b  cdb410    call    #10b4
    //-------------------------------
    selectGhostState_1066();
    blinkyStateMachine_1094();
    pinkyStateMachine_109e();
    inkyStateMachine_10a8();
    clydeStateMachine_10b4();

    //-------------------------------
    // 102e  3aa44d    ld      a,(#4da4)
    // 1031  a7        and     a
    // 1032  ca3910    jp      z,#1039
    //-------------------------------
    if (KILLED_GHOST_INDEX != 0)
    {
        //-------------------------------
        // 1035  cd3512    call    #1235
        // 1038  c9        ret     
        //-------------------------------
        ghostKilledState_1235();
        return;
    }

    //-------------------------------
    // 1039  cd1d17    call    #171d
    // 103c  cd8917    call    #1789
    //-------------------------------
    pacmanCheckGhostCoincidence_171d();
    pacmanCheckEatGhost_1789();

    //-------------------------------
    // 103f  3aa44d    ld      a,(#4da4)
    // 1042  a7        and     a
    // 1043  c0        ret     nz
    //-------------------------------
    if (KILLED_GHOST_INDEX != 0)
        return;

    //-------------------------------
    // 1044  cd0618    call    #1806
    // 1047  cd361b    call    #1b36
    // 104a  cd4b1c    call    #1c4b
    // 104d  cd221d    call    #1d22
    // 1050  cdf91d    call    #1df9
    //-------------------------------
    pacmanUpdateMovePat_1806();
    blinkyUpdateMovePat_1b36();
    pinkyUpdateMovePat_1c4b();
    inkyUpdateMovePat_1d22();
    clydeUpdateMovePat_1df9();

    //-------------------------------
    // 1053  3a044e    ld      a,(#4e04)
    // 1056  fe03      cp      #03
    // 1058  c0        ret     nz
    //-------------------------------
    if (LEVEL_STATE != 3)
        return;

    //-------------------------------
    // 1059  cd7613    call    #1376
    // 105c  cd6920    call    #2069
    // 105f  cd8c20    call    #208c
    // 1062  cdaf20    call    #20af
    // 1065  c9        ret     
    //-------------------------------
    powerupOver_1376();
    pinkyCheckLeaveHouse_2069();
    inkyCheckLeaveHouse_208c();
    clydeCheckLeaveHouse_20af();
}

void selectGhostState_1066 (void)
{
    //-------------------------------
    // 1066  3aab4d    ld      a,(#4dab)
    // 1069  a7        and     a
    // 106a  c8        ret     z
    //-------------------------------
    if (GHOST_STATE == 0)
        return;

    printf ("%s Kill g=%d\n", __func__, GHOST_STATE);

    //-------------------------------
    // 106b  3d        dec     a
    // 106c  2008      jr      nz,#1076        ; (8)
    //-------------------------------
    if (GHOST_STATE == GHOST_BLINKY)
    {
        //-------------------------------
        // 106e  32ab4d    ld      (#4dab),a
        // 1071  3c        inc     a
        // 1072  32ac4d    ld      (#4dac),a
        // 1075  c9        ret     
        //-------------------------------
        GHOST_STATE = 0;
        BLINKY_STATE = GHOST_STATE_DEAD;
        return;
    }

    //-------------------------------
    // 1076  3d        dec     a
    // 1077  2008      jr      nz,#1081        ; (8)
    //-------------------------------
    if (GHOST_STATE == GHOST_PINKY)
    {
        //-------------------------------
        // 1079  32ab4d    ld      (#4dab),a
        // 107c  3c        inc     a
        // 107d  32ad4d    ld      (#4dad),a
        // 1080  c9        ret     
        //-------------------------------
        GHOST_STATE = 0;
        PINKY_STATE = GHOST_STATE_DEAD;
        return;
    }

    //-------------------------------
    // 1081  3d        dec     a
    // 1082  2008      jr      nz,#108c        ; (8)
    //-------------------------------
    if (GHOST_STATE == GHOST_INKY)
    {
        //-------------------------------
        // 1084  32ab4d    ld      (#4dab),a
        // 1087  3c        inc     a
        // 1088  32ae4d    ld      (#4dae),a
        // 108b  c9        ret     
        //-------------------------------
        GHOST_STATE = 0;
        INKY_STATE = GHOST_STATE_DEAD;
        return;
    }

    //-------------------------------
    // 108c  32af4d    ld      (#4daf),a    ; assume a must be 1
    // 108f  3d        dec     a
    // 1090  32ab4d    ld      (#4dab),a    ; set to zero
    // 1093  c9        ret     
    //-------------------------------
    CLYDE_STATE = GHOST_STATE_DEAD;
    GHOST_STATE = 0;
}

void blinkyStateMachine_1094 (void)
{
    printf ("%s st = %d\n", __func__, BLINKY_STATE);
    //-------------------------------
    // 1094  3aac4d    ld      a,(#4dac)
    // 1097  e7        rst     #20
    // 1098  0c00 c010 d210 
    //-------------------------------
    void (*func[])() =
    {
        nothing_000c,
        blinkyStateDead_10c0,
        blinkyStateEnterHouse_10d2
    };
    tableCall_0020 (func, BLINKY_STATE);
}

void pinkyStateMachine_109e (void)
{
    //-------------------------------
    // 109e  3aad4d    ld      a,(#4dad)
    // 10a1  e7        rst     #20
    // 10a2  0c00 1811 2a11
    //-------------------------------
    void (*func[])() =
    {
        nothing_000c,
        pinkyStateDead_1118,
        pinkyStateEnterHouse_112a
    };
    tableCall_0020 (func, PINKY_STATE);
}

void inkyStateMachine_10a8 (void)
{
    //-------------------------------
    // 10a8  3aae4d    ld      a,(#4dae)
    // 10ab  e7        rst     #20
    // 10ac  0c00 5c11 6e11 8f11
    //-------------------------------
    void (*func[])() =
    {
        nothing_000c,
        inkyStateDead_115c,
        inkyStateEnterHouse_116e,
        inkyStateHouseMoveAside_118f
    };
    tableCall_0020 (func, INKY_STATE);
}

void clydeStateMachine_10b4 (void)
{
    //-------------------------------
    // 10b4  3aaf4d    ld      a,(#4daf)
    // 10b7  e7        rst     #20
    // 10b8  0c00 c911 db11 fc11
    //-------------------------------
    void (*func[])() = 
    {
        nothing_000c,
        clydeStateDead_11c9,
        clydeStateEnterHouse_11db,
        clydeStateHouseMoveAside_11fc
    };
    tableCall_0020 (func, CLYDE_STATE);
}

void blinkyStateDead_10c0 (void)
{
    //-------------------------------
    // 10c0  cdd81b    call    #1bd8
    // 10c3  2a004d    ld      hl,(#4d00)
    // 10c6  116480    ld      de,#8064
    // 10c9  a7        and     a
    // 10ca  ed52      sbc     hl,de
    // 10cc  c0        ret     nz
    //-------------------------------
    blinkyUpdatePosition_1bd8();
    if (BLINKY_POS.x != 0x80 || BLINKY_POS.y != 0x64)
        return;

    //-------------------------------
    // 10cd  21ac4d    ld      hl,#4dac
    // 10d0  34        inc     (hl)
    // 10d1  c9        ret     
    //-------------------------------
    BLINKY_STATE++;
}

void blinkyStateEnterHouse_10d2 (void)
{
    //-------------------------------
    // 10d2  dd210133  ld      ix,#3301
    // 10d6  fd21004d  ld      iy,#4d00
    // 10da  cd0020    call    #2000
    // 10dd  22004d    ld      (#4d00),hl
    //-------------------------------
    BLINKY_POS = addXYOffset_2000(*MOVE_VECTOR_DOWN, BLINKY_POS);

    //-------------------------------
    // 10e0  3e01      ld      a,#01
    // 10e2  32284d    ld      (#4d28),a
    // 10e5  322c4d    ld      (#4d2c),a
    //-------------------------------
    BLINKY_PREV_ORIENTATION = 
    BLINKY_ORIENTATION = ORIENT_DOWN;

    //-------------------------------
    // 10e8  3a004d    ld      a,(#4d00)
    // 10eb  fe80      cp      #80
    // 10ed  c0        ret     nz
    //-------------------------------
    if (BLINKY_POS.y != 0x80)
        return;

    //-------------------------------
    // 10ee  212f2e    ld      hl,#2e2f
    // 10f1  220a4d    ld      (#4d0a),hl
    // 10f4  22314d    ld      (#4d31),hl
    //-------------------------------
    BLINKY_TILE.y = BLINKY_TILE2.y = 0x2f;
    BLINKY_TILE.x = BLINKY_TILE2.x = 0x2e;

    //-------------------------------
    // 10f7  af        xor     a
    // 10f8  32a04d    ld      (#4da0),a
    // 10fb  32ac4d    ld      (#4dac),a
    // 10fe  32a74d    ld      (#4da7),a
    //-------------------------------
    BLINKY_SUBSTATE = SUBSTATE_IN_HOUSE;
    BLINKY_STATE = GHOST_STATE_ALIVE;
    BLINKY_EDIBLE = 0;
    ghostsAnyDeadSoundOff_1101 ();
}

void ghostsAnyDeadSoundOff_1101 (void)
{
    //-------------------------------
    // 1101  dd21ac4d  ld      ix,#4dac
    // 1105  ddb600    or      (ix+#00)
    // 1108  ddb601    or      (ix+#01)
    // 110b  ddb602    or      (ix+#02)
    // 110e  ddb603    or      (ix+#03)
    // 1111  c0        ret     nz
    //-------------------------------
    if (BLINKY_STATE | PINKY_STATE | INKY_STATE | CLYDE_STATE)
        return;

    //-------------------------------
    // 1112  21ac4e    ld      hl,#4eac
    // 1115  cbb6      res     6,(hl)
    // 1117  c9        ret     
    //-------------------------------
    CH2_SOUND_EFFECT->mask &= ~0x40;
}

void pinkyStateDead_1118 (void)
{
    //-------------------------------
    // 1118  cdaf1c    call    #1caf
    // 111b  2a024d    ld      hl,(#4d02)
    // 111e  116480    ld      de,#8064
    // 1121  a7        and     a
    // 1122  ed52      sbc     hl,de
    // 1124  c0        ret     nz
    //-------------------------------
    pinkyUpdatePosition_1caf ();
    if (PINKY_POS.x != 0x80 || PINKY_POS.y != 0x64)
        return;

    //-------------------------------
    // 1125  21ad4d    ld      hl,#4dad
    // 1128  34        inc     (hl)
    // 1129  c9        ret     
    //-------------------------------
    PINKY_STATE++;
}

void pinkyStateEnterHouse_112a (void)
{
    //-------------------------------
    // 112a  dd210133  ld      ix,#3301
    // 112e  fd21024d  ld      iy,#4d02
    // 1132  cd0020    call    #2000
    // 1135  22024d    ld      (#4d02),hl
    //-------------------------------
    PINKY_POS = addXYOffset_2000 (*MOVE_VECTOR_DOWN, PINKY_POS);

    //-------------------------------
    // 1138  3e01      ld      a,#01
    // 113a  32294d    ld      (#4d29),a
    // 113d  322d4d    ld      (#4d2d),a
    //-------------------------------
    PINKY_ORIENTATION = PINKY_PREV_ORIENTATION = ORIENT_DOWN;

    //-------------------------------
    // 1140  3a024d    ld      a,(#4d02)
    // 1143  fe80      cp      #80
    // 1145  c0        ret     nz
    //-------------------------------
    if (PINKY_POS.y != 0x80)
        return;

    //-------------------------------
    // 1146  212f2e    ld      hl,#2e2f
    // 1149  220c4d    ld      (#4d0c),hl
    // 114c  22334d    ld      (#4d33),hl
    //-------------------------------
    PINKY_TILE.y = PINKY_TILE2.y = 0x2f;
    PINKY_TILE.x = PINKY_TILE2.x = 0x2e;

    //-------------------------------
    // 114f  af        xor     a
    // 1150  32a14d    ld      (#4da1),a
    // 1153  32ad4d    ld      (#4dad),a
    // 1156  32a84d    ld      (#4da8),a
    //-------------------------------
    PINKY_SUBSTATE = SUBSTATE_IN_HOUSE;
    PINKY_STATE = GHOST_STATE_ALIVE;
    PINKY_EDIBLE = 0;

    //-------------------------------
    // 1159  c30111    jp      #1101
    //-------------------------------
    ghostsAnyDeadSoundOff_1101();
}

void inkyStateDead_115c (void)
{
    //-------------------------------
    // 115c  cd861d    call    #1d86
    //-------------------------------
    inkyUpdatePosition_1d86();

    //-------------------------------
    // 115f  2a044d    ld      hl,(#4d04)
    // 1162  116480    ld      de,#8064
    // 1165  a7        and     a
    // 1166  ed52      sbc     hl,de
    // 1168  c0        ret     nz
    //-------------------------------
    if (INKY_POS.x != 0x80 || INKY_POS.y != 0x64)
        return;

    //-------------------------------
    // 1169  21ae4d    ld      hl,#4dae
    // 116c  34        inc     (hl)
    // 116d  c9        ret     
    //-------------------------------
    INKY_STATE++;
}

void inkyStateEnterHouse_116e (void)
{
    //-------------------------------
    // 116e  dd210133  ld      ix,#3301
    // 1172  fd21044d  ld      iy,#4d04
    // 1176  cd0020    call    #2000
    // 1179  22044d    ld      (#4d04),hl
    //-------------------------------
    INKY_POS = addXYOffset_2000 (*MOVE_VECTOR_DOWN, INKY_POS);

    //-------------------------------
    // 117c  3e01      ld      a,#01
    // 117e  322a4d    ld      (#4d2a),a
    // 1181  322e4d    ld      (#4d2e),a
    //-------------------------------
    INKY_ORIENTATION = INKY_PREV_ORIENTATION = ORIENT_DOWN;

    //-------------------------------
    // 1184  3a044d    ld      a,(#4d04)
    // 1187  fe80      cp      #80
    // 1189  c0        ret     nz
    //-------------------------------
    if (INKY_POS.y != 0x80)
        return;

    //-------------------------------
    // 118a  21ae4d    ld      hl,#4dae
    // 118d  34        inc     (hl)
    // 118e  c9        ret     
    //-------------------------------
    INKY_STATE++;
}

void inkyStateHouseMoveAside_118f (void)
{
    //-------------------------------
    // 118f  dd210333  ld      ix,#3303
    // 1193  fd21044d  ld      iy,#4d04
    // 1197  cd0020    call    #2000
    // 119a  22044d    ld      (#4d04),hl
    //-------------------------------
    INKY_POS = addXYOffset_2000 (*MOVE_VECTOR_LEFT, INKY_POS);

    //-------------------------------
    // 119d  3e02      ld      a,#02
    // 119f  322a4d    ld      (#4d2a),a
    // 11a2  322e4d    ld      (#4d2e),a
    //-------------------------------
    INKY_ORIENTATION = INKY_PREV_ORIENTATION = ORIENT_LEFT;

    //-------------------------------
    // 11a5  3a054d    ld      a,(#4d05)
    // 11a8  fe90      cp      #90
    // 11aa  c0        ret     nz
    //-------------------------------
    if (INKY_POS.x != 0x90)
        return;

    //-------------------------------
    // 11ab  212f30    ld      hl,#302f
    // 11ae  220e4d    ld      (#4d0e),hl
    // 11b1  22354d    ld      (#4d35),hl
    //-------------------------------
    INKY_TILE.y = INKY_TILE2.y = 0x2f;
    INKY_TILE.x = INKY_TILE2.x = 0x30;

    //-------------------------------
    // 11b4  3e01      ld      a,#01
    // 11b6  322a4d    ld      (#4d2a),a
    // 11b9  322e4d    ld      (#4d2e),a
    //-------------------------------
    INKY_ORIENTATION = INKY_PREV_ORIENTATION = ORIENT_DOWN;

    //-------------------------------
    // 11bc  af        xor     a
    // 11bd  32a24d    ld      (#4da2),a
    // 11c0  32ae4d    ld      (#4dae),a
    // 11c3  32a94d    ld      (#4da9),a
    //-------------------------------
    INKY_SUBSTATE = SUBSTATE_IN_HOUSE;
    INKY_STATE = GHOST_STATE_ALIVE;
    INKY_EDIBLE = 0;

    //-------------------------------
    // 11c6  c30111    jp      #1101
    //-------------------------------
    ghostsAnyDeadSoundOff_1101();
}

void clydeStateDead_11c9 (void)
{
    //-------------------------------
    // 11c9  cd5d1e    call    #1e5d
    //-------------------------------
    clydeUpdatePosition_1e5d();

    //-------------------------------
    // 11cc  2a064d    ld      hl,(#4d06)
    // 11cf  116480    ld      de,#8064
    // 11d2  a7        and     a
    // 11d3  ed52      sbc     hl,de
    // 11d5  c0        ret     nz
    //-------------------------------
    if (CLYDE_POS.x != 0x80 || CLYDE_POS.y != 0x64)
        return;

    //-------------------------------
    // 11d6  21af4d    ld      hl,#4daf
    // 11d9  34        inc     (hl)
    // 11da  c9        ret     
    //-------------------------------
    CLYDE_STATE++;
}

void clydeStateEnterHouse_11db (void)
{
    //-------------------------------
    // 11db  dd210133  ld      ix,#3301
    // 11df  fd21064d  ld      iy,#4d06
    // 11e3  cd0020    call    #2000
    // 11e6  22064d    ld      (#4d06),hl
    //-------------------------------
    CLYDE_POS = addXYOffset_2000 (*MOVE_VECTOR_DOWN, CLYDE_POS);

    //-------------------------------
    // 11e9  3e01      ld      a,#01
    // 11eb  322b4d    ld      (#4d2b),a
    // 11ee  322f4d    ld      (#4d2f),a
    //-------------------------------
    CLYDE_ORIENTATION = CLYDE_PREV_ORIENTATION = ORIENT_DOWN;

    //-------------------------------
    // 11f1  3a064d    ld      a,(#4d06)
    // 11f4  fe80      cp      #80
    // 11f6  c0        ret     nz
    //-------------------------------
    if (CLYDE_POS.y != 0x80)
        return;

    //-------------------------------
    // 11f7  21af4d    ld      hl,#4daf
    // 11fa  34        inc     (hl)
    // 11fb  c9        ret     
    //-------------------------------
    CLYDE_STATE++;
}

void clydeStateHouseMoveAside_11fc (void)
{
    //-------------------------------
    // 11fc  dd21ff32  ld      ix,#32ff
    // 1200  fd21064d  ld      iy,#4d06
    // 1204  cd0020    call    #2000
    // 1207  22064d    ld      (#4d06),hl
    //-------------------------------
    CLYDE_POS = addXYOffset_2000 (*MOVE_VECTOR_RIGHT, CLYDE_POS);

    //-------------------------------
    // 120a  af        xor     a
    // 120b  322b4d    ld      (#4d2b),a
    // 120e  322f4d    ld      (#4d2f),a
    //-------------------------------
    CLYDE_ORIENTATION = CLYDE_PREV_ORIENTATION = ORIENT_RIGHT;

    //-------------------------------
    // 1211  3a074d    ld      a,(#4d07)
    // 1214  fe70      cp      #70
    // 1216  c0        ret     nz
    //-------------------------------
    if (CLYDE_POS.x != 0x70)
        return;

    //-------------------------------
    // 1217  212f2c    ld      hl,#2c2f
    // 121a  22104d    ld      (#4d10),hl
    // 121d  22374d    ld      (#4d37),hl
    //-------------------------------
    CLYDE_TILE.y = CLYDE_TILE2.y = 0x2f;
    CLYDE_TILE.x = CLYDE_TILE2.x = 0x2c;

    //-------------------------------
    // 1220  3e01      ld      a,#01
    // 1222  322b4d    ld      (#4d2b),a
    // 1225  322f4d    ld      (#4d2f),a
    //-------------------------------
    CLYDE_ORIENTATION = CLYDE_PREV_ORIENTATION = ORIENT_DOWN;

    //-------------------------------
    // 1228  af        xor     a
    // 1229  32a34d    ld      (#4da3),a
    // 122c  32af4d    ld      (#4daf),a
    // 122f  32aa4d    ld      (#4daa),a
    //-------------------------------
    CLYDE_SUBSTATE = SUBSTATE_IN_HOUSE;
    CLYDE_STATE = GHOST_STATE_ALIVE;
    CLYDE_EDIBLE = 0;

    //-------------------------------
    // 1232  c30111    jp      #1101
    //-------------------------------
    ghostsAnyDeadSoundOff_1101();
}

void ghostKilledState_1235 (void)
{
    //-------------------------------
    // 1235  3ad14d    ld      a,(#4dd1)
    // 1238  e7        rst     #20
    // 1239  3f 12 0c 00 3f 12 
    //-------------------------------
    void (*func[])() =
    {
        showKillPoints_123f,
        nothing_000c,
        showKillPoints_123f
    };
    tableCall_0020 (func, KILLED_STATE);
}

void showKillPoints_123f (void)
{
    //-------------------------------
    // 123f  21004c    ld      hl,#4c00
    // 1242  3aa44d    ld      a,(#4da4)
    // 1245  87        add     a,a
    // 1246  5f        ld      e,a
    // 1247  1600      ld      d,#00
    // 1249  19        add     hl,de
    //-------------------------------
    uint8_t *hl = &BLINKY_SPRITE + KILLED_GHOST_INDEX * 2 - 2;
    printf ("%s points for sprite %04lx st=%d ix=%d c=%d\n", __func__, hl-MEM,
            KILLED_STATE, KILLED_GHOST_INDEX, KILLED_COUNT);

    //-------------------------------
    // 124a  3ad14d    ld      a,(#4dd1)
    // 124d  a7        and     a
    // 124e  2027      jr      nz,#1277        ; (39)
    //-------------------------------
    if (KILLED_STATE == 0)
    {
        //-------------------------------
        // 1250  3ad04d    ld      a,(#4dd0)
        // 1253  0627      ld      b,#27
        // 1255  80        add     a,b
        // 1256  47        ld      b,a
        //-------------------------------
        uint8_t b = KILLED_COUNT + 0x27;

        //-------------------------------
        // 1257  3a724e    ld      a,(#4e72)
        // 125a  4f        ld      c,a
        // 125b  3a094e    ld      a,(#4e09)
        // 125e  a1        and     c
        // 125f  2804      jr      z,#1265         ; (4)
        //-------------------------------
        if ((COCKTAIL_MODE & PLAYER) != 0)
        {
            //-------------------------------
            // 1261  cbf0      set     6,b
            // 1263  cbf8      set     7,b
            //-------------------------------
            b |= (IMG_MIRROR | IMG_INVERT);
        }

        //-------------------------------
        // 1265  70        ld      (hl),b
        //-------------------------------
        hl[0] = b;

        //-------------------------------
        // 1266  23        inc     hl
        // 1267  3618      ld      (hl),#18
        //-------------------------------
        hl[1] = 0x18;

        //-------------------------------
        // 1269  3e00      ld      a,#00
        // 126b  320b4c    ld      (#4c0b),a
        //-------------------------------

        /*  Make pacman transparent while the points for the kill are displayed */
        PACMAN_COLOUR = 0;

        //-------------------------------
        // 126e  f7        rst     #30
        // 126f  4a0300
        //-------------------------------

        /*  Schedule a timer to advance to state 2 to allow the points to linger
         *  on screen */
        schedISRTask (0x4a, ISRTASK_INC_KILLED_STATE, 0x00);

        //-------------------------------
        // 1272  21d14d    ld      hl,#4dd1
        // 1275  34        inc     (hl)
        // 1276  c9        ret     
        //-------------------------------

        /*  Advance to state 1, which just waits for state 2 */
        KILLED_STATE++;
        return;
    }

    //-------------------------------
    // 1277  3620      ld      (hl),#20
    //-------------------------------
    hl[0] = 0x20;

    //-------------------------------
    // 1279  3e09      ld      a,#09
    // 127b  320b4c    ld      (#4c0b),a
    //-------------------------------

    /*  pacman back to yellow */
    PACMAN_COLOUR = 9;

    //-------------------------------
    // 127e  3aa44d    ld      a,(#4da4)
    // 1281  32ab4d    ld      (#4dab),a
    //-------------------------------
    GHOST_STATE = KILLED_GHOST_INDEX;
    printf ("%s ghost state=%d\n", __func__, GHOST_STATE);

    //-------------------------------
    // 1284  af        xor     a
    // 1285  32a44d    ld      (#4da4),a
    // 1288  32d14d    ld      (#4dd1),a
    //-------------------------------
    KILLED_GHOST_INDEX = 
    KILLED_STATE = 0;

    //-------------------------------
    // 128b  21ac4e    ld      hl,#4eac
    // 128e  cbf6      set     6,(hl)
    // 1290  c9        ret     
    //-------------------------------
    CH2_SOUND_EFFECT->mask |= 0x40;
}

void pacmanDeadAnimState_1291 (void)
{
    //-------------------------------
    // 1291  3aa54d    ld      a,(#4da5)
    // 1294  e7        rst     #20
    //
    // 1295                 0c 00 b7  12 b7 12 b7 12 b7 12 cb 
    // 12a0  12 f9 12 06 13 0e 13 16  13 1e 13 26 13 2e 13 36 
    // 12b0  13 3e 13 46 13 53 13                             
    //-------------------------------
    void (*func[])() = 
    {
        nothing_000c,
        pacmanDeadAnimState1To4_12b7,
        pacmanDeadAnimState1To4_12b7,
        pacmanDeadAnimState1To4_12b7,
        pacmanDeadAnimState1To4_12b7,
        pacmanDeadAnimState5_12cb,
        pacmanDeadAnimState6_12f9,
        pacmanDeadAnimState7_1306,
        pacmanDeadAnimState8_130e,
        pacmanDeadAnimState9_1316,
        pacmanDeadAnimState10_131e,
        pacmanDeadAnimState11_1326,
        pacmanDeadAnimState12_132e,
        pacmanDeadAnimState13_1336,
        pacmanDeadAnimState14_133e,
        pacmanDeadAnimState15_1346,
        decrementLives_1353
    };
    tableCall_0020 (func, PAC_DEAD_ANIM_STATE);
}

void incKilledState_1272 (void)
{
    printf ("%s\n", __func__);
    KILLED_STATE++;
}

void pacmanDeadAnimState1To4_12b7 (void)
{
    //-------------------------------
    // 12b7  2ac54d    ld      hl,(#4dc5)
    // 12ba  23        inc     hl
    // 12bb  22c54d    ld      (#4dc5),hl
    // 12be  117800    ld      de,#0078
    // 12c1  a7        and     a
    // 12c2  ed52      sbc     hl,de
    // 12c4  c0        ret     nz
    //-------------------------------
    COUNT_SINCE_PAC_KILLED++;
    if (COUNT_SINCE_PAC_KILLED != 0x78)
        return;

    //-------------------------------
    // 12c5  3e05      ld      a,#05
    // 12c7  32a54d    ld      (#4da5),a
    // 12ca  c9        ret     
    //-------------------------------
    PAC_DEAD_ANIM_STATE = 5;
}

void pacmanDeadAnimState5_12cb (void)
{
    //-------------------------------
    // 12cb  210000    ld      hl,#0000
    // 12ce  cd7e26    call    #267e
    // 12d1  3e34      ld      a,#34
    // 12d3  11b400    ld      de,#00b4
    //-------------------------------
    setGhostPosition_267e(0, 0);
    pacmanDeadAnimation_12d6(0x34, 0xb4);
}

void pacmanDeadAnimation_12d6(int ch, int count)
{
    //-------------------------------
    // 12d6  4f        ld      c,a
    // 12d7  3a724e    ld      a,(#4e72)
    // 12da  47        ld      b,a
    // 12db  3a094e    ld      a,(#4e09)
    // 12de  a0        and     b
    // 12df  2804      jr      z,#12e5         ; (4)
    //-------------------------------
    if (COCKTAIL_MODE & PLAYER)
    {
        //-------------------------------
        // 12e1  3ec0      ld      a,#c0
        // 12e3  b1        or      c
        // 12e4  4f        ld      c,a
        //-------------------------------
        ch |= 0xc0;
    }

    //-------------------------------
    // 12e5  79        ld      a,c
    // 12e6  320a4c    ld      (#4c0a),a
    //-------------------------------
    PACMAN_SPRITE = ch;

    //-------------------------------
    // 12e9  2ac54d    ld      hl,(#4dc5)
    // 12ec  23        inc     hl
    // 12ed  22c54d    ld      (#4dc5),hl
    // 12f0  a7        and     a
    // 12f1  ed52      sbc     hl,de
    // 12f3  c0        ret     nz
    //-------------------------------
    if (++COUNT_SINCE_PAC_KILLED != count)
        return;

    //-------------------------------
    // 12f4  21a54d    ld      hl,#4da5
    // 12f7  34        inc     (hl)
    // 12f8  c9        ret     
    //-------------------------------
    PAC_DEAD_ANIM_STATE++;
}

void pacmanDeadAnimState6_12f9 (void)
{
    //-------------------------------
    // 12f9  21bc4e    ld      hl,#4ebc
    // 12fc  cbe6      set     4,(hl)
    //-------------------------------
    CH3_SOUND_EFFECT->mask |= 0x10;

    //-------------------------------
    // 12fe  3e35      ld      a,#35
    // 1300  11c300    ld      de,#00c3
    // 1303  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x35, 0xc3);
}

void pacmanDeadAnimState7_1306 (void)
{
    //-------------------------------
    // 1306  3e36      ld      a,#36
    // 1308  11d200    ld      de,#00d2
    // 130b  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x36, 0xd2);
}

void pacmanDeadAnimState8_130e (void)
{
    //-------------------------------
    // 130e  3e37      ld      a,#37
    // 1310  11e100    ld      de,#00e1
    // 1313  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x37, 0xe1);
}

void pacmanDeadAnimState9_1316 (void)
{
    //-------------------------------
    // 1316  3e38      ld      a,#38
    // 1318  11f000    ld      de,#00f0
    // 131b  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x38, 0xf0);
}

void pacmanDeadAnimState10_131e (void)
{
    //-------------------------------
    // 131e  3e39      ld      a,#39
    // 1320  11ff00    ld      de,#00ff
    // 1323  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x39, 0xff);
}

void pacmanDeadAnimState11_1326 (void)
{
    //-------------------------------
    // 1326  3e3a      ld      a,#3a
    // 1328  110e01    ld      de,#010e
    // 132b  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x3a, 0x10e);
}

void pacmanDeadAnimState12_132e (void)
{
    //-------------------------------
    // 132e  3e3b      ld      a,#3b
    // 1330  111d01    ld      de,#011d
    // 1333  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x3b, 0x11d);
}

void pacmanDeadAnimState13_1336 (void)
{
    //-------------------------------
    // 1336  3e3c      ld      a,#3c
    // 1338  112c01    ld      de,#012c
    // 133b  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x3c, 0x12c);
}

void pacmanDeadAnimState14_133e (void)
{
    //-------------------------------
    // 133e  3e3d      ld      a,#3d
    // 1340  113b01    ld      de,#013b
    // 1343  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x3d, 0x13b);
}

void pacmanDeadAnimState15_1346 (void)
{
    //-------------------------------
    // 1346  21bc4e    ld      hl,#4ebc
    // 1349  3620      ld      (hl),#20
    //-------------------------------
    CH3_SOUND_EFFECT->mask = 0x20;

    //-------------------------------
    // 134b  3e3e      ld      a,#3e
    // 134d  115901    ld      de,#0159
    // 1350  c3d612    jp      #12d6
    //-------------------------------
    pacmanDeadAnimation_12d6(0x3e, 0x159);
}

void decrementLives_1353 (void)
{
    //-------------------------------
    // 1353  3e3f      ld      a,#3f
    // 1355  320a4c    ld      (#4c0a),a
    //-------------------------------
    PACMAN_SPRITE = 0x3f;

    //-------------------------------
    // 1358  2ac54d    ld      hl,(#4dc5)
    // 135b  23        inc     hl
    // 135c  22c54d    ld      (#4dc5),hl
    // 135f  11b801    ld      de,#01b8
    // 1362  a7        and     a
    // 1363  ed52      sbc     hl,de
    // 1365  c0        ret     nz
    //-------------------------------
    if (++COUNT_SINCE_PAC_KILLED != 0x1b8)
        return;

    //-------------------------------
    // 1366  21144e    ld      hl,#4e14
    // 1369  35        dec     (hl)
    // 136a  21154e    ld      hl,#4e15
    // 136d  35        dec     (hl)
    // 136e  cd7526    call    #2675
    //-------------------------------
    P1_REAL_LIVES--;
    P1_DISPLAY_LIVES--;
    resetPositions_2675();

    //-------------------------------
    // 1371  21044e    ld      hl,#4e04
    // 1374  34        inc     (hl)
    // 1375  c9        ret     
    //-------------------------------
    LEVEL_STATE++;
}

void powerupOver_1376 (void)
{
    //-------------------------------
    // 1376  3aa64d    ld      a,(#4da6)
    // 1379  a7        and     a
    // 137a  c8        ret     z
    //-------------------------------
    if (PACMAN_POWEREDUP == 0)
        return;

    //-------------------------------
    // 137b  dd21a74d  ld      ix,#4da7
    // 137f  dd7e00    ld      a,(ix+#00)
    // 1382  ddb601    or      (ix+#01)
    // 1385  ddb602    or      (ix+#02)
    // 1388  ddb603    or      (ix+#03)
    // 138b  ca9813    jp      z,#1398
    //-------------------------------
    if ((*(uint32_t*)&BLINKY_EDIBLE) != 0)
    {
        //-------------------------------
        // 138e  2acb4d    ld      hl,(#4dcb)
        // 1391  2b        dec     hl
        // 1392  22cb4d    ld      (#4dcb),hl
        // 1395  7c        ld      a,h
        // 1396  b5        or      l
        // 1397  c0        ret     nz
        //-------------------------------
        if (--EDIBLE_REMAIN_COUNT != 0)
            return;
    }

    //-------------------------------
    // 1398  210b4c    ld      hl,#4c0b
    // 139b  3609      ld      (hl),#09
    //-------------------------------
    PACMAN_COLOUR = 9;

    //-------------------------------
    // 139d  3aac4d    ld      a,(#4dac)
    // 13a0  a7        and     a
    // 13a1  c2a713    jp      nz,#13a7
    //-------------------------------
    if (BLINKY_STATE == GHOST_STATE_ALIVE)
    {
        //-------------------------------
        // 13a4  32a74d    ld      (#4da7),a
        //-------------------------------
        BLINKY_EDIBLE = 0;
    }

    //-------------------------------
    // 13a7  3aad4d    ld      a,(#4dad)
    // 13aa  a7        and     a
    // 13ab  c2b113    jp      nz,#13b1
    //-------------------------------
    if (PINKY_STATE == GHOST_STATE_ALIVE)
    {

        //-------------------------------
        // 13ae  32a84d    ld      (#4da8),a
        //-------------------------------
        PINKY_EDIBLE = 0;
    }

    //-------------------------------
    // 13b1  3aae4d    ld      a,(#4dae)
    // 13b4  a7        and     a
    // 13b5  c2bb13    jp      nz,#13bb
    //-------------------------------
    if (INKY_STATE == GHOST_STATE_ALIVE)
    {
        //-------------------------------
        // 13b8  32a94d    ld      (#4da9),a
        //-------------------------------
        INKY_EDIBLE = 0;
    }

    //-------------------------------
    // 13bb  3aaf4d    ld      a,(#4daf)
    // 13be  a7        and     a
    // 13bf  c2c513    jp      nz,#13c5
    //-------------------------------
    if (CLYDE_STATE == GHOST_STATE_ALIVE)
    {
        //-------------------------------
        // 13c2  32aa4d    ld      (#4daa),a
        //-------------------------------
        CLYDE_EDIBLE = 0;
    }

    //-------------------------------
    // 13c5  af        xor     a
    // 13c6  32cb4d    ld      (#4dcb),a
    // 13c9  32cc4d    ld      (#4dcc),a
    // 13cc  32a64d    ld      (#4da6),a
    // 13cf  32c84d    ld      (#4dc8),a
    // 13d2  32d04d    ld      (#4dd0),a
    //-------------------------------
    EDIBLE_REMAIN_COUNT = 0;
    PACMAN_POWEREDUP = 0;
    GHOST_COL_POWERUP_COUNTER = 0;
    KILLED_COUNT = 0;

    //-------------------------------
    // 13d5  21ac4e    ld      hl,#4eac
    // 13d8  cbae      res     5,(hl)
    // 13da  cbbe      res     7,(hl)
    // 13dc  c9        ret     
    //-------------------------------
    CH2_SOUND_EFFECT->mask &= 0x5f;
}

void checkInactivityCounter_13dd (void)
{
    //-------------------------------
    // 13dd  219e4d    ld      hl,#4d9e
    // 13e0  3a0e4e    ld      a,(#4e0e)
    // 13e3  be        cp      (hl)
    // 13e4  caee13    jp      z,#13ee
    //-------------------------------
    if (P1_PILLS_EATEN_LEVEL != EATEN_SINCE_MOVE)
    {
        //-------------------------------
        // 13e7  210000    ld      hl,#0000
        // 13ea  22974d    ld      (#4d97),hl
        // 13ed  c9        ret     
        //-------------------------------
        UNITS_INACTIVITY_COUNTER = 0;
        return;
    }

    //-------------------------------
    // 13ee  2a974d    ld      hl,(#4d97)
    // 13f1  23        inc     hl
    // 13f2  22974d    ld      (#4d97),hl
    //-------------------------------
    UNITS_INACTIVITY_COUNTER++;

    //-------------------------------
    // 13f5  ed5b954d  ld      de,(#4d95)
    // 13f9  a7        and     a
    // 13fa  ed52      sbc     hl,de
    // 13fc  c0        ret     nz
    //-------------------------------
    printf ("%s inac=%d b4=%d\n", __func__, UNITS_INACTIVITY_COUNTER,
            UNITS_B4_GHOST_LEAVES_HOME);
    if (UNITS_INACTIVITY_COUNTER != UNITS_B4_GHOST_LEAVES_HOME)
        return;

    //-------------------------------
    // 13fd  210000    ld      hl,#0000
    // 1400  22974d    ld      (#4d97),hl
    //-------------------------------
    UNITS_INACTIVITY_COUNTER = 0;

    //-------------------------------
    // 1403  3aa14d    ld      a,(#4da1)
    // 1406  a7        and     a
    // 1407  f5        push    af
    // 1408  cc8620    call    z,#2086  ; tail call, sets substate==2
    // 140b  f1        pop     af
    // 140c  c8        ret     z
    //-------------------------------
    if (PINKY_SUBSTATE == SUBSTATE_IN_HOUSE)
    {
        PINKY_SUBSTATE = SUBSTATE_LEAVING_HOUSE;
        return;
    }

    //-------------------------------
    // 140d  3aa24d    ld      a,(#4da2)
    // 1410  a7        and     a
    // 1411  f5        push    af
    // 1412  cca920    call    z,#20a9  ; tail call, sets substate==3
    // 1415  f1        pop     af
    // 1416  c8        ret     z
    //-------------------------------

    /*  Inky and clyde need to move sideways before they can leave the house so
     *  have an extra substate for this */

    if (INKY_SUBSTATE == SUBSTATE_IN_HOUSE)
    {
        INKY_SUBSTATE = SUBSTATE_HOUSE_MOVE;
        return;
    }

    //-------------------------------
    // 1417  3aa34d    ld      a,(#4da3)
    // 141a  a7        and     a
    // 141b  ccd120    call    z,#20d1  ; tail call, sets substate==3
    // 141e  c9        ret     
    //-------------------------------
    if (CLYDE_SUBSTATE == SUBSTATE_IN_HOUSE)
        CLYDE_SUBSTATE = SUBSTATE_HOUSE_MOVE;
}

/*  This function checks if in upright mode and stores sprite positions with an
 *  offset for reasons unknown.  The stored values don't seem to be referenced
 *  anywhere. It then calls sprite animation for upright. */
void spriteAnimationUpright_141f (void)
{
    //-------------------------------
    // 141f  3a724e    ld      a,(#4e72)
    // 1422  47        ld      b,a
    // 1423  3a094e    ld      a,(#4e09)
    // 1426  a0        and     b
    // 1427  c8        ret     z
    //-------------------------------
    if ((COCKTAIL_MODE & PLAYER) == 0)
        return;

    //-------------------------------
    // 1428  47        ld      b,a
    // 1429  dd21004c  ld      ix,#4c00
    // 142d  1e08      ld      e,#08
    // 142f  0e08      ld      c,#08
    // 1431  1607      ld      d,#07
    // 1433  3a004d    ld      a,(#4d00)
    // 1436  83        add     a,e
    // 1437  dd7713    ld      (ix+#13),a
    //-------------------------------
    MEM[0x4c13] = BLINKY_POS.y+8;

    //-------------------------------
    // 143a  3a014d    ld      a,(#4d01)
    // 143d  2f        cpl     
    // 143e  82        add     a,d
    // 143f  dd7712    ld      (ix+#12),a
    //-------------------------------
    MEM[0x4c12] = 7-BLINKY_POS.x;

    //-------------------------------
    // 1442  3a024d    ld      a,(#4d02)
    // 1445  83        add     a,e
    // 1446  dd7715    ld      (ix+#15),a
    //-------------------------------
    MEM[0x4c15] = PINKY_POS.y+8;

    //-------------------------------
    // 1449  3a034d    ld      a,(#4d03)
    // 144c  2f        cpl     
    // 144d  82        add     a,d
    // 144e  dd7714    ld      (ix+#14),a
    //-------------------------------
    MEM[0x4c14] = 7-PINKY_POS.x;

    //-------------------------------
    // 1451  3a044d    ld      a,(#4d04)
    // 1454  83        add     a,e
    // 1455  dd7717    ld      (ix+#17),a
    //-------------------------------
    MEM[0x4c17] = INKY_POS.y+8;

    //-------------------------------
    // 1458  3a054d    ld      a,(#4d05)
    // 145b  2f        cpl     
    // 145c  81        add     a,c
    // 145d  dd7716    ld      (ix+#16),a
    //-------------------------------
    MEM[0x4c16] = 7-INKY_POS.x;

    //-------------------------------
    // 1460  3a064d    ld      a,(#4d06)
    // 1463  83        add     a,e
    // 1464  dd7719    ld      (ix+#19),a
    //-------------------------------
    MEM[0x4c19] = CLYDE_POS.y+8;

    //-------------------------------
    // 1467  3a074d    ld      a,(#4d07)
    // 146a  2f        cpl     
    // 146b  81        add     a,c
    // 146c  dd7718    ld      (ix+#18),a
    //-------------------------------
    MEM[0x4c18] = 7-CLYDE_POS.x;

    //-------------------------------
    // 146f  3a084d    ld      a,(#4d08)
    // 1472  83        add     a,e
    // 1473  dd771b    ld      (ix+#1b),a
    //-------------------------------
    MEM[0x4c1b] = PACMAN_POS.y+8;

    //-------------------------------
    // 1476  3a094d    ld      a,(#4d09)
    // 1479  2f        cpl     
    // 147a  81        add     a,c
    // 147b  dd771a    ld      (ix+#1a),a
    //-------------------------------
    MEM[0x4c1a] = 8-PACMAN_POS.x;

    //-------------------------------
    // 147e  3ad24d    ld      a,(#4dd2)
    // 1481  83        add     a,e
    // 1482  dd771d    ld      (ix+#1d),a
    //-------------------------------
    MEM[0x4c1d] = FRUIT_POS.y+8;

    //-------------------------------
    // 1485  3ad34d    ld      a,(#4dd3)
    // 1488  2f        cpl     
    // 1489  81        add     a,c
    // 148a  dd771c    ld      (ix+#1c),a
    // 148d  c3fe14    jp      #14fe
    //-------------------------------
    MEM[0x4c1c] = 8-FRUIT_POS.x;
    spriteAnimation_14fe (true);
}

/*  This function checks if in cocktail mode and stores sprite positions with an
 *  offset for reasons unknown.  The stored values don't seem to be referenced
 *  anywhere. It then calls sprite animation for cocktail. */
void spriteAnimationCocktail_1490 (void)
{
    //-------------------------------
    // 1490  3a724e    ld      a,(#4e72)
    // 1493  47        ld      b,a
    // 1494  3a094e    ld      a,(#4e09)
    // 1497  a0        and     b
    // 1498  c0        ret     nz
    //-------------------------------
    if ((COCKTAIL_MODE & PLAYER) != 0)
        return;
 
    //-------------------------------
    // 1499  47        ld      b,a
    // 149a  1e09      ld      e,#09
    // 149c  0e07      ld      c,#07
    // 149e  1606      ld      d,#06
    // 14a0  dd21004c  ld      ix,#4c00
    // 14a4  3a004d    ld      a,(#4d00)
    // 14a7  2f        cpl     
    // 14a8  83        add     a,e
    // 14a9  dd7713    ld      (ix+#13),a
    //-------------------------------
    MEM[0x4c13] = 9-BLINKY_POS.y;

    //-------------------------------
    // 14ac  3a014d    ld      a,(#4d01)
    // 14af  82        add     a,d
    // 14b0  dd7712    ld      (ix+#12),a
    //-------------------------------
    MEM[0x4c12] = BLINKY_POS.x+6;

    //-------------------------------
    // 14b3  3a024d    ld      a,(#4d02)
    // 14b6  2f        cpl     
    // 14b7  83        add     a,e
    // 14b8  dd7715    ld      (ix+#15),a
    //-------------------------------
    MEM[0x4c15] = 9-PINKY_POS.y;

    //-------------------------------
    // 14bb  3a034d    ld      a,(#4d03)
    // 14be  82        add     a,d
    // 14bf  dd7714    ld      (ix+#14),a
    //-------------------------------
    MEM[0x4c14] = PINKY_POS.x+6;

    //-------------------------------
    // 14c2  3a044d    ld      a,(#4d04)
    // 14c5  2f        cpl     
    // 14c6  83        add     a,e
    // 14c7  dd7717    ld      (ix+#17),a
    //-------------------------------
    MEM[0x4c17] = 9-INKY_POS.y;

    //-------------------------------
    // 14ca  3a054d    ld      a,(#4d05)
    // 14cd  81        add     a,c
    // 14ce  dd7716    ld      (ix+#16),a
    //-------------------------------
    MEM[0x4c16] = INKY_POS.x+6;

    //-------------------------------
    // 14d1  3a064d    ld      a,(#4d06)
    // 14d4  2f        cpl     
    // 14d5  83        add     a,e
    // 14d6  dd7719    ld      (ix+#19),a
    //-------------------------------
    MEM[0x4c19] = 9-CLYDE_POS.y;

    //-------------------------------
    // 14d9  3a074d    ld      a,(#4d07)
    // 14dc  81        add     a,c
    // 14dd  dd7718    ld      (ix+#18),a
    //-------------------------------
    MEM[0x4c18] = CLYDE_POS.x+6;

    //-------------------------------
    // 14e0  3a084d    ld      a,(#4d08)
    // 14e3  2f        cpl     
    // 14e4  83        add     a,e
    // 14e5  dd771b    ld      (ix+#1b),a
    //-------------------------------
    MEM[0x4c1b] = 9-PACMAN_POS.y;

    //-------------------------------
    // 14e8  3a094d    ld      a,(#4d09)
    // 14eb  81        add     a,c
    // 14ec  dd771a    ld      (ix+#1a),a
    //-------------------------------
    MEM[0x4c1a] = PACMAN_POS.x+6;

    //-------------------------------
    // 14ef  3ad24d    ld      a,(#4dd2)
    // 14f2  2f        cpl     
    // 14f3  83        add     a,e
    // 14f4  dd771d    ld      (ix+#1d),a
    //-------------------------------
    MEM[0x4c1d] = 9-FRUIT_POS.y;

    //-------------------------------
    // 14f7  3ad34d    ld      a,(#4dd3)
    // 14fa  81        add     a,c
    // 14fb  dd771c    ld      (ix+#1c),a
    //-------------------------------
    MEM[0x4c1c] = FRUIT_POS.x+6;

    spriteAnimation_14fe (false);
}

void spriteAnimation_14fe (bool invert)
{
    // printf ("%s anim = %d killed=%d\n", __func__,
    //         PAC_DEAD_ANIM_STATE, KILLED_GHOST_INDEX);
    //-------------------------------
    // 14fe  3aa54d    ld      a,(#4da5)
    // 1501  a7        and     a
    // 1502  c24b15    jp      nz,#154b
    //-------------------------------
    if (PAC_DEAD_ANIM_STATE == 0)
    {
        //-------------------------------
        // 1505  3aa44d    ld      a,(#4da4)
        // 1508  a7        and     a
        // 1509  c2b415    jp      nz,#15b4
        //-------------------------------
        if (KILLED_GHOST_INDEX != 0)
        {
            ghostsCocktailMode_15b4 (invert);
            return;
        }

        //-------------------------------
        // 150c  211c15    ld      hl,#151c
        // 150f  e5        push    hl
        // 1510  3a304d    ld      a,(#4d30)
        // 1513  e7        rst     #20
        // 1514  8c 16 b1 16 d6 16 f7 16
        //-------------------------------
        void (*func[])() = 
        {
            selectPacmanLeftSprite_168c,
            selectPacmanDownSprite_16b1,
            selectPacmanRightSprite_16d6,
            selectPacmanUpSprite_16f7
        };
        tableCall_0020 (func, PACMAN_ORIENTATION);

        printf ("%s pac-sprite=%02x\n", __func__, PACMAN_SPRITE);

        //-------------------------------
        // 151c  78        ld      a,b
        // 151d  a7        and     a
        // 151e  282b      jr      z,#154b         ; (43)
        //-------------------------------
        if (invert)
        {
            //-------------------------------
            // 1520  0ec0      ld      c,#c0
            // 1522  3a0a4c    ld      a,(#4c0a)
            // 1525  57        ld      d,a
            // 1526  a1        and     c
            // 1527  2005      jr      nz,#152e        ; (5)
            //-------------------------------
            if ((PACMAN_SPRITE & 0xc0) == 0)
            {
                //-------------------------------
                // 1529  7a        ld      a,d
                // 152a  b1        or      c
                // 152b  c34815    jp      #1548
                //-------------------------------
                PACMAN_SPRITE|= 0xc0;
            }
            else
            {
                //-------------------------------
                // 152e  3a304d    ld      a,(#4d30)
                // 1531  fe02      cp      #02
                // 1533  2009      jr      nz,#153e        ; (9)
                //-------------------------------
                if (PACMAN_ORIENTATION == ORIENT_LEFT)
                {
                    //-------------------------------
                    // 1535  cb7a      bit     7,d
                    // 1537  2812      jr      z,#154b         ; (18)
                    //-------------------------------
                    if (PACMAN_SPRITE & 0x80)
                    {
                        //-------------------------------
                        // 1539  7a        ld      a,d
                        // 153a  a9        xor     c
                        // 153b  c34815    jp      #1548
                        //-------------------------------
                        PACMAN_SPRITE ^= 0xc0;
                    }
                }
                //-------------------------------
                // 153e  fe03      cp      #03
                // 1540  2009      jr      nz,#154b        ; (9)
                //-------------------------------
                else if (PACMAN_ORIENTATION == ORIENT_UP)
                {
                    //-------------------------------
                    // 1542  cb72      bit     6,d
                    // 1544  2805      jr      z,#154b         ; (5)
                    //-------------------------------
                    if ((PACMAN_SPRITE & 0x40) != 0)
                    {
                        //-------------------------------
                        // 1546  7a        ld      a,d
                        // 1547  a9        xor     c
                        // 1548  320a4c    ld      (#4c0a),a
                        //-------------------------------
                        PACMAN_SPRITE ^= 0xc0;
                    }
                }
            }
        }

        //-------------------------------
        // 154b  21c04d    ld      hl,#4dc0
        // 154e  56        ld      d,(hl)
        // 154f  3e1c      ld      a,#1c
        // 1551  82        add     a,d
        // 1552  dd7702    ld      (ix+#02),a
        // 1555  dd7704    ld      (ix+#04),a
        // 1558  dd7706    ld      (ix+#06),a
        // 155b  dd7708    ld      (ix+#08),a
        //-------------------------------

        /*  TODO this is invoked every time.  It sets the sprites to be
         *  frightened.  BUT why does it set them when in the killed state when
         *  the points have been set as the sprite?  NOTE it doesn't change the
         *  eyes sprite?  eyes is probably the same sprite with a colour to make
         *  only the eyes visible 
         */
        BLINKY_SPRITE = 
        PINKY_SPRITE = 
        INKY_SPRITE = 
        CLYDE_SPRITE = GHOST_ANIMATION + 0x1c;

        //-------------------------------
        // 155e  0e20      ld      c,#20
        // 1560  3aac4d    ld      a,(#4dac)
        // 1563  a7        and     a
        // 1564  2006      jr      nz,#156c        ; (6)
        // 1566  3aa74d    ld      a,(#4da7)
        // 1569  a7        and     a
        // 156a  2009      jr      nz,#1575        ; (9)
        //-------------------------------
        if (BLINKY_STATE != 0 || BLINKY_EDIBLE == 0)
        {
            //-------------------------------
            // 156c  3a2c4d    ld      a,(#4d2c)
            // 156f  87        add     a,a
            // 1570  82        add     a,d
            // 1571  81        add     a,c
            // 1572  dd7702    ld      (ix+#02),a
            //-------------------------------
            BLINKY_SPRITE = BLINKY_ORIENTATION * 2 + GHOST_ANIMATION + 0x20;
        }

        printf ("%s BLINKY sprite=%2x\n", __func__, BLINKY_SPRITE);

        //-------------------------------
        // 1575  3aad4d    ld      a,(#4dad)
        // 1578  a7        and     a
        // 1579  2006      jr      nz,#1581        ; (6)
        // 157b  3aa84d    ld      a,(#4da8)
        // 157e  a7        and     a
        // 157f  2009      jr      nz,#158a        ; (9)
        //-------------------------------
        if (PINKY_STATE != 0 || PINKY_EDIBLE == 0)
        {
            //-------------------------------
            // 1581  3a2d4d    ld      a,(#4d2d)
            // 1584  87        add     a,a
            // 1585  82        add     a,d
            // 1586  81        add     a,c
            // 1587  dd7704    ld      (ix+#04),a
            //-------------------------------
            PINKY_SPRITE = PINKY_ORIENTATION*2+GHOST_ANIMATION+0x20;
        }

        //-------------------------------
        // 158a  3aae4d    ld      a,(#4dae)
        // 158d  a7        and     a
        // 158e  2006      jr      nz,#1596        ; (6)
        // 1590  3aa94d    ld      a,(#4da9)
        // 1593  a7        and     a
        // 1594  2009      jr      nz,#159f        ; (9)
        //-------------------------------
        if (INKY_STATE!= 0 || INKY_EDIBLE==0)
        {
            //-------------------------------
            // 1596  3a2e4d    ld      a,(#4d2e)
            // 1599  87        add     a,a
            // 159a  82        add     a,d
            // 159b  81        add     a,c
            // 159c  dd7706    ld      (ix+#06),a
            //-------------------------------
            INKY_SPRITE = INKY_ORIENTATION*2+GHOST_ANIMATION+0x20;
        }

        //-------------------------------
        // 159f  3aaf4d    ld      a,(#4daf)
        // 15a2  a7        and     a
        // 15a3  2006      jr      nz,#15ab        ; (6)
        // 15a5  3aaa4d    ld      a,(#4daa)
        // 15a8  a7        and     a
        // 15a9  2009      jr      nz,#15b4        ; (9)
        //-------------------------------
        if (CLYDE_STATE!= 0 || CLYDE_EDIBLE==0)
        {
            //-------------------------------
            // 15ab  3a2f4d    ld      a,(#4d2f)
            // 15ae  87        add     a,a
            // 15af  82        add     a,d
            // 15b0  81        add     a,c
            // 15b1  dd7708    ld      (ix+#08),a
            //-------------------------------
            CLYDE_SPRITE = CLYDE_ORIENTATION*2+GHOST_ANIMATION+0x20;
        }
    }

    ghostsCocktailMode_15b4 (invert);
}

void ghostsCocktailMode_15b4 (bool invert)
{
    //-------------------------------
    // 15b4  cde615    call    #15e6
    // 15b7  cd2d16    call    #162d
    // 15ba  cd5216    call    #1652
    //-------------------------------
    scene1Animation_15e6();
    scene2Animation_162d();
    scene3Animation_1652();

    //-------------------------------
    // 15bd  78        ld      a,b
    // 15be  a7        and     a
    // 15bf  c8        ret     z
    //-------------------------------
    if (!invert)
        return;

    //-------------------------------
    // 15c0  0ec0      ld      c,#c0
    // 15c2  3a024c    ld      a,(#4c02)
    // 15c5  b1        or      c
    // 15c6  32024c    ld      (#4c02),a
    //-------------------------------
    BLINKY_SPRITE|= 0xc0;

    //-------------------------------
    // 15c9  3a044c    ld      a,(#4c04)
    // 15cc  b1        or      c
    // 15cd  32044c    ld      (#4c04),a
    //-------------------------------
    PINKY_SPRITE|= 0xc0;

    //-------------------------------
    // 15d0  3a064c    ld      a,(#4c06)
    // 15d3  b1        or      c
    // 15d4  32064c    ld      (#4c06),a
    //-------------------------------
    INKY_SPRITE|= 0xc0;

    //-------------------------------
    // 15d7  3a084c    ld      a,(#4c08)
    // 15da  b1        or      c
    // 15db  32084c    ld      (#4c08),a
    //-------------------------------
    CLYDE_SPRITE|= 0xc0;

    //-------------------------------
    // 15de  3a0c4c    ld      a,(#4c0c)
    // 15e1  b1        or      c
    // 15e2  320c4c    ld      (#4c0c),a
    // 15e5  c9        ret     
    //-------------------------------
    FRUIT_SPRITE|= 0xc0;
}

void scene1Animation_15e6 (void)
{
    //-------------------------------
    // 15e6  3a064e    ld      a,(#4e06)
    // 15e9  d605      sub     #05
    // 15eb  d8        ret     c
    //-------------------------------
    if (SCENE1_STATE < 5)
        return;

    //-------------------------------
    // 15ec  3a094d    ld      a,(#4d09)
    // 15ef  e60f      and     #0f
    // 15f1  fe0c      cp      #0c
    // 15f3  3804      jr      c,#15f9         ; (4)
    //-------------------------------
    int a = PACMAN_POS.x & 0xf;
    int d;
    if (a >= 0xc)
    {
        //-------------------------------
        // 15f5  1618      ld      d,#18
        // 15f7  1812      jr      #160b           ; (18)
        //-------------------------------
        d = 0x18;
    }

    //-------------------------------
    // 15f9  fe08      cp      #08
    // 15fb  3804      jr      c,#1601         ; (4)
    //-------------------------------
    else if (a >= 8)
    {
        //-------------------------------
        // 15fd  1614      ld      d,#14
        // 15ff  180a      jr      #160b           ; (10)
        //-------------------------------
        d = 0x14;
    }

    //-------------------------------
    // 1601  fe04      cp      #04
    // 1603  3804      jr      c,#1609         ; (4)
    //-------------------------------
    else if (a >= 4)
    {
        //-------------------------------
        // 1605  1610      ld      d,#10
        // 1607  1802      jr      #160b           ; (2)
        //-------------------------------
        d = 0x10;
    }
    else
    {
        //-------------------------------
        // 1609  1614      ld      d,#14
        //-------------------------------
        d = 0x14;
    }

    //-------------------------------
    // 160b  dd7204    ld      (ix+#04),d
    // 160e  14        inc     d
    // 160f  dd7206    ld      (ix+#06),d
    // 1612  14        inc     d
    // 1613  dd7208    ld      (ix+#08),d
    // 1616  14        inc     d
    // 1617  dd720c    ld      (ix+#0c),d
    // 161a  dd360a3f  ld      (ix+#0a),#3f
    //-------------------------------
    PINKY_SPRITE = d++;
    INKY_SPRITE = d++;
    CLYDE_SPRITE = d++;
    FRUIT_SPRITE = d++;
    PACMAN_SPRITE = 0x3f;

    //-------------------------------
    // 161e  1616      ld      d,#16
    // 1620  dd7205    ld      (ix+#05),d
    // 1623  dd7207    ld      (ix+#07),d
    // 1626  dd7209    ld      (ix+#09),d
    // 1629  dd720d    ld      (ix+#0d),d
    // 162c  c9        ret     
    //-------------------------------
    PINKY_COLOUR = 
    INKY_COLOUR = 
    CLYDE_COLOUR = 
    FRUIT_COLOUR = 0x16;
}

/* TODO assumes ix = 0x4c00 */
void scene2Animation_162d (void)
{
    //-------------------------------
    // 162d  3a074e    ld      a,(#4e07)
    // 1630  a7        and     a
    // 1631  c8        ret     z
    //-------------------------------
    if (SCENE2_STATE == 0)
        return;

    //-------------------------------
    // 1632  57        ld      d,a
    // 1633  3a3a4d    ld      a,(#4d3a)
    // 1636  d63d      sub     #3d
    // 1638  2004      jr      nz,#163e        ; (4)
    //-------------------------------
    if (PACMAN_TILE2.x == 0x3d)
    {
        //-------------------------------
        // 163a  dd360b00  ld      (ix+#0b),#00
        //-------------------------------
        PACMAN_COLOUR = 0;
    }

    //-------------------------------
    // 163e  7a        ld      a,d
    // 163f  fe0a      cp      #0a
    // 1641  d8        ret     c
    //-------------------------------
    if (SCENE2_STATE < 0xa)
        return;

    //-------------------------------
    // 1642  dd360232  ld      (ix+#02),#32
    // 1646  dd36031d  ld      (ix+#03),#1d
    //-------------------------------
    BLINKY_SPRITE = 0x32;
    BLINKY_COLOUR = 0x1d;

    //-------------------------------
    // 164a  fe0c      cp      #0c
    // 164c  d8        ret     c
    //-------------------------------
    if (SCENE2_STATE < 0xc)
        return;
    
    //-------------------------------
    // 164d  dd360233  ld      (ix+#02),#33
    // 1651  c9        ret     
    //-------------------------------
    BLINKY_SPRITE = 0x33;
}

void scene3Animation_1652 (void)
{
    //-------------------------------
    // 1652  3a084e    ld      a,(#4e08)
    // 1655  a7        and     a
    // 1656  c8        ret     z
    //-------------------------------
    if (SCENE3_STATE == 0)
        return;

    //-------------------------------
    // 1657  57        ld      d,a
    // 1658  3a3a4d    ld      a,(#4d3a)
    // 165b  d63d      sub     #3d
    // 165d  2004      jr      nz,#1663        ; (4)
    //-------------------------------
    if (PACMAN_TILE2.x == 0x3d)
    {
        //-------------------------------
        // 165f  dd360b00  ld      (ix+#0b),#00
        //-------------------------------
        PACMAN_COLOUR = 0;
    }

    //-------------------------------
    // 1663  7a        ld      a,d
    // 1664  fe01      cp      #01
    // 1666  d8        ret     c
    //-------------------------------
    if (SCENE3_STATE < 0x1)
        return;

    //-------------------------------
    // 1667  3ac04d    ld      a,(#4dc0)
    // 166a  1e08      ld      e,#08
    // 166c  83        add     a,e
    // 166d  dd7702    ld      (ix+#02),a
    //-------------------------------
    BLINKY_SPRITE = GHOST_ANIMATION+8;

    //-------------------------------
    // 1670  7a        ld      a,d
    // 1671  fe03      cp      #03
    // 1673  d8        ret     c
    //-------------------------------
    if (SCENE3_STATE < 0x3)
        return;

    //-------------------------------
    // 1674  3a014d    ld      a,(#4d01)
    // 1677  e608      and     #08
    // 1679  0f        rrca    
    // 167a  0f        rrca    
    // 167b  0f        rrca    
    // 167c  1e0a      ld      e,#0a
    // 167e  83        add     a,e
    // 167f  dd770c    ld      (ix+#0c),a
    //-------------------------------
    FRUIT_SPRITE = ((BLINKY_POS.x &8)>>3)+0xa;

    //-------------------------------
    // 1682  3c        inc     a
    // 1683  3c        inc     a
    // 1684  dd7702    ld      (ix+#02),a
    // 1687  dd360d1e  ld      (ix+#0d),#1e
    // 168b  c9        ret     
    //-------------------------------
    BLINKY_SPRITE = FRUIT_SPRITE+2;
    FRUIT_COLOUR = 0x1e;
}

/*  Select the sprite number for pacman as he moves along.  Use the least
 *  significant 3 bits of the X pos as the selector */
void selectPacmanLeftSprite_168c (void)
{
    //-------------------------------
    // 168c  3a094d    ld      a,(#4d09)
    // 168f  e607      and     #07
    // 1691  fe06      cp      #06
    // 1693  3805      jr      c,#169a         ; (5)
    //-------------------------------
    int a = PACMAN_POS.x & 7;
    if (a >= 6)
    {
        //-------------------------------
        // 1695  dd360a30  ld      (ix+#0a),#30
        // 1699  c9        ret     
        //-------------------------------
        /*  Assume ix is still 0x4c00 TODO */
        PACMAN_SPRITE = 0x30;
        return;
    }

    //-------------------------------
    // 169a  fe04      cp      #04
    // 169c  3805      jr      c,#16a3         ; (5)
    //-------------------------------
    if (a == 4)
    {

        //-------------------------------
        // 169e  dd360a2e  ld      (ix+#0a),#2e
        // 16a2  c9        ret     
        //-------------------------------
        PACMAN_SPRITE = 0x2e;
        return;
    }

    //-------------------------------
    // 16a3  fe02      cp      #02
    // 16a5  3805      jr      c,#16ac         ; (5)
    //-------------------------------
    if (a == 2)
    {
        //-------------------------------
        // 16a7  dd360a2c  ld      (ix+#0a),#2c
        // 16ab  c9        ret     
        //-------------------------------
        PACMAN_SPRITE = 0x2c;
        return;
    }

    //-------------------------------
    // 16ac  dd360a2e  ld      (ix+#0a),#2e
    // 16b0  c9        ret     
    //-------------------------------
    PACMAN_SPRITE = 0x2e;
    return;
}

void selectPacmanDownSprite_16b1 (void)
{
    //-------------------------------
    // 16b1  3a084d    ld      a,(#4d08)
    // 16b4  e607      and     #07
    // 16b6  fe06      cp      #06
    // 16b8  3805      jr      c,#16bf         ; (5)
    //-------------------------------
    int a = PACMAN_POS.y & 7;
    if (a >= 6)
    {
        //-------------------------------
        // 16ba  dd360a2f  ld      (ix+#0a),#2f
        // 16be  c9        ret     
        //-------------------------------
        PACMAN_SPRITE = 0x2f;
        return;
    }

    //-------------------------------
    // 16bf  fe04      cp      #04
    // 16c1  3805      jr      c,#16c8         ; (5)
    //-------------------------------
    if (a == 4)
    {
        //-------------------------------
        // 16c3  dd360a2d  ld      (ix+#0a),#2d
        // 16c7  c9        ret     
        //-------------------------------
        PACMAN_SPRITE = 0x2d;
        return;
    }

    //-------------------------------
    // 16c8  fe02      cp      #02
    // 16ca  3805      jr      c,#16d1         ; (5)
    //-------------------------------
    if (a == 2)
    {
        //-------------------------------
        // 16cc  dd360a2f  ld      (ix+#0a),#2f
        // 16d0  c9        ret     
        //-------------------------------
        PACMAN_SPRITE = 0x2f;
        return;
    }

    //-------------------------------
    // 16d1  dd360a30  ld      (ix+#0a),#30
    // 16d5  c9        ret     
    //-------------------------------
    PACMAN_SPRITE = 0x30;
}

void selectPacmanRightSprite_16d6 (void)
{
    //-------------------------------
    // 16d6  3a094d    ld      a,(#4d09)
    // 16d9  e607      and     #07
    // 16db  fe06      cp      #06
    // 16dd  3808      jr      c,#16e7         ; (8)
    //-------------------------------
    int a = PACMAN_POS.x & 7;
    if (a >= 6)
    {
        //-------------------------------
        // 16df  1e2e      ld      e,#2e
        // 16e1  cbfb      set     7,e
        // 16e3  dd730a    ld      (ix+#0a),e
        // 16e6  c9        ret     
        //-------------------------------
        PACMAN_SPRITE = 0x2e | 0x80;
        return;
    }

    //-------------------------------
    // 16e7  fe04      cp      #04
    // 16e9  3804      jr      c,#16ef         ; (4)
    //-------------------------------
    if (a >= 4)
    {
        //-------------------------------
        // 16eb  1e2c      ld      e,#2c
        // 16ed  18f2      jr      #16e1           ; (-14)
        //-------------------------------
        PACMAN_SPRITE = 0x2c | 0x80;
        return;
    }

    //-------------------------------
    // 16ef  fe02      cp      #02
    // 16f1  30ec      jr      nc,#16df        ; (-20)
    //-------------------------------
    if (a < 2)
    {
        //-------------------------------
        // 16f3  1e30      ld      e,#30
        // 16f5  18ea      jr      #16e1           ; (-22)
        //-------------------------------
        PACMAN_SPRITE = 0x30 | 0x80;
    }
}

void selectPacmanUpSprite_16f7 (void)
{
    //-------------------------------
    // 16f7  3a084d    ld      a,(#4d08)
    // 16fa  e607      and     #07
    // 16fc  fe06      cp      #06
    // 16fe  3805      jr      c,#1705         ; (5)
    //-------------------------------
    int a = PACMAN_POS.y & 7;
    if (a >= 6)
    {
        //-------------------------------
        // 1700  dd360a30  ld      (ix+#0a),#30
        // 1704  c9        ret     
        //-------------------------------
        PACMAN_SPRITE = 0x30;
        return;
    }

    //-------------------------------
    // 1705  fe04      cp      #04
    // 1707  3808      jr      c,#1711         ; (8)
    //-------------------------------
    if (a >= 4)
    {
        //-------------------------------
        // 1709  1e2f      ld      e,#2f
        // 170b  cbf3      set     6,e
        // 170d  dd730a    ld      (ix+#0a),e
        // 1710  c9        ret     
        //-------------------------------
        PACMAN_SPRITE = 0x2f | 0x40;
        return;
    }

    //-------------------------------
    // 1711  fe02      cp      #02
    // 1713  3804      jr      c,#1719         ; (4)
    //-------------------------------
    if (a >= 2)
    {
        //-------------------------------
        // 1715  1e2d      ld      e,#2d
        // 1717  18f2      jr      #170b           ; (-14)
        //-------------------------------
        PACMAN_SPRITE = 0x2d | 0x40;
        return;
    }

    //-------------------------------
    // 1719  1e2f      ld      e,#2f
    // 171b  18ee      jr      #170b           ; (-18)
    //-------------------------------
    PACMAN_SPRITE = 0x2f | 0x40;
}

/*  Checks if pacman and a ghost occupy the same tile.  b is the index of the
 *  ghost if any.  If ghost is edible, add points to score */
void pacmanCheckGhostCoincidence_171d (void)
{
    //-------------------------------
    // 171d  0604      ld      b,#04
    // 171f  ed5b394d  ld      de,(#4d39)
    // 1723  3aaf4d    ld      a,(#4daf)
    // 1726  a7        and     a
    // 1727  2009      jr      nz,#1732        ; (9)
    // 1729  2a374d    ld      hl,(#4d37)
    // 172c  a7        and     a
    // 172d  ed52      sbc     hl,de
    // 172f  ca6317    jp      z,#1763
    //-------------------------------
    if (CLYDE_STATE == GHOST_STATE_ALIVE &&
        CLYDE_TILE2.y == PACMAN_TILE2.y &&
        CLYDE_TILE2.x == PACMAN_TILE2.x)
    {
        pacmanGhostCoincide_1763 (GHOST_CLYDE);
        return;
    }

    //-------------------------------
    // 1732  05        dec     b
    // 1733  3aae4d    ld      a,(#4dae)
    // 1736  a7        and     a
    // 1737  2009      jr      nz,#1742        ; (9)
    // 1739  2a354d    ld      hl,(#4d35)
    // 173c  a7        and     a
    // 173d  ed52      sbc     hl,de
    // 173f  ca6317    jp      z,#1763
    //-------------------------------
    if (INKY_STATE == GHOST_STATE_ALIVE && 
        INKY_TILE2.y == PACMAN_TILE2.y &&
        INKY_TILE2.x == PACMAN_TILE2.x)
    {
        pacmanGhostCoincide_1763 (GHOST_INKY);
        return;
    }

    //-------------------------------
    // 1742  05        dec     b
    // 1743  3aad4d    ld      a,(#4dad)
    // 1746  a7        and     a
    // 1747  2009      jr      nz,#1752        ; (9)
    // 1749  2a334d    ld      hl,(#4d33)
    // 174c  a7        and     a
    // 174d  ed52      sbc     hl,de
    // 174f  ca6317    jp      z,#1763
    //-------------------------------
    if (PINKY_STATE == GHOST_STATE_ALIVE &&
        PINKY_TILE2.y == PACMAN_TILE2.y &&
        PINKY_TILE2.x == PACMAN_TILE2.x)
    {
        pacmanGhostCoincide_1763 (GHOST_PINKY);
        return;
    }

    //-------------------------------
    // 1752  05        dec     b
    // 1753  3aac4d    ld      a,(#4dac)
    // 1756  a7        and     a
    // 1757  2009      jr      nz,#1762        ; (9)
    // 1759  2a314d    ld      hl,(#4d31)
    // 175c  a7        and     a
    // 175d  ed52      sbc     hl,de
    // 175f  ca6317    jp      z,#1763
    //-------------------------------
    if (BLINKY_STATE == GHOST_STATE_ALIVE &&
        BLINKY_TILE2.y == PACMAN_TILE2.y&&
        BLINKY_TILE2.x == PACMAN_TILE2.x)
    {
        pacmanGhostCoincide_1763 (GHOST_BLINKY);
        return;
    }

    //-------------------------------
    // 1762  05        dec     b
    //-------------------------------
    pacmanGhostCoincide_1763(0);
}

void pacmanGhostCoincide_1763 (int b)
{
    //-------------------------------
    // 1763  78        ld      a,b
    // 1764  32a44d    ld      (#4da4),a
    // 1767  32a54d    ld      (#4da5),a
    //-------------------------------
    KILLED_GHOST_INDEX = 
    PAC_DEAD_ANIM_STATE = b;
    //-------------------------------
    // 176a  a7        and     a
    // 176b  c8        ret     z
    //-------------------------------
    if (b == 0)
        return;

    printf ("%s ghost = %d\n", __func__, b);

    //-------------------------------
    // 176c  21a64d    ld      hl,#4da6
    // 176f  5f        ld      e,a
    // 1770  1600      ld      d,#00
    // 1772  19        add     hl,de
    // 1773  7e        ld      a,(hl)
    // 1774  a7        and     a
    // 1775  c8        ret     z
    //-------------------------------
    uint8_t edible = (&BLINKY_EDIBLE)[b - 1];
    printf ("%s ghost %d edible=%d\n", __func__, b, edible);
    if (edible == 0)
        return;

    //-------------------------------
    // 1776  af        xor     a
    // 1777  32a54d    ld      (#4da5),a
    // 177a  21d04d    ld      hl,#4dd0
    // 177d  34        inc     (hl)
    //-------------------------------

    /*  Ghost was edible so pacman is not dead */
    PAC_DEAD_ANIM_STATE = 0;
    KILLED_COUNT++;

    //-------------------------------
    // 177e  46        ld      b,(hl)
    // 177f  04        inc     b
    // 1780  cd5a2a    call    #2a5a
    //-------------------------------

    /*  200 for 1st ghost, 400 for second, etc */
    addToScore_2a5a(KILLED_COUNT+1);

    //-------------------------------
    // 1783  21bc4e    ld      hl,#4ebc
    // 1786  cbde      set     3,(hl)
    // 1788  c9        ret     
    //-------------------------------
    CH3_SOUND_EFFECT->mask |= 0x8;
}

/*  TODO I don't understand how this function works.  Just comparing x and y
 *  differences to 4 and jumping if there is a carry will cause a false detetion
 *  of pacman eatng a ghost any time he is to the upper left of the ghost??? 
 *
 *  Disabled for now.  Seems redundant anyway? */

void pacmanCheckEatGhost_1789 (void)
{
    //-------------------------------
    // 1789  3aa44d    ld      a,(#4da4)
    // 178c  a7        and     a
    // 178d  c0        ret     nz
    //-------------------------------
    if (KILLED_GHOST_INDEX != 0)
        return;

    //-------------------------------
    // 178e  3aa64d    ld      a,(#4da6)
    // 1791  a7        and     a
    // 1792  c8        ret     z
    //-------------------------------
    if (PACMAN_POWEREDUP == 0)
        return;

// return;
    //-------------------------------
    // 1793  0e04      ld      c,#04
    // 1795  0604      ld      b,#04
    // 1797  dd21084d  ld      ix,#4d08         ; pacman_pos
    // 179b  3aaf4d    ld      a,(#4daf)        ; clyde state
    // 179e  a7        and     a
    // 179f  2013      jr      nz,#17b4        ; (19)
    // 17a1  3a064d    ld      a,(#4d06)        ; clyde pos y
    // 17a4  dd9600    sub     (ix+#00)         ; pacman y
    // 17a7  b9        cp      c
    // 17a8  300a      jr      nc,#17b4        ; (10)
    // 17aa  3a074d    ld      a,(#4d07)        ; clyde pos x
    // 17ad  dd9601    sub     (ix+#01)         ; pacman x
    // 17b0  b9        cp      c
    // 17b1  da6317    jp      c,#1763
    //-------------------------------

    /*  Subtract pacman's tile from clyde's tile and compare the result to 4.
     *  Note that because the CP instruction does not set the carry flag unless
     *  the sign changes, we have to compare to 4 but also to 0. */
    uint8_t dx = CLYDE_POS.x - PACMAN_POS.x;
    uint8_t dy = CLYDE_POS.y - PACMAN_POS.y;

    if (CLYDE_STATE == GHOST_STATE_ALIVE &&
        dx >= 0 && dx < 4 &&
        dy >= 0 && dy < 4)
    {
        printf ("%s pacman eats clyde\n", __func__);
        pacmanGhostCoincide_1763 (GHOST_CLYDE);
        return;
    }

    //-------------------------------
    // 17b4  05        dec     b
    // 17b5  3aae4d    ld      a,(#4dae)
    // 17b8  a7        and     a
    // 17b9  2013      jr      nz,#17ce        ; (19)
    // 17bb  3a044d    ld      a,(#4d04)
    // 17be  dd9600    sub     (ix+#00)
    // 17c1  b9        cp      c
    // 17c2  300a      jr      nc,#17ce        ; (10)
    // 17c4  3a054d    ld      a,(#4d05)
    // 17c7  dd9601    sub     (ix+#01)
    // 17ca  b9        cp      c
    // 17cb  da6317    jp      c,#1763
    //-------------------------------
    dx = INKY_POS.x - PACMAN_POS.x;
    dy = INKY_POS.y - PACMAN_POS.y;

    if (INKY_STATE == GHOST_STATE_ALIVE && 
        dx >= 0 && dx < 4 &&
        dy >= 0 && dy < 4)
    {
        printf ("%s pacman eats inky\n", __func__);
        pacmanGhostCoincide_1763 (GHOST_INKY);
        return;
    }

    //-------------------------------
    // 17ce  05        dec     b
    // 17cf  3aad4d    ld      a,(#4dad)
    // 17d2  a7        and     a
    // 17d3  2013      jr      nz,#17e8        ; (19)
    // 17d5  3a024d    ld      a,(#4d02)
    // 17d8  dd9600    sub     (ix+#00)
    // 17db  b9        cp      c
    // 17dc  300a      jr      nc,#17e8        ; (10)
    // 17de  3a034d    ld      a,(#4d03)
    // 17e1  dd9601    sub     (ix+#01)
    // 17e4  b9        cp      c
    // 17e5  da6317    jp      c,#1763
    //-------------------------------
    dx = PINKY_POS.x - PACMAN_POS.x;
    dy = PINKY_POS.y - PACMAN_POS.y;

    if (PINKY_STATE == GHOST_STATE_ALIVE &&
        dx >= 0 && dx < 4 &&
        dy >= 0 && dy < 4)
    {
        printf ("%s pacman eats pinky\n", __func__);
        pacmanGhostCoincide_1763 (GHOST_PINKY);
        return;
    }

    //-------------------------------
    // 17e8  05        dec     b
    // 17e9  3aac4d    ld      a,(#4dac)
    // 17ec  a7        and     a
    // 17ed  2013      jr      nz,#1802        ; (19)
    // 17ef  3a004d    ld      a,(#4d00)
    // 17f2  dd9600    sub     (ix+#00)
    // 17f5  b9        cp      c
    // 17f6  300a      jr      nc,#1802        ; (10)
    // 17f8  3a014d    ld      a,(#4d01)
    // 17fb  dd9601    sub     (ix+#01)
    // 17fe  b9        cp      c
    // 17ff  da6317    jp      c,#1763
    //-------------------------------
    dx = BLINKY_POS.x - PACMAN_POS.x;
    dy = BLINKY_POS.y - PACMAN_POS.y;

    if (BLINKY_STATE == GHOST_STATE_ALIVE &&
        dx >= 0 && dx < 4 &&
        dy >= 0 && dy < 4)
    {
        printf ("%s pacman eats blinky\n", __func__);
        pacmanGhostCoincide_1763 (GHOST_BLINKY);
        return;
    }

    //-------------------------------
    // 1802  05        dec     b
    // 1803  c36317    jp      #1763
    //-------------------------------
    pacmanGhostCoincide_1763 (0);
}

void pacmanUpdateMovePat_1806 (void)
{
    printf ("%s\n", __func__);
    //-------------------------------
    // 1806  219d4d    ld      hl,#4d9d
    // 1809  3eff      ld      a,#ff
    // 180b  be        cp      (hl)
    // 180c  ca1118    jp      z,#1811
    //-------------------------------
    if (PACMAN_MOVE_DELAY != 0xff)
    {
        //-------------------------------
        // 180f  35        dec     (hl)
        // 1810  c9        ret     
        //-------------------------------
        PACMAN_MOVE_DELAY--;
        return;
    }

    //-------------------------------
    // 1811  3aa64d    ld      a,(#4da6)
    // 1814  a7        and     a
    // 1815  ca2f18    jp      z,#182f
    //-------------------------------

    if (PACMAN_POWEREDUP != 0)
    {
        //-------------------------------
        // 1818  2a4c4d    ld      hl,(#4d4c)
        // 181b  29        add     hl,hl
        // 181c  224c4d    ld      (#4d4c),hl
        // 181f  2a4a4d    ld      hl,(#4d4a)
        // 1822  ed6a      adc     hl,hl
        // 1824  224a4d    ld      (#4d4a),hl
        // 1827  d0        ret     nc
        // 1828  214c4d    ld      hl,#4d4c
        // 182b  34        inc     (hl)
        // 182c  c34318    jp      #1843
        //-------------------------------
        rotate32 (&PACMAN_MOVE_PAT_POWERUP, 1);

        if ((PACMAN_MOVE_PAT_POWERUP & 1) == 0)
            return;
    }
    else
    {
        //-------------------------------
        // 182f  2a484d    ld      hl,(#4d48)
        // 1832  29        add     hl,hl
        // 1833  22484d    ld      (#4d48),hl
        // 1836  2a464d    ld      hl,(#4d46)
        // 1839  ed6a      adc     hl,hl
        // 183b  22464d    ld      (#4d46),hl
        // 183e  d0        ret     nc
        // 183f  21484d    ld      hl,#4d48
        // 1842  34        inc     (hl)
        //-------------------------------
        rotate32 (&PACMAN_MOVE_PAT_NORMAL, 1);

        if ((PACMAN_MOVE_PAT_NORMAL & 1) == 0)
            return;
    }

    //-------------------------------
    // 1843  3a0e4e    ld      a,(#4e0e)
    // 1846  329e4d    ld      (#4d9e),a
    //-------------------------------
    EATEN_SINCE_MOVE = P1_PILLS_EATEN_LEVEL;

    //-------------------------------
    // 1849  3a724e    ld      a,(#4e72)
    // 184c  4f        ld      c,a
    // 184d  3a094e    ld      a,(#4e09)
    // 1850  a1        and     c
    //-------------------------------
    int inverted = (COCKTAIL_MODE & PLAYER);

    //-------------------------------
    // 1851  4f        ld      c,a
    // 1852  213a4d    ld      hl,#4d3a
    // 1855  7e        ld      a,(hl)
    // 1856  0621      ld      b,#21
    // 1858  90        sub     b
    // 1859  3809      jr      c,#1864         ; (9)
    // 185b  7e        ld      a,(hl)
    // 185c  063b      ld      b,#3b
    // 185e  90        sub     b
    // 185f  3003      jr      nc,#1864        ; (3)
    // 1861  c3ab18    jp      #18ab
    //-------------------------------
    if (PACMAN_TILE2.x < 0x21 ||
        PACMAN_TILE2.x >= 0x3b)
    {
        //-------------------------------
        // 1864  3e01      ld      a,#01
        // 1866  32bf4d    ld      (#4dbf),a
        //-------------------------------
        PACMAN_ENTERING_TUNNEL = 1;

        //-------------------------------
        // 1869  3a004e    ld      a,(#4e00)
        // 186c  fe01      cp      #01
        // 186e  ca191a    jp      z,#1a19
        //-------------------------------
        if (MAIN_STATE == MAIN_STATE_DEMO)
        {
            pacmanMoveTile_1a19();
            return;
        }

        //-------------------------------
        // 1871  3a044e    ld      a,(#4e04)
        // 1874  fe10      cp      #10
        // 1876  d2191a    jp      nc,#1a19
        //-------------------------------
        if (LEVEL_STATE >= 0x10)
        {
            pacmanMoveTile_1a19();
            return;
        }

        //-------------------------------
        // 1879  79        ld      a,c
        // 187a  a7        and     a
        // 187b  2806      jr      z,#1883         ; (6)
        //-------------------------------
        int input;
        if (inverted)
        {
            //-------------------------------
            // 187d  3a4050    ld      a,(#5040)
            // 1880  c38618    jp      #1886
            //-------------------------------
            input = IO_INPUT1;
        }
        else
        {
            //-------------------------------
            // 1883  3a0050    ld      a,(#5000)
            //-------------------------------
            input = IO_INPUT0;
        }
        //-------------------------------
        // 1886  cb4f      bit     1,a
        // 1888  c29918    jp      nz,#1899
        //-------------------------------

        if (~input & INPUT_LEFT)
        {
            //-------------------------------
            // 188b  2a0333    ld      hl,(#3303)
            // 188e  3e02      ld      a,#02
            // 1890  32304d    ld      (#4d30),a
            // 1893  221c4d    ld      (#4d1c),hl
            //-------------------------------
            PACMAN_ORIENTATION = ORIENT_LEFT;
            PACMAN_VECTOR = *MOVE_VECTOR_LEFT;

            //-------------------------------
            // 1896  c35019    jp      #1950
            //-------------------------------
            pacmanMove_1950();
            return;
        }

        //-------------------------------
        // 1899  cb57      bit     2,a
        // 189b  c25019    jp      nz,#1950
        //-------------------------------
        else if (~input & INPUT_RIGHT)
        {
            //-------------------------------
            // 189e  2aff32    ld      hl,(#32ff)
            // 18a1  af        xor     a
            // 18a2  32304d    ld      (#4d30),a
            // 18a5  221c4d    ld      (#4d1c),hl
            //-------------------------------
            PACMAN_ORIENTATION = ORIENT_RIGHT;
            PACMAN_VECTOR = *MOVE_VECTOR_RIGHT;

            //-------------------------------
            // 18a8  c35019    jp      #1950
            //-------------------------------
            pacmanMove_1950();
            return;
        }
    }

    //-------------------------------
    // 18ab  3a004e    ld      a,(#4e00)
    // 18ae  fe01      cp      #01
    // 18b0  ca191a    jp      z,#1a19
    //-------------------------------
    if (MAIN_STATE == MAIN_STATE_DEMO)
    {
        pacmanMoveTile_1a19();
        return;
    }

    //-------------------------------
    // 18b3  3a044e    ld      a,(#4e04)
    // 18b6  fe10      cp      #10
    // 18b8  d2191a    jp      nc,#1a19
    //-------------------------------
    if (LEVEL_STATE >= 0x10)
    {
        pacmanMoveTile_1a19();
        return;
    }

    //-------------------------------
    // 18bb  79        ld      a,c
    // 18bc  a7        and     a
    // 18bd  2806      jr      z,#18c5         ; (6)
    //-------------------------------
    int input;
    if (inverted)
    {
        //-------------------------------
        // 18bf  3a4050    ld      a,(#5040)
        // 18c2  c3c818    jp      #18c8
        //-------------------------------
        input = IO_INPUT1;
    }
    else
    {
        //-------------------------------
        // 18c5  3a0050    ld      a,(#5000)
        //-------------------------------
        input = IO_INPUT0;
    }

    //-------------------------------
    // 18c8  cb4f      bit     1,a
    // 18ca  cac91a    jp      z,#1ac9
    //-------------------------------
    if (~input & INPUT_LEFT)
    {
        pacmanOrientLeft_1ac9();
        return;
    }

    //-------------------------------
    // 18cd  cb57      bit     2,a
    // 18cf  cad91a    jp      z,#1ad9
    //-------------------------------
    if (~input & INPUT_RIGHT)
    {
        pacmanOrientRight_1ad9();
        return;
    }

    //-------------------------------
    // 18d2  cb47      bit     0,a
    // 18d4  cae81a    jp      z,#1ae8
    //-------------------------------
    if (~input & INPUT_UP)
    {
        pacmanOrientUp_1ae8();
        return;
    }

    //-------------------------------
    // 18d7  cb5f      bit     3,a
    // 18d9  caf81a    jp      z,#1af8
    //-------------------------------
    if (~input & INPUT_DOWN)
    {
        pacmanOrientDown_1af8();
        return;
    }

    //-------------------------------
    // 18dc  2a1c4d    ld      hl,(#4d1c)
    // 18df  22264d    ld      (#4d26),hl
    // 18e2  0601      ld      b,#01
    //-------------------------------
    PACMAN_VECTOR2 = PACMAN_VECTOR;
    pacmanCheckMoveClear_18e4 (1);
}

/*  Check if pacman can move in the desired direction.  Parameter noInput is
 *  zero if joystick input has been applied */
void pacmanCheckMoveClear_18e4 (int noInput)
{
    printf ("%s\n", __func__);
    //-------------------------------
    // 18e4  dd21264d  ld      ix,#4d26
    // 18e8  fd21394d  ld      iy,#4d39
    // 18ec  cd0f20    call    #200f
    //-------------------------------
    int a = getScreenCharPosOffset_200f (PACMAN_VECTOR2, PACMAN_TILE2);

    //-------------------------------
    // 18ef  e6c0      and     #c0
    // 18f1  d6c0      sub     #c0
    // 18f3  204b      jr      nz,#1940        ; (75)
    //-------------------------------
    // printf("%s a = %02x\n", __func__, a);
    if ((a & CHAR_MAZE_MASK) != CHAR_MAZE_MASK)
    {
        pacmanHitMazeWall_1940 (noInput);
        return;
    }

    //-------------------------------
    // 18f5  05        dec     b
    // 18f6  c21619    jp      nz,#1916
    //-------------------------------
    if (noInput == 1)
    {
        //-------------------------------
        // 18f9  3a304d    ld      a,(#4d30)
        // 18fc  0f        rrca    
        // 18fd  da0b19    jp      c,#190b
        //-------------------------------
        if ((PACMAN_ORIENTATION & ORIENT_VERTICAL) == 0)
        {
            //-------------------------------
            // 1900  3a094d    ld      a,(#4d09)
            // 1903  e607      and     #07
            // 1905  fe04      cp      #04
            // 1907  c8        ret     z
            //-------------------------------

            /*  Orientation is left or right, check if past mid tile before
             *  allowing direction change */
            if ((PACMAN_POS.x & 7) == 4)
                return;

            //-------------------------------
            // 1908  c34019    jp      #1940
            //-------------------------------
            pacmanHitMazeWall_1940 (1);
            return;
        }
        else
        {
            //-------------------------------
            // 190b  3a084d    ld      a,(#4d08)
            // 190e  e607      and     #07
            // 1910  fe04      cp      #04
            // 1912  c8        ret     z
            //-------------------------------

            /*  Orientation is up or down, check if past mid tile before
             *  allowing direction change */
            if ((PACMAN_POS.y & 7) == 4)
                return;

            //-------------------------------
            // 1913  c34019    jp      #1940
            //-------------------------------
            pacmanHitMazeWall_1940 (1);
            return;
        }
    }

    //-------------------------------
    // 1916  dd211c4d  ld      ix,#4d1c
    // 191a  cd0f20    call    #200f
    //-------------------------------
    a = getScreenCharPosOffset_200f (PACMAN_VECTOR, PACMAN_TILE2);

    //-------------------------------
    // 191d  e6c0      and     #c0
    // 191f  d6c0      sub     #c0
    // 1921  202d      jr      nz,#1950        ; (45)
    //-------------------------------
    if ((a & CHAR_MAZE_MASK) != CHAR_MAZE_MASK)
    {
        pacmanMove_1950 ();
        return;
    }

    //-------------------------------
    // 1923  3a304d    ld      a,(#4d30)
    // 1926  0f        rrca    
    // 1927  da3519    jp      c,#1935
    //-------------------------------
    if ((PACMAN_ORIENTATION & ORIENT_VERTICAL) == 0)
    {
        //-------------------------------
        // 192a  3a094d    ld      a,(#4d09)
        // 192d  e607      and     #07
        // 192f  fe04      cp      #04
        // 1931  c8        ret     z
        //-------------------------------
        if ((PACMAN_POS.x & 7) == 4)
            return;

        //-------------------------------
        // 1932  c35019    jp      #1950
        //-------------------------------
        pacmanMove_1950 ();
        return;
    }

    //-------------------------------
    // 1935  3a084d    ld      a,(#4d08)
    // 1938  e607      and     #07
    // 193a  fe04      cp      #04
    // 193c  c8        ret     z
    //-------------------------------
    if ((PACMAN_POS.y & 7) == 4)
        return;

    //-------------------------------
    // 193d  c35019    jp      #1950
    //-------------------------------
    pacmanMove_1950 ();
}

void pacmanHitMazeWall_1940 (int noInput)
{
    // printf ("%s\n", __func__);
    //-------------------------------
    // 1940  2a264d    ld      hl,(#4d26)
    // 1943  221c4d    ld      (#4d1c),hl
    // 1946  05        dec     b
    // 1947  ca5019    jp      z,#1950
    // 194a  3a3c4d    ld      a,(#4d3c)
    // 194d  32304d    ld      (#4d30),a
    //-------------------------------
    PACMAN_VECTOR = PACMAN_VECTOR2;

    /*  If there has been a joystick input (!noInput) then change orientation */

    if (noInput != 1)
        PACMAN_ORIENTATION = PACMAN_DESIRED_ORIENTATION;

    pacmanMove_1950 ();
}

void pacmanMove_1950 (void)
{
    printf ("%s\n", __func__);
    //-------------------------------
    // 1950  dd211c4d  ld      ix,#4d1c
    // 1954  fd21084d  ld      iy,#4d08
    // 1958  cd0020    call    #2000
    //-------------------------------
    XYPOS pacmanXY = addXYOffset_2000 (PACMAN_VECTOR, PACMAN_POS);

    //-------------------------------
    // 195b  3a304d    ld      a,(#4d30)
    // 195e  0f        rrca    
    // 195f  da7519    jp      c,#1975
    //-------------------------------
    printf ("%s xy=%d,%d, &7=%d,%d\n", __func__,
            pacmanXY.x,pacmanXY.y,
            pacmanXY.x&7,pacmanXY.y&7);

    /*  In addition to the straight line move vector, also allow pacman to cut
     *  corners by moving diagonally at intersections.  For example, if moving
     *  horizontally but orientation is vertical then also allow up to 3 pixels
     *  of vertical movement once at the midpoint of the tile before the
     *  vector direction change */

    if ((PACMAN_ORIENTATION & ORIENT_VERTICAL) == 0)
    {
        //-------------------------------
        // 1962  7d        ld      a,l
        // 1963  e607      and     #07
        // 1965  fe04      cp      #04
        // 1967  ca8519    jp      z,#1985
        //-------------------------------
        if ((pacmanXY.y & 7) != 4)
        {
            //-------------------------------
            // 196a  da7119    jp      c,#1971
            // 196d  2d        dec     l
            // 196e  c38519    jp      #1985
            // 1971  2c        inc     l
            // 1972  c38519    jp      #1985
            //-------------------------------
            if ((pacmanXY.y & 7) < 4)
                pacmanXY.y++;
            else
                pacmanXY.y--;
        }
    }
    else
    {
        //-------------------------------
        // 1975  7c        ld      a,h
        // 1976  e607      and     #07
        // 1978  fe04      cp      #04
        // 197a  ca8519    jp      z,#1985
        //-------------------------------
        if ((pacmanXY.x & 7) != 4)
        {
            //-------------------------------
            // 197d  da8419    jp      c,#1984
            // 1980  25        dec     h
            // 1981  c38519    jp      #1985
            // 1984  24        inc     h
            //-------------------------------
            if ((pacmanXY.x & 7) < 4)
                pacmanXY.x++;
            else
                pacmanXY.x--;
        }
    }

    pacmanUpdatePos_1985(pacmanXY);
}

/*  Pass in pacman XY pixel coords in hl */
void pacmanUpdatePos_1985 (XYPOS pos)
{
    printf ("%s\n", __func__);
    //-------------------------------
    // 1985  22084d    ld      (#4d08),hl
    // 1988  cd1820    call    #2018
    // 198b  22394d    ld      (#4d39),hl
    //-------------------------------
    PACMAN_POS = pos;
    PACMAN_TILE2 = pixelToTile_2018 (pos);
    // printf ("%s %d,%d -> %d,%d\n", __func__, PACMAN_POS.x,PACMAN_POS.y,pos.x,pos.y);

    //-------------------------------
    // 198e  dd21bf4d  ld      ix,#4dbf
    // 1992  dd7e00    ld      a,(ix+#00)
    // 1995  dd360000  ld      (ix+#00),#00
    // 1999  a7        and     a
    // 199a  c0        ret     nz
    //-------------------------------
    if (PACMAN_ENTERING_TUNNEL)
    {
        PACMAN_ENTERING_TUNNEL = 0;
        return;
    }

    //-------------------------------
    // 199b  3ad24d    ld      a,(#4dd2)
    // 199e  a7        and     a
    // 199f  282c      jr      z,#19cd         ; (44)
    //-------------------------------
    if (FRUIT_POS.y != 0)
    {
        //-------------------------------
        // 19a1  3ad44d    ld      a,(#4dd4)
        // 19a4  a7        and     a
        // 19a5  2826      jr      z,#19cd         ; (38)
        //-------------------------------
        if (FRUIT_POINTS != 0)
        {
            //-------------------------------
            // 19a7  2a084d    ld      hl,(#4d08)
            // 19aa  119480    ld      de,#8094
            // 19ad  a7        and     a
            // 19ae  ed52      sbc     hl,de
            // 19b0  201b      jr      nz,#19cd        ; (27)
            //-------------------------------
            if (PACMAN_POS.x == 0x80 && PACMAN_POS.y == 0x94)
            {
                //-------------------------------
                // 19b2  0619      ld      b,#19
                // 19b4  4f        ld      c,a
                // 19b5  cd4200    call    #0042
                //-------------------------------
                addTask_0042 (0x19, FRUIT_POINTS);

                //-------------------------------
                // 19b8  0e15      ld      c,#15
                // 19ba  81        add     a,c
                // 19bb  4f        ld      c,a
                // 19bc  061c      ld      b,#1c
                // 19be  cd4200    call    #0042
                // 19c1  cd0410    call    #1004
                //-------------------------------
                addTask_0042 (TASK_DISPLAY_MSG, FRUIT_POINTS+0x15);
                resetFruitState_1004();

                //-------------------------------
                // 19c4  f7        rst     #30
                // 19c5  540500
                //-------------------------------
                schedISRTask (0x54, 0x05, 0x00);

                //-------------------------------
                // 19c8  21bc4e    ld      hl,#4ebc
                // 19cb  cbd6      set     2,(hl)
                //-------------------------------
                CH3_SOUND_EFFECT->mask |= 0x4;
            }
        }
    }

    //-------------------------------
    // 19cd  3eff      ld      a,#ff
    // 19cf  329d4d    ld      (#4d9d),a
    // 19d2  2a394d    ld      hl,(#4d39)
    // 19d5  cd6500    call    #0065
    //-------------------------------
    PACMAN_MOVE_DELAY = 0xff;
    uint16_t addr = getScreenOffset_0065 (PACMAN_TILE2);

    //-------------------------------
    // 19d8  7e        ld      a,(hl)
    // 19d9  fe10      cp      #10
    // 19db  2803      jr      z,#19e0         ; (3)
    // 19dd  fe14      cp      #14
    // 19df  c0        ret     nz
    //-------------------------------
    if (SCREEN[addr] != CHAR_PILL && SCREEN[addr] != CHAR_POWERUP)
        return;

    //-------------------------------
    // 19e0  dd210e4e  ld      ix,#4e0e
    // 19e4  dd3400    inc     (ix+#00)
    //-------------------------------
    P1_PILLS_EATEN_LEVEL++;

    //-------------------------------
    // 19e7  e60f      and     #0f
    // 19e9  cb3f      srl     a
    //-------------------------------
    int a = (SCREEN[addr] & 0xf)>>1;

    //-------------------------------
    // 19eb  0640      ld      b,#40
    // 19ed  70        ld      (hl),b
    //-------------------------------
    SCREEN[addr] = 0x40; // write space to screen

    //-------------------------------
    // 19ee  0619      ld      b,#19
    // 19f0  4f        ld      c,a
    // 19f1  cb39      srl     c
    // 19f3  cd4200    call    #0042
    //-------------------------------
    addTask_0042 (TASK_ADD_TO_SCORE, a>>1);

    //-------------------------------
    // 19f6  3c        inc     a
    // 19f7  fe01      cp      #01
    // 19f9  cafd19    jp      z,#19fd
    //-------------------------------

    a++;
    if (a!= 1)
    {
        //-------------------------------
        // 19fc  87        add     a,a
        //-------------------------------
        a *= 2;
    }

    //-------------------------------
    // 19fd  329d4d    ld      (#4d9d),a
    // 1a00  cd081b    call    #1b08
    // 1a03  cd6a1a    call    #1a6a
    //-------------------------------
    PACMAN_MOVE_DELAY = a;
    updateLeaveHouseCounters_1b08();
    checkGhostsBecomeEdible_1a6a();

    //-------------------------------
    // 1a06  21bc4e    ld      hl,#4ebc
    // 1a09  3a0e4e    ld      a,(#4e0e)
    // 1a0c  0f        rrca    
    // 1a0d  3805      jr      c,#1a14         ; (5)
    //-------------------------------
    if ((P1_PILLS_EATEN_LEVEL & 1) == 0)
    {
        //-------------------------------
        // 1a0f  cbc6      set     0,(hl)
        // 1a11  cb8e      res     1,(hl)
        // 1a13  c9        ret     
        //-------------------------------
        CH3_SOUND_EFFECT->mask |= 1;
        CH3_SOUND_EFFECT->mask &= 0xfd;
        return;
    }
    else
    {
        //-------------------------------
        // 1a14  cb86      res     0,(hl)
        // 1a16  cbce      set     1,(hl)
        // 1a18  c9        ret     
        //-------------------------------
        CH3_SOUND_EFFECT->mask &= 0xfe;
        CH3_SOUND_EFFECT->mask |= 2;
        return;
    }
}

void pacmanMoveTile_1a19 (void)
{
    printf ("%s pos=%d,%d\n", __func__, PACMAN_POS.x, PACMAN_POS.y);
    //-------------------------------
    // 1a19  211c4d    ld      hl,#4d1c
    // 1a1c  7e        ld      a,(hl)
    // 1a1d  a7        and     a
    // 1a1e  ca2e1a    jp      z,#1a2e
    //-------------------------------
    if (PACMAN_VECTOR.y != 0)
    {
        //-------------------------------
        // 1a21  3a084d    ld      a,(#4d08)
        // 1a24  e607      and     #07
        // 1a26  fe04      cp      #04
        // 1a28  ca381a    jp      z,#1a38
        //-------------------------------
        if ((PACMAN_POS.y & 7) != 4)
        {
            //-------------------------------
            // 1a2b  c35c1a    jp      #1a5c
            //-------------------------------
            pacmanMove_1a5c ();
            return;
        }
    }
    else
    {
        //-------------------------------
        // 1a2e  3a094d    ld      a,(#4d09)
        // 1a31  e607      and     #07
        // 1a33  fe04      cp      #04
        // 1a35  c25c1a    jp      nz,#1a5c
        //-------------------------------
        if ((PACMAN_POS.x & 7) != 4)
        {
            pacmanMove_1a5c ();
            return;
        }
    }

    //-------------------------------
    // 1a38  3e05      ld      a,#05
    // 1a3a  cdd01e    call    #1ed0
    // 1a3d  3803      jr      c,#1a42         ; (3)
    //-------------------------------
    if (!checkTunnelTBD_1ed0(5))
    {
        //-------------------------------
        // 1a3f  ef        rst     #28
        // 1a40  1700
        //-------------------------------
        schedTask (TASK_PACMAN_ORIENT, 0);
    }

    //-------------------------------
    // 1a42  dd21264d  ld      ix,#4d26
    // 1a46  fd21124d  ld      iy,#4d12
    // 1a4a  cd0020    call    #2000
    // 1a4d  22124d    ld      (#4d12),hl
    //-------------------------------
    PACMAN_TILE = addXYOffset_2000 (PACMAN_VECTOR2, PACMAN_TILE);

    //-------------------------------
    // 1a50  2a264d    ld      hl,(#4d26)
    // 1a53  221c4d    ld      (#4d1c),hl
    //-------------------------------
    // printf ("%s tile change %d,%d -> %d,%d\n",
    //         __func__,
    //         PACMAN_VECTOR2.x, PACMAN_VECTOR2.y,
    //         PACMAN_VECTOR.x, PACMAN_VECTOR.y);
    PACMAN_VECTOR = PACMAN_VECTOR2;
    // printf ("%s tile change %d,%d -> %d,%d\n",
    //         __func__,
    //         PACMAN_VECTOR2.x, PACMAN_VECTOR2.y,
    //         PACMAN_VECTOR.x, PACMAN_VECTOR.y);

    //-------------------------------
    // 1a56  3a3c4d    ld      a,(#4d3c)
    // 1a59  32304d    ld      (#4d30),a
    //-------------------------------
    // printf ("%s orient change %d,%d\n",
    //         __func__,
    //         PACMAN_DESIRED_ORIENTATION,
    //         PACMAN_ORIENTATION);
    PACMAN_ORIENTATION = PACMAN_DESIRED_ORIENTATION;

    pacmanMove_1a5c ();
}

void pacmanMove_1a5c (void)
{
    //-------------------------------
    // 1a5c  dd211c4d  ld      ix,#4d1c
    // 1a60  fd21084d  ld      iy,#4d08
    // 1a64  cd0020    call    #2000
    // 1a67  c38519    jp      #1985
    //-------------------------------
    XYPOS pos = addXYOffset_2000 (PACMAN_VECTOR, PACMAN_POS);
    pacmanUpdatePos_1985 (pos);
}

void checkGhostsBecomeEdible_1a6a (void)
{
    //-------------------------------
    // 1a6a  3a9d4d    ld      a,(#4d9d)
    // 1a6d  fe06      cp      #06
    // 1a6f  c0        ret     nz
    //-------------------------------
    printf ("%s delay = %d\n", __func__, PACMAN_MOVE_DELAY);
    if (PACMAN_MOVE_DELAY!= 0x6)
        return;

    ghostsBecomeEdible_1a70();
}

void ghostsBecomeEdible_1a70 (void)
{
    //-------------------------------
    // 1a70  2abd4d    ld      hl,(#4dbd)
    // 1a73  22cb4d    ld      (#4dcb),hl
    //-------------------------------
    EDIBLE_REMAIN_COUNT = GHOST_EDIBLE_TIME;

    //-------------------------------
    // 1a76  3e01      ld      a,#01
    // 1a78  32a64d    ld      (#4da6),a
    // 1a7b  32a74d    ld      (#4da7),a
    // 1a7e  32a84d    ld      (#4da8),a
    // 1a81  32a94d    ld      (#4da9),a
    // 1a84  32aa4d    ld      (#4daa),a
    // 1a87  32b14d    ld      (#4db1),a
    // 1a8a  32b24d    ld      (#4db2),a
    // 1a8d  32b34d    ld      (#4db3),a
    // 1a90  32b44d    ld      (#4db4),a
    // 1a93  32b54d    ld      (#4db5),a
    //-------------------------------
    PACMAN_POWEREDUP = 
    BLINKY_EDIBLE = 
    PINKY_EDIBLE = 
    INKY_EDIBLE = 
    CLYDE_EDIBLE = 
    BLINKY_ORIENT_CHG_FLAG = 
    PINKY_ORIENT_CHG_FLAG = 
    INKY_ORIENT_CHG_FLAG = 
    CLYDE_ORIENT_CHG_FLAG = 
    PACMAN_ORIENT_CHG_FLAG = 1;
    // printf ("%s orient chg = %d\n", __func__, PACMAN_ORIENT_CHG_FLAG);

    //-------------------------------
    // 1a96  af        xor     a
    // 1a97  32c84d    ld      (#4dc8),a
    // 1a9a  32d04d    ld      (#4dd0),a
    //-------------------------------
    GHOST_COL_POWERUP_COUNTER = 
    KILLED_COUNT = 0;

    //-------------------------------
    // 1a9d  dd21004c  ld      ix,#4c00
    // 1aa1  dd36021c  ld      (ix+#02),#1c
    // 1aa5  dd36041c  ld      (ix+#04),#1c
    // 1aa9  dd36061c  ld      (ix+#06),#1c
    // 1aad  dd36081c  ld      (ix+#08),#1c
    // 1ab1  dd360311  ld      (ix+#03),#11
    // 1ab5  dd360511  ld      (ix+#05),#11
    // 1ab9  dd360711  ld      (ix+#07),#11
    // 1abd  dd360911  ld      (ix+#09),#11
    //-------------------------------
    BLINKY_SPRITE = 
    PINKY_SPRITE = 
    INKY_SPRITE = 
    CLYDE_SPRITE = 0x1c;

    BLINKY_COLOUR = 
    PINKY_COLOUR = 
    INKY_COLOUR = 
    CLYDE_COLOUR = 0x11;

    //-------------------------------
    // 1ac1  21ac4e    ld      hl,#4eac
    // 1ac4  cbee      set     5,(hl)
    // 1ac6  cbbe      res     7,(hl)
    // 1ac8  c9        ret     
    //-------------------------------
    CH2_SOUND_EFFECT->mask |= 0x20;
    CH2_SOUND_EFFECT->mask &= ~0x80;
}

void pacmanOrientLeft_1ac9 (void)
{
    //-------------------------------
    // 1ac9  2a0333    ld      hl,(#3303)
    // 1acc  3e02      ld      a,#02
    // 1ace  323c4d    ld      (#4d3c),a
    // 1ad1  22264d    ld      (#4d26),hl
    //-------------------------------
    PACMAN_DESIRED_ORIENTATION = ORIENT_LEFT;
    PACMAN_VECTOR2 = *MOVE_VECTOR_LEFT;

    //-------------------------------
    // 1ad4  0600      ld      b,#00
    // 1ad6  c3e418    jp      #18e4
    //-------------------------------
    pacmanCheckMoveClear_18e4 (0);
}

void pacmanOrientRight_1ad9 (void)
{
    //-------------------------------
    // 1ad9  2aff32    ld      hl,(#32ff)
    // 1adc  af        xor     a
    // 1add  323c4d    ld      (#4d3c),a
    // 1ae0  22264d    ld      (#4d26),hl
    //-------------------------------
    PACMAN_DESIRED_ORIENTATION = ORIENT_RIGHT;
    PACMAN_VECTOR2 = *MOVE_VECTOR_RIGHT;

    //-------------------------------
    // 1ae3  0600      ld      b,#00
    // 1ae5  c3e418    jp      #18e4
    //-------------------------------
    pacmanCheckMoveClear_18e4 (0);
}

void pacmanOrientUp_1ae8 (void)
{
    //-------------------------------
    // 1ae8  2a0533    ld      hl,(#3305)
    // 1aeb  3e03      ld      a,#03
    // 1aed  323c4d    ld      (#4d3c),a
    // 1af0  22264d    ld      (#4d26),hl
    //-------------------------------
    PACMAN_DESIRED_ORIENTATION = ORIENT_UP;
    PACMAN_VECTOR2 = *MOVE_VECTOR_UP;

    //-------------------------------
    // 1af3  0600      ld      b,#00
    // 1af5  c3e418    jp      #18e4
    //-------------------------------
    pacmanCheckMoveClear_18e4 (0);
}

void pacmanOrientDown_1af8 (void)
{
    //-------------------------------
    // 1af8  2a0133    ld      hl,(#3301)
    // 1afb  3e01      ld      a,#01
    // 1afd  323c4d    ld      (#4d3c),a
    // 1b00  22264d    ld      (#4d26),hl
    //-------------------------------
    PACMAN_DESIRED_ORIENTATION = ORIENT_DOWN;
    PACMAN_VECTOR2 = *MOVE_VECTOR_DOWN;

    //-------------------------------
    // 1b03  0600      ld      b,#00
    // 1b05  c3e418    jp      #18e4
    //-------------------------------
    pacmanCheckMoveClear_18e4 (0);
}

/*  Update counters for ghosts to exit the house.  As each ghost leaves
 *  (substate!=0) increment the counter for the next ghost.  Pinky then Inky
 *  then Clyde */
void updateLeaveHouseCounters_1b08 (void)
{
    //-------------------------------
    // 1b08  3a124e    ld      a,(#4e12)
    // 1b0b  a7        and     a
    // 1b0c  ca141b    jp      z,#1b14
    //-------------------------------
    if (P1_DIED_IN_LEVEL != 0)
    {
        //-------------------------------
        // 1b0f  219f4d    ld      hl,#4d9f
        // 1b12  34        inc     (hl)
        // 1b13  c9        ret     
        //-------------------------------
        EATEN_PILLS_COUNT++;
    }

    //-------------------------------
    // 1b14  3aa34d    ld      a,(#4da3)
    // 1b17  a7        and     a
    // 1b18  c0        ret     nz
    //-------------------------------

    /*  If Clyde has left then the house is empty so return */

    if (CLYDE_SUBSTATE != SUBSTATE_IN_HOUSE)
        return;

    //-------------------------------
    // 1b19  3aa24d    ld      a,(#4da2)
    // 1b1c  a7        and     a
    // 1b1d  ca251b    jp      z,#1b25
    //-------------------------------
    if (INKY_SUBSTATE != SUBSTATE_IN_HOUSE)
    {
        //-------------------------------
        // 1b20  21114e    ld      hl,#4e11
        // 1b23  34        inc     (hl)
        // 1b24  c9        ret     
        //-------------------------------
        P1_CLYDE_LEAVE_HOME_COUNTER++;
        return;
    }

    //-------------------------------
    // 1b25  3aa14d    ld      a,(#4da1)
    // 1b28  a7        and     a
    // 1b29  ca311b    jp      z,#1b31
    //-------------------------------
    if (PINKY_SUBSTATE != SUBSTATE_IN_HOUSE)
    {
        //-------------------------------
        // 1b2c  21104e    ld      hl,#4e10
        // 1b2f  34        inc     (hl)
        // 1b30  c9        ret     
        //-------------------------------
        P1_INKY_LEAVE_HOME_COUNTER++;
        return;
    }

    //-------------------------------
    // 1b31  210f4e    ld      hl,#4e0f
    // 1b34  34        inc     (hl)
    // 1b35  c9        ret     
    //-------------------------------
    P1_PINKY_LEAVE_HOME_COUNTER++;
}

void blinkyUpdateMovePat_1b36 (void)
{
    printf ("%s sub = %d st=%d\n", __func__, BLINKY_SUBSTATE, BLINKY_STATE);
    //-------------------------------
    // 1b36  3aa04d    ld      a,(#4da0)
    // 1b39  a7        and     a
    // 1b3a  c8        ret     z
    //-------------------------------
    if (BLINKY_SUBSTATE == SUBSTATE_IN_HOUSE)
        return;

    //-------------------------------
    // 1b3b  3aac4d    ld      a,(#4dac)
    // 1b3e  a7        and     a
    // 1b3f  c0        ret     nz
    //-------------------------------
    if (BLINKY_STATE != 0)
        return;

    //-------------------------------
    // 1b40  cdd720    call    #20d7
    //-------------------------------
    updateDifficultyTBD_20d7();

    //-------------------------------
    // 1b43  2a314d    ld      hl,(#4d31)
    // 1b46  01994d    ld      bc,#4d99
    // 1b49  cd5a20    call    #205a
    //-------------------------------
    checkGhostEnterTunnel_205a (BLINKY_TILE2, &BLINKY_IN_TUNNEL);
    //-------------------------------
    // 1b4c  3a994d    ld      a,(#4d99)
    // 1b4f  a7        and     a
    // 1b50  ca6a1b    jp      z,#1b6a
    //-------------------------------
    printf ("%s aux = %d\n", __func__, BLINKY_IN_TUNNEL);
    if (BLINKY_IN_TUNNEL != 0)
    {
        //-------------------------------
        // 1b53  2a604d    ld      hl,(#4d60)
        // 1b56  29        add     hl,hl
        // 1b57  22604d    ld      (#4d60),hl
        // 1b5a  2a5e4d    ld      hl,(#4d5e)
        // 1b5d  ed6a      adc     hl,hl
        // 1b5f  225e4d    ld      (#4d5e),hl
        // 1b62  d0        ret     nc
        // 1b63  21604d    ld      hl,#4d60
        // 1b66  34        inc     (hl)
        // 1b67  c3d81b    jp      #1bd8
        //-------------------------------
        rotate32 (&BLINKY_MOVE_PAT_TUNNEL, 1);

        if ((BLINKY_MOVE_PAT_TUNNEL & 1) == 0)
            return;
    }

    //-------------------------------
    // 1b6a  3aa74d    ld      a,(#4da7)
    // 1b6d  a7        and     a
    // 1b6e  ca881b    jp      z,#1b88
    //-------------------------------
    else if (BLINKY_EDIBLE != 0)
    {
        //-------------------------------
        // 1b71  2a5c4d    ld      hl,(#4d5c)
        // 1b74  29        add     hl,hl
        // 1b75  225c4d    ld      (#4d5c),hl
        // 1b78  2a5a4d    ld      hl,(#4d5a)
        // 1b7b  ed6a      adc     hl,hl
        // 1b7d  225a4d    ld      (#4d5a),hl
        // 1b80  d0        ret     nc
        // 1b81  215c4d    ld      hl,#4d5c
        // 1b84  34        inc     (hl)
        // 1b85  c3d81b    jp      #1bd8
        //-------------------------------
        rotate32 (&BLINKY_MOVE_PAT_EDIBLE, 1);

        if ((BLINKY_MOVE_PAT_EDIBLE & 1) == 0)
            return;
    }

    //-------------------------------
    // 1b88  3ab74d    ld      a,(#4db7)
    // 1b8b  a7        and     a
    // 1b8c  caa61b    jp      z,#1ba6
    //-------------------------------
    else if (DIFF_FLAG_2 != 0)
    {
        //-------------------------------
        // 1b8f  2a504d    ld      hl,(#4d50)
        // 1b92  29        add     hl,hl
        // 1b93  22504d    ld      (#4d50),hl
        // 1b96  2a4e4d    ld      hl,(#4d4e)
        // 1b99  ed6a      adc     hl,hl
        // 1b9b  224e4d    ld      (#4d4e),hl
        // 1b9e  d0        ret     nc
        // 1b9f  21504d    ld      hl,#4d50
        // 1ba2  34        inc     (hl)
        // 1ba3  c3d81b    jp      #1bd8
        //-------------------------------
        rotate32 (&PACMAN_MOVE_PAT_DIFF2, 1);

        if ((PACMAN_MOVE_PAT_DIFF2 & 1) == 0)
            return;
    }
    else
    {
        //-------------------------------
        // 1ba6  3ab64d    ld      a,(#4db6)
        // 1ba9  a7        and     a
        // 1baa  cac41b    jp      z,#1bc4
        //-------------------------------
        if (DIFF_FLAG_1 != 0)
        {
            //-------------------------------
            // 1bad  2a544d    ld      hl,(#4d54)
            // 1bb0  29        add     hl,hl
            // 1bb1  22544d    ld      (#4d54),hl
            // 1bb4  2a524d    ld      hl,(#4d52)
            // 1bb7  ed6a      adc     hl,hl
            // 1bb9  22524d    ld      (#4d52),hl
            // 1bbc  d0        ret     nc
            // 1bbd  21544d    ld      hl,#4d54
            // 1bc0  34        inc     (hl)
            // 1bc1  c3d81b    jp      #1bd8
            //-------------------------------
            rotate32 (&PACMAN_MOVE_PAT_DIFF1, 1);

            if ((PACMAN_MOVE_PAT_DIFF1 & 1) == 0)
                return;
        }
        else
        {
            //-------------------------------
            // 1bc4  2a584d    ld      hl,(#4d58)
            // 1bc7  29        add     hl,hl
            // 1bc8  22584d    ld      (#4d58),hl
            // 1bcb  2a564d    ld      hl,(#4d56)
            // 1bce  ed6a      adc     hl,hl
            // 1bd0  22564d    ld      (#4d56),hl
            // 1bd3  d0        ret     nc
            // 1bd4  21584d    ld      hl,#4d58
            // 1bd7  34        inc     (hl)
            //-------------------------------
            rotate32 (&BLINKY_MOVE_PAT_NORMAL, 1);

            if ((BLINKY_MOVE_PAT_NORMAL & 1) == 0)
                return;
        }
    }
    blinkyUpdatePosition_1bd8();
}

void blinkyUpdatePosition_1bd8 (void)
{
    printf ("%s\n", __func__);
    //-------------------------------
    // 1bd8  21144d    ld      hl,#4d14
    // 1bdb  7e        ld      a,(hl)
    // 1bdc  a7        and     a
    // 1bdd  caed1b    jp      z,#1bed
    //-------------------------------
    if (BLINKY_VECTOR.y != 0)
    {
        //-------------------------------
        // 1be0  3a004d    ld      a,(#4d00)
        // 1be3  e607      and     #07
        // 1be5  fe04      cp      #04
        // 1be7  caf71b    jp      z,#1bf7
        // 1bea  c3361c    jp      #1c36
        //-------------------------------
        if ((BLINKY_POS.y & 7) != 4)
            goto jump_1c36;
    }
    else
    {
        //-------------------------------
        // 1bed  3a014d    ld      a,(#4d01)
        // 1bf0  e607      and     #07
        // 1bf2  fe04      cp      #04
        // 1bf4  c2361c    jp      nz,#1c36
        //-------------------------------
        if ((BLINKY_POS.x & 7) != 4)
            goto jump_1c36;
    }

    //-------------------------------
    // 1bf7  3e01      ld      a,#01
    // 1bf9  cdd01e    call    #1ed0
    // 1bfc  381b      jr      c,#1c19         ; (27)
    //-------------------------------
    if (!checkTunnelTBD_1ed0(GHOST_BLINKY))
    {
        //-------------------------------
        // 1bfe  3aa74d    ld      a,(#4da7)
        // 1c01  a7        and     a
        // 1c02  ca0b1c    jp      z,#1c0b
        //-------------------------------
        if (BLINKY_EDIBLE != 0)
        {
            //-------------------------------
            // 1c05  ef        rst     #28
            // 1c06  0c00
            // 1c08  c3191c    jp      #1c19
            //-------------------------------
            schedTask (TASK_HOME_RANDOM_BLINKY, 0x00);
        }
        else
        {
            //-------------------------------
            // 1c0b  2a0a4d    ld      hl,(#4d0a)
            // 1c0e  cd5220    call    #2052
            //-------------------------------
            uint16_t addr = getColourOffset_2052(BLINKY_TILE);

            //-------------------------------
            // 1c11  7e        ld      a,(hl)
            // 1c12  fe1a      cp      #1a
            // 1c14  2803      jr      z,#1c19         ; (3)
            //-------------------------------
            if (COLOUR[addr] != 0x1a)
            {
                //-------------------------------
                // 1c16  ef        rst     #28
                // 1c17  0800
                //-------------------------------
                schedTask (TASK_SCATTER_CHASE_BLINKY, 0x00);
            }
        }
    }

    //-------------------------------
    // 1c19  cdfe1e    call    #1efe
    // 1c1c  dd211e4d  ld      ix,#4d1e
    // 1c20  fd210a4d  ld      iy,#4d0a
    // 1c24  cd0020    call    #2000
    // 1c27  220a4d    ld      (#4d0a),hl
    //-------------------------------
    blinkyCheckReverse_1efe();
    BLINKY_TILE = addXYOffset_2000 (BLINKY_VECTOR2, BLINKY_TILE);

    //-------------------------------
    // 1c2a  2a1e4d    ld      hl,(#4d1e)
    // 1c2d  22144d    ld      (#4d14),hl
    // 1c30  3a2c4d    ld      a,(#4d2c)
    // 1c33  32284d    ld      (#4d28),a
    //-------------------------------
    BLINKY_VECTOR = BLINKY_VECTOR2;
    BLINKY_PREV_ORIENTATION = BLINKY_ORIENTATION;

jump_1c36:
    //-------------------------------
    // 1c36  dd21144d  ld      ix,#4d14
    // 1c3a  fd21004d  ld      iy,#4d00
    // 1c3e  cd0020    call    #2000
    // 1c41  22004d    ld      (#4d00),hl
    //-------------------------------
    BLINKY_POS = addXYOffset_2000 (BLINKY_VECTOR, BLINKY_POS);

    //-------------------------------
    // 1c44  cd1820    call    #2018
    // 1c47  22314d    ld      (#4d31),hl
    // 1c4a  c9        ret     
    //-------------------------------
    BLINKY_TILE2 = pixelToTile_2018(BLINKY_POS);

    printf ("%s upd blinky pos %d,%d -> %d,%d\n", __func__,
            BLINKY_VECTOR.x,
            BLINKY_VECTOR.y,
            BLINKY_POS.x,
            BLINKY_POS.y);
}

void pinkyUpdateMovePat_1c4b (void)
{
    //-------------------------------
    // 1c4b  3aa14d    ld      a,(#4da1)
    // 1c4e  fe01      cp      #01
    // 1c50  c0        ret     nz
    //-------------------------------
    if (PINKY_SUBSTATE != SUBSTATE_CHASE)
        return;

    //-------------------------------
    // 1c51  3aad4d    ld      a,(#4dad)
    // 1c54  a7        and     a
    // 1c55  c0        ret     nz
    //-------------------------------
    if (PINKY_STATE != GHOST_STATE_ALIVE)
        return;

    //-------------------------------
    // 1c56  2a334d    ld      hl,(#4d33)
    // 1c59  019a4d    ld      bc,#4d9a
    // 1c5c  cd5a20    call    #205a
    //-------------------------------
    checkGhostEnterTunnel_205a (PINKY_TILE2, &PINKY_IN_TUNNEL);

    //-------------------------------
    // 1c5f  3a9a4d    ld      a,(#4d9a)
    // 1c62  a7        and     a
    // 1c63  ca7d1c    jp      z,#1c7d
    //-------------------------------
    if (PINKY_IN_TUNNEL != 0)
    {
        //-------------------------------
        // 1c66  2a6c4d    ld      hl,(#4d6c)
        // 1c69  29        add     hl,hl
        // 1c6a  226c4d    ld      (#4d6c),hl
        // 1c6d  2a6a4d    ld      hl,(#4d6a)
        // 1c70  ed6a      adc     hl,hl
        // 1c72  226a4d    ld      (#4d6a),hl
        // 1c75  d0        ret     nc
        // 1c76  216c4d    ld      hl,#4d6c
        // 1c79  34        inc     (hl)
        // 1c7a  c3af1c    jp      #1caf
        //-------------------------------
        rotate32 (&PINKY_MOVE_PAT_TUNNEL, 1);

        if ((PINKY_MOVE_PAT_TUNNEL & 1) == 0)
            return;
    }
    else
    {
        //-------------------------------
        // 1c7d  3aa84d    ld      a,(#4da8)
        // 1c80  a7        and     a
        // 1c81  ca9b1c    jp      z,#1c9b
        //-------------------------------
        if (PINKY_EDIBLE != 0)
        {
            //-------------------------------
            // 1c84  2a684d    ld      hl,(#4d68)
            // 1c87  29        add     hl,hl
            // 1c88  22684d    ld      (#4d68),hl
            // 1c8b  2a664d    ld      hl,(#4d66)
            // 1c8e  ed6a      adc     hl,hl
            // 1c90  22664d    ld      (#4d66),hl
            // 1c93  d0        ret     nc
            // 1c94  21684d    ld      hl,#4d68
            // 1c97  34        inc     (hl)
            // 1c98  c3af1c    jp      #1caf
            //-------------------------------
            rotate32 (&PINKY_MOVE_PAT_EDIBLE, 1);

            if ((PINKY_MOVE_PAT_EDIBLE & 1) == 0)
                return;
        }
        else
        {
            //-------------------------------
            // 1c9b  2a644d    ld      hl,(#4d64)
            // 1c9e  29        add     hl,hl
            // 1c9f  22644d    ld      (#4d64),hl
            // 1ca2  2a624d    ld      hl,(#4d62)
            // 1ca5  ed6a      adc     hl,hl
            // 1ca7  22624d    ld      (#4d62),hl
            // 1caa  d0        ret     nc
            // 1cab  21644d    ld      hl,#4d64
            // 1cae  34        inc     (hl)
            //-------------------------------
            rotate32 (&PINKY_MOVE_PAT_NORMAL, 1);

            if ((PINKY_MOVE_PAT_NORMAL & 1) == 0)
                return;
        }
    }
    pinkyUpdatePosition_1caf();
}

void pinkyUpdatePosition_1caf (void)
{
    //-------------------------------
    // 1caf  21164d    ld      hl,#4d16
    // 1cb2  7e        ld      a,(hl)
    // 1cb3  a7        and     a
    // 1cb4  cac41c    jp      z,#1cc4
    //-------------------------------
    if (PINKY_VECTOR.y != 0)
    {
        //-------------------------------
        // 1cb7  3a024d    ld      a,(#4d02)
        // 1cba  e607      and     #07
        // 1cbc  fe04      cp      #04
        // 1cbe  cace1c    jp      z,#1cce
        // 1cc1  c30d1d    jp      #1d0d
        //-------------------------------
        if ((PINKY_POS.y & 7) != 4)
            goto jump_1d0d;
    }
    else
    {
        //-------------------------------
        // 1cc4  3a034d    ld      a,(#4d03)
        // 1cc7  e607      and     #07
        // 1cc9  fe04      cp      #04
        // 1ccb  c20d1d    jp      nz,#1d0d
        //-------------------------------
        if ((PINKY_POS.x & 7) != 4)
            goto jump_1d0d;
    }

    //-------------------------------
    // 1cce  3e02      ld      a,#02
    // 1cd0  cdd01e    call    #1ed0
    // 1cd3  381b      jr      c,#1cf0         ; (27)
    //-------------------------------
    if (!checkTunnelTBD_1ed0(GHOST_PINKY))
    {
        //-------------------------------
        // 1cd5  3aa84d    ld      a,(#4da8)
        // 1cd8  a7        and     a
        // 1cd9  cae21c    jp      z,#1ce2
        //-------------------------------
        if (PINKY_EDIBLE != 0)
        {
            //-------------------------------
            // 1cdc  ef        rst     #28
            // 1cdd  0d00
            // 1cdf  c3f01c    jp      #1cf0
            //-------------------------------
            schedTask (TASK_HOME_RANDOM_PINKY, 0x00);
        }
        else
        {
            //-------------------------------
            // 1ce2  2a0c4d    ld      hl,(#4d0c)
            // 1ce5  cd5220    call    #2052
            //-------------------------------
            uint16_t addr = getColourOffset_2052(PINKY_TILE);

            //-------------------------------
            // 1ce8  7e        ld      a,(hl)
            // 1ce9  fe1a      cp      #1a
            // 1ceb  2803      jr      z,#1cf0         ; (3)
            //-------------------------------
            if (COLOUR[addr] != 0x1a)
            {
                //-------------------------------
                // 1ced  ef        rst     #28
                // 1cee  0900
                //-------------------------------
                schedTask (TASK_SCATTER_CHASE_PINKY, 0x00);
            }
        }
    }

    //-------------------------------
    // 1cf0  cd251f    call    #1f25
    //-------------------------------
    pinkyCheckReverse_1f25();

    //-------------------------------
    // 1cf3  dd21204d  ld      ix,#4d20
    // 1cf7  fd210c4d  ld      iy,#4d0c
    // 1cfb  cd0020    call    #2000
    // 1cfe  220c4d    ld      (#4d0c),hl
    //-------------------------------
    PINKY_TILE = addXYOffset_2000 (PINKY_VECTOR2, PINKY_TILE);

    //-------------------------------
    // 1d01  2a204d    ld      hl,(#4d20)
    // 1d04  22164d    ld      (#4d16),hl
    //-------------------------------
    PINKY_VECTOR = PINKY_VECTOR2;

    //-------------------------------
    // 1d07  3a2d4d    ld      a,(#4d2d)
    // 1d0a  32294d    ld      (#4d29),a
    //-------------------------------
    PINKY_PREV_ORIENTATION = PINKY_ORIENTATION;

jump_1d0d:
    //-------------------------------
    // 1d0d  dd21164d  ld      ix,#4d16
    // 1d11  fd21024d  ld      iy,#4d02
    // 1d15  cd0020    call    #2000
    // 1d18  22024d    ld      (#4d02),hl
    //-------------------------------
    PINKY_POS = addXYOffset_2000 (PINKY_VECTOR, PINKY_POS);

    //-------------------------------
    // 1d1b  cd1820    call    #2018
    // 1d1e  22334d    ld      (#4d33),hl
    // 1d21  c9        ret     
    //-------------------------------
    PINKY_TILE2 = pixelToTile_2018(PINKY_POS);
}

void inkyUpdateMovePat_1d22 (void)
{
    //-------------------------------
    // 1d22  3aa24d    ld      a,(#4da2)
    // 1d25  fe01      cp      #01
    // 1d27  c0        ret     nz
    //-------------------------------
    if (INKY_SUBSTATE != SUBSTATE_CHASE)
        return;

    //-------------------------------
    // 1d28  3aae4d    ld      a,(#4dae)
    // 1d2b  a7        and     a
    // 1d2c  c0        ret     nz
    //-------------------------------
    if (INKY_STATE != GHOST_STATE_ALIVE)
        return;

    //-------------------------------
    // 1d2d  2a354d    ld      hl,(#4d35)
    // 1d30  019b4d    ld      bc,#4d9b
    // 1d33  cd5a20    call    #205a
    //-------------------------------
    checkGhostEnterTunnel_205a (INKY_TILE2, &INKY_IN_TUNNEL);

    //-------------------------------
    // 1d36  3a9b4d    ld      a,(#4d9b)
    // 1d39  a7        and     a
    // 1d3a  ca541d    jp      z,#1d54
    //-------------------------------
    if (INKY_IN_TUNNEL != 0)
    {
        //-------------------------------
        // 1d3d  2a784d    ld      hl,(#4d78)
        // 1d40  29        add     hl,hl
        // 1d41  22784d    ld      (#4d78),hl
        // 1d44  2a764d    ld      hl,(#4d76)
        // 1d47  ed6a      adc     hl,hl
        // 1d49  22764d    ld      (#4d76),hl
        // 1d4c  d0        ret     nc
        // 1d4d  21784d    ld      hl,#4d78
        // 1d50  34        inc     (hl)
        // 1d51  c3861d    jp      #1d86
        //-------------------------------
        rotate32 (&INKY_MOVE_PAT_TUNNEL, 1);

        if ((INKY_MOVE_PAT_TUNNEL & 1) == 0)
            return;
    }
    else
    {
        //-------------------------------
        // 1d54  3aa94d    ld      a,(#4da9)
        // 1d57  a7        and     a
        // 1d58  ca721d    jp      z,#1d72
        //-------------------------------
        if (INKY_EDIBLE != 0)
        {
            //-------------------------------
            // 1d5b  2a744d    ld      hl,(#4d74)
            // 1d5e  29        add     hl,hl
            // 1d5f  22744d    ld      (#4d74),hl
            // 1d62  2a724d    ld      hl,(#4d72)
            // 1d65  ed6a      adc     hl,hl
            // 1d67  22724d    ld      (#4d72),hl
            // 1d6a  d0        ret     nc
            // 1d6b  21744d    ld      hl,#4d74
            // 1d6e  34        inc     (hl)
            // 1d6f  c3861d    jp      #1d86
            //-------------------------------
            rotate32 (&INKY_MOVE_PAT_EDIBLE, 1);

            if ((INKY_MOVE_PAT_EDIBLE & 1) == 0)
                return;
        }
        else
        {
            //-------------------------------
            // 1d72  2a704d    ld      hl,(#4d70)
            // 1d75  29        add     hl,hl
            // 1d76  22704d    ld      (#4d70),hl
            // 1d79  2a6e4d    ld      hl,(#4d6e)
            // 1d7c  ed6a      adc     hl,hl
            // 1d7e  226e4d    ld      (#4d6e),hl
            // 1d81  d0        ret     nc
            // 1d82  21704d    ld      hl,#4d70
            // 1d85  34        inc     (hl)
            //-------------------------------
            rotate32 (&INKY_MOVE_PAT_NORMAL, 1);

            if ((INKY_MOVE_PAT_NORMAL & 1) == 0)
                return;
        }
    }
    inkyUpdatePosition_1d86();
}

void inkyUpdatePosition_1d86 (void)
{
    //-------------------------------
    // 1d86  21184d    ld      hl,#4d18
    // 1d89  7e        ld      a,(hl)
    // 1d8a  a7        and     a
    // 1d8b  ca9b1d    jp      z,#1d9b
    //-------------------------------
    if (INKY_VECTOR.y != 0)
    {
        //-------------------------------
        // 1d8e  3a044d    ld      a,(#4d04)
        // 1d91  e607      and     #07
        // 1d93  fe04      cp      #04
        // 1d95  caa51d    jp      z,#1da5
        // 1d98  c3e41d    jp      #1de4
        //-------------------------------
        if ((INKY_POS.y & 7) != 4)
            goto jump_1de4;
    }
    else
    {
        //-------------------------------
        // 1d9b  3a054d    ld      a,(#4d05)
        // 1d9e  e607      and     #07
        // 1da0  fe04      cp      #04
        // 1da2  c2e41d    jp      nz,#1de4
        //-------------------------------
        if ((INKY_POS.x & 7) != 4)
            goto jump_1de4;
    }

    //-------------------------------
    // 1da5  3e03      ld      a,#03
    // 1da7  cdd01e    call    #1ed0
    // 1daa  381b      jr      c,#1dc7         ; (27)
    //-------------------------------
    if (!checkTunnelTBD_1ed0(GHOST_INKY))
    {
        //-------------------------------
        // 1dac  3aa94d    ld      a,(#4da9)
        // 1daf  a7        and     a
        // 1db0  cab91d    jp      z,#1db9
        //-------------------------------
        if (INKY_EDIBLE != 0)
        {
            //-------------------------------
            // 1db3  ef        rst     #28
            // 1db4  0e00
            // 1db6  c3c71d    jp      #1dc7
            //-------------------------------
            schedTask (TASK_HOME_RANDOM_INKY, 0x00);
        }
        else
        {
            //-------------------------------
            // 1db9  2a0e4d    ld      hl,(#4d0e)
            // 1dbc  cd5220    call    #2052
            //-------------------------------
            uint16_t addr = getColourOffset_2052(INKY_TILE);

            //-------------------------------
            // 1dbf  7e        ld      a,(hl)
            // 1dc0  fe1a      cp      #1a
            // 1dc2  2803      jr      z,#1dc7         ; (3)
            //-------------------------------
            if (COLOUR[addr] != 0x1a)
            {
                //-------------------------------
                // 1dc4  ef        rst     #28
                // 1dc5  0a00
                //-------------------------------
                schedTask (TASK_SCATTER_CHASE_INKY, 0x00);
            }
        }
    }

    //-------------------------------
    // 1dc7  cd4c1f    call    #1f4c
    // 1dca  dd21224d  ld      ix,#4d22
    // 1dce  fd210e4d  ld      iy,#4d0e
    // 1dd2  cd0020    call    #2000
    // 1dd5  220e4d    ld      (#4d0e),hl
    //-------------------------------
    inkyCheckReverse_1f4c();
    INKY_TILE = addXYOffset_2000 (INKY_VECTOR2, INKY_TILE);

    //-------------------------------
    // 1dd8  2a224d    ld      hl,(#4d22)
    // 1ddb  22184d    ld      (#4d18),hl
    // 1dde  3a2e4d    ld      a,(#4d2e)
    // 1de1  322a4d    ld      (#4d2a),a
    //-------------------------------
    INKY_VECTOR = INKY_VECTOR2;
    INKY_PREV_ORIENTATION = INKY_ORIENTATION;

jump_1de4:
    //-------------------------------
    // 1de4  dd21184d  ld      ix,#4d18
    // 1de8  fd21044d  ld      iy,#4d04
    // 1dec  cd0020    call    #2000
    // 1def  22044d    ld      (#4d04),hl
    //-------------------------------
    INKY_POS = addXYOffset_2000 (INKY_VECTOR, INKY_POS);

    //-------------------------------
    // 1df2  cd1820    call    #2018
    // 1df5  22354d    ld      (#4d35),hl
    // 1df8  c9        ret     
    //-------------------------------
    INKY_TILE2 = pixelToTile_2018(INKY_POS);
}

void clydeUpdateMovePat_1df9 (void)
{
    //-------------------------------
    // 1df9  3aa34d    ld      a,(#4da3)
    // 1dfc  fe01      cp      #01
    // 1dfe  c0        ret     nz
    //-------------------------------
    if (CLYDE_SUBSTATE != SUBSTATE_CHASE)
        return;

    //-------------------------------
    // 1dff  3aaf4d    ld      a,(#4daf)
    // 1e02  a7        and     a
    // 1e03  c0        ret     nz
    //-------------------------------
    if (CLYDE_STATE != GHOST_STATE_ALIVE)
        return;

    //-------------------------------
    // 1e04  2a374d    ld      hl,(#4d37)
    // 1e07  019c4d    ld      bc,#4d9c
    // 1e0a  cd5a20    call    #205a
    //-------------------------------
    checkGhostEnterTunnel_205a (CLYDE_TILE2, &CLYDE_IN_TUNNEL);

    //-------------------------------
    // 1e0d  3a9c4d    ld      a,(#4d9c)
    // 1e10  a7        and     a
    // 1e11  ca2b1e    jp      z,#1e2b
    //-------------------------------
    if (CLYDE_IN_TUNNEL != 0)
    {
        //-------------------------------
        // 1e14  2a844d    ld      hl,(#4d84)
        // 1e17  29        add     hl,hl
        // 1e18  22844d    ld      (#4d84),hl
        // 1e1b  2a824d    ld      hl,(#4d82)
        // 1e1e  ed6a      adc     hl,hl
        // 1e20  22824d    ld      (#4d82),hl
        // 1e23  d0        ret     nc
        // 1e24  21844d    ld      hl,#4d84
        // 1e27  34        inc     (hl)
        // 1e28  c35d1e    jp      #1e5d
        //-------------------------------
        rotate32 (&CLYDE_MOVE_PAT_TUNNEL, 1);

        if ((CLYDE_MOVE_PAT_TUNNEL & 1) == 0)
            return;
    }
    else
    {
        //-------------------------------
        // 1e2b  3aaa4d    ld      a,(#4daa)
        // 1e2e  a7        and     a
        // 1e2f  ca491e    jp      z,#1e49
        //-------------------------------
        if (CLYDE_EDIBLE != 0)
        {
            //-------------------------------
            // 1e32  2a804d    ld      hl,(#4d80)
            // 1e35  29        add     hl,hl
            // 1e36  22804d    ld      (#4d80),hl
            // 1e39  2a7e4d    ld      hl,(#4d7e)
            // 1e3c  ed6a      adc     hl,hl
            // 1e3e  227e4d    ld      (#4d7e),hl
            // 1e41  d0        ret     nc
            // 1e42  21804d    ld      hl,#4d80
            // 1e45  34        inc     (hl)
            // 1e46  c35d1e    jp      #1e5d
            //-------------------------------
            rotate32 (&CLYDE_MOVE_PAT_EDIBLE, 1);

            if ((CLYDE_MOVE_PAT_EDIBLE & 1) == 0)
                return;
        }
        else
        {
            //-------------------------------
            // 1e49  2a7c4d    ld      hl,(#4d7c)
            // 1e4c  29        add     hl,hl
            // 1e4d  227c4d    ld      (#4d7c),hl
            // 1e50  2a7a4d    ld      hl,(#4d7a)
            // 1e53  ed6a      adc     hl,hl
            // 1e55  227a4d    ld      (#4d7a),hl
            // 1e58  d0        ret     nc
            // 1e59  217c4d    ld      hl,#4d7c
            // 1e5c  34        inc     (hl)
            //-------------------------------
            rotate32 (&CLYDE_MOVE_PAT_NORMAL, 1);

            if ((CLYDE_MOVE_PAT_NORMAL & 1) == 0)
                return;
        }
    }
    clydeUpdatePosition_1e5d();
}

void clydeUpdatePosition_1e5d (void)
{
    //-------------------------------
    // 1e5d  211a4d    ld      hl,#4d1a
    // 1e60  7e        ld      a,(hl)
    // 1e61  a7        and     a
    // 1e62  ca721e    jp      z,#1e72
    //-------------------------------
    if (CLYDE_VECTOR.y != 0)
    {
        //-------------------------------
        // 1e65  3a064d    ld      a,(#4d06)
        // 1e68  e607      and     #07
        // 1e6a  fe04      cp      #04
        // 1e6c  ca7c1e    jp      z,#1e7c
        // 1e6f  c3bb1e    jp      #1ebb
        //-------------------------------
        if ((CLYDE_POS.y & 7) != 4)
            goto jump_1ebb;
    }
    else
    {
        //-------------------------------
        // 1e72  3a074d    ld      a,(#4d07)
        // 1e75  e607      and     #07
        // 1e77  fe04      cp      #04
        // 1e79  c2bb1e    jp      nz,#1ebb
        //-------------------------------
        if ((CLYDE_POS.x & 7) != 4)
            goto jump_1ebb;
    }

    //-------------------------------
    // 1e7c  3e04      ld      a,#04
    // 1e7e  cdd01e    call    #1ed0
    // 1e81  381b      jr      c,#1e9e         ; (27)
    //-------------------------------
    if (!checkTunnelTBD_1ed0(GHOST_CLYDE))
    {
        //-------------------------------
        // 1e83  3aaa4d    ld      a,(#4daa)
        // 1e86  a7        and     a
        // 1e87  ca901e    jp      z,#1e90
        //-------------------------------
        if (CLYDE_EDIBLE != 0)
        {
            //-------------------------------
            // 1e8a  ef        rst     #28
            // 1e8b  0f00
            // 1e8d  c39e1e    jp      #1e9e
            //-------------------------------
            schedTask (TASK_HOME_RANDOM_CLYDE, 0x00);
        }
        else
        {
            //-------------------------------
            // 1e90  2a104d    ld      hl,(#4d10)
            // 1e93  cd5220    call    #2052
            //-------------------------------
            uint16_t addr = getColourOffset_2052 (CLYDE_TILE);

            //-------------------------------
            // 1e96  7e        ld      a,(hl)
            // 1e97  fe1a      cp      #1a
            // 1e99  2803      jr      z,#1e9e         ; (3)
            //-------------------------------
            if (COLOUR[addr] != 0x1a)
            {
                //-------------------------------
                // 1e9b  ef        rst     #28
                // 1e9c  0b00
                //-------------------------------
                schedTask (TASK_SCATTER_CHASE_CLYDE, 0x00);
            }
        }
    }

    //-------------------------------
    // 1e9e  cd731f    call    #1f73
    // 1ea1  dd21244d  ld      ix,#4d24
    // 1ea5  fd21104d  ld      iy,#4d10
    // 1ea9  cd0020    call    #2000
    // 1eac  22104d    ld      (#4d10),hl
    //-------------------------------
    clydeCheckReverse_1f73();
    CLYDE_TILE = addXYOffset_2000 (CLYDE_VECTOR2, CLYDE_TILE);

    //-------------------------------
    // 1eaf  2a244d    ld      hl,(#4d24)
    // 1eb2  221a4d    ld      (#4d1a),hl
    // 1eb5  3a2f4d    ld      a,(#4d2f)
    // 1eb8  322b4d    ld      (#4d2b),a
    //-------------------------------
    CLYDE_VECTOR = CLYDE_VECTOR2;
    CLYDE_PREV_ORIENTATION = CLYDE_ORIENTATION;

jump_1ebb:
    //-------------------------------
    // 1ebb  dd211a4d  ld      ix,#4d1a
    // 1ebf  fd21064d  ld      iy,#4d06
    // 1ec3  cd0020    call    #2000
    // 1ec6  22064d    ld      (#4d06),hl
    //-------------------------------
    CLYDE_POS = addXYOffset_2000 (CLYDE_VECTOR, CLYDE_POS);

    //-------------------------------
    // 1ec9  cd1820    call    #2018
    // 1ecc  22374d    ld      (#4d37),hl
    // 1ecf  c9        ret     
    //-------------------------------
    CLYDE_TILE2 = pixelToTile_2018 (CLYDE_POS);
}

/*  Ghost number 1-4 or 5 for pacman.  Checking if in tunnel ?
 *  Tile positions are 0x1e to 0x3d for x and 0x22 to 0x3e for y
 *  Wrap-around is when x reaches 0x1d or 0x3e */
bool checkTunnelTBD_1ed0 (int ghost)
{
    //-------------------------------
    // 1ed0  87        add     a,a
    // 1ed1  4f        ld      c,a
    // 1ed2  0600      ld      b,#00
    // 1ed4  21094d    ld      hl,#4d09
    // 1ed7  09        add     hl,bc
    // 1ed8  7e        ld      a,(hl)
    //-------------------------------
    /*  Note 4d09 is odd, it's 4d08 + 1 which is (blinky-1).x */
    XYPOS *tile = &BLINKY_TILE + ghost - 1;
    printf ("%s check %04lx\n", __func__, (uint8_t*)tile-MEM);

    //-------------------------------
    // 1ed9  fe1d      cp      #1d
    // 1edb  c2e31e    jp      nz,#1ee3
    //-------------------------------
    if (tile->x == 0x1d)
    {
        //-------------------------------
        // 1ede  363d      ld      (hl),#3d
        // 1ee0  c3fc1e    jp      #1efc
        //-------------------------------
        tile->x = 0x3d;
    }

    //-------------------------------
    // 1ee3  fe3e      cp      #3e
    // 1ee5  c2ed1e    jp      nz,#1eed
    //-------------------------------
    else if (tile->x == 0x3e)
    {
        //-------------------------------
        // 1ee8  361e      ld      (hl),#1e
        // 1eea  c3fc1e    jp      #1efc
        //-------------------------------
        tile->x = 0x1e;
    }
    else
    {
        //-------------------------------
        // 1eed  0621      ld      b,#21
        // 1eef  90        sub     b
        // 1ef0  dafc1e    jp      c,#1efc
        // 1ef3  7e        ld      a,(hl)
        // 1ef4  063b      ld      b,#3b
        // 1ef6  90        sub     b
        // 1ef7  d2fc1e    jp      nc,#1efc
        // 1efa  a7        and     a            ; clear carry flag
        // 1efb  c9        ret     
        //-------------------------------
        if (tile->x >= 0x21 && tile->x < 0x3b)
            return false;
    }

    //-------------------------------
    // 1efc  37        scf     
    // 1efd  c9        ret     
    //-------------------------------
    return true;
}

void blinkyCheckReverse_1efe (void)
{
    //-------------------------------
    // 1efe  3ab14d    ld      a,(#4db1)
    // 1f01  a7        and     a
    // 1f02  c8        ret     z
    //-------------------------------
    if (BLINKY_ORIENT_CHG_FLAG == 0)
        return;

    //-------------------------------
    // 1f03  af        xor     a
    // 1f04  32b14d    ld      (#4db1),a
    //-------------------------------
    BLINKY_ORIENT_CHG_FLAG = 0;

    //-------------------------------
    // 1f07  21ff32    ld      hl,#32ff
    // 1f0a  3a284d    ld      a,(#4d28)
    // 1f0d  ee02      xor     #02
    // 1f0f  322c4d    ld      (#4d2c),a
    //-------------------------------
    BLINKY_ORIENTATION = BLINKY_PREV_ORIENTATION ^ 2;

    //-------------------------------
    // 1f12  47        ld      b,a
    // 1f13  df        rst     #18
    // 1f14  221e4d    ld      (#4d1e),hl
    //-------------------------------
    BLINKY_VECTOR2 = MOVE_VECTOR_DATA[BLINKY_ORIENTATION];

    //-------------------------------
    // 1f17  3a024e    ld      a,(#4e02)
    // 1f1a  fe22      cp      #22
    // 1f1c  c0        ret     nz
    //-------------------------------
    if (INTRO_STATE != 0x22)
        return;

    //-------------------------------
    // 1f1d  22144d    ld      (#4d14),hl
    //-------------------------------
    BLINKY_VECTOR = BLINKY_VECTOR2;

    //-------------------------------
    // 1f20  78        ld      a,b
    // 1f21  32284d    ld      (#4d28),a
    // 1f24  c9        ret     
    //-------------------------------
    BLINKY_PREV_ORIENTATION = BLINKY_ORIENTATION;
}

void pinkyCheckReverse_1f25 (void)
{
    //-------------------------------
    // 1f25  3ab24d    ld      a,(#4db2)
    // 1f28  a7        and     a
    // 1f29  c8        ret     z
    //-------------------------------
    if (PINKY_ORIENT_CHG_FLAG == 0)
        return;

    //-------------------------------
    // 1f2a  af        xor     a
    // 1f2b  32b24d    ld      (#4db2),a
    //-------------------------------
    PINKY_ORIENT_CHG_FLAG = 0;
    pinkyReverse_1f2e ();
}

void pinkyReverse_1f2e (void)
{
    //-------------------------------
    // 1f2e  21ff32    ld      hl,#32ff
    // 1f31  3a294d    ld      a,(#4d29)
    // 1f34  ee02      xor     #02
    // 1f36  322d4d    ld      (#4d2d),a
    //-------------------------------
    PINKY_ORIENTATION = PINKY_PREV_ORIENTATION ^ 2;

    //-------------------------------
    // 1f39  47        ld      b,a
    // 1f3a  df        rst     #18
    // 1f3b  22204d    ld      (#4d20),hl
    //-------------------------------
    PINKY_VECTOR2 = MOVE_VECTOR_DATA[PINKY_ORIENTATION];

    //-------------------------------
    // 1f3e  3a024e    ld      a,(#4e02)
    // 1f41  fe22      cp      #22
    // 1f43  c0        ret     nz
    //-------------------------------
    if (INTRO_STATE != 0x22)
        return;

    //-------------------------------
    // 1f44  22164d    ld      (#4d16),hl
    //-------------------------------
    PINKY_VECTOR = PINKY_VECTOR2;

    //-------------------------------
    // 1f47  78        ld      a,b
    // 1f48  32294d    ld      (#4d29),a
    // 1f4b  c9        ret     
    //-------------------------------
    PINKY_PREV_ORIENTATION = PINKY_ORIENTATION;
}

void inkyCheckReverse_1f4c (void)
{
    //-------------------------------
    // 1f4c  3ab34d    ld      a,(#4db3)
    // 1f4f  a7        and     a
    // 1f50  c8        ret     z
    //-------------------------------
    if (INKY_ORIENT_CHG_FLAG == 0)
        return;

    //-------------------------------
    // 1f51  af        xor     a
    // 1f52  32b34d    ld      (#4db3),a
    //-------------------------------
    INKY_ORIENT_CHG_FLAG = 0;
    inkyReverse_1f55();
}

void inkyReverse_1f55 (void)
{
    //-------------------------------
    // 1f55  21ff32    ld      hl,#32ff
    // 1f58  3a2a4d    ld      a,(#4d2a)
    // 1f5b  ee02      xor     #02
    // 1f5d  322e4d    ld      (#4d2e),a
    //-------------------------------
    printf ("%s change orient from %d to %d\n", 
            __func__,
            INKY_ORIENTATION, 
            INKY_PREV_ORIENTATION ^ 2);
    INKY_ORIENTATION = INKY_PREV_ORIENTATION ^ 2;

    //-------------------------------
    // 1f60  47        ld      b,a
    // 1f61  df        rst     #18
    // 1f62  22224d    ld      (#4d22),hl
    //-------------------------------
    INKY_VECTOR2 = MOVE_VECTOR_DATA[INKY_ORIENTATION];

    //-------------------------------
    // 1f65  3a024e    ld      a,(#4e02)
    // 1f68  fe22      cp      #22
    // 1f6a  c0        ret     nz
    //-------------------------------
    if (INTRO_STATE != 0x22)
        return;

    //-------------------------------
    // 1f6b  22184d    ld      (#4d18),hl
    // 1f6e  78        ld      a,b
    // 1f6f  322a4d    ld      (#4d2a),a
    // 1f72  c9        ret     
    //-------------------------------
    INKY_PREV_ORIENTATION = INKY_ORIENTATION;
}

void clydeCheckReverse_1f73 (void)
{
    //-------------------------------
    // 1f73  3ab44d    ld      a,(#4db4)
    // 1f76  a7        and     a
    // 1f77  c8        ret     z
    //-------------------------------
    if (CLYDE_ORIENT_CHG_FLAG == 0)
        return;

    //-------------------------------
    // 1f78  af        xor     a
    // 1f79  32b44d    ld      (#4db4),a
    //-------------------------------
    CLYDE_ORIENT_CHG_FLAG = 0;
    clydeReverse_1f7c();
}

void clydeReverse_1f7c (void)
{
    //-------------------------------
    // 1f7c  21ff32    ld      hl,#32ff
    // 1f7f  3a2b4d    ld      a,(#4d2b)
    // 1f82  ee02      xor     #02
    // 1f84  322f4d    ld      (#4d2f),a
    //-------------------------------
    CLYDE_ORIENTATION = CLYDE_PREV_ORIENTATION ^ 2;

    //-------------------------------
    // 1f87  47        ld      b,a
    // 1f88  df        rst     #18
    // 1f89  22244d    ld      (#4d24),hl
    //-------------------------------
    CLYDE_VECTOR2 = MOVE_VECTOR_DATA[CLYDE_ORIENTATION];

    //-------------------------------
    // 1f8c  3a024e    ld      a,(#4e02)
    // 1f8f  fe22      cp      #22
    // 1f91  c0        ret     nz
    //-------------------------------
    if (INTRO_STATE != 0x22)
        return;

    //-------------------------------
    // 1f92  221a4d    ld      (#4d1a),hl
    // 1f95  78        ld      a,b
    // 1f96  322b4d    ld      (#4d2b),a
    // 1f99  c9        ret     
    //-------------------------------
    CLYDE_PREV_ORIENTATION = CLYDE_ORIENTATION;
}

    /*  End of ROM and checksum */

    //-------------------------------
    // 1f9a                                 00 00 00 00 00 00
    // 1fa0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 1fb0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 1fc0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 1fd0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 1fe0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 1ff0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 5d e1
    //-------------------------------
    
/*  Adds a pair of bytes together representing X and Y coords and return the
 *  result.  Used for both tiles and pixel positions.
 *
 *  ix = position
 *  iy = translation
 *
 *  returns new position
 */
XYPOS addXYOffset_2000 (XYPOS ix, XYPOS iy)
{
    //-------------------------------
    // 2000  fd7e00    ld      a,(iy+#00)
    // 2003  dd8600    add     a,(ix+#00)
    // 2006  6f        ld      l,a
    // 2007  fd7e01    ld      a,(iy+#01)
    // 200a  dd8601    add     a,(ix+#01)
    // 200d  67        ld      h,a
    // 200e  c9        ret     
    //-------------------------------
    ix.x+= iy.x;
    ix.y+= iy.y;
    return ix;
}

uint8_t getScreenCharPosOffset_200f (XYPOS offset, XYPOS pos)
{
    //-------------------------------
    // 200f  cd0020    call    #2000
    // 2012  cd6500    call    #0065
    //-------------------------------
    pos = addXYOffset_2000(offset, pos);
    uint16_t addr = getScreenOffset_0065(pos);

    //-------------------------------
    // 2015  7e        ld      a,(hl)
    // 2016  a7        and     a
    // 2017  c9        ret     
    //-------------------------------
    return SCREEN[addr];
}

XYPOS pixelToTile_2018 (XYPOS pos)
{
    //-------------------------------
    // 2018  7d        ld      a,l
    // 2019  cb3f      srl     a
    // 201b  cb3f      srl     a
    // 201d  cb3f      srl     a
    // 201f  c620      add     a,#20
    // 2021  6f        ld      l,a
    //-------------------------------
    pos.y = (pos.y >> 3) + 0x20;

    //-------------------------------
    // 2022  7c        ld      a,h
    // 2023  cb3f      srl     a
    // 2025  cb3f      srl     a
    // 2027  cb3f      srl     a
    // 2029  c61e      add     a,#1e
    // 202b  67        ld      h,a
    // 202c  c9        ret     
    //-------------------------------
    pos.x = (pos.x >> 3) + 0x1e;
    return pos;
}

/*  Convert tile x y to screen address */
uint16_t getScreenOffset_202d (XYPOS hl)
{
    printf ("%s convert %d,%d to ", __func__, hl.x, hl.y);
    //-------------------------------
    // 202d  f5        push    af
    // 202e  c5        push    bc
    // 202f  7d        ld      a,l
    // 2030  d620      sub     #20
    // 2032  6f        ld      l,a
    // 2033  7c        ld      a,h
    // 2034  d620      sub     #20
    // 2036  67        ld      h,a
    //-------------------------------
    hl.y -= 0x20;
    hl.x -= 0x20;

    //-------------------------------
    // 2037  0600      ld      b,#00
    // 2039  cb24      sla     h
    // 203b  cb24      sla     h
    // 203d  cb24      sla     h
    // 203f  cb24      sla     h
    // 2041  cb10      rl      b
    // 2043  cb24      sla     h
    // 2045  cb10      rl      b
    // 2047  4c        ld      c,h
    // 2048  2600      ld      h,#00
    // 204a  09        add     hl,bc
    // 204b  014040    ld      bc,#4040
    // 204e  09        add     hl,bc
    //-------------------------------
    /*  0x4040 is video+0x40 so just add 0x40 to get an offset into SCREEN */
    int result = (hl.x << 5) + hl.y + 0x40;
    result &= 0x3ff;
    printf ("%x\n", result);

    //-------------------------------
    // 204f  c1        pop     bc
    // 2050  f1        pop     af
    // 2051  c9        ret     
    //-------------------------------
    return result;
}

/* Gets a screen offset and converts into an offset in the colour table by
 * adding 0x400.  Since we use a separate array, we don't do the add */
uint16_t getColourOffset_2052 (XYPOS pos)
{
    //-------------------------------
    // 2052  cd6500    call    #0065
    // 2055  110004    ld      de,#0400
    // 2058  19        add     hl,de
    // 2059  c9        ret     
    //-------------------------------
    return getScreenOffset_0065(pos);
}

void checkGhostEnterTunnel_205a (XYPOS pos, uint8_t *aux)
{
    //-------------------------------
    // 205a  cd5220    call    #2052
    //-------------------------------
    uint16_t addr = getColourOffset_2052 (pos);

    //-------------------------------
    // 205d  7e        ld      a,(hl)
    // 205e  fe1b      cp      #1b
    // 2060  2004      jr      nz,#2066        ; (4)
    //-------------------------------
    if (COLOUR[addr] == 0x1b)
    {
        //-------------------------------
        // 2062  3e01      ld      a,#01
        // 2064  02        ld      (bc),a
        // 2065  c9        ret     
        //-------------------------------
        *aux = 1;
    }
    else
    {
        //-------------------------------
        // 2066  af        xor     a
        // 2067  02        ld      (bc),a
        // 2068  c9        ret     
        //-------------------------------
        *aux = 0;
    }
}

void pinkyCheckLeaveHouse_2069 (void)
{
    //-------------------------------
    // 2069  3aa14d    ld      a,(#4da1)
    // 206c  a7        and     a
    // 206d  c0        ret     nz
    //-------------------------------
    if (PINKY_SUBSTATE != SUBSTATE_IN_HOUSE)
        return;

    //-------------------------------
    // 206e  3a124e    ld      a,(#4e12)
    // 2071  a7        and     a
    // 2072  ca7e20    jp      z,#207e
    //-------------------------------
    if (P1_DIED_IN_LEVEL)
    {
        //-------------------------------
        // 2075  3a9f4d    ld      a,(#4d9f)
        // 2078  fe07      cp      #07
        // 207a  c0        ret     nz
        // 207b  c38620    jp      #2086
        //-------------------------------
        if (EATEN_PILLS_COUNT != 7)
            return;
    }
    else
    {
        //-------------------------------
        // 207e  21b84d    ld      hl,#4db8
        // 2081  3a0f4e    ld      a,(#4e0f)
        // 2084  be        cp      (hl)
        // 2085  d8        ret     c
        //-------------------------------
        printf ("%s p1c=%d lhc=%d\n", __func__,
                P1_PINKY_LEAVE_HOME_COUNTER, PINKY_LEAVE_HOME_COUNTER);
        if (P1_PINKY_LEAVE_HOME_COUNTER < PINKY_LEAVE_HOME_COUNTER)
            return;
    }
    //-------------------------------
    // 2086  3e02      ld      a,#02
    // 2088  32a14d    ld      (#4da1),a
    // 208b  c9        ret     
    //-------------------------------
    PINKY_SUBSTATE = SUBSTATE_LEAVING_HOUSE;
}

void inkyCheckLeaveHouse_208c (void)
{
    //-------------------------------
    // 208c  3aa24d    ld      a,(#4da2)
    // 208f  a7        and     a
    // 2090  c0        ret     nz
    //-------------------------------
    if (INKY_SUBSTATE != SUBSTATE_IN_HOUSE)
        return;

    //-------------------------------
    // 2091  3a124e    ld      a,(#4e12)
    // 2094  a7        and     a
    // 2095  caa120    jp      z,#20a1
    //-------------------------------
    if (P1_DIED_IN_LEVEL)
    {
        //-------------------------------
        // 2098  3a9f4d    ld      a,(#4d9f)
        // 209b  fe11      cp      #11
        // 209d  c0        ret     nz
        // 209e  c3a920    jp      #20a9
        //-------------------------------
        if (EATEN_PILLS_COUNT != 0x11)
            return;
    }
    else
    {
        //-------------------------------
        // 20a1  21b94d    ld      hl,#4db9
        // 20a4  3a104e    ld      a,(#4e10)
        // 20a7  be        cp      (hl)
        // 20a8  d8        ret     c
        //-------------------------------
        printf ("%s p1c=%d lhc=%d\n", __func__,
                P1_INKY_LEAVE_HOME_COUNTER, INKY_LEAVE_HOME_COUNTER);
        if (P1_INKY_LEAVE_HOME_COUNTER < INKY_LEAVE_HOME_COUNTER)
            return;
    }

    //-------------------------------
    // 20a9  3e03      ld      a,#03
    // 20ab  32a24d    ld      (#4da2),a
    // 20ae  c9        ret     
    //-------------------------------
    INKY_SUBSTATE = SUBSTATE_HOUSE_MOVE;
}

void clydeCheckLeaveHouse_20af (void)
{
    //-------------------------------
    // 20af  3aa34d    ld      a,(#4da3)
    // 20b2  a7        and     a
    // 20b3  c0        ret     nz
    //-------------------------------
    if (CLYDE_SUBSTATE != SUBSTATE_IN_HOUSE)
        return;

    //-------------------------------
    // 20b4  3a124e    ld      a,(#4e12)
    // 20b7  a7        and     a
    // 20b8  cac920    jp      z,#20c9
    //-------------------------------
    if (P1_DIED_IN_LEVEL)
    {
        //-------------------------------
        // 20bb  3a9f4d    ld      a,(#4d9f)
        // 20be  fe20      cp      #20
        // 20c0  c0        ret     nz
        //-------------------------------
        if (EATEN_PILLS_COUNT != 0x20)
            return;

        //-------------------------------
        // 20c1  af        xor     a
        // 20c2  32124e    ld      (#4e12),a
        // 20c5  329f4d    ld      (#4d9f),a
        // 20c8  c9        ret     
        //-------------------------------
        P1_DIED_IN_LEVEL = 
        EATEN_PILLS_COUNT = 0;
        return;
    }

    //-------------------------------
    // 20c9  21ba4d    ld      hl,#4dba
    // 20cc  3a114e    ld      a,(#4e11)
    // 20cf  be        cp      (hl)
    // 20d0  d8        ret     c
    //-------------------------------
    if (P1_CLYDE_LEAVE_HOME_COUNTER < CLYDE_LEAVE_HOME_COUNTER)
        return;

    //-------------------------------
    // 20d1  3e03      ld      a,#03
    // 20d3  32a34d    ld      (#4da3),a
    // 20d6  c9        ret     
    //-------------------------------
    CLYDE_SUBSTATE = SUBSTATE_HOUSE_MOVE;
}

void updateDifficultyTBD_20d7 (void)
{
    //-------------------------------
    // 20d7  3aa34d    ld      a,(#4da3)
    // 20da  a7        and     a
    // 20db  c8        ret     z
    //-------------------------------
    if (CLYDE_SUBSTATE == SUBSTATE_IN_HOUSE)
        return;

    //-------------------------------
    // 20dc  210e4e    ld      hl,#4e0e
    // 20df  3ab64d    ld      a,(#4db6)
    // 20e2  a7        and     a
    // 20e3  c2f420    jp      nz,#20f4
    //-------------------------------
    if (DIFF_FLAG_1 == 0)
    {
        //-------------------------------
        // 20e6  3ef4      ld      a,#f4
        // 20e8  96        sub     (hl)
        // 20e9  47        ld      b,a
        // 20ea  3abb4d    ld      a,(#4dbb)
        // 20ed  90        sub     b
        // 20ee  d8        ret     c
        //-------------------------------
        if (PILLS_REM_DIFF_1 < 0xf4 - P1_PILLS_EATEN_LEVEL)
            return;

        //-------------------------------
        // 20ef  3e01      ld      a,#01
        // 20f1  32b64d    ld      (#4db6),a
        //-------------------------------
        DIFF_FLAG_1 = 1;
    }

    //-------------------------------
    // 20f4  3ab74d    ld      a,(#4db7)
    // 20f7  a7        and     a
    // 20f8  c0        ret     nz
    //-------------------------------
    if (DIFF_FLAG_2 == 0)
        return;

    //-------------------------------
    // 20f9  3ef4      ld      a,#f4
    // 20fb  96        sub     (hl)
    // 20fc  47        ld      b,a
    // 20fd  3abc4d    ld      a,(#4dbc)
    // 2100  90        sub     b
    // 2101  d8        ret     c
    //-------------------------------
    if (PILLS_REM_DIFF_2 < 0xf4 - P1_PILLS_EATEN_LEVEL)
        return;

    //-------------------------------
    // 2102  3e01      ld      a,#01
    // 2104  32b74d    ld      (#4db7),a
    // 2107  c9        ret     
    //-------------------------------
    DIFF_FLAG_2 = 1;
}

void scene1StateMachine_2108 (void)
{
    //-------------------------------
    // 2108  3a064e    ld      a,(#4e06)
    // 210b  e7        rst     #20
    // 2100                                       1a 21 40 21
    // 2110  4b 21 0c 00 70 21 7b 21  86 21 
    //-------------------------------
    void (*func[])() = 
    {
        scene1State0_211a,
        scene1State1_2140,
        scene1State2_214b,
        nothing_000c,
        scene1State4_2170,
        scene1State5_217b,
        scene1State6_2186
    };
    tableCall_0020 (func, SCENE1_STATE);
}

void scene1State0_211a (void)
{
    //-------------------------------
    // 211a  3a3a4d    ld      a,(#4d3a)
    // 211d  d621      sub     #21
    // 211f  200f      jr      nz,#2130        ; (15)
    //-------------------------------
    if (PACMAN_TILE2.x == 0x21)
    {
        //-------------------------------
        // 2121  3c        inc     a
        // 2122  32a04d    ld      (#4da0),a
        // 2125  32b74d    ld      (#4db7),a
        //-------------------------------
        BLINKY_SUBSTATE = SUBSTATE_CHASE;
        DIFF_FLAG_2 = 1;

        //-------------------------------
        // 2128  cd0605    call    #0506
        // 212b  21064e    ld      hl,#4e06
        // 212e  34        inc     (hl)
        // 212f  c9        ret     
        //-------------------------------
        demoMazeHorizontal_0506 ();
        SCENE1_STATE++;
        return;
    }

    updateMoveVectorPacmanBlinky_2130();
}

void incScene1State_212b (void)
{
    SCENE1_STATE++;
}

void updateMoveVectorPacmanBlinky_2130 (void)
{
    //-------------------------------
    // 2130  cd0618    call    #1806
    // 2133  cd0618    call    #1806
    //-------------------------------
    pacmanUpdateMovePat_1806();
    pacmanUpdateMovePat_1806();
    updateMoveVectorBlinky_2136();
}

void updateMoveVectorBlinky_2136 (void)
{
    //-------------------------------
    // 2136  cd361b    call    #1b36
    // 2139  cd361b    call    #1b36
    // 213c  cd230e    call    #0e23
    // 213f  c9        ret     
    //-------------------------------
    blinkyUpdateMovePat_1b36();
    blinkyUpdateMovePat_1b36();
    toggleGhostAnimation_0e23();
}

void scene1State1_2140 (void)
{
    //-------------------------------
    // 2140  3a3a4d    ld      a,(#4d3a)
    // 2143  d61e      sub     #1e
    // 2145  c23021    jp      nz,#2130
    // 2148  c32b21    jp      #212b    ; tail call to inc (#4e06) and ret
    //-------------------------------
    if (PACMAN_TILE2.x != 0x1e)
        updateMoveVectorPacmanBlinky_2130();
    else
        SCENE1_STATE++;
}

void scene1State2_214b (void)
{
    //-------------------------------
    // 214b  3a324d    ld      a,(#4d32)
    // 214e  d61e      sub     #1e
    // 2150  c23621    jp      nz,#2136
    //-------------------------------
    if (BLINKY_TILE2.x != 0x1e)
    {
        updateMoveVectorBlinky_2136();
        return;
    }

    //-------------------------------
    // 2153  cd701a    call    #1a70
    // 2156  af        xor     a
    // 2157  32ac4e    ld      (#4eac),a
    // 215a  32bc4e    ld      (#4ebc),a
    //-------------------------------
    ghostsBecomeEdible_1a70();
    CH2_SOUND_EFFECT->mask = 
    CH3_SOUND_EFFECT->mask = 0;

    //-------------------------------
    // 215d  cda505    call    #05a5
    // 2160  221c4d    ld      (#4d1c),hl
    // 2163  3a3c4d    ld      a,(#4d3c)
    // 2166  32304d    ld      (#4d30),a
    //-------------------------------
    XYPOS vector = pacmanReverse_05a5();
    PACMAN_VECTOR = vector;
    PACMAN_ORIENTATION = PACMAN_DESIRED_ORIENTATION;

    //-------------------------------
    // 2169  f7        rst     #30
    // 216a  450700
    //-------------------------------
    schedISRTask (0x45, ISRTASK_INC_SCENE1_STATE, 0x00);

    //-------------------------------
    // 216d  c32b21    jp      #212b
    //-------------------------------
    SCENE1_STATE++;
}

void scene1State4_2170 (void)
{
    //-------------------------------
    // 2170  3a324d    ld      a,(#4d32)
    // 2173  d62f      sub     #2f
    // 2175  c23621    jp      nz,#2136
    //-------------------------------
    if (BLINKY_TILE2.x != 0x2f)
    {
        updateMoveVectorBlinky_2136 ();
        return;
    }
    //-------------------------------
    // 2178  c32b21    jp      #212b
    //-------------------------------
    SCENE1_STATE++;
}

void scene1State5_217b (void)
{
    //-------------------------------
    // 217b  3a324d    ld      a,(#4d32)
    // 217e  d63d      sub     #3d
    // 2180  c23021    jp      nz,#2130
    //-------------------------------
    if (BLINKY_TILE2.x != 0x3d)
    {
        updateMoveVectorPacmanBlinky_2130 ();
        return;
    }
    //-------------------------------
    // 2183  c32b21    jp      #212b
    //-------------------------------
    SCENE1_STATE++;
}

void scene1State6_2186 (void)
{
    //-------------------------------
    // 2186  cd0618    call    #1806
    // 2189  cd0618    call    #1806
    //-------------------------------
    pacmanUpdateMovePat_1806();
    pacmanUpdateMovePat_1806();

    //-------------------------------
    // 218c  3a3a4d    ld      a,(#4d3a)
    // 218f  d63d      sub     #3d
    // 2191  c0        ret     nz
    //-------------------------------
    if (PACMAN_TILE2.x != 0x3d)
        return;

    //-------------------------------
    // 2192  32064e    ld      (#4e06),a
    // 2195  f7        rst     #30
    // 2196  450000
    //-------------------------------
    SCENE1_STATE = 0;
    schedISRTask (0x45, ISRTASK_INC_LEVEL_STATE, 0x00);

    //-------------------------------
    // 2199  21044e    ld      hl,#4e04
    // 219c  34        inc     (hl)
    // 219d  c9        ret     
    //-------------------------------
    LEVEL_STATE++;
}

void scene2StateMachine_219e (void)
{
    //-------------------------------
    // 219e  3a074e    ld      a,(#4e07)
    // 21a1  fd21d241  ld      iy,#41d2
    // 21a5  e7        rst     #20
    // 21a0                    c2 21  0c 00 e1 21 f5 21 0c 22
    // 21b0  1e 22 44 22 5d 22 0c 00  6a 22 0c 00 86 22 0c 00
    // 21c0  8d 22 3e 01 32 d2 45 32  d3 45 32 f2 45 32 f3 45
    //-------------------------------
    void (*func[])(uint16_t param) = 
    {
        scene2State0_21c2,
        nothingParam_000c,
        scene2State2_21e1,
        scene2State3_21f5,
        scene2State4_220c,
        scene2State5_221e,
        scene2State6_2244,
        scene2State7_225d,
        nothingParam_000c,
        scene2State9_226a,
        nothingParam_000c,
        scene2State11_2286,
        nothingParam_000c,
        scene2State13_228d
    };
    func[SCENE2_STATE] (0x41d2);
}

void scene2State0_21c2 (uint16_t iy)
{
    //-------------------------------
    // 21c2  3e01      ld      a,#01
    // 21c4  32d245    ld      (#45d2),a
    // 21c7  32d345    ld      (#45d3),a
    // 21ca  32f245    ld      (#45f2),a
    // 21cd  32f345    ld      (#45f3),a
    //-------------------------------
    COLOUR[0x1d2] = 
    COLOUR[0x1d3] = 
    COLOUR[0x1f2] = 
    COLOUR[0x1f3] = 1;

    //-------------------------------
    // 21d0  cd0605    call    #0506
    //-------------------------------
    demoMazeHorizontal_0506();

    //-------------------------------
    // 21d3  fd360060  ld      (iy+#00),#60
    // 21d7  fd360161  ld      (iy+#01),#61
    //-------------------------------
    MEM[iy] = 0x60;
    MEM[iy+1] = 0x61;

    //-------------------------------
    // 21db  f7        rst     #30
    // 21dc  430800
    //-------------------------------
    schedISRTask (0x43, ISRTASK_INC_SCENE2_STATE, 0x00);

    //-------------------------------
    // 21df  180f      jr      #21f0           ; (15)
    //-------------------------------
    incScene2State_212b();
}

void scene2State2_21e1(uint16_t iy)
{
    //-------------------------------
    // 21e1  3a3a4d    ld      a,(#4d3a)
    // 21e4  d62c      sub     #2c
    // 21e6  c23021    jp      nz,#2130
    //-------------------------------
    if (PACMAN_TILE2.x != 0x2c)
    {
        updateMoveVectorPacmanBlinky_2130();
        return;
    }

    //-------------------------------
    // 21e9  3c        inc     a
    // 21ea  32a04d    ld      (#4da0),a
    // 21ed  32b74d    ld      (#4db7),a
    //-------------------------------
    BLINKY_SUBSTATE = 
    DIFF_FLAG_2 = 1;
    incScene2State_212b();
}

void incScene2State_212b (void)
{
    //-------------------------------
    // 21f0  21074e    ld      hl,#4e07
    // 21f3  34        inc     (hl)
    // 21f4  c9        ret     
    //-------------------------------
    SCENE2_STATE++;
}

void scene2State3_21f5 (uint16_t iy)
{
    //-------------------------------
    // 21f5  3a014d    ld      a,(#4d01)
    // 21f8  fe77      cp      #77
    // 21fa  2805      jr      z,#2201         ; (5)
    //-------------------------------
    if (BLINKY_POS.x != 0x77)
    {
        //-------------------------------
        // 21fc  fe78      cp      #78
        // 21fe  c23021    jp      nz,#2130
        //-------------------------------
        if (BLINKY_POS.x != 0x78)
        {
            updateMoveVectorPacmanBlinky_2130();
            return;
        }
    }

    //-------------------------------
    // 2201  218420    ld      hl,#2084
    // 2204  224e4d    ld      (#4d4e),hl
    // 2207  22504d    ld      (#4d50),hl
    //-------------------------------
    PACMAN_MOVE_PAT_DIFF2 = 0x20842084;

    //-------------------------------
    // 220a  18e4      jr      #21f0           ; (-28)
    //-------------------------------
    incScene2State_212b();
}

void scene2State4_220c (uint16_t iy)
{
    //-------------------------------
    // 220c  3a014d    ld      a,(#4d01)
    // 220f  d678      sub     #78
    // 2211  c23722    jp      nz,#2237
    //-------------------------------
    if (BLINKY_POS.x != 0x78)
    {
        updateMoveVector_2237();
        return;
    }

    //-------------------------------
    // 2214  fd360062  ld      (iy+#00),#62
    // 2218  fd360163  ld      (iy+#01),#63
    //-------------------------------
    MEM[iy] = 0x62;
    MEM[iy+1] = 0x63;

    //-------------------------------
    // 221c  18d2      jr      #21f0           ; (-46)
    //-------------------------------
    incScene2State_212b();
}

void scene2State5_221e (uint16_t iy)
{
    //-------------------------------
    // 221e  3a014d    ld      a,(#4d01)
    // 2221  d67b      sub     #7b
    // 2223  2012      jr      nz,#2237        ; (18)
    //-------------------------------
    if (BLINKY_POS.x != 0x7b)
    {
        updateMoveVector_2237();
        return;
    }

    //-------------------------------
    // 2225  fd360064  ld      (iy+#00),#64
    // 2229  fd360165  ld      (iy+#01),#65
    // 222d  fd362066  ld      (iy+#20),#66
    // 2231  fd362167  ld      (iy+#21),#67
    //-------------------------------
    MEM[iy] = 0x64;
    MEM[iy+1] = 0x65;
    MEM[iy+0x20] = 0x66;
    MEM[iy+0x21] = 0x67;

    //-------------------------------
    // 2235  18b9      jr      #21f0           ; (-71)
    //-------------------------------
    incScene2State_212b();
}

/*  This is very simliar to 2136 but only updates blinky's move pattern once */
void updateMoveVector_2237 (void)
{
    //-------------------------------
    // 2237  cd0618    call    #1806
    // 223a  cd0618    call    #1806
    // 223d  cd361b    call    #1b36
    // 2240  cd230e    call    #0e23
    // 2243  c9        ret     
    //-------------------------------
    pacmanUpdateMovePat_1806();
    pacmanUpdateMovePat_1806();
    blinkyUpdateMovePat_1b36();
    toggleGhostAnimation_0e23();
}

void scene2State6_2244 (uint16_t iy)
{
    //-------------------------------
    // 2244  3a014d    ld      a,(#4d01)
    // 2247  d67e      sub     #7e
    // 2249  20ec      jr      nz,#2237        ; (-20)
    //-------------------------------
    if (BLINKY_POS.x != 0x7e)
    {
        updateMoveVector_2237 ();
        return;
    }

    //-------------------------------
    // 224b  fd360068  ld      (iy+#00),#68
    // 224f  fd360169  ld      (iy+#01),#69
    // 2253  fd36206a  ld      (iy+#20),#6a
    // 2257  fd36216b  ld      (iy+#21),#6b
    // 225b  1893      jr      #21f0           ; (-109)
    //-------------------------------
    MEM[iy] = 0x68;
    MEM[iy+1] = 0x69;
    MEM[iy+0x20] = 0x6a;
    MEM[iy+0x21] = 0x6b;
    incScene2State_212b();
}

void scene2State7_225d (uint16_t iy)
{
    //-------------------------------
    // 225d  3a014d    ld      a,(#4d01)
    // 2260  d680      sub     #80
    // 2262  20d3      jr      nz,#2237        ; (-45)
    //-------------------------------
    if (BLINKY_POS.x != 0x80)
    {
        updateMoveVector_2237 ();
        return;
    }
    //-------------------------------
    // 2264  f7        rst     #30
    // 2265  4f0800
    // 2268  1886      jr      #21f0           ; (-122)
    //-------------------------------
    schedISRTask (0x4f, ISRTASK_INC_SCENE2_STATE, 0x00);
    incScene2State_212b();
}

void scene2State9_226a (uint16_t iy)
{
    //-------------------------------
    // 226a  21014d    ld      hl,#4d01
    // 226d  34        inc     (hl)
    // 226e  34        inc     (hl)
    //-------------------------------
    BLINKY_POS.x += 2;

    //-------------------------------
    // 226f  fd36006c  ld      (iy+#00),#6c
    // 2273  fd36016d  ld      (iy+#01),#6d
    // 2277  fd362040  ld      (iy+#20),#40
    // 227b  fd362140  ld      (iy+#21),#40
    //-------------------------------
    MEM[iy] = 0x6c;
    MEM[iy+1] = 0x6d;
    MEM[iy+0x20] = 0x40;
    MEM[iy+0x21] = 0x40;

    //-------------------------------
    // 227f  f7        rst     #30
    // 2280  4a0800
    //-------------------------------
    schedISRTask (0x4a, ISRTASK_INC_SCENE2_STATE, 0x00);

    //-------------------------------
    // 2283  c3f021    jp      #21f0
    //-------------------------------
    incScene2State_212b();
}

void scene2State11_2286 (uint16_t iy)
{
    //-------------------------------
    // 2286  f7        rst     #30
    // 2287  540800
    //-------------------------------
    schedISRTask (0x54, ISRTASK_INC_SCENE2_STATE, 0x00);

    //-------------------------------
    // 228a  c3f021    jp      #21f0
    //-------------------------------
    incScene2State_212b();
}

void scene2State13_228d (uint16_t iy)
{
    //-------------------------------
    // 228d  af        xor     a
    // 228e  32074e    ld      (#4e07),a
    //-------------------------------
    SCENE2_STATE = 0;

    //-------------------------------
    // 2291  21044e    ld      hl,#4e04
    // 2294  34        inc     (hl)
    // 2295  34        inc     (hl)
    // 2296  c9        ret     
    //-------------------------------
    LEVEL_STATE+= 2;
}

void scene3StateMachine_2297 (void)
{
    //-------------------------------
    // 2297  3a084e    ld      a,(#4e08)
    // 229a  e7        rst     #20
    // 229b                                    a7 22 be 22 0c
    // 22a0  00 dd 22 f5 22 fe 22 
    //-------------------------------
    void (*func[])() = 
    {
        scene3State0_22a7,
        scene3State1_22be,
        nothing_000c,
        scene3State3_22dd,
        scene3State4_22f5,
        scene3State5_22fe
    };

    tableCall_0020 (func, SCENE3_STATE);
}

void scene3State0_22a7 (void)
{
    //-------------------------------
    // 22a7  3a3a4d    ld      a,(#4d3a)
    // 22aa  d625      sub     #25
    // 22ac  c23021    jp      nz,#2130
    //-------------------------------
    if (PACMAN_TILE2.x != 0x25)
    {
        updateMoveVectorPacmanBlinky_2130();
        return;
    }

    //-------------------------------
    // 22af  3c        inc     a
    // 22b0  32a04d    ld      (#4da0),a
    // 22b3  32b74d    ld      (#4db7),a
    // 22b6  cd0605    call    #0506
    //-------------------------------
    BLINKY_SUBSTATE = DIFF_FLAG_2 = 1;
    demoMazeHorizontal_0506();
    incScene3State_22b9();
}

void incScene3State_22b9 (void)
{
    //-------------------------------
    // 22b9  21084e    ld      hl,#4e08
    // 22bc  34        inc     (hl)
    // 22bd  c9        ret     
    //-------------------------------
    SCENE3_STATE++;
}

void scene3State1_22be (void)
{
    //-------------------------------
    // 22be  3a014d    ld      a,(#4d01)
    // 22c1  feff      cp      #ff
    // 22c3  2805      jr      z,#22ca         ; (5)
    // 22c5  fefe      cp      #fe
    // 22c7  c23021    jp      nz,#2130
    //-------------------------------
    if (BLINKY_POS.x != 0xff && BLINKY_POS.x != 0xfe)
    {
        updateMoveVectorPacmanBlinky_2130 ();
        return;
    }

    //-------------------------------
    // 22ca  3c        inc     a
    // 22cb  3c        inc     a
    // 22cc  32014d    ld      (#4d01),a
    //-------------------------------
    BLINKY_POS.x += 2;

    //-------------------------------
    // 22cf  3e01      ld      a,#01
    // 22d1  32b14d    ld      (#4db1),a
    // 22d4  cdfe1e    call    #1efe
    //-------------------------------
    BLINKY_ORIENT_CHG_FLAG = 1;
    blinkyCheckReverse_1efe();

    //-------------------------------
    // 22d7  f7        rst     #30
    // 22d8  4a0900
    //-------------------------------
    schedISRTask (0x4a, ISRTASK_INC_SCENE3_STATE, 0x00);

    //-------------------------------
    // 22db  18dc      jr      #22b9           ; (-36)
    //-------------------------------
    incScene3State_22b9();
}

void scene3State3_22dd (void)
{
    //-------------------------------
    // 22dd  3a324d    ld      a,(#4d32)
    // 22e0  d62d      sub     #2d
    // 22e2  28d5      jr      z,#22b9         ; (-43)
    //-------------------------------
    if (BLINKY_TILE2.x == 0x2d)
    {
        incScene3State_22b9();
        return;
    }
    scene3FruitPos_22e4 ();
}

void scene3FruitPos_22e4 (void)
{
    //-------------------------------
    // 22e4  3a004d    ld      a,(#4d00)
    // 22e7  32d24d    ld      (#4dd2),a
    //-------------------------------
    FRUIT_POS.y = BLINKY_POS.y;

    //-------------------------------
    // 22ea  3a014d    ld      a,(#4d01)
    // 22ed  d608      sub     #08
    // 22ef  32d34d    ld      (#4dd3),a
    //-------------------------------
    FRUIT_POS.x = BLINKY_POS.x - 8;

    //-------------------------------
    // 22f2  c33021    jp      #2130
    //-------------------------------
    updateMoveVectorPacmanBlinky_2130();
}

void scene3State4_22f5 (void)
{
    //-------------------------------
    // 22f5  3a324d    ld      a,(#4d32)
    // 22f8  d61e      sub     #1e
    // 22fa  28bd      jr      z,#22b9         ; (-67)
    //-------------------------------
    if (BLINKY_TILE2.x == 0x1e)
    {
        incScene3State_22b9 ();
        return;
    }

    //-------------------------------
    // 22fc  18e6      jr      #22e4           ; (-26)
    //-------------------------------
    scene3FruitPos_22e4();
}

void scene3State5_22fe (void)
{
    //-------------------------------
    // 22fe  af        xor     a
    // 22ff  32084e    ld      (#4e08),a
    // 2302  f7        rst     #30
    // 2303  450000
    //-------------------------------
    SCENE3_STATE = 0;
    schedISRTask (0x45, ISRTASK_INC_LEVEL_STATE, 0x00);

    //-------------------------------
    // 2306  21044e    ld      hl,#4e04
    // 2309  34        inc     (hl)
    // 230a  c9        ret     
    //-------------------------------
    LEVEL_STATE++;
}

void initSelfTest_230b (void)
{
    //-------------------------------
    // 230b  210050    ld      hl,#5000
    // 230e  0608      ld      b,#08
    // 2310  af        xor     a		; a = 0
    // 2311  77        ld      (hl),a
    // 2312  2c        inc     l
    // 2313  10fc      djnz    #2311           ; (-4)
    //-------------------------------
    INTENABLE = 
    SOUNDENABLE = 
    AUXENABLE = 
    FLIPSCREEN = 
    P1START = 
    P2START = 
    COINLOCKOUT = 
    COINCOUNTER = 0;

    //-------------------------------
    // 2315  210040    ld      hl,#4000
    // 2318  0604      ld      b,#04
    //-------------------------------
    int hl = 0;
    for (int b = 0; b <= 4; b++)
    {
        //-------------------------------
        // 231a  32c050    ld      (#50c0),a	; Kick the dog
        // 231d  320750    ld      (#5007),a	; Clear coin
        //-------------------------------
        kickWatchdog();
        COINCOUNTER = 0;

        //-------------------------------
        // 2320  3e40      ld      a,#40
        // 2322  77        ld      (hl),a
        // 2323  2c        inc     l
        // 2324  20fc      jr      nz,#2322        ; (-4)
        // 2326  24        inc     h
        // 2327  10f1      djnz    #231a           ; (-15)
        //-------------------------------
        for (int l = 0; l < 0x100; l++)
            SCREEN[hl++] = 0x40;
    }

    /* Set 4400-47ff to 0x0f (color ram) */
    hl = 0;
    //-------------------------------
    // 2329  0604      ld      b,#04
    //-------------------------------
    for (int b = 0; b <= 4; b++)
    {
        //-------------------------------
        // 232b  32c050    ld      (#50c0),a	; Kick the dog
        // 232e  af        xor     a		; a = 0
        // 232f  320750    ld      (#5007),a	; Clear coin
        //-------------------------------
        kickWatchdog();
        COINCOUNTER = 0;

        //-------------------------------
        // 2332  3e0f      ld      a,#0f
        // 2334  77        ld      (hl),a
        // 2335  2c        inc     l
        // 2336  20fc      jr      nz,#2334        ; (-4)
        // 2338  24        inc     h
        // 2339  10f0      djnz    #232b           ; (-16)
        //-------------------------------
        for (int i = 0; i < 0x100; i++)
            COLOUR[hl++] = 0x0f;
    }

    //-------------------------------
    // 233b  ed5e      im      2		; interrupt mode 2
    // 233d  3efa      ld      a,#fa		
    // 233f  d300      out     (#00),a		; interrupt vector -> 0xfa
    //-------------------------------
    interruptMode (2);
    interruptVector (isr_3000);

    //-------------------------------
    // 2341  af        xor     a		; a = 0
    // 2342  320750    ld      (#5007),a	; Clear coin
    // 2345  3c        inc     a		; a = 1 
    // 2346  320050    ld      (#5000),a	; Enable interrupts
    //-------------------------------
    COINCOUNTER = 0;
    INTENABLE = 1;

    //-------------------------------
    // 2349  fb        ei			; Enable interrupts
    // 234a  76        halt			; Wait for interrupt
    //-------------------------------
    interruptEnable();
    interruptHalt();
    mainTaskLoop_234b();
}

void mainTaskLoop_234b (void)
{
    //-------------------------------
    // 234b  32c050    ld      (#50c0),a	; Kick the dog
    //-------------------------------
    kickWatchdog();

    //-------------------------------
    // 234e  31c04f    ld      sp,#4fc0	; Set stack pointer to 0x4fc0
    // 2351  af        xor     a		; a = 0
    // 2352  210050    ld      hl,#5000	
    // 2355  010808    ld      bc,#0808
    // 2358  cf        rst     #8
    //-------------------------------

    /*  Clear all write registers */
    memset (&REGSWRITE, 0, 8);

    // 	;; Clear ram
    //-------------------------------
    // 2359  21004c    ld      hl,#4c00
    // 235c  06be      ld      b,#be
    // 235e  cf        rst     #8
    // 235f  cf        rst     #8
    // 2360  cf        rst     #8
    // 2361  cf        rst     #8
    //-------------------------------
    memset (&MEM[0x4c00], 0, 0x4be);

    // 	;; Clear sound registers, sprite positions
    //-------------------------------
    // 2362  214050    ld      hl,#5040
    // 2365  0640      ld      b,#40
    // 2367  cf        rst     #8
    //-------------------------------
    memset (&SOUND[0], 0, 0x40);

    //-------------------------------
    // 2368  32c050    ld      (#50c0),a	; Kick the dog
    //-------------------------------
    kickWatchdog();

    //-------------------------------
    // 236b  cd0d24    call    #240d		; Clear color ram
    //-------------------------------
    clearColour_240d(0);

    //-------------------------------
    // 236e  32c050    ld      (#50c0),a	; Kick the dog
    //-------------------------------
    kickWatchdog();
    //-------------------------------
    // 2371  0600      ld      b,#00
    // 2373  cded23    call    #23ed
    //-------------------------------
    jumpClearScreen_23ed (0);

    //-------------------------------
    // 2376  32c050    ld      (#50c0),a	; Kick the dog 
    //-------------------------------
    kickWatchdog();

    //-------------------------------
    // 2379  21c04c    ld      hl,#4cc0
    // 237c  22804c    ld      (#4c80),hl       ; init begin ptr
    // 237f  22824c    ld      (#4c82),hl       ; init end ptr
    //-------------------------------
    TASK_LIST_BEGIN = TASK_LIST_END = 0x4cc0;

    //-------------------------------
    // 2382  3eff      ld      a,#ff
    // 2384  0640      ld      b,#40
    // 2386  cf        rst     #8       ; set the task area to 0xff
    //-------------------------------
    memset (&MEM[0x4cc0], 0xff, 0x40);

    //-------------------------------
    // 2387  3e01      ld      a,#01
    // 2389  320050    ld      (#5000),a	; enable interrupts
    // 238c  fb        ei			; enable interrupts
    //-------------------------------
    INTENABLE = 1;
    interruptEnable();

    while(1)
    {
        //-------------------------------
        // 238d  2a824c    ld      hl,(#4c82)
        // 2390  7e        ld      a,(hl)
        // 2391  a7        and     a
        // 2392  fa8d23    jp      m,#238d
        //-------------------------------

        /* Spin waiting for a task.  Since we are a single thread, add a check
         * for interrupts while we're here */
        while (MEM[TASK_LIST_BEGIN] > 0x80)
        {
            printf ("game task list empty, MEM[%x] = %x, halt\n", TASK_LIST_BEGIN, MEM[TASK_LIST_BEGIN]);
            interruptHalt();
        }

        //-------------------------------
        // 2395  36ff      ld      (hl),#ff
        // 2397  2c        inc     l
        // 2398  46        ld      b,(hl)
        // 2399  36ff      ld      (hl),#ff
        // 239b  2c        inc     l
        //-------------------------------
        int task = MEM[TASK_LIST_BEGIN];
        int param = MEM[TASK_LIST_BEGIN+1];
        MEM[TASK_LIST_BEGIN] = 0xff;
        MEM[TASK_LIST_BEGIN+1] = 0xff;
        TASK_LIST_BEGIN+= 2;
            printf ("pop game task %d next %x\n", task, TASK_LIST_BEGIN);
        //-------------------------------
        // 239c  2002      jr      nz,#23a0        ; (2)
        // 239e  2ec0      ld      l,#c0
        // 23a0  22824c    ld      (#4c82),hl
        //-------------------------------
        if ((TASK_LIST_BEGIN & 0xff) == 0)
            TASK_LIST_BEGIN = 0x4cc0;

        //-------------------------------
        // 23a3  218d23    ld      hl,#238d     ; return to start of loop
        // 23a6  e5        push    hl
        // 23a7  e7        rst     #20
        // 23a8  ed23
        // 23aa  d724 1924 4824 3d25 
        // 23b2  8b26 0d24 9826 3027
        // 23ba  6c27 a927 f127 3b28
        //       6528 8f28 b928 0d00
        // 23ca  a226 c924 352a d026
        // 23d2  8724 e823 e328 e02a
        //       5a2a 6a2b ea2b 5e2c
        // 23e2  a12b 7526 b226
        //-------------------------------
        void (*func[])(int param) = 
        {
            jumpClearScreen_23ed,       // 0
            mazeColours_24d7,           // 1 TASK_MAZE_COLOURS
            drawMaze_2419,              // 2
            drawPills_2448,             // 3
            initialisePositions_25d3,   // 4 TASK_INIT_POSITIONS
            blinkySubstateTBD_268b,     // 5
            clearColour_240d,
            resetGameState_2698,
            blinkyScatterOrChase_2730,  // 8 TASK_SCATTER_CHASE_BLINKY
            pinkyScatterOrChase_276c,
            inkyScatterOrChase_27a9,
            clydeScatterOrChase_27f1,
            homeOrRandomBlinky_283b,    // 0x0c TASK_HOME_RANDOM_BLINKY
            homeOrRandomPinky_2865,
            homeOrRandomInky_288f,
            homeOrRandomClyde_28b9,
            setupGhostTimers_000d,      // 0x10 TASK_SETUP_GHOST_TIMERS
            clearGhostState_26a2,       // 0x11
            clearPillArrays_24c9,       // 0x12
            clearPillsScreen_2a35,
            configureGame_26d0,         // 0x14 TASK_CONFIGURE_GAME
            updatePillsFromScreen_2487,
            advanceLevelState_23e8,
            pacmanOrientationDemo_28e3, // 0x17 TASK_PACMAN_ORIENT
            clearScores_2ae0,           // 0x18 TASK_CLEAR_SCORES
            addToScore_2a5a,            // 0x19 TASK_ADD_TO_SCORE
            bottomTextColourAndDisplayLives_2b6a, // 0x1A TASK_BOTTOM_COLOUR
            fruitHistoryLevelCheck_2bea,// 0x1b
            displayMsg_2c5e,            // 0x1c TASK_DISPLAY_MSG
            displayCredits_2ba1,
            resetPositions_2675,        // 0x1e
            showBonusLifeScore_26b2     // 0x1f
        };
        // tableCall_0020 (func, task, param);
        printf ("%s dispatch task %d\n", __func__, task);
        func[task] (param);
    }
}

void advanceLevelState_23e8 (int param)
{
    //-------------------------------
    // 23e8  21044e    ld      hl,#4e04
    // 23eb  34        inc     (hl)
    // 23ec  c9        ret     
    //-------------------------------
    LEVEL_STATE++;
}

void jumpClearScreen_23ed(int param)
{
    //-------------------------------
    // 23ed  78        ld      a,b
    // 23ee  e7        rst     #20
    //
    // 23ef  f323
    // 23f1  0024
    //-------------------------------
    void (*func[])() = { clearScreen_23f3, clearScreenMazeOnly_2400 };
    tableCall_0020 (func, param);
}

void clearScreen_23f3 (void)
{
    //-------------------------------
    // 23f3  3e40      ld      a,#40
    // 23f5  010400    ld      bc,#0004
    // 23f8  210040    ld      hl,#4000
    // 23fb  cf        rst     #8
    // 23fc  0d        dec     c
    // 23fd  20fc      jr      nz,#23fb        ; (-4)
    // 23ff  c9        ret     
    //-------------------------------
    memset (SCREEN, 0x40, 0x400);
    printf ("%s\n", __func__);
}

void clearScreenMazeOnly_2400 (void)
{
    //-------------------------------
    // 2400  3e40      ld      a,#40
    // 2402  214040    ld      hl,#4040
    // 2405  010480    ld      bc,#8004
    // 2408  cf        rst     #8
    // 2409  0d        dec     c
    // 240a  20fc      jr      nz,#2408        ; (-4)
    // 240c  c9        ret     
    //-------------------------------

    /*  Only clear the maze part of the screen.  Leave the 2 lines at the top
     *  and at the bottom intact */
    memset (SCREEN+0x40, 0x40, 0x380);
    printf ("%s\n", __func__);
}

void clearColour_240d (int param)
{
    //-------------------------------
    // 	;; Set Color ram to 0x00
    // 240d  af        xor     a
    // 240e  010400    ld      bc,#0004
    // 2411  210044    ld      hl,#4400
    // 2414  cf        rst     #8
    // 2415  0d        dec     c
    // 2416  20fc      jr      nz,#2414        ; (-4)
    // 2418  c9        ret     
    //-------------------------------
    memset (COLOUR, 0, 0x400);
    printf ("%s\n", __func__);
}

void drawMaze_2419 (int param)
{
    //-------------------------------
    // 2419  210040    ld      hl,#4000
    // 241c  013534    ld      bc,#3435
    //-------------------------------

    printf ("%s\n", __func__);
    uint16_t hl = 0;
    uint8_t *bc = DATA_3435;

    while (1)
    {
        //-------------------------------
        // 241f  0a        ld      a,(bc)
        // 2420  a7        and     a
        // 2421  c8        ret     z
        //-------------------------------
        uint8_t a = *bc;
        if (a == 0)
           return;

        printf ("%s ROM[%04x] -> %02X ", __func__, (int)(bc-ROM),a);
        //-------------------------------
        // 2422  fa2c24    jp      m,#242c
        //-------------------------------
        if (a < 0x80)
        {
            //-------------------------------
            // 2425  5f        ld      e,a
            // 2426  1600      ld      d,#00
            // 2428  19        add     hl,de
            // 2429  2b        dec     hl
            // 242a  03        inc     bc
            // 242b  0a        ld      a,(bc)
            //-------------------------------
            hl += a - 1;
            a = *++bc;
            printf ("M:%02x ", a);
        }
        //-------------------------------
        // 242c  23        inc     hl
        // 242d  77        ld      (hl),a
        //-------------------------------
        hl++;
        SCREEN[hl] = a;
        printf ("v[%04x] = %02x ", hl, a);

        //-------------------------------
        // 242e  f5        push    af
        // 242f  e5        push    hl
        // 2430  11e083    ld      de,#83e0
        // 2433  7d        ld      a,l
        // 2434  e61f      and     #1f
        // 2436  87        add     a,a
        // 2437  2600      ld      h,#00
        // 2439  6f        ld      l,a
        // 243a  19        add     hl,de
        // 243b  d1        pop     de
        // 243c  a7        and     a
        // 243d  ed52      sbc     hl,de
        //-------------------------------

        /*  Slightly complicated formula to work out the mirror-image location
         *  on screen.  Copy the same byte with the LSB flipped to create the
         *  mirror */
        uint16_t tmp = 0x3e0 + (hl & 0x1f) * 2 - hl;
        printf (" v[%04x] = %02x\n", tmp, a^1);

        //-------------------------------
        // 243f  f1        pop     af
        // 2440  ee01      xor     #01
        // 2442  77        ld      (hl),a
        // 2443  eb        ex      de,hl
        // 2444  03        inc     bc
        // 2445  c31f24    jp      #241f
        //-------------------------------
        SCREEN[tmp] = a ^ 1;
        bc++;
    }
}

void drawPills_2448 (int param)
{
    //-------------------------------
    // 2448  210040    ld      hl,#4000
    // 244b  dd21164e  ld      ix,#4e16
    // 244f  fd21b535  ld      iy,#35b5
    //-------------------------------
    uint8_t *hl = SCREEN;
    uint8_t *ix = P1_PILL_ARRAY;
    uint8_t *iy = DATA_35b5;
    //-------------------------------
    // 2453  1600      ld      d,#00
    // 2455  061e      ld      b,#1e
    //-------------------------------
    for (int b = 0; b < 0x1e; b++)
    {
        //-------------------------------
        // 2457  0e08      ld      c,#08
        // 2459  dd7e00    ld      a,(ix+#00)
        //-------------------------------

        for (int c = 0; c < 8; c++)
        {
            //-------------------------------
            // 245c  fd5e00    ld      e,(iy+#00)
            // 245f  19        add     hl,de
            //-------------------------------
            hl += *iy;

            //-------------------------------
            // 2460  07        rlca    
            // 2461  3002      jr      nc,#2465        ; (2)
            // 2463  3610      ld      (hl),#10
            //-------------------------------
            if (*ix & (0x80>>c))
                *hl = CHAR_PILL;

            //-------------------------------
            // 2465  fd23      inc     iy
            // 2467  0d        dec     c
            // 2468  20f2      jr      nz,#245c        ; (-14)
            //-------------------------------
            iy++;
        }
        //-------------------------------
        // 246a  dd23      inc     ix
        // 246c  05        dec     b
        // 246d  20e8      jr      nz,#2457        ; (-24)
        //-------------------------------
        ix++;
    }
    //-------------------------------
    // 246f  21344e    ld      hl,#4e34
    // 2472  116440    ld      de,#4064
    // 2475  eda0      ldi     
    // 2477  117840    ld      de,#4078
    // 247a  eda0      ldi     
    // 247c  118443    ld      de,#4384
    // 247f  eda0      ldi     
    // 2481  119843    ld      de,#4398
    // 2484  eda0      ldi     
    // 2486  c9        ret    
    //-------------------------------
    SCREEN[0x64] = P1_POWERUP_ARRAY[0];
    SCREEN[0x78] = P1_POWERUP_ARRAY[1];
    SCREEN[0x384] = P1_POWERUP_ARRAY[2];
    SCREEN[0x398] = P1_POWERUP_ARRAY[3];
}

/*  Build bytes in pill array 0x4e16-0x4e34 1 bit at a time by reading screen offsets from a ROM
 *  table and checking if the byte on the screen at that offset == 0x10 */
void updatePillsFromScreen_2487 (int param)
{
    //-------------------------------
    // 2487  210040    ld      hl,#4000
    // 248a  dd21164e  ld      ix,#4e16
    // 248e  fd21b535  ld      iy,#35b5
    // 2492  1600      ld      d,#00
    // 2494  061e      ld      b,#1e
    //-------------------------------
    int hl = 0;
    uint8_t *ix = P1_PILL_ARRAY;
    uint8_t *iy = DATA_35b5;

    for (int b = 0; b < 0x1e; b++)
    {
        //-------------------------------
        // 2496  0e08      ld      c,#08
        //-------------------------------

        for (int c = 0; c < 8; c++)
        {
            //-------------------------------
            // 2498  fd5e00    ld      e,(iy+#00)
            // 249b  19        add     hl,de
            // 249c  7e        ld      a,(hl)
            // 249d  fe10      cp      #10
            // 249f  37        scf     
            // 24a0  2801      jr      z,#24a3         ; (1)
            // 24a2  3f        ccf     
            // 24a3  ddcb0016  rl      (ix+#00)
            //-------------------------------
            hl += *iy;
            *ix <<= 1;

            if (SCREEN[hl] == 0x10)
                *ix |= 1;

            //-------------------------------
            // 24a7  fd23      inc     iy
            // 24a9  0d        dec     c
            // 24aa  20ec      jr      nz,#2498        ; (-20)
            //-------------------------------
            iy++;
        }

        //-------------------------------
        // 24ac  dd23      inc     ix
        // 24ae  05        dec     b
        // 24af  20e5      jr      nz,#2496        ; (-27)
        //-------------------------------
        ix++;
    }

    //-------------------------------
    // 24b1  216440    ld      hl,#4064
    // 24b4  11344e    ld      de,#4e34
    // 24b7  eda0      ldi     
    // 24b9  217840    ld      hl,#4078
    // 24bc  eda0      ldi     
    // 24be  218443    ld      hl,#4384
    // 24c1  eda0      ldi     
    // 24c3  219843    ld      hl,#4398
    // 24c6  eda0      ldi     
    // 24c8  c9        ret     
    //-------------------------------
    P1_POWERUP_ARRAY[0] = SCREEN[0x64];
    P1_POWERUP_ARRAY[1] = SCREEN[0x78];
    P1_POWERUP_ARRAY[2] = SCREEN[0x384];
    P1_POWERUP_ARRAY[3] = SCREEN[0x398];
}

void clearPillArrays_24c9 ()
{
    //-------------------------------
    // 24c9  21164e    ld      hl,#4e16
    // 24cc  3eff      ld      a,#ff
    // 24ce  061e      ld      b,#1e
    // 24d0  cf        rst     #8
    // 24d1  3e14      ld      a,#14
    // 24d3  0604      ld      b,#04
    // 24d5  cf        rst     #8
    // 24d6  c9        ret     
    //-------------------------------
    memset (P1_PILL_ARRAY, 0xff, 0x1e);
    memset (P1_POWERUP_ARRAY, 0x14, 0x4);
}
 
void mazeColours_24d7 (int param)
{
    //-------------------------------
    // 24d7  58        ld      e,b
    // 24d8  78        ld      a,b
    // 24d9  fe02      cp      #02
    // 24db  3e1f      ld      a,#1f
    // 24dd  2802      jr      z,#24e1         ; (2)
    // 24df  3e10      ld      a,#10
    //-------------------------------
    int a;
    if (param == 2)
        a = 0x1f;
    else
        a = 0x10;

    //-------------------------------
    // 24e1  214044    ld      hl,#4440
    // 24e4  010480    ld      bc,#8004
    // 24e7  cf        rst     #8
    // 24e8  0d        dec     c
    // 24e9  20fc      jr      nz,#24e7        ; (-4)
    //-------------------------------
    memset (COLOUR+0x40, a, 0x380);

    //-------------------------------
    // 24eb  3e0f      ld      a,#0f
    // 24ed  0640      ld      b,#40
    // 24ef  21c047    ld      hl,#47c0
    // 24f2  cf        rst     #8
    //-------------------------------
    memset (COLOUR+0x3c0, 0xf, 0x40);

    //-------------------------------
    // 24f3  7b        ld      a,e
    // 24f4  fe01      cp      #01
    // 24f6  c0        ret     nz
    //-------------------------------
    if (param != 1)
        return;

    //-------------------------------
    // 24f7  3e1a      ld      a,#1a
    // 24f9  112000    ld      de,#0020
    // 24fc  0606      ld      b,#06
    // 24fe  dd21a045  ld      ix,#45a0
    //-------------------------------

    /* Colour top and bottom of house */
    uint8_t *ix = &COLOUR[0x1a0];
    for (int b = 0; b < 6; b++)
    {
        //-------------------------------
        // 2502  dd770c    ld      (ix+#0c),a
        // 2505  dd7718    ld      (ix+#18),a
        // 2508  dd19      add     ix,de
        // 250a  10f6      djnz    #2502           ; (-10)
        //-------------------------------
        ix[0xc] = 0x1a;
        ix[0x18] = 0x1a;
        ix+= 0x20;
    }

    /*  Put colour marker 0x1b to outline the tunnel entrances */
    //-------------------------------
    // 250c  3e1b      ld      a,#1b
    // 250e  0605      ld      b,#05
    // 2510  dd214044  ld      ix,#4440
    //-------------------------------
    ix = COLOUR+0x40;
    for (int b = 0; b < 5; b++)
    {
        //-------------------------------
        // 2514  dd770e    ld      (ix+#0e),a
        // 2517  dd770f    ld      (ix+#0f),a
        // 251a  dd7710    ld      (ix+#10),a
        // 251d  dd19      add     ix,de
        // 251f  10f3      djnz    #2514           ; (-13)
        //-------------------------------
        ix[0xe] = 0x1b;
        ix[0xf] = 0x1b;
        ix[0x10] = 0x1b;
        ix += 0x20;
    }

    //-------------------------------
    // 2521  0605      ld      b,#05
    // 2523  dd212047  ld      ix,#4720
    //-------------------------------
    ix = COLOUR+0x320;
    for (int b = 0; b < 5; b++)
    {
        //-------------------------------
        // 2527  dd770e    ld      (ix+#0e),a
        // 252a  dd770f    ld      (ix+#0f),a
        // 252d  dd7710    ld      (ix+#10),a
        // 2530  dd19      add     ix,de
        // 2532  10f3      djnz    #2527           ; (-13)
        //-------------------------------
        ix[0xe] = 0x1b;
        ix[0xf] = 0x1b;
        ix[0x10] = 0x1b;
        ix += 0x20;
    }

    //-------------------------------
    // 2534  3e18      ld      a,#18
    // 2536  32ed45    ld      (#45ed),a
    // 2539  320d46    ld      (#460d),a
    // 253c  c9        ret     
    //-------------------------------

    /* Colour 0x18 is ghost house door */
    COLOUR[0x1ed] = 0x18;
    COLOUR[0x20d] = 0x18;
}

void initialisePositions_25d3 (int intro)
{
    //-------------------------------
    // 253d  dd21004c  ld      ix,#4c00
    // 2541  dd360220  ld      (ix+#02),#20
    // 2545  dd360420  ld      (ix+#04),#20
    // 2549  dd360620  ld      (ix+#06),#20
    // 254d  dd360820  ld      (ix+#08),#20
    // 2551  dd360a2c  ld      (ix+#0a),#2c
    // 2555  dd360c3f  ld      (ix+#0c),#3f
    //-------------------------------
    BLINKY_SPRITE = 0x20;
    PINKY_SPRITE = 0x20;
    INKY_SPRITE = 0x20;
    CLYDE_SPRITE = 0x20;
    PACMAN_SPRITE = 0x2c;
    FRUIT_SPRITE = 0x3f;

    //-------------------------------
    // 2559  dd360301  ld      (ix+#03),#01
    // 255d  dd360503  ld      (ix+#05),#03
    // 2561  dd360705  ld      (ix+#07),#05
    // 2565  dd360907  ld      (ix+#09),#07
    // 2569  dd360b09  ld      (ix+#0b),#09
    // 256d  dd360d00  ld      (ix+#0d),#00
    //-------------------------------
    BLINKY_COLOUR = 0x01;
    PINKY_COLOUR = 0x03;
    INKY_COLOUR = 0x05;
    CLYDE_COLOUR = 0x07;
    PACMAN_COLOUR = 0x09;
    FRUIT_COLOUR = 0x00;

    //-------------------------------
    // 2571  78        ld      a,b
    // 2572  a7        and     a
    // 2573  c20f26    jp      nz,#260f
    //-------------------------------
    if (intro == 0)
    {
        //-------------------------------
        // 2576  216480    ld      hl,#8064
        // 2579  22004d    ld      (#4d00),hl
        //-------------------------------
        BLINKY_POS.y = 0x64;
        BLINKY_POS.x = 0x80;

        //-------------------------------
        // 257c  217c80    ld      hl,#807c
        // 257f  22024d    ld      (#4d02),hl
        //-------------------------------
        PINKY_POS.y = 0x7c;
        PINKY_POS.x = 0x80;

        //-------------------------------
        // 2582  217c90    ld      hl,#907c
        // 2585  22044d    ld      (#4d04),hl
        //-------------------------------
        INKY_POS.y = 0x7c;
        INKY_POS.x = 0x90;

        //-------------------------------
        // 2588  217c70    ld      hl,#707c
        // 258b  22064d    ld      (#4d06),hl
        //-------------------------------
        CLYDE_POS.y = 0x7c;
        CLYDE_POS.x = 0x70;

        //-------------------------------
        // 258e  21c480    ld      hl,#80c4
        // 2591  22084d    ld      (#4d08),hl
        //-------------------------------
        PACMAN_POS.y = 0xc4;
        PACMAN_POS.x = 0x80;

        //-------------------------------
        // 2594  212c2e    ld      hl,#2e2c
        // 2597  220a4d    ld      (#4d0a),hl
        // 259a  22314d    ld      (#4d31),hl
        //-------------------------------
        BLINKY_TILE.y = BLINKY_TILE2.y = 0x2c;
        BLINKY_TILE.x = BLINKY_TILE2.x = 0x2e;

        //-------------------------------
        // 259d  212f2e    ld      hl,#2e2f
        // 25a0  220c4d    ld      (#4d0c),hl
        // 25a3  22334d    ld      (#4d33),hl
        //-------------------------------
        PINKY_TILE.y = PINKY_TILE2.y = 0x2f;
        PINKY_TILE.x = PINKY_TILE2.x = 0x2e;

        //-------------------------------
        // 25a6  212f30    ld      hl,#302f
        // 25a9  220e4d    ld      (#4d0e),hl
        // 25ac  22354d    ld      (#4d35),hl
        //-------------------------------
        INKY_TILE.y = INKY_TILE2.y = 0x2f;
        INKY_TILE.x = INKY_TILE2.x = 0x30;

        //-------------------------------
        // 25af  212f2c    ld      hl,#2c2f
        // 25b2  22104d    ld      (#4d10),hl
        // 25b5  22374d    ld      (#4d37),hl
        //-------------------------------
        CLYDE_TILE.y = CLYDE_TILE2.y = 0x2f;
        CLYDE_TILE.x = CLYDE_TILE2.x = 0x2c;

        //-------------------------------
        // 25b8  21382e    ld      hl,#2e38
        // 25bb  22124d    ld      (#4d12),hl
        // 25be  22394d    ld      (#4d39),hl
        //-------------------------------
        PACMAN_TILE.y = PACMAN_TILE2.y = 0x38;
        PACMAN_TILE.x = PACMAN_TILE2.x = 0x2e;

        //-------------------------------
        // 25c1  210001    ld      hl,#0100
        // 25c4  22144d    ld      (#4d14),hl
        // 25c7  221e4d    ld      (#4d1e),hl
        //-------------------------------
        BLINKY_VECTOR.y = BLINKY_VECTOR2.y = 0x00;
        BLINKY_VECTOR.x = BLINKY_VECTOR2.x = 0x01;

        //-------------------------------
        // 25ca  210100    ld      hl,#0001
        // 25cd  22164d    ld      (#4d16),hl
        // 25d0  22204d    ld      (#4d20),hl
        //-------------------------------
        PINKY_VECTOR.y = PINKY_VECTOR2.y = 0x01;
        PINKY_VECTOR.x = PINKY_VECTOR2.x = 0x00;

        //-------------------------------
        // 25d3  21ff00    ld      hl,#00ff
        // 25d6  22184d    ld      (#4d18),hl
        // 25d9  22224d    ld      (#4d22),hl
        //-------------------------------
        INKY_VECTOR.y = INKY_VECTOR2.y = 0xff;
        INKY_VECTOR.x = INKY_VECTOR2.x = 0x00;

        //-------------------------------
        // 25dc  21ff00    ld      hl,#00ff
        // 25df  221a4d    ld      (#4d1a),hl
        // 25e2  22244d    ld      (#4d24),hl
        //-------------------------------
        CLYDE_VECTOR.y = CLYDE_VECTOR2.y = 0xff;
        CLYDE_VECTOR.x = CLYDE_VECTOR2.x = 0x00;

        //-------------------------------
        // 25e5  210001    ld      hl,#0100
        // 25e8  221c4d    ld      (#4d1c),hl
        // 25eb  22264d    ld      (#4d26),hl
        //-------------------------------
        PACMAN_VECTOR.y = PACMAN_VECTOR2.y = 0x00;
        PACMAN_VECTOR.x = PACMAN_VECTOR2.x = 0x01;

        //-------------------------------
        // 25ee  210201    ld      hl,#0102
        // 25f1  22284d    ld      (#4d28),hl
        // 25f4  222c4d    ld      (#4d2c),hl
        //-------------------------------
        BLINKY_ORIENTATION = BLINKY_PREV_ORIENTATION = ORIENT_LEFT;
        PINKY_ORIENTATION = PINKY_PREV_ORIENTATION = ORIENT_DOWN;

        //-------------------------------
        // 25f7  210303    ld      hl,#0303
        // 25fa  222a4d    ld      (#4d2a),hl
        // 25fd  222e4d    ld      (#4d2e),hl
        //-------------------------------
        INKY_ORIENTATION = INKY_PREV_ORIENTATION = ORIENT_UP;
        CLYDE_ORIENTATION = CLYDE_PREV_ORIENTATION = ORIENT_UP;

        //-------------------------------
        // 2600  3e02      ld      a,#02
        // 2602  32304d    ld      (#4d30),a
        // 2605  323c4d    ld      (#4d3c),a
        //-------------------------------
        PACMAN_ORIENTATION = PACMAN_DESIRED_ORIENTATION = ORIENT_LEFT;

        //-------------------------------
        // 2608  210000    ld      hl,#0000
        // 260b  22d24d    ld      (#4dd2),hl
        // 260e  c9        ret     
        //-------------------------------
        FRUIT_POS.y = FRUIT_POS.x = 0;
    }
    else
    {
        //-------------------------------
        // 260f  219400    ld      hl,#0094
        // 2612  22004d    ld      (#4d00),hl
        // 2615  22024d    ld      (#4d02),hl
        // 2618  22044d    ld      (#4d04),hl
        // 261b  22064d    ld      (#4d06),hl
        //-------------------------------
        BLINKY_POS.y =
        PINKY_POS.y =
        INKY_POS.y =
        CLYDE_POS.y = 0x94;

        BLINKY_POS.x =
        PINKY_POS.x =
        INKY_POS.x =
        CLYDE_POS.x = 0x00;

        //-------------------------------
        // 261e  21321e    ld      hl,#1e32
        // 2621  220a4d    ld      (#4d0a),hl
        // 2624  220c4d    ld      (#4d0c),hl
        // 2627  220e4d    ld      (#4d0e),hl
        // 262a  22104d    ld      (#4d10),hl
        // 262d  22314d    ld      (#4d31),hl
        // 2630  22334d    ld      (#4d33),hl
        // 2633  22354d    ld      (#4d35),hl
        // 2636  22374d    ld      (#4d37),hl
        //-------------------------------
        BLINKY_TILE.y = BLINKY_TILE2.y =
        PINKY_TILE.y = PINKY_TILE2.y =
        INKY_TILE.y = INKY_TILE2.y =
        CLYDE_TILE.y = CLYDE_TILE2.y = 0x32;

        BLINKY_TILE.x = BLINKY_TILE2.x =
        PINKY_TILE.x = PINKY_TILE2.x =
        INKY_TILE.x = INKY_TILE2.x =
        CLYDE_TILE.x = CLYDE_TILE2.x = 0x1e;

        //-------------------------------
        // 2639  210001    ld      hl,#0100
        // 263c  22144d    ld      (#4d14),hl
        // 263f  22164d    ld      (#4d16),hl
        // 2642  22184d    ld      (#4d18),hl
        // 2645  221a4d    ld      (#4d1a),hl
        // 2648  221e4d    ld      (#4d1e),hl
        // 264b  22204d    ld      (#4d20),hl
        // 264e  22224d    ld      (#4d22),hl
        // 2651  22244d    ld      (#4d24),hl
        // 2654  221c4d    ld      (#4d1c),hl
        // 2657  22264d    ld      (#4d26),hl
        //-------------------------------
        BLINKY_VECTOR.y = BLINKY_VECTOR2.y =
        PINKY_VECTOR.y = PINKY_VECTOR2.y =
        INKY_VECTOR.y = INKY_VECTOR2.y =
        CLYDE_VECTOR.y = CLYDE_VECTOR2.y =
        PACMAN_VECTOR.y = PACMAN_VECTOR2.y = 0x00;

        BLINKY_VECTOR.x = BLINKY_VECTOR2.x =
        PINKY_VECTOR.x = PINKY_VECTOR2.x =
        INKY_VECTOR.x = INKY_VECTOR2.x =
        CLYDE_VECTOR.x = CLYDE_VECTOR2.x =
        PACMAN_VECTOR.x = PACMAN_VECTOR2.x = 0x01;

        //-------------------------------
        // 265a  21284d    ld      hl,#4d28
        // 265d  3e02      ld      a,#02
        // 265f  0609      ld      b,#09
        // 2661  cf        rst     #8
        //-------------------------------
        memset (&BLINKY_PREV_ORIENTATION, ORIENT_LEFT, 9);

        //-------------------------------
        // 2662  323c4d    ld      (#4d3c),a
        // 2665  219408    ld      hl,#0894
        // 2668  22084d    ld      (#4d08),hl
        //-------------------------------
        PACMAN_DESIRED_ORIENTATION = ORIENT_LEFT;
        PACMAN_POS.y = 0x94;
        PACMAN_POS.x = 0x08;

        //-------------------------------
        // 266b  21321f    ld      hl,#1f32
        // 266e  22124d    ld      (#4d12),hl
        // 2671  22394d    ld      (#4d39),hl
        // 2674  c9        ret     
        //-------------------------------
        PACMAN_TILE.y = PACMAN_TILE2.y = 0x32;
        PACMAN_TILE.x = PACMAN_TILE2.x = 0x1f;
        printf ("%s pacman pos set to %d,%d\n", __func__, 0x1f, 0x32);
    }
}

void resetPositions_2675 ()
{
    //-------------------------------
    // 2675  210000    ld      hl,#0000
    // 2678  22d24d    ld      (#4dd2),hl
    // 267b  22084d    ld      (#4d08),hl
    //-------------------------------
    FRUIT_POS.y = FRUIT_POS.x = 0;
    PACMAN_POS.y = PACMAN_POS.x = 0;
    setGhostPosition_267e (0, 0);
}

void setGhostPosition_267e (int y, int x)
{
    //-------------------------------
    // 267e  22004d    ld      (#4d00),hl
    // 2681  22024d    ld      (#4d02),hl
    // 2684  22044d    ld      (#4d04),hl
    // 2687  22064d    ld      (#4d06),hl
    // 268a  c9        ret     
    //-------------------------------
    BLINKY_POS.x = x;
    PINKY_POS.x = x;
    INKY_POS.x = x;
    CLYDE_POS.x = x;
    BLINKY_POS.y = y;
    PINKY_POS.y = y;
    INKY_POS.y = y;
    CLYDE_POS.y = y;
}

void blinkySubstateTBD_268b(int param)
{
    //-------------------------------
    // 268b  3e55      ld      a,#55
    // 268d  32944d    ld      (#4d94),a
    // 2690  05        dec     b
    // 2691  c8        ret     z
    //-------------------------------
    GHOST_HOUSE_MOVE_COUNT = 0x55;
    if (--param == 0)
        return;

    //-------------------------------
    // 2692  3e01      ld      a,#01
    // 2694  32a04d    ld      (#4da0),a
    // 2697  c9        ret     
    //-------------------------------
    BLINKY_SUBSTATE = SUBSTATE_CHASE;
}

void resetGameState_2698 ()
{
    //-------------------------------
    // 2698  3e01      ld      a,#01
    // 269a  32004e    ld      (#4e00),a
    // 269d  af        xor     a
    // 269e  32014e    ld      (#4e01),a
    // 26a1  c9        ret     
    //-------------------------------
    MAIN_STATE = MAIN_STATE_DEMO;
    RESET_STATE = RESET_STATE_RESET;
}

void clearGhostState_26a2 ()
{
    //-------------------------------
    // 26a2  af        xor     a
    // 26a3  11004d    ld      de,#4d00
    // 26a6  21004e    ld      hl,#4e00
    // 26a9  12        ld      (de),a
    // 26aa  13        inc     de
    // 26ab  a7        and     a            ; clear carry flag
    // 26ac  ed52      sbc     hl,de        ; check if equal
    // 26ae  c2a626    jp      nz,#26a6
    // 26b1  c9        ret     
    //-------------------------------
    for (int i = 0x4d00; i < 0x4e00; i++)
        MEM[i] = 0;
}

void showBonusLifeScore_26b2 ()
{
    //-------------------------------
    // 26b2  dd213641  ld      ix,#4136
    // 26b6  3a714e    ld      a,(#4e71)
    // 26b9  e60f      and     #0f
    // 26bb  c630      add     a,#30
    // 26bd  dd7700    ld      (ix+#00),a
    //-------------------------------
    int digit = BONUS_LIFE;
    SCREEN[0x136] = (digit & 0xf) + 0x30;

    //-------------------------------
    // 26c0  3a714e    ld      a,(#4e71)
    // 26c3  0f        rrca    
    // 26c4  0f        rrca    
    // 26c5  0f        rrca    
    // 26c6  0f        rrca    
    // 26c7  e60f      and     #0f
    // 26c9  c8        ret     z
    //-------------------------------
    digit >>= 4;
    if ((digit & 0xf) == 0)
        return;

    //-------------------------------
    // 26ca  c630      add     a,#30
    // 26cc  dd7720    ld      (ix+#20),a
    // 26cf  c9        ret     
    //-------------------------------
    SCREEN[0x156] = digit + 0x30;
}

void configureGame_26d0 (int unused)
{
    //-------------------------------
    // 26d0  3a8050    ld      a,(#5080)
    // 26d3  47        ld      b,a
    // 26d4  e603      and     #03
    // 26d6  c2de26    jp      nz,#26de
    //-------------------------------
    int a = DIP_SWITCH_COINS;
    if (a == 0)
    {
        //-------------------------------
        // 26d9  216e4e    ld      hl,#4e6e
        // 26dc  36ff      ld      (hl),#ff
        //-------------------------------
        CREDITS = 0xff;
    }
    //-------------------------------
    // 26de  4f        ld      c,a
    // 26df  1f        rra     
    // 26e0  ce00      adc     a,#00
    // 26e2  326b4e    ld      (#4e6b),a
    //-------------------------------

    /*  1 or 2 = 1 coin; 3 = 2 coin */
    COINS_PER_CREDIT = (a & 1) + (a >> 1);

    //-------------------------------
    // 26e5  e602      and     #02
    // 26e7  a9        xor     c
    // 26e8  326d4e    ld      (#4e6d),a
    //-------------------------------

    /*  0 = 0; 1 = 1; 2 = 2; 3 = 1 */
    CREDITS_PER_COIN = (COINS_PER_CREDIT & 2) ^ a;
    //-------------------------------
    // 26eb  78        ld      a,b
    // 26ec  0f        rrca    
    // 26ed  0f        rrca    
    // 26ee  e603      and     #03
    // 26f0  3c        inc     a
    // 26f1  fe04      cp      #04
    // 26f3  2001      jr      nz,#26f6        ; (1)
    // 26f5  3c        inc     a
    // 26f6  326f4e    ld      (#4e6f),a
    //-------------------------------
    LIVES_PER_GAME = DIP_SWITCH_LIVES + 1;

    if (LIVES_PER_GAME == 4) 
        LIVES_PER_GAME++;

    //-------------------------------
    // 26f9  78        ld      a,b
    // 26fa  0f        rrca    
    // 26fb  0f        rrca    
    // 26fc  0f        rrca    
    // 26fd  0f        rrca    
    // 26fe  e603      and     #03
    // 2700  212827    ld      hl,#2728
    // 2703  d7        rst     #10
    // 2704  32714e    ld      (#4e71),a
    //-------------------------------
    BONUS_LIFE = BONUS_LIFE_DATA[DIP_SWITCH_BONUS];

    //-------------------------------
    // 2707  78        ld      a,b
    // 2708  07        rlca    
    // 2709  2f        cpl     
    // 270a  e601      and     #01
    // 270c  32754e    ld      (#4e75),a
    //-------------------------------
    GHOST_NAMES_MODE = DIP_SWITCH_NAMES ^ 1;
    printf ("%s names=%d\n", __func__, GHOST_NAMES_MODE);

    //-------------------------------
    // 270f  78        ld      a,b
    // 2710  07        rlca    
    // 2711  07        rlca    
    // 2712  2f        cpl     
    // 2713  e601      and     #01
    // 2715  47        ld      b,a
    // 2716  212c27    ld      hl,#272c
    // 2719  df        rst     #18
    // 271a  22734e    ld      (#4e73),hl
    //-------------------------------
    DIFFICULTY_PTR = DIFFICULTY_DATA[DIP_SWITCH_DIFFICULTY ^ 1];

    //-------------------------------
    // 271d  3a4050    ld      a,(#5040)
    // 2720  07        rlca    
    // 2721  2f        cpl     
    // 2722  e601      and     #01
    // 2724  32724e    ld      (#4e72),a
    // 2727  c9        ret     
    //-------------------------------
    COCKTAIL_MODE = IN1_CABINET ? 0 : 1;
}

    /*  Bonus life data (in BCD: 10,000, 15,000, 20,000 or none */
    /*  Difficulty data ptr 0x0068 or 0x007d */

    //-------------------------------
    // 2728  10 15 20 ff 68 00 7d 00
    //-------------------------------

void blinkyScatterOrChase_2730 (int param)
{
    //-------------------------------
    // 2730  3ac14d    ld      a,(#4dc1)
    // 2733  cb47      bit     0,a
    // 2735  c25827    jp      nz,#2758
    //-------------------------------
    if ((NONRANDOM_MOVEMENT & 1) == 0)
    {
        //-------------------------------
        // 2738  3ab64d    ld      a,(#4db6)
        // 273b  a7        and     a
        // 273c  201a      jr      nz,#2758        ; (26)
        //-------------------------------
        if (DIFF_FLAG_1 == 0)
        {
            //-------------------------------
            // 273e  3a044e    ld      a,(#4e04)
            // 2741  fe03      cp      #03
            // 2743  2013      jr      nz,#2758        ; (19)
            //-------------------------------
            if (LEVEL_STATE == 3)
            {
                //-------------------------------
                // 2745  2a0a4d    ld      hl,(#4d0a)
                // 2748  3a2c4d    ld      a,(#4d2c)
                // 274b  111d22    ld      de,#221d
                // 274e  cd6629    call    #2966
                // 2751  221e4d    ld      (#4d1e),hl
                // 2754  322c4d    ld      (#4d2c),a
                // 2757  c9        ret     
                //-------------------------------
                XYPOS target = { 0x1d, 0x22 };
                BLINKY_VECTOR2 = 
                    findBestOrientation_2966 (BLINKY_TILE, target, &BLINKY_ORIENTATION);
                showTarget (BLINKY_TILE, target, GHOST_BLINKY);
                return;
            }
        }
    }

    //-------------------------------
    // 2758  2a0a4d    ld      hl,(#4d0a)
    // 275b  ed5b394d  ld      de,(#4d39)
    // 275f  3a2c4d    ld      a,(#4d2c)
    // 2762  cd6629    call    #2966
    // 2765  221e4d    ld      (#4d1e),hl
    // 2768  322c4d    ld      (#4d2c),a
    // 276b  c9        ret     
    //-------------------------------
    BLINKY_VECTOR2 = findBestOrientation_2966 (BLINKY_TILE, PACMAN_TILE2, &BLINKY_ORIENTATION);
    showTarget (BLINKY_TILE, PACMAN_TILE2, GHOST_BLINKY);
}

void pinkyScatterOrChase_276c (int param)
{
    //-------------------------------
    // 276c  3ac14d    ld      a,(#4dc1)
    // 276f  cb47      bit     0,a
    // 2771  c28e27    jp      nz,#278e
    //-------------------------------
    if ((NONRANDOM_MOVEMENT & 1) == 0)
    {
        //-------------------------------
        // 2774  3a044e    ld      a,(#4e04)
        // 2777  fe03      cp      #03
        // 2779  2013      jr      nz,#278e        ; (19)
        //-------------------------------

        if (LEVEL_STATE == 3)
        {
            //-------------------------------
            // 277b  2a0c4d    ld      hl,(#4d0c)
            // 277e  3a2d4d    ld      a,(#4d2d)
            // 2781  111d39    ld      de,#391d
            // 2784  cd6629    call    #2966
            // 2787  22204d    ld      (#4d20),hl
            // 278a  322d4d    ld      (#4d2d),a
            // 278d  c9        ret     
            //-------------------------------
            XYPOS target = { 0x1d, 0x39 };
            PINKY_VECTOR2 = findBestOrientation_2966 (PINKY_TILE, target, &PINKY_ORIENTATION);
            showTarget (PINKY_TILE, target, GHOST_PINKY);
            return;
        }
    }

    //-------------------------------
    // 278e  ed5b394d  ld      de,(#4d39)
    // 2792  2a1c4d    ld      hl,(#4d1c)
    // 2795  29        add     hl,hl
    // 2796  29        add     hl,hl
    // 2797  19        add     hl,de
    // 2798  eb        ex      de,hl
    //-------------------------------

    /*  Make a target tile for pinky that is 4 times pacman's current direction
     *  of travel plus pacman's current tile */
    XYPOS target;
    target.x = PACMAN_VECTOR.x * 4 + PACMAN_TILE2.x;
    target.y = PACMAN_VECTOR.y * 4 + PACMAN_TILE2.y;

    //-------------------------------
    // 2799  2a0c4d    ld      hl,(#4d0c)
    // 279c  3a2d4d    ld      a,(#4d2d)
    // 279f  cd6629    call    #2966
    // 27a2  22204d    ld      (#4d20),hl
    // 27a5  322d4d    ld      (#4d2d),a
    // 27a8  c9        ret     
    //-------------------------------
    PINKY_VECTOR2 = findBestOrientation_2966 (PINKY_TILE, target, &PINKY_ORIENTATION);
    showTarget (PINKY_TILE, target, GHOST_PINKY);
}

void inkyScatterOrChase_27a9 (int param)
{
    //-------------------------------
    // 27a9  3ac14d    ld      a,(#4dc1)
    // 27ac  cb47      bit     0,a
    // 27ae  c2cb27    jp      nz,#27cb
    //-------------------------------
    if ((NONRANDOM_MOVEMENT & 1) == 0)
    {
        //-------------------------------
        // 27b1  3a044e    ld      a,(#4e04)
        // 27b4  fe03      cp      #03
        // 27b6  2013      jr      nz,#27cb        ; (19)
        //-------------------------------
        if (LEVEL_STATE == 3)
        {
            //-------------------------------
            // 27b8  2a0e4d    ld      hl,(#4d0e)
            // 27bb  3a2e4d    ld      a,(#4d2e)
            // 27be  114020    ld      de,#2040
            // 27c1  cd6629    call    #2966
            // 27c4  22224d    ld      (#4d22),hl
            // 27c7  322e4d    ld      (#4d2e),a
            // 27ca  c9        ret     
            //-------------------------------
            XYPOS target = { 0x40, 0x20 };
            INKY_VECTOR2 = 
                findBestOrientation_2966 (INKY_TILE, target, &INKY_ORIENTATION);
            showTarget (INKY_TILE, target, GHOST_INKY);
            return;
        }
    }

    //-------------------------------
    // 27cb  ed4b0a4d  ld      bc,(#4d0a)
    // 27cf  ed5b394d  ld      de,(#4d39)
    // 27d3  2a1c4d    ld      hl,(#4d1c)
    // 27d6  29        add     hl,hl
    // 27d7  19        add     hl,de
    //-------------------------------

    /*  Inky tries to get pacman in a pincer movement with blinky so he targets
     *  a tile that is 2 tiles ahead of pacman's current vector and then twice
     *  the vector between that tile and blinky's tile */
    XYPOS target;
    target.y = PACMAN_VECTOR.y * 2 + PACMAN_TILE2.y;
    target.x = PACMAN_VECTOR.x * 2 + PACMAN_TILE2.x;

    //-------------------------------
    // 27d8  7d        ld      a,l
    // 27d9  87        add     a,a
    // 27da  91        sub     c
    // 27db  6f        ld      l,a
    //-------------------------------
    target.y = target.y * 2 - BLINKY_TILE.x;

    //-------------------------------
    // 27dc  7c        ld      a,h
    // 27dd  87        add     a,a
    // 27de  90        sub     b
    // 27df  67        ld      h,a
    //-------------------------------
    target.x = target.x * 2 - BLINKY_TILE.y;

    //-------------------------------
    // 27e0  eb        ex      de,hl
    // 27e1  2a0e4d    ld      hl,(#4d0e)
    // 27e4  3a2e4d    ld      a,(#4d2e)
    // 27e7  cd6629    call    #2966
    // 27ea  22224d    ld      (#4d22),hl
    // 27ed  322e4d    ld      (#4d2e),a
    // 27f0  c9        ret     
    //-------------------------------
    INKY_VECTOR2 = 
        findBestOrientation_2966 (INKY_TILE, target, &INKY_ORIENTATION);
    showTarget (INKY_TILE, target, GHOST_INKY);
}

void clydeScatterOrChase_27f1 (int param)
{
    //-------------------------------
    // 27f1  3ac14d    ld      a,(#4dc1)
    // 27f4  cb47      bit     0,a
    // 27f6  c21328    jp      nz,#2813
    //-------------------------------
    if ((NONRANDOM_MOVEMENT & 1) == 0)
    {
        //-------------------------------
        // 27f9  3a044e    ld      a,(#4e04)
        // 27fc  fe03      cp      #03
        // 27fe  2013      jr      nz,#2813        ; (19)
        //-------------------------------
        if (LEVEL_STATE == 3)
        {
            random:
            //-------------------------------
            // 2800  2a104d    ld      hl,(#4d10)
            // 2803  3a2f4d    ld      a,(#4d2f)
            // 2806  11403b    ld      de,#3b40
            // 2809  cd6629    call    #2966
            // 280c  22244d    ld      (#4d24),hl
            // 280f  322f4d    ld      (#4d2f),a
            // 2812  c9        ret     
            //-------------------------------

            XYPOS target = { 0x40, 0x3b };
            CLYDE_VECTOR2 = 
                findBestOrientation_2966 (CLYDE_TILE, target, &CLYDE_ORIENTATION);
            showTarget (CLYDE_TILE, target, GHOST_CLYDE);
            return;
        }
    }

    //-------------------------------
    // 2813  dd21394d  ld      ix,#4d39
    // 2817  fd21104d  ld      iy,#4d10
    // 281b  cdea29    call    #29ea
    //-------------------------------
    uint16_t dist = computeDistance_29ea (PACMAN_TILE2, CLYDE_TILE);

    //-------------------------------
    // 281e  114000    ld      de,#0040
    // 2821  a7        and     a
    // 2822  ed52      sbc     hl,de
    // 2824  da0028    jp      c,#2800
    //-------------------------------
    if (dist < 0x40)
        goto random;

    //-------------------------------
    // 2827  2a104d    ld      hl,(#4d10)
    // 282a  ed5b394d  ld      de,(#4d39)
    // 282e  3a2f4d    ld      a,(#4d2f)
    // 2831  cd6629    call    #2966
    // 2834  22244d    ld      (#4d24),hl
    // 2837  322f4d    ld      (#4d2f),a
    // 283a  c9        ret     
    //-------------------------------
    CLYDE_VECTOR2 = 
        findBestOrientation_2966 (CLYDE_TILE, PACMAN_TILE2, &CLYDE_ORIENTATION);
    showTarget (CLYDE_TILE, PACMAN_TILE2, GHOST_CLYDE);
}

/*  Send blinky home if he is dead otherwise make him move randomly (frightened) */
void homeOrRandomBlinky_283b ()
{
    //-------------------------------
    // 283b  3aac4d    ld      a,(#4dac)
    // 283e  a7        and     a
    // 283f  ca5528    jp      z,#2855
    //-------------------------------
    if (BLINKY_STATE != GHOST_STATE_ALIVE)
    {
        //-------------------------------
        // 2842  112c2e    ld      de,#2e2c
        // 2845  2a0a4d    ld      hl,(#4d0a)
        // 2848  3a2c4d    ld      a,(#4d2c)
        // 284b  cd6629    call    #2966
        // 284e  221e4d    ld      (#4d1e),hl
        // 2851  322c4d    ld      (#4d2c),a
        // 2854  c9        ret     
        //-------------------------------
        XYPOS target = { 0x2c, 0x2e };
        BLINKY_VECTOR2 = 
            findBestOrientation_2966(BLINKY_TILE, target, &BLINKY_ORIENTATION);
        showTarget (BLINKY_TILE, target, GHOST_BLINKY);
        return;
    }
    //-------------------------------
    // 2855  2a0a4d    ld      hl,(#4d0a)
    // 2858  3a2c4d    ld      a,(#4d2c)
    // 285b  cd1e29    call    #291e
    // 285e  221e4d    ld      (#4d1e),hl
    // 2861  322c4d    ld      (#4d2c),a
    // 2864  c9        ret     
    //-------------------------------
    BLINKY_VECTOR2 = 
        randomDirection_291e(BLINKY_TILE, &BLINKY_ORIENTATION);
    showTarget (BLINKY_TILE, BLINKY_TILE, GHOST_BLINKY);
}

void homeOrRandomPinky_2865 ()
{
    //-------------------------------
    // 2865  3aad4d    ld      a,(#4dad)
    // 2868  a7        and     a
    // 2869  ca7f28    jp      z,#287f
    //-------------------------------
    if (PINKY_STATE != GHOST_STATE_ALIVE)
    {
        //-------------------------------
        // 286c  112c2e    ld      de,#2e2c
        // 286f  2a0c4d    ld      hl,(#4d0c)
        // 2872  3a2d4d    ld      a,(#4d2d)
        // 2875  cd6629    call    #2966
        // 2878  22204d    ld      (#4d20),hl
        // 287b  322d4d    ld      (#4d2d),a
        // 287e  c9        ret     
        //-------------------------------
        XYPOS target = { 0x2c, 0x2e };
        PINKY_VECTOR2 = 
            findBestOrientation_2966(PINKY_TILE, target, &PINKY_ORIENTATION);
        showTarget (PINKY_TILE, target, GHOST_PINKY);
        return;
    }

    //-------------------------------
    // 287f  2a0c4d    ld      hl,(#4d0c)
    // 2882  3a2d4d    ld      a,(#4d2d)
    // 2885  cd1e29    call    #291e
    // 2888  22204d    ld      (#4d20),hl
    // 288b  322d4d    ld      (#4d2d),a
    // 288e  c9        ret     
    //-------------------------------
    PINKY_VECTOR2 = 
        randomDirection_291e(PINKY_TILE, &PINKY_ORIENTATION);
    showTarget (PINKY_TILE, PINKY_TILE, GHOST_PINKY);
}

void homeOrRandomInky_288f ()
{
    //-------------------------------
    // 288f  3aae4d    ld      a,(#4dae)
    // 2892  a7        and     a
    // 2893  caa928    jp      z,#28a9
    //-------------------------------
    if (INKY_STATE)
    {
        //-------------------------------
        // 2896  112c2e    ld      de,#2e2c
        // 2899  2a0e4d    ld      hl,(#4d0e)
        // 289c  3a2e4d    ld      a,(#4d2e)
        // 289f  cd6629    call    #2966
        // 28a2  22224d    ld      (#4d22),hl
        // 28a5  322e4d    ld      (#4d2e),a
        // 28a8  c9        ret     
        //-------------------------------
        XYPOS target = { 0x2c, 0x2e };
        INKY_VECTOR2 = 
            findBestOrientation_2966(INKY_TILE, target, &INKY_ORIENTATION);
        showTarget (INKY_TILE, target, GHOST_INKY);
        return;
    }

    //-------------------------------
    // 28a9  2a0e4d    ld      hl,(#4d0e)
    // 28ac  3a2e4d    ld      a,(#4d2e)
    // 28af  cd1e29    call    #291e
    // 28b2  22224d    ld      (#4d22),hl
    // 28b5  322e4d    ld      (#4d2e),a
    // 28b8  c9        ret     
    //-------------------------------
    INKY_VECTOR2 = 
        randomDirection_291e(INKY_TILE, &INKY_ORIENTATION);
    showTarget (INKY_TILE, INKY_TILE, GHOST_INKY);
}

void homeOrRandomClyde_28b9 ()
{
    //-------------------------------
    // 28b9  3aaf4d    ld      a,(#4daf)
    // 28bc  a7        and     a
    // 28bd  cad328    jp      z,#28d3
    //-------------------------------
    if (CLYDE_STATE)
    {
        //-------------------------------
        // 28c0  112c2e    ld      de,#2e2c
        // 28c3  2a104d    ld      hl,(#4d10)
        // 28c6  3a2f4d    ld      a,(#4d2f)
        // 28c9  cd6629    call    #2966
        // 28cc  22244d    ld      (#4d24),hl
        // 28cf  322f4d    ld      (#4d2f),a
        // 28d2  c9        ret     
        //-------------------------------
        XYPOS target = { 0x2c, 0x2e };
        CLYDE_VECTOR2 = 
            findBestOrientation_2966 (CLYDE_TILE, target, &CLYDE_ORIENTATION);
        showTarget (CLYDE_TILE, target, GHOST_CLYDE);
        return;
    }

    //-------------------------------
    // 28d3  2a104d    ld      hl,(#4d10)
    // 28d6  3a2f4d    ld      a,(#4d2f)
    // 28d9  cd1e29    call    #291e
    // 28dc  22244d    ld      (#4d24),hl
    // 28df  322f4d    ld      (#4d2f),a
    // 28e2  c9        ret     
    //-------------------------------
    CLYDE_VECTOR2 = 
        randomDirection_291e (CLYDE_TILE, &CLYDE_ORIENTATION);
    showTarget (CLYDE_TILE, CLYDE_TILE, GHOST_CLYDE);
}

/*  Choose pacman orientation in demo mode based on ghosts' locations.  If
 *  blinky is edible, then chase pinky, otherwise run away from pinky.
 */
void pacmanOrientationDemo_28e3 ()
{
    //-------------------------------
    // 28e3  3aa74d    ld      a,(#4da7)
    // 28e6  a7        and     a
    // 28e7  cafe28    jp      z,#28fe
    //-------------------------------
    if (BLINKY_EDIBLE)
    {
        //-------------------------------
        // 28ea  2a124d    ld      hl,(#4d12)
        // 28ed  ed5b0c4d  ld      de,(#4d0c)
        // 28f1  3a3c4d    ld      a,(#4d3c)
        // 28f4  cd6629    call    #2966
        // 28f7  22264d    ld      (#4d26),hl
        // 28fa  323c4d    ld      (#4d3c),a
        // 28fd  c9        ret     
        //-------------------------------
        printf ("%s chase pinky %d,%d\n", __func__, PINKY_TILE.x,PINKY_TILE.y);
        PACMAN_VECTOR2 = 
            findBestOrientation_2966 (PACMAN_TILE, PINKY_TILE, &PACMAN_DESIRED_ORIENTATION);
        showTarget (PACMAN_TILE, PINKY_TILE, 5);
        return;
    }

    //-------------------------------
    // 28fe  2a394d    ld      hl,(#4d39)       ; pacman tile2
    // 2901  ed4b0c4d  ld      bc,(#4d0c)       ; pinky tile
    // 2905  7d        ld      a,l
    // 2906  87        add     a,a
    // 2907  91        sub     c
    // 2908  6f        ld      l,a
    // 2909  7c        ld      a,h
    // 290a  87        add     a,a
    // 290b  90        sub     b
    // 290c  67        ld      h,a
    //-------------------------------

    /*  Try to get away from pinky in demo mode by creating a target tile that
     *  is in the opposite direction to pinky's vector to pacman */

    XYPOS target;
    target.y = PACMAN_TILE2.y * 2 - PINKY_TILE.y;
    target.x = PACMAN_TILE2.x * 2 - PINKY_TILE.x;

    //-------------------------------
    // 290d  eb        ex      de,hl
    // 290e  2a124d    ld      hl,(#4d12)       ; pacman_tile
    // 2911  3a3c4d    ld      a,(#4d3c)        ; pacman des orient
    // 2914  cd6629    call    #2966
    // 2917  22264d    ld      (#4d26),hl       ; pacman vector2
    // 291a  323c4d    ld      (#4d3c),a        ; pacman des orient
    // 291d  c9        ret     
    //-------------------------------
    printf ("%s run from pacman_tile2=%d,%d\n", __func__, PACMAN_TILE2.x,PACMAN_TILE.y);
    printf ("%s run from pinky=%d,%d\n", __func__, PINKY_TILE2.x,PINKY_TILE.y);
    printf ("%s run from pinky target=%d,%d\n", __func__, target.x,target.y);
    printf ("%s dx,dy target %d,%d\n", __func__,
        PACMAN_TILE.x-target.x,PACMAN_TILE.y-target.y);
    PACMAN_VECTOR2 = 
        findBestOrientation_2966 (PACMAN_TILE, target, &PACMAN_DESIRED_ORIENTATION);
    showTarget (PACMAN_TILE, target, 5);
}

XYPOS randomDirection_291e (XYPOS hl, uint8_t *orientation)
{
    //-------------------------------
    // 291e  223e4d    ld      (#4d3e),hl
    // 2921  ee02      xor     #02
    // 2923  323d4d    ld      (#4d3d),a
    //-------------------------------
    CURRENT_TILE_POS = hl;
    OPPOSITE_ORIENTATION = *orientation ^ 2;

    //-------------------------------
    // 2926  cd232a    call    #2a23
    // 2929  e603      and     #03
    // 292b  213b4d    ld      hl,#4d3b
    // 292e  77        ld      (hl),a
    //-------------------------------
    BEST_ORIENTATION_FOUND = random_2a23() & 3;

    //-------------------------------
    // 292f  87        add     a,a
    // 2930  5f        ld      e,a
    // 2931  1600      ld      d,#00
    // 2933  dd21ff32  ld      ix,#32ff
    // 2937  dd19      add     ix,de
    // 2939  fd213e4d  ld      iy,#4d3e
    //-------------------------------
    XYPOS *ix = &MOVE_VECTOR_DATA[BEST_ORIENTATION_FOUND];
    XYPOS iy = CURRENT_TILE_POS;

    while (1)
    {
        //-------------------------------
        // 293d  3a3d4d    ld      a,(#4d3d)
        // 2940  be        cp      (hl)
        // 2941  ca5729    jp      z,#2957
        //-------------------------------

        /* Prohibit ghosts from doing u-turns */
        if (OPPOSITE_ORIENTATION != BEST_ORIENTATION_FOUND)
        {
            //-------------------------------
            // 2944  cd0f20    call    #200f
            // 2947  e6c0      and     #c0
            // 2949  d6c0      sub     #c0
            // 294b  280a      jr      z,#2957         ; (10)
            //-------------------------------

            /* Ensure this direction is not into a wall */
            int a = getScreenCharPosOffset_200f(*ix, iy);
            if ((a & CHAR_MAZE_MASK) != CHAR_MAZE_MASK)
            {
                //-------------------------------
                // 294d  dd6e00    ld      l,(ix+#00)
                // 2950  dd6601    ld      h,(ix+#01)
                // 2953  3a3b4d    ld      a,(#4d3b)
                // 2956  c9        ret     
                //-------------------------------
                *orientation = BEST_ORIENTATION_FOUND;
                return *(XYPOS*)ix;
            }
        }
        //-------------------------------
        // 2957  dd23      inc     ix
        // 2959  dd23      inc     ix
        //-------------------------------
        ix++;

        //-------------------------------
        // 295b  213b4d    ld      hl,#4d3b
        // 295e  7e        ld      a,(hl)
        // 295f  3c        inc     a
        // 2960  e603      and     #03
        // 2962  77        ld      (hl),a
        // 2963  c33d29    jp      #293d
        //-------------------------------
        BEST_ORIENTATION_FOUND = (BEST_ORIENTATION_FOUND+1)&3;
    }

    /*  Unreachable but must return something */
    return hl;
}

/*  hl = current position
 *  de = target position
 *  a = current orientation
 *
 *  returns new direction vector
 */
XYPOS findBestOrientation_2966 (XYPOS hl, XYPOS de, uint8_t *a)
{
    //-------------------------------
    // 2966  223e4d    ld      (#4d3e),hl
    // 2969  ed53404d  ld      (#4d40),de
    // 296d  323b4d    ld      (#4d3b),a
    // 2970  ee02      xor     #02
    // 2972  323d4d    ld      (#4d3d),a
    //-------------------------------
    printf ("%s from %d,%d to %d,%d\n",
            __func__,
            hl.x, hl.y, de.x, de.y);
    CURRENT_TILE_POS = hl;
    DEST_TILE_POS = de;
    BEST_ORIENTATION_FOUND = *a;
    OPPOSITE_ORIENTATION = *a ^ 2;
    printf ("%s initial orient = %d opp=%d\n", __func__, *a, OPPOSITE_ORIENTATION);
    //-------------------------------
    // 2975  21ffff    ld      hl,#ffff
    // 2978  22444d    ld      (#4d44),hl
    //-------------------------------
    MIN_DISTANCE_FOUND = 0xffff;

    //-------------------------------
    // 297b  dd21ff32  ld      ix,#32ff
    // 297f  fd213e4d  ld      iy,#4d3e
    // 2983  21c74d    ld      hl,#4dc7
    // 2986  3600      ld      (hl),#00
    //-------------------------------
    TRIAL_ORIENTATION = 0;
    XYPOS *ix = MOVE_VECTOR_DATA;

    do
    {
        //-------------------------------
        // 2988  3a3d4d    ld      a,(#4d3d)
        // 298b  be        cp      (hl)
        // 298c  cac629    jp      z,#29c6
        //-------------------------------
        if (OPPOSITE_ORIENTATION != TRIAL_ORIENTATION)
        {
            //-------------------------------
            // 298f  cd0020    call    #2000
            // 2992  22424d    ld      (#4d42),hl
            // 2995  cd6500    call    #0065
            //-------------------------------
            TMP_RESULT_POS = addXYOffset_2000(*ix, CURRENT_TILE_POS);
            int offset = getScreenOffset_0065(TMP_RESULT_POS);

            //-------------------------------
            // 2998  7e        ld      a,(hl)
            // 2999  e6c0      and     #c0
            // 299b  d6c0      sub     #c0
            // 299d  2827      jr      z,#29c6         ; (39)
            //-------------------------------
            printf ("%s orient = %d scr[%04x]=%02x (mask=%02x)\n", __func__,
                    TRIAL_ORIENTATION,
                    offset,
                    SCREEN[offset], SCREEN[offset] & CHAR_MAZE_MASK
                    );

            /*  If the trial orientation points us at a maze wall then
             *  skip it and try another orientatoin */

            if ((SCREEN[offset] & CHAR_MAZE_MASK) != CHAR_MAZE_MASK)
            {
                //-------------------------------
                // 299f  dde5      push    ix
                // 29a1  fde5      push    iy
                // 29a3  dd21404d  ld      ix,#4d40
                // 29a7  fd21424d  ld      iy,#4d42
                // 29ab  cdea29    call    #29ea
                //-------------------------------
                printf ("%s computing dist\n", __func__);
                uint16_t dist = computeDistance_29ea (DEST_TILE_POS, TMP_RESULT_POS);
                printf ("%s dist = %d\n", __func__, dist);

                //-------------------------------
                // 29ae  fde1      pop     iy
                // 29b0  dde1      pop     ix
                // 29b2  eb        ex      de,hl
                // 29b3  2a444d    ld      hl,(#4d44)
                // 29b6  a7        and     a
                // 29b7  ed52      sbc     hl,de
                // 29b9  dac629    jp      c,#29c6
                //-------------------------------
                if (dist < MIN_DISTANCE_FOUND)
                {
                    //-------------------------------
                    // 29bc  ed53444d  ld      (#4d44),de
                    // 29c0  3ac74d    ld      a,(#4dc7)
                    // 29c3  323b4d    ld      (#4d3b),a
                    //-------------------------------
                    MIN_DISTANCE_FOUND = dist;
                    BEST_ORIENTATION_FOUND = TRIAL_ORIENTATION;
                }
            }
        }

        //-------------------------------
        // 29c6  dd23      inc     ix
        // 29c8  dd23      inc     ix
        //-------------------------------
        ix++;

        //-------------------------------
        // 29ca  21c74d    ld      hl,#4dc7
        // 29cd  34        inc     (hl)
        // 29ce  3e04      ld      a,#04
        // 29d0  be        cp      (hl)
        // 29d1  c28829    jp      nz,#2988
        //-------------------------------
    }
    while (++TRIAL_ORIENTATION < 4);
    
    //-------------------------------
    // 29d4  3a3b4d    ld      a,(#4d3b)
    // 29d7  87        add     a,a
    // 29d8  5f        ld      e,a
    // 29d9  1600      ld      d,#00
    // 29db  dd21ff32  ld      ix,#32ff
    // 29df  dd19      add     ix,de
    // 29e1  dd6e00    ld      l,(ix+#00)
    // 29e4  dd6601    ld      h,(ix+#01)
    // 29e7  cb3f      srl     a
    // 29e9  c9        ret     
    //-------------------------------
                printf ("%s best orient = %d\n", __func__, BEST_ORIENTATION_FOUND);
    *a = BEST_ORIENTATION_FOUND;
    return ix[BEST_ORIENTATION_FOUND];
}

/*  Computes the distance between two sets of co-ords by summing the squares of
 *  the x and y differences.
 *
 *  ix, iy = input co-ords
 *  returns hl = sum of squares
 */
uint16_t computeDistance_29ea(XYPOS ix, XYPOS iy)
{
    //-------------------------------
    // 29ea  dd7e00    ld      a,(ix+#00)
    // 29ed  fd4600    ld      b,(iy+#00)
    // 29f0  90        sub     b
    // 29f1  d2f929    jp      nc,#29f9
    //-------------------------------
    int b = ix.y - iy.y;
    if (b < 0)
    {
        //-------------------------------
        // 29f4  78        ld      a,b
        // 29f5  dd4600    ld      b,(ix+#00)
        // 29f8  90        sub     b
        //-------------------------------
        b = iy.y - ix.y;
    }
    //-------------------------------
    // 29f9  cd122a    call    #2a12
    //-------------------------------
    uint16_t hl = calcSquare_2a12(b);

    //-------------------------------
    // 29fc  e5        push    hl
    // 29fd  dd7e01    ld      a,(ix+#01)
    // 2a00  fd4601    ld      b,(iy+#01)
    // 2a03  90        sub     b
    // 2a04  d20c2a    jp      nc,#2a0c
    //-------------------------------
    b = ix.x - iy.x;
    if (b < 0)
    {
        //-------------------------------
        // 2a07  78        ld      a,b
        // 2a08  dd4601    ld      b,(ix+#01)
        // 2a0b  90        sub     b
        //-------------------------------
        b = iy.x - ix.x;
    }

    //-------------------------------
    // 2a0c  cd122a    call    #2a12
    // 2a0f  c1        pop     bc
    // 2a10  09        add     hl,bc
    // 2a11  c9        ret     
    //-------------------------------
    hl += calcSquare_2a12(b);

    return hl;
}

/*  Calculates the square of a value using bit shifts and add.  Not sure how it
 *  works - magic of some kind.
 *
 *  input : a 
 *  output : hl
 */
uint16_t calcSquare_2a12 (uint8_t a)
{
    //-------------------------------
    // 2a12  67        ld      h,a
    // 2a13  5f        ld      e,a
    // 2a14  2e00      ld      l,#00
    // 2a16  55        ld      d,l
    // 2a17  0e08      ld      c,#08
    //-------------------------------
    uint16_t hl = a << 8;
    uint16_t de = a;
    for (int c = 0; c < 8; c++)
    {
        //-------------------------------
        // 2a19  29        add     hl,hl
        // 2a1a  d21e2a    jp      nc,#2a1e
        //-------------------------------
        int carry = hl & 0x8000;
        hl <<= 1;
        if (carry)
        {
            //-------------------------------
            // 2a1d  19        add     hl,de
            //-------------------------------
            hl += de;
        }

        //-------------------------------
        // 2a1e  0d        dec     c
        // 2a1f  c2192a    jp      nz,#2a19
        //-------------------------------
    }
    //-------------------------------
    // 2a22  c9        ret     
    //-------------------------------
    return hl;
}

/*  Generates a random number by reading a byte from a randomised ROM address 
 *  NOTE : this will generate different movement unless original ROM data is used */
uint8_t random_2a23 (void)
{
    // 2a23  2ac94d    ld      hl,(#4dc9)
    uint16_t hl = RND_VAL_PTR;
    // 2a26  54        ld      d,h
    // 2a27  5d        ld      e,l
    // 2a28  29        add     hl,hl
    // 2a29  29        add     hl,hl
    // 2a2a  19        add     hl,de
    // 2a2b  23        inc     hl
    hl *= 5;
    hl++;
    // 2a2c  7c        ld      a,h
    // 2a2d  e61f      and     #1f
    // 2a2f  67        ld      h,a
    hl &= 0x1f00;
    // 2a30  7e        ld      a,(hl)
    // 2a31  22c94d    ld      (#4dc9),hl
    // 2a34  c9        ret     
    return MEM[hl];
}

void clearPillsScreen_2a35 ()
{
    //-------------------------------
    // 2a35  114040    ld      de,#4040
    // 2a38  21c043    ld      hl,#43c0
    // 2a3b  a7        and     a
    // 2a3c  ed52      sbc     hl,de
    // 2a3e  c8        ret     z
    //-------------------------------
    int de = 0x40;

    while (de != 0x3c0)
    {
        //-------------------------------
        // 2a3f  1a        ld      a,(de)
        // 2a40  fe10      cp      #10
        // 2a42  ca532a    jp      z,#2a53
        // 2a45  fe12      cp      #12
        // 2a47  ca532a    jp      z,#2a53
        // 2a4a  fe14      cp      #14
        // 2a4c  ca532a    jp      z,#2a53
        //-------------------------------
        int a = SCREEN[de];
        if (a!= 0x10 && a!=0x12 && a!=0x14)
        {
            //-------------------------------
            // 2a4f  13        inc     de
            // 2a50  c3382a    jp      #2a38
            //-------------------------------
            de++;
        }
        else
        {
            //-------------------------------
            // 2a53  3e40      ld      a,#40
            // 2a55  12        ld      (de),a
            // 2a56  13        inc     de
            // 2a57  c3382a    jp      #2a38
            //-------------------------------
            SCREEN[de++] = 0x40;
        }
    }
}

void addToScore_2a5a (int b)
{
    //-------------------------------
    // 2a5a  3a004e    ld      a,(#4e00)
    // 2a5d  fe01      cp      #01
    // 2a5f  c8        ret     z
    //-------------------------------
    if (MAIN_STATE == MAIN_STATE_DEMO)
        return;

    //-------------------------------
    // 2a60  21172b    ld      hl,#2b17
    // 2a63  df        rst     #18
    //-------------------------------

    /*  Retrieve the 2-byte value to be added to the 4-byte score */
    uint16_t add = scoreTable_2b17[b];
    printf ("%s score = %d\n", __func__, add);

    //-------------------------------
    // 2a64  eb        ex      de,hl
    // 2a65  cd0b2b    call    #2b0b
    //-------------------------------

    /*  Fetch a pointer to the player's score (P1 or P2) */
    uint8_t *score = getPlayerScorePtr_2b0b();

    //-------------------------------
    // 2a68  7b        ld      a,e
    // 2a69  86        add     a,(hl)
    // 2a6a  27        daa     
    // 2a6b  77        ld      (hl),a
    // 2a6c  23        inc     hl
    //-------------------------------

    /*  Add the LSB of the addition to the LSB of the score and adjust for BCD */
    score[0] += add & 0xff;
    int carry = bcdAdjust (&score[0]);

    //-------------------------------
    // 2a6d  7a        ld      a,d
    // 2a6e  8e        adc     a,(hl)
    // 2a6f  27        daa     
    // 2a70  77        ld      (hl),a
    // 2a71  5f        ld      e,a
    // 2a72  23        inc     hl
    //-------------------------------

    /*  Add the 2nd byte of the addition and adjust for BCD */
    score[1] += (add >> 8) + carry;
    carry = bcdAdjust (&score[1]);

    //-------------------------------
    // 2a73  3e00      ld      a,#00
    // 2a75  8e        adc     a,(hl)
    // 2a76  27        daa     
    // 2a77  77        ld      (hl),a
    //-------------------------------

    /*  Add any BCD carry to the 3rd byte of the score */
    score[2] += carry;
    carry = bcdAdjust (&score[2]);

    //-------------------------------
    // 2a78  57        ld      d,a
    // 2a79  eb        ex      de,hl
    //-------------------------------
    uint16_t hl = (score[2] << 8) + score[1];

    //-------------------------------
    // 2a7a  29        add     hl,hl
    // 2a7b  29        add     hl,hl
    // 2a7c  29        add     hl,hl
    // 2a7d  29        add     hl,hl
    //-------------------------------
    hl *= 16;

    //-------------------------------
    // 2a7e  3a714e    ld      a,(#4e71)
    // 2a81  3d        dec     a
    // 2a82  bc        cp      h
    // 2a83  dc332b    call    c,#2b33
    //-------------------------------
    if (hl>>8 > BONUS_LIFE-1)
        extraLife_2b33 (&score[2]);

    //-------------------------------
    // 2a86  cdaf2a    call    #2aaf
    // 2a89  13        inc     de
    // 2a8a  13        inc     de
    // 2a8b  13        inc     de
    //-------------------------------
    drawPlayerScore_2aaf (&score[2]);

    //-------------------------------
    // 2a8c  218a4e    ld      hl,#4e8a
    //-------------------------------

    /*  Get Ptr to MSD of high score */
    uint8_t *highScore = HIGH_SCORE;

    //-------------------------------
    // 2a8f  0603      ld      b,#03
    //-------------------------------
    for (b = 2; b >= 0; b--)
    {
        //-------------------------------
        // 2a91  1a        ld      a,(de)
        // 2a92  be        cp      (hl)
        // 2a93  d8        ret     c
        //-------------------------------
        if (score[b] < highScore[b])
            return;

        //-------------------------------
        // 2a94  2005      jr      nz,#2a9b        ; (5)
        //-------------------------------
        if (score[b] != 0)
            break;

        //-------------------------------
        // 2a96  1b        dec     de
        // 2a97  2b        dec     hl
        // 2a98  10f7      djnz    #2a91           ; (-9)
        //-------------------------------
    }
    //-------------------------------
    // 2a9a  c9        ret     
    //-------------------------------
    if (b == -1)
        return;

    //-------------------------------
    // 2a9b  cd0b2b    call    #2b0b
    //-------------------------------
    score = getPlayerScorePtr_2b0b();

    //-------------------------------
    // 2a9e  11884e    ld      de,#4e88
    //-------------------------------
    highScore = HIGH_SCORE;

    //-------------------------------
    // 2aa1  010300    ld      bc,#0003
    // 2aa4  edb0      ldir    
    //-------------------------------
    memcpy (highScore, score, 3);

    //-------------------------------
    // 2aa6  1b        dec     de
    // 2aa7  010403    ld      bc,#0304
    // 2aaa  21f243    ld      hl,#43f2
    // 2aad  180f      jr      #2abe           ; (15)
    //-------------------------------
    drawScore_2abe (0x3f2, &highScore[2], 4);
}

void drawPlayerScore_2aaf (uint8_t *score)
{
    //-------------------------------
    // 2aaf  3a094e    ld      a,(#4e09)
    // 2ab2  010403    ld      bc,#0304
    // 2ab5  21fc43    ld      hl,#43fc
    // 2ab8  a7        and     a
    // 2ab9  2803      jr      z,#2abe         ; (3)
    // 2abb  21e943    ld      hl,#43e9
    //-------------------------------
    uint16_t screenLoc;
    if (PLAYER == 0)
        screenLoc = 0x3fc;
    else
        screenLoc = 0x3e9;

    drawScore_2abe (screenLoc, score, 4);
}

/*  Draw score on screen while maintaining a flag to indicate leading blanks.
 *  As soon as a non zero digit is encountered, clear the leading blanks flag.
 *  Reg de is pointer to score, hl is screen ptr */
void drawScore_2abe (uint16_t screenLoc, uint8_t *score, int blanks)
{
    for (int b = 0; b < 3; b++)
    {
        printf ("%s drawing %02x\n", __func__, *score);
        //-------------------------------
        // 2abe  1a        ld      a,(de)
        // 2abf  0f        rrca    
        // 2ac0  0f        rrca    
        // 2ac1  0f        rrca    
        // 2ac2  0f        rrca    
        // 2ac3  cdce2a    call    #2ace
        //-------------------------------
        blanks = drawDigit_2ace (&screenLoc, *score >> 4, blanks);

        //-------------------------------
        // 2ac6  1a        ld      a,(de)
        // 2ac7  cdce2a    call    #2ace
        //-------------------------------
        blanks = drawDigit_2ace (&screenLoc, *score, blanks);

        //-------------------------------
        // 2aca  1b        dec     de
        // 2acb  10f1      djnz    #2abe           ; (-15)
        //-------------------------------
        score--;
    }
    //-------------------------------
    // 2acd  c9        ret     
    //-------------------------------
}

/*  Draw digit (discard leading 0's) */
int drawDigit_2ace(uint16_t *screenLoc, int digit, int blanks)
{
    //-------------------------------
    // 2ace  e60f      and     #0f
    // 2ad0  2804      jr      z,#2ad6         ; a = 0?
    //-------------------------------
    digit &= 0xf;
    printf ("%s dig=%x bl=%d ", __func__, digit, blanks);
    if (digit != 0)
    {
        //-------------------------------
        // 2ad2  0e00      ld      c,#00
        // 2ad4  1807      jr      #2add  
        //-------------------------------
        blanks = 0;
    }
    else
    {
        //-------------------------------
        // 2ad6  79        ld      a,c
        // 2ad7  a7        and     a
        // 2ad8  2803      jr      z,#2add         ; (3)
        //-------------------------------
        if (blanks!= 0)
        {
            //-------------------------------
            // 2ada  3e40      ld      a,#40
            // 2adc  0d        dec     c
            //-------------------------------
            digit = 0x40;
            blanks--;
        }
    }

    //-------------------------------
    // 2add  77        ld      (hl),a
    // 2ade  2b        dec     hl
    // 2adf  c9        ret     
    //-------------------------------
    printf (" store [%04x]=%02x\n", *screenLoc, digit);
    SCREEN[(*screenLoc)--] = digit;
    return blanks;
}

void clearScores_2ae0 ()
{
    //-------------------------------
    // 2ae0  0600      ld      b,#00		; Draw 'High Score' 
    // 2ae2  cd5e2c    call    #2c5e
    //-------------------------------
    displayMsg_2c5e(MSG_HIGHSCORE);

    //-------------------------------
    // 2ae5  af        xor     a
    // 2ae6  21804e    ld      hl,#4e80
    // 2ae9  0608      ld      b,#08
    // 2aeb  cf        rst     #8
    //-------------------------------
    /*  Zero both P1 and P2 scores */
    memset (P1_SCORE, 0, 8);

    //-------------------------------
    // 2aec  010403    ld      bc,#0304	; Draw Score P1
    // 2aef  11824e    ld      de,#4e82
    // 2af2  21fc43    ld      hl,#43fc	; location 
    // 2af5  cdbe2a    call    #2abe
    //-------------------------------
    drawScore_2abe (0x3fc, &P1_SCORE[2], 4);

    //-------------------------------
    // 2af8  010403    ld      bc,#0304	; Draw Score P2
    // 2afb  11864e    ld      de,#4e86
    // 2afe  21e943    ld      hl,#43e9
    // 2b01  3a704e    ld      a,(#4e70)
    // 2b04  a7        and     a
    // 2b05  20b7      jr      nz,#2abe        ; score needed
    // 2b07  0e06      ld      c,#06
    //-------------------------------
    int blanks = 4;
    if (TWO_PLAYERS)
        blanks = 6;

    //-------------------------------
    // 2b09  18b3      jr      #2abe           ; draw blanks
    //-------------------------------
    drawScore_2abe (0x3e9, &P2_SCORE[2], blanks);
}

/*  Returns a pointer to the 4-byte array containing a player's score */
uint8_t* getPlayerScorePtr_2b0b (void)
{
    //-------------------------------
    // 2b0b  3a094e    ld      a,(#4e09)
    // 2b0e  21804e    ld      hl,#4e80
    // 2b11  a7        and     a
    // 2b12  c8        ret     z
    //-------------------------------
    if (PLAYER ==0)
        return P1_SCORE;

    //-------------------------------
    // 2b13  21844e    ld      hl,#4e84
    // 2b16  c9        ret     
    //-------------------------------
    return P2_SCORE;
}

/*  Score table for edible things.  Encoded in BCD */
uint16_t scoreTable_2b17[] = 
{
    //-------------------------------
    // 2b17                       10  00 50 00 00 02 00 04 00
    // 2b20  08 00 16 00 01 00 03 00  05 00 07 00 10 00 20 00
    // 2b30  30 00 50
    //-------------------------------
    0x0010,			// dot
    0x0050,			// pellet
    0x0200,			// ghost 1
    0x0400,			// ghost 2
    0x0800,			// ghost 3
    0x1600,			// ghost 4
    0x0100,			// fruit
    0x0300,			// fruit
    0x0500,			// fruit
    0x0700,			// fruit
    0x1000,			// fruit
    0x2000,			// fruit
    0x3000,			// fruit
    0x5000		        // fruit
};

void extraLife_2b33 (uint8_t *score)
{
    //-------------------------------
    // 2b33  13        inc     de
    // 2b34  6b        ld      l,e
    // 2b35  62        ld      h,d
    // 2b36  1b        dec     de
    // 2b37  cb46      bit     0,(hl)
    // 2b39  c0        ret     nz
    //-------------------------------
    if ((score[1] & 1) != 0)
        return;

    //-------------------------------
    // 2b3a  cbc6      set     0,(hl)
    // 2b3c  219c4e    ld      hl,#4e9c
    // 2b3f  cbc6      set     0,(hl)
    //-------------------------------
    score[1] |= 1;
    CH1_SOUND_EFFECT->mask |= 1;

    //-------------------------------
    // 2b41  21144e    ld      hl,#4e14
    // 2b44  34        inc     (hl)
    // 2b45  21154e    ld      hl,#4e15
    // 2b48  34        inc     (hl)
    // 2b49  46        ld      b,(hl)
    //-------------------------------
    P1_REAL_LIVES++;
    P1_DISPLAY_LIVES++;
    displayLives_2b4a (P1_DISPLAY_LIVES);
}

uint16_t displayLives_2b4a (int lives)
{
    //-------------------------------
    // 2b4a  211a40    ld      hl,#401a
    // 2b4d  0e05      ld      c,#05
    // 2b4f  78        ld      a,b
    // 2b50  a7        and     a
    // 2b51  280e      jr      z,#2b61         ; (14)
    //-------------------------------
    int hl = 0x1a;
    int c = 5;
    if (lives != 0)
    {
        //-------------------------------
        // 2b53  fe06      cp      #06
        // 2b55  300a      jr      nc,#2b61        ; (10)
        //-------------------------------
        if (lives < 6)
        {
            for (int i = 0; i < lives; i++)
            {
                //-------------------------------
                // 2b57  3e20      ld      a,#20
                // 2b59  cd8f2b    call    #2b8f
                //-------------------------------
                drawFruit_2b8f (&SCREEN[hl], 0x20);

                //-------------------------------
                // 2b5c  2b        dec     hl
                // 2b5d  2b        dec     hl
                // 2b5e  0d        dec     c
                // 2b5f  10f6      djnz    #2b57           ; (-10)
                //-------------------------------
                hl-= 2;
                c--;
            }
        }
    }

    //-------------------------------
    // 2b61  0d        dec     c
    // 2b62  f8        ret     m
    //-------------------------------
    while (c-- >= 0)
    {
        //-------------------------------
        // 2b63  cd7e2b    call    #2b7e
        // 2b66  2b        dec     hl
        // 2b67  2b        dec     hl
        // 2b68  18f7      jr      #2b61           ; (-9)
        //-------------------------------
        drawBlankSquare_2b7e(&SCREEN[hl]);
        hl-= 2;
    }

    return hl;
}

void bottomTextColourAndDisplayLives_2b6a (int unused)
{
    //-------------------------------
    // 2b6a  3a004e    ld      a,(#4e00)
    // 2b6d  fe01      cp      #01
    // 2b6f  c8        ret     z
    //-------------------------------
    if (MAIN_STATE == MAIN_STATE_DEMO)
        return;

    //-------------------------------
    // 2b70  cdcd2b    call    #2bcd
    // 2b73  12 44 09 0a 02
    //-------------------------------
    fillScreenArea_2bcd (0x4412, 0x09, 0x0a, 0x02);

    //-------------------------------
    // 2b78  21154e    ld      hl,#4e15
    // 2b7b  46        ld      b,(hl)
    // 2b7c  18cc      jr      #2b4a           ; (-52)
    //-------------------------------
    displayLives_2b4a (P1_DISPLAY_LIVES);
}

void drawBlankSquare_2b7e(uint8_t *hl)
{
    //-------------------------------
    // 2b7e  3e40      ld      a,#40
    //-------------------------------
    drawCharSquare_2b80 (hl, 0x40);
}

/* Draw [a] to a 2x2 char square */
void drawCharSquare_2b80 (uint8_t *hl, int a)
{
    //-------------------------------
    // 2b80  e5        push    hl
    // 2b81  d5        push    de
    // 2b82  77        ld      (hl),a
    // 2b83  23        inc     hl
    // 2b84  77        ld      (hl),a
    // 2b85  111f00    ld      de,#001f
    // 2b88  19        add     hl,de
    // 2b89  77        ld      (hl),a
    // 2b8a  23        inc     hl
    // 2b8b  77        ld      (hl),a
    // 2b8c  d1        pop     de
    // 2b8d  e1        pop     hl
    // 2b8e  c9        ret     
    //-------------------------------
    hl[0] = a;
    hl[1] = a;
    hl[0x20] = a;
    hl[0x21] = a;
}

void drawFruit_2b8f (uint8_t *hl, int a)
{
    //-------------------------------
    // 2b8f  e5        push    hl
    // 2b90  d5        push    de
    // 2b91  111f00    ld      de,#001f
    // 2b94  77        ld      (hl),a
    // 2b95  3c        inc     a
    // 2b96  23        inc     hl
    // 2b97  77        ld      (hl),a
    // 2b98  3c        inc     a
    // 2b99  19        add     hl,de
    // 2b9a  77        ld      (hl),a
    // 2b9b  3c        inc     a
    // 2b9c  23        inc     hl
    // 2b9d  77        ld      (hl),a
    // 2b9e  d1        pop     de
    // 2b9f  e1        pop     hl
    // 2ba0  c9        ret     
    //-------------------------------
    printf ("%s hl = [%lx]=%02x\n", __func__, hl-SCREEN, a);
    hl[0] = a++;
    hl[1] = a++;
    hl[0x20] = a++;
    hl[0x21] = a;
}

void displayCredits_2ba1 ()
{
    //-------------------------------
    // 	;; Draw # credits/free play on bottom of screen
    // 2ba1  3a6e4e    ld      a,(#4e6e)		; Check # credits	
    // 2ba4  feff      cp      #ff
    // 2ba6  2005      jr      nz,#2bad        ; (5)
    //-------------------------------
    if (CREDITS == 0xff)
    {
        //-------------------------------
        // 2ba8  0602      ld      b,#02
        // 2baa  c35e2c    jp      #2c5e
        //-------------------------------
        displayMsg_2c5e (MSG_FREEPLAY);
        return;
    }
    //-------------------------------
    // 2bad  0601      ld      b,#01
    // 2baf  cd5e2c    call    #2c5e
    // 2bb2  3a6e4e    ld      a,(#4e6e)
    // 2bb5  e6f0      and     #f0
    // 2bb7  2809      jr      z,#2bc2         ; (9)
    //-------------------------------
    displayMsg_2c5e (MSG_CREDIT);
    int digit = CREDITS & 0xf0;
    if (digit != 0)
    {
        //-------------------------------
        // 2bb9  0f        rrca    
        // 2bba  0f        rrca    
        // 2bbb  0f        rrca    
        // 2bbc  0f        rrca    
        // 2bbd  c630      add     a,#30
        // 2bbf  323440    ld      (#4034),a
        //-------------------------------
        SCREEN[0x34] = (digit >> 4) + 0x30;
    }

    //-------------------------------
    // 2bc2  3a6e4e    ld      a,(#4e6e)
    // 2bc5  e60f      and     #0f
    // 2bc7  c630      add     a,#30
    // 2bc9  323340    ld      (#4033),a
    // 2bcc  c9        ret     
    //-------------------------------
    digit = CREDITS & 0x0f;
    SCREEN[0x33] = digit + 0x30;
}

void fillScreenArea_2bcd (int addr, int ch, int cols, int rows)
{
    printf ("%s %04x %02x @ %dx%d\n", __func__, addr, ch, cols, rows);
    //-------------------------------
    // fetch e,d,c,b,a from stack
    // de = screen location
    // a = rows
    // b = cols
    // c = char

    // 2bcd  e1        pop     hl
    // 2bce  5e        ld      e,(hl)   ; fetch low byte of screen addr
    // 2bcf  23        inc     hl
    // 2bd0  56        ld      d,(hl)   ; fetch high byte of screen addr
    // 2bd1  23        inc     hl
    // 2bd2  4e        ld      c,(hl)   ; fetch fill character
    // 2bd3  23        inc     hl
    // 2bd4  46        ld      b,(hl)   ; fetch col count
    // 2bd5  23        inc     hl
    // 2bd6  7e        ld      a,(hl)   ; fetch row count
    // 2bd7  23        inc     hl

    // 2bd8  e5        push    hl
    // 2bd9  eb        ex      de,hl
    // 2bda  112000    ld      de,#0020 ; chars per row
    //-------------------------------

    while (rows--)
    {
        //-------------------------------
        // 2bdd  e5        push    hl
        // 2bde  c5        push    bc
        //-------------------------------

        for (int x = 0; x < cols; x++)
        {
            //-------------------------------
            // 2bdf  71        ld      (hl),c
            // 2be0  23        inc     hl
            // 2be1  10fc      djnz    #2bdf           ; (-4)
            //-------------------------------
            MEM[addr + x] = ch;
            printf ("%s screen-addr [%04x]=%02x\n", __func__, addr+x-0x4400, ch);
        }

        //-------------------------------
        // 2be3  c1        pop     bc
        // 2be4  e1        pop     hl
        // 2be5  19        add     hl,de
        // 2be6  3d        dec     a
        // 2be7  20f4      jr      nz,#2bdd        ; (-12)
        //-------------------------------
        addr += 0x20;
    }

    //-------------------------------
    // 2be9  c9        ret     
    //-------------------------------
}

void fruitHistoryLevelCheck_2bea (int param)
{
    //-------------------------------
    // 2bea  3a004e    ld      a,(#4e00)
    // 2bed  fe01      cp      #01
    // 2bef  c8        ret     z
    //-------------------------------
    if (MAIN_STATE == MAIN_STATE_DEMO)
        return;

    //-------------------------------
    // 2bf0  3a134e    ld      a,(#4e13)	; Load level # 
    // 2bf3  3c        inc     a		; Increment  
    // 2bf4  fe08      cp      #08		; >= 8? 
    // 2bf6  d22e2c    jp      nc,#2c2e	; No -> 0x2c2e 
    //-------------------------------
    int level = P1_LEVEL;

    if (level >= 8)
    {
        fruitHistoryLevelHigherThan8_2c2e(level);
        return;
    }

    //-------------------------------
    // 2bf9  11083b    ld      de,#3b08	; Fruit table
    // 2bfc  47        ld      b,a
    //-------------------------------
    displayFruitHistory_2bfd (FRUIT_TABLE, level);
}

void displayFruitHistory_2bfd (uint8_t *table, int level)
{
    //-------------------------------
    // 2bfd  0e07      ld      c,#07		; Fruit count	 
    // 2bff  210440    ld      hl,#4004	; Starting loc 
    //-------------------------------
    int c = 7;
    uint16_t hl = 0x4; // offset into video
    for (int i = 0; i < level; i++)
    {
        //-------------------------------
        // 2c02  1a        ld      a,(de)		;  
        // 2c03  cd8f2b    call    #2b8f		; Draw fruit 
        //-------------------------------
        drawFruit_2b8f (&SCREEN[hl], table[0]);

        //-------------------------------
        // 2c06  3e04      ld      a,#04		; v
        // 2c08  84        add     a,h		; v
        // 2c09  67        ld      h,a		; v
        // 2c0a  13        inc     de		; v
        // 2c0b  1a        ld      a,(de)		; v
        // 2c0c  cd802b    call    #2b80		; Erase next fruit 
        //-------------------------------

        /*  No need to modify hl as we just pass colour hl+= 0x400;*/
        drawCharSquare_2b80 (&COLOUR[hl], table[1]);

        //-------------------------------
        // 2c0f  3efc      ld      a,#fc		; 
        // 2c11  84        add     a,h		; 
        // 2c12  67        ld      h,a		; 
        // 2c13  13        inc     de
        // 2c14  23        inc     hl
        // 2c15  23        inc     hl
        //-------------------------------
        table += 2;
        hl += 2;

        //-------------------------------
        // 2c16  0d        dec     c
        // 2c17  10e9      djnz    #2c02           ; (-23)
        //-------------------------------
        c--;
    }

    //-------------------------------
    // 2c19  0d        dec     c
    // 2c1a  f8        ret     m
    //-------------------------------
    while (c-- > 0)
    {
        //-------------------------------
        // 2c1b  cd7e2b    call    #2b7e
        //-------------------------------
        drawBlankSquare_2b7e(&SCREEN[hl]);

        //-------------------------------
        // 2c1e  3e04      ld      a,#04
        // 2c20  84        add     a,h
        // 2c21  67        ld      h,a
        // 2c22  af        xor     a
        // 2c23  cd802b    call    #2b80
        //-------------------------------
        drawCharSquare_2b80 (&COLOUR[hl], 0);

        //-------------------------------
        // 2c26  3efc      ld      a,#fc
        // 2c28  84        add     a,h
        // 2c29  67        ld      h,a
        // 2c2a  23        inc     hl
        // 2c2b  23        inc     hl
        // 2c2c  18eb      jr      #2c19           ; (-21)
        //-------------------------------
        hl += 2;
    }
}

void fruitHistoryLevelHigherThan8_2c2e (int level)
{
    //-------------------------------
    // 2c2e  fe13      cp      #13
    // 2c30  3802      jr      c,#2c34         ; (2)
    // 2c32  3e13      ld      a,#13
    //-------------------------------
    if (level >= 0x13)
        level = 0x13;

    //-------------------------------
    // 2c34  d607      sub     #07
    // 2c36  4f        ld      c,a
    // 2c37  0600      ld      b,#00
    // 2c39  21083b    ld      hl,#3b08
    // 2c3c  09        add     hl,bc
    // 2c3d  09        add     hl,bc
    // 2c3e  eb        ex      de,hl
    // 2c3f  0607      ld      b,#07
    // 2c41  c3fd2b    jp      #2bfd
    //-------------------------------
    displayFruitHistory_2bfd (&FRUIT_TABLE[(level - 7) * 2], 7);
}

void func_2c44(uint8_t a)
{
    //-------------------------------
    // 2c44  47        ld      b,a
    // 2c45  e60f      and     #0f
    // 2c47  c600      add     a,#00
    // 2c49  27        daa     
    //-------------------------------
    uint8_t b = a & 0xf;
    bcdAdjust (&b);
    //-------------------------------
    // 2c4a  4f        ld      c,a
    // 2c4b  78        ld      a,b
    // 2c4c  e6f0      and     #f0
    // 2c4e  280b      jr      z,#2c5b         ; (11)
    //-------------------------------
    if ((a & 0xf0) != 0)
    {
            //-------------------------------
        // 2c50  0f        rrca    
        // 2c51  0f        rrca    
        // 2c52  0f        rrca    
        // 2c53  0f        rrca    
        // 2c54  47        ld      b,a
        // 2c55  af        xor     a
        //-------------------------------
        a >>= 4;
        for (int b = 0; b < a; b++)
        {
            //-------------------------------
            // 2c56  c616      add     a,#16
            // 2c58  27        daa     
            // 2c59  10fb      djnz    #2c56           ; (-5)
            //-------------------------------
            a+= 0x16;
            bcdAdjust(&a);
        }
    }
    //-------------------------------
    // 2c5b  81        add     a,c
    // 2c5c  27        daa     
    // 2c5d  c9        ret     
    //-------------------------------
    bcdAdjust(&a);
}

/* draw messages from a table
 * coordinates and message data
 *  b = message # in table
 */
void displayMsg_2c5e (int b)
{
    //-------------------------------
    // 2c5e  21a536    ld      hl,#36a5
    // 2c61  df        rst     #18		; (hl+2*b) -> hl 
    // 2c62  5e        ld      e,(hl)
    // 2c63  23        inc     hl
    // 2c64  56        ld      d,(hl)
    //-------------------------------
    uint16_t hl = tableLookup_0018 (DATA_MSG_TABLE, b);
    int16_t de = *(int16_t*)(&ROM[hl]);
    uint8_t *chr = &ROM[hl+1];
    printf ("%s msg = %02x -> %x -> %x \n", __func__, b, hl, de);

    /* TODO if the msg starts with 0x4d, 0x83, then what prevents the video
     * address from being c74d ???? */
    de &= 0x7fff;

    //-------------------------------
    // 2c65  dd210044  ld      ix,#4400	; Start of Color RAM
    // 2c69  dd19      add     ix,de	; Calculate starting pos in CRAM
    //-------------------------------
    uint8_t *colour = &COLOUR[de];

    //-------------------------------
    // 2c6b  dde5      push    ix		; 4400 + (hl) -> stack 
    // 2c6d  1100fc    ld      de,#fc00	
    // 2c70  dd19      add     ix,de	; Calculate starting pos in VRAM
    // 2c72  11ffff    ld      de,#ffff	; Offset for normal text  
    //-------------------------------
    uint8_t *video = &SCREEN[de];
    de = -1;

    //-------------------------------
    // 2c75  cb7e      bit     7,(hl)  
    // 2c77  2003      jr      nz,#2c7c     ; (3) 
    //-------------------------------
    if ((*chr & 0x80) == 0)
    {
        //-------------------------------
        // 2c79  11e0ff    ld      de,#ffe0	; Offset for top + bottom 2 lines 
        //-------------------------------
        de = -0x20;
    }

    //-------------------------------
    // 2c7c  23        inc     hl
    // 2c7d  78        ld      a,b		; b -> a
    // 2c7e  010000    ld      bc,#0000	; 0 -> b,c 
    // 2c81  87        add     a,a		; 2*a -> a 
    // 2c82  3828      jr      c,#2cac         ; Special Draw routine for entries 80+
    //-------------------------------
    chr++;
    uint16_t bc = 0;
    if (b < 0x80)
    {
        //-------------------------------
        // 2c84  7e        ld      a,(hl)		; Read next char 
        // 2c85  fe2f      cp      #2f		; #2f = end of text
        // 2c87  2809      jr      z,#2c92         ; Done with VRAM
        //-------------------------------
        while(*chr != 0x2f)
        {
            //-------------------------------
            // 2c89  dd7700    ld      (ix+#00),a	; Write char to screen 
            // 2c8c  23        inc     hl		; Next char
            // 2c8d  dd19      add     ix,de		; Calc next VRAM pos
            // 2c8f  04        inc     b		; Inc char count
            //-------------------------------
            printf ("%s normal %04lx => [%04lx]='%c', move %d\n", __func__,
                    chr-MEM, video-MEM, *chr, de);
            *video = *chr++;
            video += de;
            bc++;

            //-------------------------------
            // 2c90  18f2      jr      #2c84           ; loop
            //-------------------------------
        }

        //-------------------------------
        // 2c92  23        inc     hl
        //-------------------------------
        chr++;
       
jump_2c93:
        //-------------------------------
        // 2c93  dde1      pop     ix		; Get CRAM start pos
        // 2c95  7e        ld      a,(hl)		; Get color 
        // 2c96  a7        and     a
        // 2c97  faa42c    jp      m,#2ca4		; Jump if > #80 
        //-------------------------------
        if (*chr < 0x80)
        {
            while (bc--)
            {
                //-------------------------------
                // 2c9a  7e        ld      a,(hl)		; Get color  
                // 2c9b  dd7700    ld      (ix+#00),a	; Drop in CRAM
                // 2c9e  23        inc     hl		; Next color 
                // 2c9f  dd19      add     ix,de		; Calc next CRAM pos
                //-------------------------------
                printf ("%s multi-colour [%04lx] => [%04lx]=%02x, move %d\n", __func__, 
                        chr-MEM, colour-MEM, *chr, de);
                *colour = *chr++;
                colour += de;

                //-------------------------------
                // 2ca1  10f7      djnz    #2c9a           ; Loop until b = 0
                // 2ca3  c9        ret     
                //-------------------------------
            }

            return;
        }
        else
        {
            // 	;; Same as above, but all the same color
            while (bc--)
            {
                //-------------------------------
                // 2ca4  dd7700    ld      (ix+#00),a	; Drop in CRAM
                // 2ca7  dd19      add     ix,de		; Calc next CRAM pos
                // 2ca9  10f9      djnz    #2ca4           ; Loop until b = 0
                // 2cab  c9        ret     
                //-------------------------------
                printf ("%s single-colour [%04lx] => [%04lx]=%02x, move %d\n",
                        __func__, chr-MEM, colour-MEM, *chr, de);
                *colour = *chr;
                colour += de;
            }

            return;
        }
    }
    else
    {
        //-------------------------------
        // 	;; Message # > 80 (erase previous message), use 2nd color code
        // 2cac  7e        ld      a,(hl)		; Read next char
        // 2cad  fe2f      cp      #2f
        // 2caf  280a      jr      z,#2cbb         ; Done with VRAM
        //-------------------------------
        int TODO_count = 0;
        while (*chr != 0x2f)
        {
            //-------------------------------
            // 2cb1  dd360040  ld      (ix+#00),#40	; Write 40 to VRAM? 
            // 2cb5  23        inc     hl		; Next char 
            // 2cb6  dd19      add     ix,de		; Next screen pos
            // 2cb8  04        inc     b		; Inc char count  
            //-------------------------------
            printf ("%s blank [%04lx]=0x40, move %d\n", __func__, video-MEM, de);
            *video = 0x40;
            chr++;
            video += de;
            bc++;
            if (++TODO_count > 20)
            {
                printf ("!! %s taking too long\n", __func__);
                exit(1);
            }

            //-------------------------------
            // 2cb9  18f1      jr      #2cac           ; Loop
            //-------------------------------
        }

        //-------------------------------
        // 2cbb  23        inc     hl		; Next char 
        // 2cbc  04        inc     b		; Inc char count 
        // 2cbd  edb1      cpir			; Loop until [hl] = 2f 
        //-------------------------------
        chr++;
        bc++;
        while (*chr != 0x2f && bc > 0)
        {
            printf ("%s skip [%04lX] count=%d\n", __func__, chr-MEM, bc);
            chr++;
            bc--;
        }

        //-------------------------------
        // 2cbf  18d2      jr      #2c93           ; Do CRAM
        //-------------------------------
        goto jump_2c93;
    }
}

void playSongsAllChannels_2cc1 (void)
{
    //-------------------------------
    // 2cc1  21c83b    ld      hl,#3bc8
    // 2cc4  dd21cc4e  ld      ix,#4ecc
    // 2cc8  fd218c4e  ld      iy,#4e8c
    // 2ccc  cd442d    call    #2d44
    //-------------------------------
    int volume = playSongOneChannel_2d44 (CH1_SOUND_WAVE, &CH1_FREQ0, SONG_TABLE_CH1_3bc8);

    //-------------------------------
    // 2ccf  47        ld      b,a
    // 2cd0  3acc4e    ld      a,(#4ecc)
    // 2cd3  a7        and     a
    // 2cd4  2804      jr      z,#2cda         ; (4)
    //-------------------------------
    if (CH1_SOUND_WAVE->mask != 0)
    {
        //-------------------------------
        // 2cd6  78        ld      a,b
        // 2cd7  32914e    ld      (#4e91),a
        //-------------------------------
        CH1_VOL = volume;
    }

    //-------------------------------
    // 2cda  21cc3b    ld      hl,#3bcc
    // 2cdd  dd21dc4e  ld      ix,#4edc
    // 2ce1  fd21924e  ld      iy,#4e92
    // 2ce5  cd442d    call    #2d44
    //-------------------------------
    volume = playSongOneChannel_2d44 (CH2_SOUND_WAVE, &CH2_FREQ1, SONG_TABLE_CH2_3bcc);

    //-------------------------------
    // 2ce8  47        ld      b,a
    // 2ce9  3adc4e    ld      a,(#4edc)
    // 2cec  a7        and     a
    // 2ced  2804      jr      z,#2cf3         ; (4)
    //-------------------------------
    if (CH2_SOUND_WAVE->mask != 0)
    {
        //-------------------------------
        // 2cef  78        ld      a,b
        // 2cf0  32964e    ld      (#4e96),a
        //-------------------------------
        CH2_VOL = volume;
    }

    //-------------------------------
    // 2cf3  21d03b    ld      hl,#3bd0
    // 2cf6  dd21ec4e  ld      ix,#4eec
    // 2cfa  fd21974e  ld      iy,#4e97
    // 2cfe  cd442d    call    #2d44
    //-------------------------------
    volume = playSongOneChannel_2d44 (CH3_SOUND_WAVE, &CH3_FREQ1, SONG_TABLE_CH3_3bd0);

    //-------------------------------
    // 2d01  47        ld      b,a
    // 2d02  3aec4e    ld      a,(#4eec)
    // 2d05  a7        and     a
    // 2d06  c8        ret     z
    //-------------------------------
    if (CH3_SOUND_WAVE->mask == 0)
        return;

    //-------------------------------
    // 2d07  78        ld      a,b
    // 2d08  329b4e    ld      (#4e9b),a
    // 2d0b  c9        ret     
    //-------------------------------
    CH3_VOL = volume;
}

void soundEffectsAllChannels_2d0c (void)
{
    //-------------------------------
    // 2d0c  21303b    ld      hl,#3b30
    // 2d0f  dd219c4e  ld      ix,#4e9c
    // 2d13  fd218c4e  ld      iy,#4e8c
    // 2d17  cdee2d    call    #2dee
    // 2d1a  32914e    ld      (#4e91),a
    //-------------------------------
    CH1_VOL = soundEffectOneChannel_2dee (CH1_SOUND_EFFECT, &CH1_FREQ0, EFFECT_TABLE_CH1_3b30, 1);

    //-------------------------------
    // 2d1d  21403b    ld      hl,#3b40
    // 2d20  dd21ac4e  ld      ix,#4eac
    // 2d24  fd21924e  ld      iy,#4e92
    // 2d28  cdee2d    call    #2dee
    // 2d2b  32964e    ld      (#4e96),a
    //-------------------------------
    CH2_VOL = soundEffectOneChannel_2dee (CH2_SOUND_EFFECT, &CH2_FREQ1, EFFECT_TABLE_CH2_3b40, 2);

    //-------------------------------
    // 2d2e  21803b    ld      hl,#3b80
    // 2d31  dd21bc4e  ld      ix,#4ebc
    // 2d35  fd21974e  ld      iy,#4e97
    // 2d39  cdee2d    call    #2dee
    // 2d3c  329b4e    ld      (#4e9b),a
    //-------------------------------
    CH3_VOL = soundEffectOneChannel_2dee (CH3_SOUND_EFFECT, &CH3_FREQ1, EFFECT_TABLE_CH3_3b80, 3);

    //-------------------------------
    // 2d3f  af        xor     a
    // 2d40  32904e    ld      (#4e90),a
    // 2d43  c9        ret     
    //-------------------------------
    CH1_FREQ4 = 0;
}

/* *  Returns volume */
uint8_t playSongOneChannel_2d44 (SOUND_EFFECT *effect, uint8_t *frequency, uint8_t *table)
{
    //-------------------------------
    // 2d44  dd7e00    ld      a,(ix+#00)
    // 2d47  a7        and     a
    // 2d48  caf42d    jp      z,#2df4
    //-------------------------------
    if (effect->mask == 0)
        return soundEffectClear_2df4 (effect, frequency);

    //-------------------------------
    // 2d4b  4f        ld      c,a
    // 2d4c  0608      ld      b,#08
    // 2d4e  1e80      ld      e,#80
    //-------------------------------
    printf ("%s process mask %02x\n", __func__, effect->mask);
    uint8_t e = 0x80;
    int b;
    for (b = 8; b > 0; b--)
    {
        //-------------------------------
        // 2d50  7b        ld      a,e
        // 2d51  a1        and     c
        // 2d52  2005      jr      nz,#2d59        ; (5)
        // 2d54  cb3b      srl     e
        // 2d56  10f8      djnz    #2d50           ; (-8)
        //-------------------------------

        if ((effect->mask & e) != 0)
            break;

        e >>= 1;
    }

    //-------------------------------
    // 2d58  c9        ret     
    //-------------------------------
    if (b == 0)
        return 0;

    //-------------------------------
    // 2d59  dd7e02    ld      a,(ix+#02)
    // 2d5c  a3        and     e
    // 2d5d  2007      jr      nz,#2d66        ; (7)
    //-------------------------------
    uint16_t addr;
    if ((effect->current & e) == 0)
    {
        //-------------------------------
        // 2d5f  dd7302    ld      (ix+#02),e
        // 2d62  05        dec     b
        //-------------------------------
        effect->current = e;
        printf ("%s new note %02x\n", __func__, effect->current);
        b--;
        //-------------------------------
        // 2d63  df        rst     #18
        // 2d64  180c      jr      #2d72
        //-------------------------------
        addr = tableLookup_0018 (table, b);
        printf ("%s fetched addr %04x\n", __func__, addr);
    }
    else
    {
        //-------------------------------
        // 2d66  dd350c    dec     (ix+#0c)     ; duration
        // 2d69  c2d72d    jp      nz,#2dd7
        //-------------------------------
        printf ("%s continue note %02x dur=%d\n", __func__, effect->current,
                effect->duration);
        if (--effect->duration)
            goto jump_2dd7;

        //-------------------------------
        // 2d6c  dd6e06    ld      l,(ix+#06)   ; offset
        // 2d6f  dd6607    ld      h,(ix+#07)
        //-------------------------------
jump_2d6c:
        addr = effect->offset;
    }

    //-------------------------------
    // 2d72  7e        ld      a,(hl)
    // 2d73  23        inc     hl
    // 2d74  dd7506    ld      (ix+#06),l
    // 2d77  dd7407    ld      (ix+#07),h
    //-------------------------------
    int a = MEM[addr++];
    effect->offset = addr;

    //-------------------------------
    // 2d7a  fef0      cp      #f0
    // 2d7c  3827      jr      c,#2da5         ; (39)
    //-------------------------------
    printf ("%s process %02x\n", __func__, a);
    if (a >= 0xf0)
    {
        //-------------------------------
        // 2d7e  216c2d    ld      hl,#2d6c
        // 2d81  e5        push    hl
        // 2d82  e60f      and     #0f
        //-------------------------------
        printf ("%s a=%2x, jump\n", __func__, a);
        a &= 0xf;

        //-------------------------------
        // 2d84  e7        rst     #20
        // 2d85                 55 2f 65  2f 77 2f 89 2f 9b 2f 0c
        // 2d90  00 0c 00 0c 00 0c 00 0c  00 0c 00 0c 00 0c 00 0c
        // 2da0  00 0c 00 ad 2f                                 
        //-------------------------------
        void (*func[])(SOUND_EFFECT*, uint8_t *) = 
        {
            soundEffectIndirect_2f55,
            soundEffectSelect_2f65,
            soundEffectInitialFrequency_2f77,
            soundEffectInitialVolume_2f89,
            soundEffectType_2f9b,
            nothing_000c,
            nothing_000c,
            nothing_000c, nothing_000c,
            nothing_000c, nothing_000c, 
            nothing_000c, nothing_000c,
            nothing_000c, nothing_000c,
            soundEffectMarkDone_2fad
        };
        func[a] (effect, frequency);
        goto jump_2d6c;
    }

    //-------------------------------
    // 2da5  47        ld      b,a
    // 2da6  e61f      and     #1f
    // 2da8  2803      jr      z,#2dad         ; (3)
    //-------------------------------
    if ((a & 0x1f) != 0)
    {
        //-------------------------------
        // 2daa  dd700d    ld      (ix+#0d),b   ; dir?
        //-------------------------------
        effect->dir = a;
    }

    //-------------------------------
    // 2dad  dd4e09    ld      c,(ix+#09)
    // 2db0  dd7e0b    ld      a,(ix+#0b)
    // 2db3  e608      and     #08
    // 2db5  2802      jr      z,#2db9         ; (2)
    // 2db7  0e00      ld      c,#00
    //-------------------------------
    int c = effect->volumeInitial;
    if ((effect->type & 8) != 0)
    {
        c = 0;
    }

    //-------------------------------
    // 2db9  dd710f    ld      (ix+#0f),c
    //-------------------------------
    effect->volume = c;

    //-------------------------------
    // 2dbc  78        ld      a,b
    // 2dbd  07        rlca    
    // 2dbe  07        rlca    
    // 2dbf  07        rlca    
    // 2dc0  e607      and     #07
    // 2dc2  21b03b    ld      hl,#3bb0
    // 2dc5  d7        rst     #10
    // 2dc6  dd770c    ld      (ix+#0c),a
    //-------------------------------
    effect->duration = POWER_OF_2_3bb0[(a>>5) & 7];

    //-------------------------------
    // 2dc9  78        ld      a,b
    // 2dca  e61f      and     #1f
    // 2dcc  2809      jr      z,#2dd7         ; (9)
    //-------------------------------
    if ((a & 0x1f) != 0)
    {
        //-------------------------------
        // 2dce  e60f      and     #0f
        // 2dd0  21b83b    ld      hl,#3bb8
        // 2dd3  d7        rst     #10
        // 2dd4  dd770e    ld      (ix+#0e),a
        //-------------------------------
        effect->frequency = FREQ_TABLE_3bb8[a & 0x0f];
    }

jump_2dd7:
    //-------------------------------
    // 2dd7  dd6e0e    ld      l,(ix+#0e)
    // 2dda  2600      ld      h,#00
    //-------------------------------
    // uint8_t frequencyValue = effect->frequency;

    //-------------------------------
    // 2ddc  dd7e0d    ld      a,(ix+#0d)
    // 2ddf  e610      and     #10
    // 2de1  2802      jr      z,#2de5         ; (2)
    //-------------------------------
    a = effect->dir & 0x10;
    if (a != 0)
    {
        //-------------------------------
        // 2de3  3e01      ld      a,#01
        //-------------------------------
        a = 1;
    }

    //-------------------------------
    // 2de5  dd8604    add     a,(ix+#04)
    // 2de8  cae82e    jp      z,#2ee8          ; comput enew freq?
    // 2deb  c3e42e    jp      #2ee4
    //-------------------------------
    a += effect->frequencyInitial;

    printf ("%s new freq=%d scale=%d (f=%d) vol=%d\n", __func__, effect->frequency, a,
            effect->frequency<<a, effect->volume);

    if (a == 0)
        return frequencyWithVolume_2ee8 (effect, frequency, effect->frequency);
    else
        return frequencyScaledWithVolume_2ee4 (effect, frequency,
                                              effect->frequency, a);
}

uint8_t soundEffectOneChannel_2dee (SOUND_EFFECT *effect, uint8_t *frequency, uint8_t *table,int chan)
{
    //-------------------------------
    // 2dee  dd7e00    ld      a,(ix+#00)
    // 2df1  a7        and     a
    // 2df2  2027      jr      nz,#2e1b        ; (39) ; find effect?
    //-------------------------------
    if (effect->mask != 0)
        return soundEffectProcess_2e1b (effect, frequency, table, chan);
    else
        return soundEffectClear_2df4 (effect, frequency);
}

uint8_t soundEffectClear_2df4(SOUND_EFFECT *effect, uint8_t *frequency)
{
    //-------------------------------
    // 2df4  dd7e02    ld      a,(ix+#02)
    // 2df7  a7        and     a
    // 2df8  c8        ret     z
    //-------------------------------
    if (effect->current == 0)
        return 0;

    //-------------------------------
    // 2df9  dd360200  ld      (ix+#02),#00
    // 2dfd  dd360d00  ld      (ix+#0d),#00
    // 2e01  dd360e00  ld      (ix+#0e),#00
    // 2e05  dd360f00  ld      (ix+#0f),#00
    // 2e09  fd360000  ld      (iy+#00),#00
    // 2e0d  fd360100  ld      (iy+#01),#00
    // 2e11  fd360200  ld      (iy+#02),#00
    // 2e15  fd360300  ld      (iy+#03),#00
    // 2e19  af        xor     a
    // 2e1a  c9        ret     
    //-------------------------------
    effect->current = 
    effect->dir = 
    effect->frequency = 
    effect->volume = 0;

    frequency[0] = 
    frequency[1] = 
    frequency[2] = 
    frequency[3] = 0;

    return 0;
}

uint8_t soundEffectProcess_2e1b (SOUND_EFFECT *effect, uint8_t *frequency,
                                 uint8_t *table, int chan)
{
    //-------------------------------
    // 2e1b  4f        ld      c,a
    // 2e1c  0608      ld      b,#08
    // 2e1e  1e80      ld      e,#80
    //-------------------------------
    printf ("\n%s EFF BEGIN ch=%d mask %02x\n", __func__,
            chan, effect->mask);
    uint8_t mask = 0x80;
    int bit;
    for (bit = 8; bit > 0; bit--)
    {
        //-------------------------------
        // 2e20  7b        ld      a,e
        // 2e21  a1        and     c
        // 2e22  2005      jr      nz,#2e29        ; (5)
        // 2e24  cb3b      srl     e
        // 2e26  10f8      djnz    #2e20           ; (-8)
        // 2e28  c9        ret     
        //-------------------------------
        if ((effect->mask & mask) != 0)
            break;

        mask >>= 1;
    }

    if (bit == 0)
        // return e << 1;
        return 0;
 
    //-------------------------------
    // 2e29  dd7e02    ld      a,(ix+#02)
    // 2e2c  a3        and     e
    // 2e2d  203f      jr      nz,#2e6e        ; (63)
    //-------------------------------
    if ((effect->current & mask) == 0)
    {
        //-------------------------------
        // 2e2f  dd7302    ld      (ix+#02),e
        // 2e32  05        dec     b
        // 2e33  78        ld      a,b
        // 2e34  07        rlca    
        // 2e35  07        rlca    
        // 2e36  07        rlca    
        // 2e37  4f        ld      c,a
        // 2e38  0600      ld      b,#00
        // 2e3a  e5        push    hl
        // 2e3b  09        add     hl,bc
        //-------------------------------
        effect->current = mask;
        printf ("%s EFF new effect %02x\n", __func__, effect->current);
        table += (bit - 1) * 8;

        //-------------------------------
        // 2e3c  dde5      push    ix
        // 2e3e  d1        pop     de
        // 2e3f  13        inc     de
        // 2e40  13        inc     de
        // 2e41  13        inc     de
        // 2e42  010800    ld      bc,#0008
        // 2e45  edb0      ldir    
        //-------------------------------
        memcpy (&effect->selected, table, 8);
        printf ("%s EFF memcpy %04lx sel=%02x fri=%02x frd=%d off=%02x%02x "
                "repeat=%02x volinit=%d vold=%d\n",
                __func__, table-ROM,
                table[0],
                table[1],
                table[2],
                table[4], table[3], // little endian
                table[5],
                table[6],
                table[7]);

        //-------------------------------
        // 2e47  e1        pop     hl
        // 2e48  dd7e06    ld      a,(ix+#06)
        // 2e4b  e67f      and     #7f
        // 2e4d  dd770c    ld      (ix+#0c),a
        // 2e50  dd7e04    ld      a,(ix+#04)
        // 2e53  dd770e    ld      (ix+#0e),a
        //-------------------------------
        effect->duration = effect->offset & 0x7f;
        effect->frequency = effect->frequencyInitial;

        //-------------------------------
        // 2e56  dd7e09    ld      a,(ix+#09)
        // 2e59  47        ld      b,a
        // 2e5a  0f        rrca    
        // 2e5b  0f        rrca    
        // 2e5c  0f        rrca    
        // 2e5d  0f        rrca    
        // 2e5e  e60f      and     #0f
        // 2e60  dd770b    ld      (ix+#0b),a
        //-------------------------------
        effect->type = effect->volumeInitial >> 4;
        printf ("%s EFF effect type set to %02x\n", __func__, effect->type);

        //-------------------------------
        // 2e63  e608      and     #08
        // 2e65  2007      jr      nz,#2e6e        ; (7)
        //-------------------------------
        if ((effect->type & 8) == 0)
        {
            //-------------------------------
            // 2e67  dd700f    ld      (ix+#0f),b
            // 2e6a  dd360d00  ld      (ix+#0d),#00
            //-------------------------------
            effect->volume = effect->volumeInitial;
            effect->dir = 0;
        }
    }

    //-------------------------------
    // 2e6e  dd350c    dec     (ix+#0c)
    // 2e71  205a      jr      nz,#2ecd        ; (90)
    //-------------------------------
    printf ("%s EFF continue sound %02x dur=%d\n", __func__, effect->current,
            effect->duration);

    if (--effect->duration != 0)
        goto jump_2ecd;

    //-------------------------------
    // 2e73  dd7e08    ld      a,(ix+#08)
    // 2e76  a7        and     a
    // 2e77  2810      jr      z,#2e89         ; (16)
    // 2e79  dd3508    dec     (ix+#08)
    // 2e7c  200b      jr      nz,#2e89        ; (11)
    //-------------------------------
    if (effect->repeat != 0 && --effect->repeat == 0)
    {
        //-------------------------------
        // 2e7e  7b        ld      a,e
        // 2e7f  2f        cpl     
        // 2e80  dda600    and     (ix+#00)
        // 2e83  dd7700    ld      (ix+#00),a
        // 2e86  c3ee2d    jp      #2dee
        //-------------------------------
        printf ("%s EFF repeat is %d, clear %02x\n", __func__, effect->repeat,
        mask);
        effect->mask &= ~mask;
        return soundEffectOneChannel_2dee (effect, frequency, table, chan);
    }
    else
    {
        //-------------------------------
        // 2e89  dd7e06    ld      a,(ix+#06)
        // 2e8c  e67f      and     #7f
        // 2e8e  dd770c    ld      (ix+#0c),a
        //-------------------------------
        printf ("%s EFF rep=%d, get dur, off&7f=%02x\n", __func__, effect->repeat, effect->offset);
        effect->duration = effect->offset & 0x7f;

        //-------------------------------
        // 2e91  ddcb067e  bit     7,(ix+#06)
        // 2e95  2816      jr      z,#2ead         ; (22)
        //-------------------------------
        if ((effect->offset & 0x80) != 0)
        {
            //-------------------------------
            // 2e97  dd7e05    ld      a,(ix+#05)
            // 2e9a  ed44      neg     
            // 2e9c  dd7705    ld      (ix+#05),a
            //-------------------------------
            effect->frequencyDelta = -effect->frequencyDelta;

            //-------------------------------
            // 2e9f  ddcb0d46  bit     0,(ix+#0d)
            // 2ea3  ddcb0dc6  set     0,(ix+#0d)
            // 2ea7  2824      jr      z,#2ecd         ; (36)
            // 2ea9  ddcb0d86  res     0,(ix+#0d)
            //-------------------------------
            printf ("%s EFF dir=%02x\n", __func__, effect->dir);
            effect->dir ^= 1;
            if ((effect->dir & 1) != 0)
                goto jump_2ecd;
        }

        //-------------------------------
        // 2ead  dd7e04    ld      a,(ix+#04)
        // 2eb0  dd8607    add     a,(ix+#07)
        // 2eb3  dd7704    ld      (ix+#04),a
        // 2eb6  dd770e    ld      (ix+#0e),a
        //-------------------------------
        printf ("%s EFF off=%04x fri=%04x voli=%02x vold=%02x\n", __func__,
            effect->offset,
            effect->frequencyInitial, 
            effect->volumeInitial, 
            effect->volumeDelta);

        effect->frequencyInitial += effect->offset >> 8;
        effect->frequency = effect->frequencyInitial;

        //-------------------------------
        // 2eb9  dd7e09    ld      a,(ix+#09)
        // 2ebc  dd860a    add     a,(ix+#0a)
        // 2ebf  dd7709    ld      (ix+#09),a
        //-------------------------------
        effect->volumeInitial += effect->volumeDelta;

        //-------------------------------
        // 2ec2  47        ld      b,a
        // 2ec3  dd7e0b    ld      a,(ix+#0b)
        // 2ec6  e608      and     #08
        // 2ec8  2003      jr      nz,#2ecd        ; (3)
        // 2eca  dd700f    ld      (ix+#0f),b
        //-------------------------------
        if ((effect->type & 8) == 0)
            effect->volume = effect->volumeInitial;
    }

jump_2ecd:
    //-------------------------------
    // 2ecd  dd7e0e    ld      a,(ix+#0e)
    // 2ed0  dd8605    add     a,(ix+#05)
    // 2ed3  dd770e    ld      (ix+#0e),a
    //-------------------------------
    effect->frequency += effect->frequencyDelta;

    //-------------------------------
    // 2ed6  6f        ld      l,a
    // 2ed7  2600      ld      h,#00
    // 2ed9  dd7e03    ld      a,(ix+#03)
    // 2edc  e670      and     #70
    // 2ede  2808      jr      z,#2ee8         ; (8)
    // 2ee0  0f        rrca    
    // 2ee1  0f        rrca    
    // 2ee2  0f        rrca    
    // 2ee3  0f        rrca    
    //-------------------------------
    // uint8_t frequencyValue = effect->frequency;
    // uint8_t selected = effect->selected;

    if ((effect->selected & 0x70) == 0)
        return frequencyWithVolume_2ee8 (effect, frequency, effect->frequency);
    else
        return frequencyScaledWithVolume_2ee4 (effect, frequency,
                                              effect->frequency, effect->selected >> 4);
}

uint8_t frequencyScaledWithVolume_2ee4 (SOUND_EFFECT *effect, uint8_t *frequency, uint16_t frequencyValue, uint8_t scale)
{
    //-------------------------------
    // 2ee4  47        ld      b,a
    // 2ee5  29        add     hl,hl
    // 2ee6  10fd      djnz    #2ee5           ; (-3)
    //-------------------------------
    printf ("%s EFF scale freq by %d from %d to %d\n", __func__, scale,
    frequencyValue, frequencyValue<<scale);
    // while (scale--)
    //     frequencyValue *= 2;
    frequencyValue <<= scale;

    return frequencyWithVolume_2ee8 (effect, frequency, frequencyValue);
}

uint8_t frequencyWithVolume_2ee8 (SOUND_EFFECT *effect, uint8_t *frequency, uint16_t frequencyValue)
{
    //-------------------------------
    // 2ee8  fd7500    ld      (iy+#00),l
    // 2eeb  7d        ld      a,l
    // 2eec  0f        rrca    
    // 2eed  0f        rrca    
    // 2eee  0f        rrca    
    // 2eef  0f        rrca    
    // 2ef0  fd7701    ld      (iy+#01),a
    // 2ef3  fd7402    ld      (iy+#02),h
    // 2ef6  7c        ld      a,h
    // 2ef7  0f        rrca    
    // 2ef8  0f        rrca    
    // 2ef9  0f        rrca    
    // 2efa  0f        rrca    
    // 2efb  fd7703    ld      (iy+#03),a
    //-------------------------------
    frequency[0] = frequencyValue & 0xff;
    frequency[1] = (frequencyValue >> 4) & 0xf;
    frequency[2] = (frequencyValue >> 8) & 0xff;
    frequency[3] = (frequencyValue >> 12) & 0xf;

    //-------------------------------
    // 2efe  dd7e0b    ld      a,(ix+#0b)
    // 2f01  e7        rst     #20
    //
    // 2f02  222f 262f 2b2f 3c2f 
    // 2f0a  432f 4a2f 4b2f 4c2f 
    // 2f12  4d2f 4e2f 4f2f 502f 
    // 2f1a  512f 522f 532f 542f 
    //-------------------------------

    /*  Addresses 0x2f4a thru 0x2f43 are just a ret, so insert the same for each */
    uint8_t (*func[])(SOUND_EFFECT*) = 
    {
        volumeDecayNone_2f22,
        volumeDecay_2f26,
        volumeDecayHalfTime_2f2b,
        volumeDecayQuarterTime_2f3c,
        volumeDecayEighthTime_2f43,
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a, 
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a,
        soundEffectDoNothing_2f4a
    };
    int vol = func[effect->type] (effect);
    printf ("%s volume-effect %d freq %d ret vol %d\n", __func__, effect->type,
        frequencyValue, vol);
    return vol;
}

uint8_t volumeDecayNone_2f22 (SOUND_EFFECT *effect)
{
    //-------------------------------
    // 2f22  dd7e0f    ld      a,(ix+#0f)
    // 2f25  c9        ret     
    //-------------------------------
    return effect->volume;
}

uint8_t volumeDecay_2f26 (SOUND_EFFECT *effect)
{
    //-------------------------------
    // 2f26  dd7e0f    ld      a,(ix+#0f)
    // 2f29  1809      jr      #2f34           ; (9)
    //-------------------------------
    return volumeDecrease_2f34 (effect, effect->volume);
}

uint8_t volumeDecayHalfTime_2f2b (SOUND_EFFECT *effect)
{
    //-------------------------------
    // 2f2b  3a844c    ld      a,(#4c84)
    // 2f2e  e601      and     #01
    //-------------------------------
    return volumeDecreaseConditional_2f30 (effect, *SOUND_COUNTER & 1);
}

uint8_t volumeDecreaseConditional_2f30 (SOUND_EFFECT *effect, int condition)
{
    //-------------------------------
    // 2f30  dd7e0f    ld      a,(ix+#0f)
    // 2f33  c0        ret     nz
    //-------------------------------
    if (condition != 0)
        return effect->volume;

    return volumeDecrease_2f34 (effect, effect->volume);
}

uint8_t volumeDecrease_2f34 (SOUND_EFFECT *effect, uint8_t volume)
{
    //-------------------------------
    // 2f34  e60f      and     #0f
    // 2f36  c8        ret     z
    //-------------------------------
    volume &= 0xf;

    if (volume == 0)
        return 0;

    //-------------------------------
    // 2f37  3d        dec     a
    // 2f38  dd770f    ld      (ix+#0f),a
    // 2f3b  c9        ret     
    //-------------------------------
    effect->volume = --volume;
    return volume;
}

/*  Decrease volume if lowest 2-bits of sound counter are zero, i.e. every
 *  fourth interval */
uint8_t volumeDecayQuarterTime_2f3c (SOUND_EFFECT *effect)
{
    //-------------------------------
    // 2f3c  3a844c    ld      a,(#4c84)
    // 2f3f  e603      and     #03
    // 2f41  18ed      jr      #2f30           ; (-19)
    //-------------------------------
    return volumeDecreaseConditional_2f30 (effect, *SOUND_COUNTER & 3);
}

/*  Decrease volume if lowest 3-bits of sound counter are zero, i.e. every
 *  eighth interval */
uint8_t volumeDecayEighthTime_2f43 (SOUND_EFFECT *effect)
{
    //-------------------------------
    // 2f43  3a844c    ld      a,(#4c84)
    // 2f46  e607      and     #07
    // 2f48  18e6      jr      #2f30           ; (-26)
    //-------------------------------
    return volumeDecreaseConditional_2f30 (effect, *SOUND_COUNTER & 7);
}

uint8_t soundEffectDoNothing_2f4a (SOUND_EFFECT *effect)
{
    return 0;
}

    //-------------------------------
    // 2f4a  c9        ret     
    // 2f4b  c9        ret     
    // 2f4c  c9        ret     
    // 2f4d  c9        ret     
    // 2f4e  c9        ret     
    // 2f4f  c9        ret     
    // 2f50  c9        ret     
    // 2f51  c9        ret     
    // 2f52  c9        ret     
    // 2f53  c9        ret     
    // 2f54  c9        ret     
    //-------------------------------

void soundEffectIndirect_2f55 (SOUND_EFFECT *effect, uint8_t *frequency)
{
    //-------------------------------
    // 2f55  dd6e06    ld      l,(ix+#06)
    // 2f58  dd6607    ld      h,(ix+#07)
    // 2f5b  7e        ld      a,(hl)
    // 2f5c  dd7706    ld      (ix+#06),a
    // 2f5f  23        inc     hl
    // 2f60  7e        ld      a,(hl)
    // 2f61  dd7707    ld      (ix+#07),a
    // 2f64  c9        ret     
    //-------------------------------
    // uint16_t addr = effect->offset;
    // effect->offset = (MEM[addr+1] << 8) | MEM[addr];
    printf ("EFF indirect from addr %04x\n", effect->offset);
    effect->offset = *((uint16_t*)&MEM[effect->offset]);
}

void soundEffectSelect_2f65 (SOUND_EFFECT *effect, uint8_t *frequency)
{
    //-------------------------------
    // 2f65  dd6e06    ld      l,(ix+#06)
    // 2f68  dd6607    ld      h,(ix+#07)
    // 2f6b  7e        ld      a,(hl)
    // 2f6c  23        inc     hl
    // 2f6d  dd7506    ld      (ix+#06),l
    // 2f70  dd7407    ld      (ix+#07),h
    // 2f73  dd7703    ld      (ix+#03),a
    // 2f76  c9        ret     
    //-------------------------------
    effect->selected = MEM[effect->offset++];
    printf ("%s EFF read selected %02x from %04x\n", __func__, effect->selected,
        effect->offset-1);
}

void soundEffectInitialFrequency_2f77 (SOUND_EFFECT *effect, uint8_t *frequency)
{
    //-------------------------------
    // 2f77  dd6e06    ld      l,(ix+#06)
    // 2f7a  dd6607    ld      h,(ix+#07)
    // 2f7d  7e        ld      a,(hl)
    // 2f7e  23        inc     hl
    // 2f7f  dd7506    ld      (ix+#06),l
    // 2f82  dd7407    ld      (ix+#07),h
    // 2f85  dd7704    ld      (ix+#04),a
    // 2f88  c9        ret     
    //-------------------------------
    effect->frequencyInitial = MEM[effect->offset++];
    printf ("%s EFF read freqi=%02x from %04x\n", __func__,
            effect->frequencyInitial, effect->offset-1);
}

void soundEffectInitialVolume_2f89 (SOUND_EFFECT *effect, uint8_t *frequency)
{
    //-------------------------------
    // 2f89  dd6e06    ld      l,(ix+#06)
    // 2f8c  dd6607    ld      h,(ix+#07)
    // 2f8f  7e        ld      a,(hl)
    // 2f90  23        inc     hl
    // 2f91  dd7506    ld      (ix+#06),l
    // 2f94  dd7407    ld      (ix+#07),h
    // 2f97  dd7709    ld      (ix+#09),a
    // 2f9a  c9        ret     
    //-------------------------------
    effect->volumeInitial = MEM[effect->offset++];
    printf ("%s EFF read tbd9 %02x from %04x\n", __func__,
            effect->volumeInitial, effect->offset-1);
}

void soundEffectType_2f9b (SOUND_EFFECT *effect, uint8_t *frequency)
{
    //-------------------------------
    // 2f9b  dd6e06    ld      l,(ix+#06)
    // 2f9e  dd6607    ld      h,(ix+#07)
    // 2fa1  7e        ld      a,(hl)
    // 2fa2  23        inc     hl
    // 2fa3  dd7506    ld      (ix+#06),l
    // 2fa6  dd7407    ld      (ix+#07),h
    // 2fa9  dd770b    ld      (ix+#0b),a
    // 2fac  c9        ret     
    //-------------------------------
    effect->type = MEM[effect->offset++];
    printf ("%s EFF read type %02x from %04X\n", __func__, effect->type,
            effect->offset-1);
}

void soundEffectMarkDone_2fad (SOUND_EFFECT *effect, uint8_t *frequency)
{
    //-------------------------------
    // 2fad  dd7e02    ld      a,(ix+#02)
    // 2fb0  2f        cpl     
    // 2fb1  dda600    and     (ix+#00)
    // 2fb4  dd7700    ld      (ix+#00),a
    // 2fb7  c3f42d    jp      #2df4
    //-------------------------------
    effect->mask &= ~effect->current;
    printf ("%s EFF clear mask %02x\n", __func__, effect->current);
    soundEffectClear_2df4 (effect, frequency);
}

    //-------------------------------
    // 2fba-2ffd 00 
    // 2ffe  834c      ; checksum
    //-------------------------------

/* Interrupt routine for vector #3ffa
 * 
 * Check rom checksums */
void isr_3000 (void)
{
    //-------------------------------
    // 3000  210000    ld      hl,#0000
    //-------------------------------
    uint8_t h = 0;
    uint8_t l = 0;

    do // odd/even bytes
    {
        do // all roms
        {
            //-------------------------------
            // 3003  010010    ld      bc,#1000
            //-------------------------------
            uint8_t c = 0;

            for (uint8_t b = 0; b < 0x10; b++)
            {
                //-------------------------------
                // 3006  32c050    ld      (#50c0),a	; Kick the dog
                //-------------------------------
                kickWatchdog();
                do
                {
                    //-------------------------------
                    // 3009  79        ld      a,c
                    // 300a  86        add     a,(hl)
                    // 300b  4f        ld      c,a
                    //-------------------------------
                    c += ROM[(h << 8) | l];
                    //-------------------------------
                    // 300c  7d        ld      a,l
                    // 300d  c602      add     a,#02
                    // 300f  6f        ld      l,a
                    //-------------------------------
                    l += 2;
                    //-------------------------------
                    // 3010  fe02      cp      #02
                    // 3012  d20930    jp      nc,#3009
                    //-------------------------------
                }
                while (l >= 2);
                //-------------------------------
                // 3015  24        inc     h
                // 3016  10ee      djnz    #3006           ; (-18)
                //-------------------------------
                h++;
            }
            //-------------------------------
            // 3018  79        ld      a,c
            // 3019  a7        and     a
            // 301a  2015      jr      nz,#3031        ; Rom checksum bad (?)
            //-------------------------------
            if (c != 0)
            {
                romChecksumBad_3031 (h, c);
                return;
            }

            //-------------------------------
            // 301c  320750    ld      (#5007),a	; Clear coin
            //-------------------------------
            COINCOUNTER = 0;

            //-------------------------------
            // 301f  7c        ld      a,h
            // 3020  fe30      cp      #30
            // 3022  c20330    jp      nz,#3003	; Continue for other roms
            //-------------------------------
        }
        while (h != 0x30);

        //-------------------------------
        // 3025  2600      ld      h,#00
        // 3027  2c        inc     l
        //-------------------------------
        h = 0;
        l++;

        //-------------------------------
        // 3028  7d        ld      a,l
        // 3029  fe02      cp      #02
        // 302b  da0330    jp      c,#3003
        //-------------------------------
    }
    while (l < 2);

    //-------------------------------
    // 302e  c34230    jp      #3042
    //-------------------------------
    ramTest_3042 ();
}

/* Bad rom checksum (?) */
void romChecksumBad_3031 (uint8_t h, uint8_t checksum)
{
    //-------------------------------
    // 3031  25        dec     h
    // 3032  7c        ld      a,h
    // 3033  e6f0      and     #f0
    // 3035  320750    ld      (#5007),a	; Clear coin
    //-------------------------------
    h--;
    COINCOUNTER = h & 0xf0;

    //-------------------------------
    // 3038  0f        rrca    
    // 3039  0f        rrca    
    // 303a  0f        rrca    
    // 303b  0f        rrca    
    // 303c  5f        ld      e,a		; Failed rom -> e (?)
    // 303d  0600      ld      b,#00
    // 303f  c3bd30    jp      #30bd
    //-------------------------------
    printf ("ROM checksum fail\n");
    testResultRamRom (h>>4, checksum, 0);
}

/* RAM test (4c00) */
void ramTest_3042 (void)
{
    //-------------------------------
    // 3042  315431    ld      sp,#3154
    //-------------------------------
    uint16_t *stackData = DATA_3154;
    uint8_t a = 0;
    uint16_t de = 0;
    uint8_t testValue = 0;

    do
    {
        printf ("%s a=%02x de=%04x\n", __func__, a, de);
        //-------------------------------
        // 3045  06ff      ld      b,#ff
        //-------------------------------
        for (uint8_t b = 0xff; b != 0; b--)
        {
            //-------------------------------
            // 3047  e1        pop     hl		; 4c00 (first time)
            // 3048  d1        pop     de		; 040f (first time)
            // 3049  48        ld      c,b		; 0xff -> c
            //-------------------------------
            uint16_t hl = *stackData++;
            de = *stackData++;
            testValue = b;
            // printf ("round %d, hl = %04x de=%04x\n", b, hl, de);

            do
            {
                //-------------------------------
                // 304a  32c050    ld      (#50c0),a	; Kick the dog
                //-------------------------------
                kickWatchdog();

                /*  Add a sleep to show power on test progress when testing
                 *  video */
                if (hl < 0x4800) usleep (10000);

                do
                {
                    do
                    {
                        //-------------------------------
                        // 304d  79        ld      a,c		; 0xff -> a
                        // 304e  a3        and     e		; e -> a
                        // 304f  77        ld      (hl),a
                        //-------------------------------
                        testValue &= de;
                        MEM[hl] = testValue;
                        // printf ("%04X = %02x=%02x ", hl, testValue, MEM[hl]);
                        //-------------------------------
                        // 3050  c633      add     a,#33
                        // 3052  4f        ld      c,a
                        // 3053  2c        inc     l
                        //-------------------------------
                        testValue += 0x33;
                        hl++;

                        //-------------------------------
                        // 3054  7d        ld      a,l
                        // 3055  e60f      and     #0f
                        // 3057  c24d30    jp      nz,#304d
                        //-------------------------------
                    }
                    while ((hl & 0x0f) != 0);
                    // printf ("\n");

                    //-------------------------------
                    // 305a  79        ld      a,c
                    // 305b  87        add     a,a
                    // 305c  87        add     a,a
                    // 305d  81        add     a,c
                    // 305e  c631      add     a,#31
                    // 3060  4f        ld      c,a
                    //-------------------------------
                    testValue = testValue * 5 + 0x31;
                    //-------------------------------
                    // 3061  7d        ld      a,l
                    // 3062  a7        and     a		
                    // 3063  c24d30    jp      nz,#304d
                    //-------------------------------
                }
                while ((hl & 0xff) != 0);

                //-------------------------------
                // 3066  24        inc     h
                // 3067  15        dec     d
                // 3068  c24a30    jp      nz,#304a
                //-------------------------------
                // hl += 0x100;
                de -= 0x100;
            }
            while ((de & 0xff00) != 0);

            //-------------------------------
            // 306b  3b        dec     sp
            // 306c  3b        dec     sp
            // 306d  3b        dec     sp
            // 306e  3b        dec     sp
            // 306f  e1        pop     hl		; 4c00
            // 3070  d1        pop     de		; 040f 
            // 3071  48        ld      c,b
            //-------------------------------
            stackData -= 2;
            hl = *stackData++;
            de = *stackData++;
            testValue = b;
            // printf ("round %d, hl = %04x de=%04x\n", b, hl, de);

            // 	;; Check crap in ram
            do
            {
                //-------------------------------
                // 3072  32c050    ld      (#50c0),a	; Kick the dog
                //-------------------------------
                kickWatchdog();
                do
                {
                    do
                    {
                        //-------------------------------
                        // 3075  79        ld      a,c
                        // 3076  a3        and     e
                        // 3077  4f        ld      c,a
                        //-------------------------------
                        // printf ("%02x&%04x = %02x ", testValue, de, testValue&de);
                        testValue &= de;
                        //-------------------------------
                        // 3078  7e        ld      a,(hl)
                        // 3079  a3        and     e
                        // 307a  b9        cp      c
                        // 307b  c2b530    jp      nz,#30b5	; Ram test failed
                        //-------------------------------
                        // printf ("%04X = %02x=%02x ", hl, testValue, MEM[hl]);
                        if (testValue != (MEM[hl] & de))
                        {
                            // printf ("test = %02X, MEM[%04x]=%02x\n",
                            //         testValue, hl, MEM[hl]);
                            printf ("RAM fail\n");
                            badRam_30b5 (de & 0xff, testValue);
                            return;
                        }

                        //-------------------------------
                        // 307e  c633      add     a,#33
                        // 3080  4f        ld      c,a
                        // printf ("%02x+0x33 = %02x ", testValue, testValue+0x33);
                        //-------------------------------
                        testValue += 0x33;
                        //-------------------------------
                        // 3081  2c        inc     l
                        // 3082  7d        ld      a,l
                        // 3083  e60f      and     #0f
                        // 3085  c27530    jp      nz,#3075
                        //-------------------------------
                    }
                    while ((++hl & 0x0f) != 0);
                    // printf ("\nnext row : ");

                    //-------------------------------
                    // 3088  79        ld      a,c
                    // 3089  87        add     a,a
                    // 308a  87        add     a,a
                    // 308b  81        add     a,c
                    // 308c  c631      add     a,#31
                    // 308e  4f        ld      c,a
                    //-------------------------------
                    testValue = testValue * 5 + 0x31;
                    //-------------------------------
                    // 308f  7d        ld      a,l
                    // 3090  a7        and     a
                    // 3091  c27530    jp      nz,#3075
                    //-------------------------------
                }
                while ((hl & 0xff) != 0);
                //-------------------------------
                // 3094  24        inc     h
                // 3095  15        dec     d
                // 3096  c27230    jp      nz,#3072
                //-------------------------------
                // hl += 0x100;
                de -= 0x100;
            }
            while ((de & 0xff00) != 0);

            //-------------------------------
            // 3099  3b        dec     sp
            // 309a  3b        dec     sp
            // 309b  3b        dec     sp
            // 309c  3b        dec     sp
            // 309d  78        ld      a,b
            // 309e  d610      sub     #10
            // 30a0  47        ld      b,a
            // 30a1  10a4      djnz    #3047           ; (-92)
            //-------------------------------
            stackData -= 2;
            b -= 0x10;
        }

        //-------------------------------
        // 30a3  f1        pop     af		; 4c00 
        // 30a4  d1        pop     de
        // 30a5  fe44      cp      #44
        // 30a7  c24530    jp      nz,#3045	; Check if 0x44xx done
        // 30aa  7b        ld      a,e
        // 30ab  eef0      xor     #f0
        // 30ad  c24530    jp      nz,#3045	; Check if totally done
        //-------------------------------
        a = *stackData++ >> 8;
        de = *stackData++;
    }
    while ((a != 0x44) || ((de & 0xff) ^ 0xf0) != 0);
    //-------------------------------
    // 30b0  0601      ld      b,#01
    // 30b2  c3bd30    jp      #30bd
    //-------------------------------
    printf ("RAM test pass\n");
    testResultRamRom ((de & 0xff), testValue, 1);
}

/* Display bad ram (?) */
void badRam_30b5 (uint8_t e, uint8_t c)
{
    printf ("BADRAM!\n");
    //-------------------------------
    // 30b5  7b        ld      a,e
    // 30b6  e601      and     #01
    // 30b8  ee01      xor     #01
    // 30ba  5f        ld      e,a
    // 30bb  0600      ld      b,#00
    //-------------------------------
    testResultRamRom ((e&1)^1, c, 0);
}

/* Display bad rom (?) */
void testResultRamRom (int e, uint8_t checksum, int pass)
{
    printf ("Check RAM/ROM tests passed\n");
    //-------------------------------
    // 30bd  31c04f    ld      sp,#4fc0
    // 30c0  d9        exx			; Swap register pairs 
    //-------------------------------
    // 
    // 	;; Clear all program ram

    //-------------------------------
    // 30c1  21004c    ld      hl,#4c00
    // 30c4  0604      ld      b,#04
    // 30c6  32c050    ld      (#50c0),a	; Kick watchdog
    //-------------------------------
    kickWatchdog();
    for (int i = 0; i < 0x400; i++)
    {
        //-------------------------------
        // 30c9  3600      ld      (hl),#00
        //-------------------------------
        MEM[0x4c00 + i] = 0;
        //-------------------------------
        // 30cb  2c        inc     l
        // 30cc  20fb      jr      nz,#30c9        ; (-5)
        // 30ce  24        inc     h
        // 30cf  10f5      djnz    #30c6           ; (-11)
        //-------------------------------
    }

    //-------------------------------
    // 30d1  210040    ld      hl,#4000
    // 30d4  0604      ld      b,#04
    // 30d6  32c050    ld      (#50c0),a	; Kick watchdog
    //-------------------------------
    kickWatchdog();
    /* Set all video ram to 0x40 */
    for (int i = 0; i < 0x400; i++)
    {
        //-------------------------------
        // 30d9  3e40      ld      a,#40
        // 30db  77        ld      (hl),a
        //-------------------------------
        SCREEN[i] = 0x40;
        //-------------------------------
        // 30dc  2c        inc     l
        // 30dd  20fc      jr      nz,#30db        ; (-4)
        // 30df  24        inc     h
        // 30e0  10f4      djnz    #30d6           ; (-12)
        //-------------------------------
    }

    //-------------------------------
    // 30e2  0604      ld      b,#04
    // 30e4  32c050    ld      (#50c0),a
    //-------------------------------

    /* Set all color ram to 0x0f */
    kickWatchdog();
    for (int i = 0; i < 0x400; i++)
    {
        //-------------------------------
        // 30e7  3e0f      ld      a,#0f
        // 30e9  77        ld      (hl),a
        //-------------------------------
        COLOUR[i] = 0x0f;
        //-------------------------------
        // 30ea  2c        inc     l
        // 30eb  20fc      jr      nz,#30e9        ; (-4)
        // 30ed  24        inc     h
        // 30ee  10f4      djnz    #30e4           ; (-12)
        //-------------------------------
    }

    //-------------------------------
    // 30f0  d9        exx			; Reswap register pairs 
    // 30f1  1008      djnz    #30fb           ; b = 1 -> no errors
    //-------------------------------
    if (pass == 0)
    {
        badRomOrRamMessage_30fb(e, 4, checksum);
        return;
    }

    //-------------------------------
    // 30f3  0623      ld      b,#2
    // 30f5  cd5e2c    call    #2c5e	
    // 30f8  c37431    jp      #3174		; Run code ?!?!?
    //-------------------------------
    displayMsg_2c5e (MSG_FREEPLAY);
    serviceModeOrStartGame_3174();
}

void badRomOrRamMessage_30fb (int e, int h, uint8_t checksum)
{
    //-------------------------------
    // 30fb  7b        ld      a,e		; Bad rom # -> a 
    // 30fc  c630      add     a,#30 
    // 30fe  328441    ld      (#4184),a	; Write to screen  [31] [30]
    //-------------------------------
    SCREEN[0x184] = e + 0x30;
    //-------------------------------
    // 3101  c5        push    bc		; [ff0f] 
    // 3102  e5        push    hl		; [4c00] 
    // 3103  0624      ld      b,#24
    // 3105  cd5e2c    call    #2c5e		; < = - gets called. 
    //-------------------------------
    displayMsg_2c5e (MSG_BADROMRAM);
    //-------------------------------
    // 3108  e1        pop     hl
    // 3109  7c        ld      a,h
    // 310a  fe40      cp      #40
    // 310c  2a6c31    ld      hl,(#316c)
    // 310f  3811      jr      c,#3122         ; (17)
    //-------------------------------
    uint8_t *hl = BAD_ROM_316c;
    if (h >= 0x40)
    {
        //-------------------------------
        // 3111  fe4c      cp      #4c
        // 3113  2a6e31    ld      hl,(#316e)
        // 3116  300a      jr      nc,#3122        ; (10)
        //-------------------------------
        hl = BAD_W_RAM_316e;
        if (h < 0x4c)
        {
            //-------------------------------
            // 3118  fe44      cp      #44
            // 311a  2a7031    ld      hl,(#3170)
            // 311d  3803      jr      c,#3122         ; (3)
            //-------------------------------
            hl = BAD_V_RAM_3170;
            if (h >= 0x44)
            {
                //-------------------------------
                // 311f  2a7231    ld      hl,(#3172)
                //-------------------------------
                hl = BAD_C_RAM_3172;
            }
        }
    }

    //-------------------------------
    // 3122  7d        ld      a,l
    // 3123  320442    ld      (#4204),a
    // 3126  7c        ld      a,h
    // 3127  326442    ld      (#4264),a
    //-------------------------------
    SCREEN[0x204] = hl[0];
    SCREEN[0x264] = hl[1];

    //-------------------------------
    // 312a  3a0050    ld      a,(#5000)
    // 312d  47        ld      b,a
    // 312e  3a4050    ld      a,(#5040)
    // 3131  b0        or      b
    // 3132  e601      and     #01
    // 3134  2011      jr      nz,#3147        ; (17)
    //-------------------------------
    if ((IN0_UP & IN1_UP) == 0)
    {
        //-------------------------------
        // 3136  c1        pop     bc
        // 3137  79        ld      a,c
        // 3138  e60f      and     #0f
        // 313a  47        ld      b,a
        // 313b  79        ld      a,c
        // 313c  e6f0      and     #f0
        // 313e  0f        rrca    
        // 313f  0f        rrca    
        // 3140  0f        rrca    
        // 3141  0f        rrca    
        // 3142  4f        ld      c,a
        // 3143  ed438541  ld      (#4185),bc
        //-------------------------------
        SCREEN[0x185] = checksum & 0xf;
        SCREEN[0x186] = checksum >> 4;
    }

    do
    {
        //-------------------------------
        // 3147  32c050    ld      (#50c0),a
        //-------------------------------
        kickWatchdog();
        //-------------------------------
        // 314a  3a4050    ld      a,(#5040)
        // 314d  e610      and     #10
        // 314f  28f6      jr      z,#3147         ; (-10)
        //-------------------------------
    }
    while (IN1_SERVICE == 0);

    //-------------------------------
    // 3151  c30b23    jp      #230b
    //-------------------------------
    initSelfTest_230b ();
}

    /* Stack stuff used in ram test */

    //-------------------------------
    // 3154  004c
    // 3156  0f04
    // 3158  004c
    // 315a  f004
    // 315c  0040
    // 315e  0f04
    // 3160  0040
    // 3162  f004
    // 3164  0044
    // 3166  0f04
    // 3168  0044
    // 316a  f004
    //-------------------------------

    // 	;; RAM Error data
    //-------------------------------
    // 316c  4f40				; O _ -> BAD   ROM 
    // 316e  4157				; A W -> BAD W RAM 
    // 3170  4156				; A V -> BAD V RAM 
    // 3172  4143				; A C -> BAD C RAM 
    //-------------------------------
/* Start the game ?!?!? */
void serviceModeOrStartGame_3174 (void)
{
    //-------------------------------
    // 3174  210650    ld      hl,#5006
    // 3177  3e01      ld      a,#01
    // 3179  77        ld      (hl),a		; Enable all
    // 317a  2d        dec     l	
    // 317b  20fc      jr      nz,#3179        ; (-4)
    //-------------------------------
    INTENABLE = 
    SOUNDENABLE = 
    AUXENABLE = 
    FLIPSCREEN = 
    P1START = 
    P2START = 
    COINLOCKOUT = 1;
    //-------------------------------
    // 317d  af        xor     a		; 0x00->a
    // 317e  320350    ld      (#5003),a	; unflip screen
    //-------------------------------
    FLIPSCREEN = 0;
    //-------------------------------
    // 3181  d604      sub     #04		; 0xfc->a
    // 3183  d300      out     (#00),a		; set vector
    //-------------------------------
    interruptVector (isr_008d);
    //-------------------------------
    // 3185  31c04f    ld      sp,#4fc0
    //-------------------------------

    do
    {
        //-------------------------------
        // 3188  32c050    ld      (#50c0),a	; Kick the dog
        //-------------------------------
        kickWatchdog();
        //-------------------------------
        // 318b  af        xor     a		; 0x00->a
        // 318c  32004e    ld      (#4e00),a
        //-------------------------------
        MAIN_STATE = MAIN_STATE_INIT;
        //-------------------------------
        // 318f  3c        inc     a		; 0x01->a
        // 3190  32014e    ld      (#4e01),a
        //-------------------------------
        RESET_STATE = RESET_STATE_DONE;
        //-------------------------------
        // 3193  320050    ld      (#5000),a	; enable interrupts
        // 3196  fb        ei			; enable interrupts
        //-------------------------------
        INTENABLE = 1;
        interruptEnable ();

        // 	;; Test mode sound checks
        //-------------------------------
        // 3197  3a0050    ld      a,(#5000)	
        // 319a  2f        cpl     
        // 319b  47        ld      b,a
        // 319c  e6e0      and     #e0		; Check coin/credit inputs
        // 319e  2805      jr      z,#31a5         ; (5)
        //-------------------------------
        if ((~IO_INPUT0 & INPUT_ANYCOIN) != 0)
        {
            //-------------------------------
            // 31a0  3e02      ld      a,#02
            // 31a2  329c4e    ld      (#4e9c),a	; Choose sound 2
            //-------------------------------
            CH1_SOUND_EFFECT->mask = 2;
        }

        //-------------------------------
        // 31a5  3a4050    ld      a,(#5040)
        // 31a8  2f        cpl     
        // 31a9  4f        ld      c,a
        // 31aa  e660      and     #60		; Check p1/p2 start 
        // 31ac  2805      jr      z,#31b3         ; (5)
        //-------------------------------
        if ((~IO_INPUT1 & INPUT_ANYSTART) != 0)
        {
            //-------------------------------
            // 31ae  3e01      ld      a,#01
            // 31b0  329c4e    ld      (#4e9c),a	; Choose sound 1
            //-------------------------------
            CH1_SOUND_EFFECT->mask = 1;
        }

        //-------------------------------
        // 31b3  78        ld      a,b
        // 31b4  b1        or      c
        // 31b5  e601      and     #01		; Check up
        // 31b7  2805      jr      z,#31be         ; (5)
        //-------------------------------
        if (IN0_UP == 0 || IN1_UP == 0)
        {
            //-------------------------------
            // 31b9  3e08      ld      a,#08
            // 31bb  32bc4e    ld      (#4ebc),a	; Choose sound 8
            //-------------------------------
            CH3_SOUND_EFFECT->mask = 8;
        }

        //-------------------------------
        // 31be  78        ld      a,b
        // 31bf  b1        or      c
        // 31c0  e602      and     #02		; Check left
        // 31c2  2805      jr      z,#31c9         ; (5)
        //-------------------------------
        if (IN0_LEFT == 0 || IN1_LEFT == 0)
        {
            //-------------------------------
            // 31c4  3e04      ld      a,#04
            // 31c6  32bc4e    ld      (#4ebc),a	; Choose sound 4
            //-------------------------------
            CH3_SOUND_EFFECT->mask = 4;
        }

        //-------------------------------
        // 31c9  78        ld      a,b
        // 31ca  b1        or      c
        // 31cb  e604      and     #04		; Check right
        // 31cd  2805      jr      z,#31d4         ; (5)
        //-------------------------------
        if (IN0_RIGHT == 0 || IN1_RIGHT == 0)
        {
            //-------------------------------
            // 31cf  3e10      ld      a,#10
            // 31d1  32bc4e    ld      (#4ebc),a	; Choose sound 16
            //-------------------------------
            CH3_SOUND_EFFECT->mask = 0x10;
        }

        //-------------------------------
        // 31d4  78        ld      a,b
        // 31d5  b1        or      c
        // 31d6  e608      and     #08		; Check down
        // 31d8  2805      jr      z,#31df         ; (5)
        //-------------------------------
        if (IN0_DOWN == 0 || IN1_DOWN == 0)
        {
            //-------------------------------
            // 31da  3e20      ld      a,#20
            // 31dc  32bc4e    ld      (#4ebc),a	; Choose sound 32
            //-------------------------------
            CH3_SOUND_EFFECT->mask = 0x20;
        }

        //-------------------------------
        // 31df  3a8050    ld      a,(#5080)	; Read dips
        // 31e2  e603      and     #03		; Mask coin info
        // 31e4  c625      add     a,#25
        // 31e6  47        ld      b,a
        // 31e7  cd5e2c    call    #2c5e		
        //-------------------------------
        displayMsg_2c5e (MSG_NOCOINS + DIP_SWITCH_COINS);

        //-------------------------------
        // 31ea  3a8050	ld      a,(#5080)	; Read dips
        // 31ed  0f        rrca    
        // 31ee  0f        rrca    
        // 31ef  0f        rrca    
        // 31f0  0f        rrca    
        // 31f1  e603      and     #03		; Mask extras
        // 31f3  fe03      cp      #03
        // 31f5  2008      jr      nz,#31ff        ; (8)
        //-------------------------------
        if (DIP_SWITCH_BONUS == 3)
        {
            //-------------------------------
            // 31f7  062a      ld      b,#2a
            // 31f9  cd5e2c    call    #2c5e
            // 31fc  c31c32    jp      #321c
            //-------------------------------
            displayMsg_2c5e (MSG_BONUS_NONE);
        }
        else
        {
            //-------------------------------
            // 31ff  07        rlca    
            // 3200  5f        ld      e,a
            // 3201  d5        push    de
            // 3202  062b      ld      b,#2b
            // 3204  cd5e2c    call    #2c5e
            //-------------------------------
            displayMsg_2c5e (MSG_BONUS);

            //-------------------------------
            // 3207  062e      ld      b,#2e
            // 3209  cd5e2c    call    #2c5e
            //-------------------------------
            displayMsg_2c5e (MSG_000);

            //-------------------------------
            // 320c  d1        pop     de
            // 320d  1600      ld      d,#00
            // 320f  21f932    ld      hl,#32f9
            // 3212  19        add     hl,de
            // 3213  7e        ld      a,(hl)
            // 3214  322a42    ld      (#422a),a
            //-------------------------------
            SCREEN[0x22a] = DATA_32f9[DIP_SWITCH_BONUS];
            //-------------------------------
            // 3217  23        inc     hl
            // 3218  7e        ld      a,(hl)
            // 3219  324a42    ld      (#424a),a
            //-------------------------------
            SCREEN[0x24a] = DATA_32f9[DIP_SWITCH_BONUS + 1];
        }
        //-------------------------------
        // 321c  3a8050    ld      a,(#5080)
        // 321f  0f        rrca    
        // 3220  0f        rrca    
        // 3221  e603      and     #03
        // 3223  c631      add     a,#31
        //-------------------------------
        uint8_t a = (DIP_SWITCH_LIVES) + 0x31;
        //-------------------------------
        // 3225  fe34      cp      #34
        // 3227  2001      jr      nz,#322a        ; (1)
        // 3229  3c        inc     a
        //-------------------------------

        /* DIP switches = 3 means 5-lives so add 1 */

        if (a == 0x34)
            a++;
        //-------------------------------
        // 322a  320c42    ld      (#420c),a
        //-------------------------------
        SCREEN[0x20c] = a;
        //-------------------------------
        // 322d  0629      ld      b,#29
        // 322f  cd5e2c    call    #2c5e
        //-------------------------------
        displayMsg_2c5e (MSG_PACMAN);
        //-------------------------------
        // 3232  3a4050    ld      a,(#5040)
        // 3235  07        rlca    
        // 3236  e601      and     #01
        // 3238  c62c      add     a,#2c
        // 323a  47        ld      b,a
        // 323b  cd5e2c    call    #2c5e
        //-------------------------------
        displayMsg_2c5e (((IN1_CABINET == 0) ? 1 : 0) + MSG_TABLE);
        printf ("ret from dsp msg TABLE\n");
        //-------------------------------
        // 323e  3a4050    ld      a,(#5040)
        // 3241  e610      and     #10
        // 3243  ca8831    jp      z,#3188
        //-------------------------------
        usleep (500000);  // Allow user to see test progress
    }
    while (IN1_SERVICE == 0);
    printf ("service loop done\n");

    //-------------------------------
    // 3246  af        xor     a
    // 3247  320050    ld      (#5000),a
    // 324a  f3        di      
    //-------------------------------
    INTENABLE = 0;
    interruptDisable ();
    //-------------------------------
    // 324b  210750    ld      hl,#5007
    // 324e  af        xor     a
    // 324f  77        ld      (hl),a
    // 3250  2d        dec     l
    // 3251  20fc      jr      nz,#324f        ; (-4)
    //-------------------------------
    INTENABLE = 
    SOUNDENABLE = 
    AUXENABLE = 
    FLIPSCREEN = 
    P1START = 
    P2START = 
    COINLOCKOUT = 
    COINCOUNTER = 0;

    //-------------------------------
    // 3253  31e23a    ld      sp,#3ae2
    // 3256  0603      ld      b,#03
    //-------------------------------
    uint16_t *stackData = DATA_3ae2;
    for (uint8_t b = 0; b < 3; b++)
    {
        //-------------------------------
        // 3258  d9        exx     
        // 3259  e1        pop     hl
        // 325a  d1        pop     de
        //-------------------------------
        uint16_t hl = *stackData++ - 0x4000; // 0x4002 in ROM which is video
        uint16_t de = *stackData++;
        do
        {
            //-------------------------------
            // 325b  32c050    ld      (#50c0),a
            // 325e  c1        pop     bc
            //-------------------------------
            kickWatchdog();
            uint16_t bc = *stackData++;
        printf ("%s hl = %4x de=%04x, bc=%04x\n", __func__, hl, de, bc);

            // for (int i = 0; i < (bc >> 8); i++)
            for (int i = 0; i < 0x10; i++)
            {
                //-------------------------------
                // 325f  3e3c      ld      a,#3c
                // 3261  77        ld      (hl),a
                // 3262  23        inc     hl
                //-------------------------------
                SCREEN[hl++] = 0x3c;
                //-------------------------------
                // 3263  72        ld      (hl),d
                // 3264  23        inc     hl
                // 3265  10f8      djnz    #325f           ; (-8)
                //-------------------------------
                SCREEN[hl++] = de >> 8;
            }

            //-------------------------------
            // 3267  3b        dec     sp
            // 3268  3b        dec     sp
            // 3269  c1        pop     bc
            //-------------------------------
            // stackData--;
            // bc = *stackData++;

            for (int i = 0; i < 0x10; i++)
            {
                //-------------------------------
                // 326a  71        ld      (hl),c
                // 326b  23        inc     hl
                //-------------------------------
                SCREEN[hl++] = bc & 0xff;
                //-------------------------------
                // 326c  3e3f      ld      a,#3f
                // 326e  77        ld      (hl),a
                // 326f  23        inc     hl
                // 3270  10f8      djnz    #326a           ; (-8)
                //-------------------------------
                SCREEN[hl++] = 0x3f;
            }

            //-------------------------------
            // 3272  3b        dec     sp
            // 3273  3b        dec     sp
            // 3274  1d        dec     e
            // 3275  c25b32    jp      nz,#325b
            //-------------------------------
            stackData--;
            de--;
        }
        while ((de & 0xff) > 0);

        //-------------------------------
        // 3278  f1        pop     af
        // 3279  d9        exx     
        // 327a  10dc      djnz    #3258           ; (-36)
        //-------------------------------
        stackData++;
    }

    //-------------------------------
    // 327c  31c04f    ld      sp,#4fc0
    // 327f  0608      ld      b,#08
    //-------------------------------
    for (uint8_t b = 0; b < 8; b++)
    {
        //-------------------------------
        // 3281  cded32    call    #32ed
        // 3284  10fb      djnz    #3281           ; (-5)
        //-------------------------------
        delay_32ed();
    }

    do
    {
        //-------------------------------
        // 3286  32c050    ld      (#50c0),a	; Kick the dog
        //-------------------------------
        kickWatchdog();
        //-------------------------------
        // 3289  3a4050    ld      a,(#5040)
        // 328c  e610      and     #10
        // 328e  28f6      jr      z,#3286         ; Wait until test switch is off
        //-------------------------------
    }
    while (!IN1_SERVICE);

    //-------------------------------
    // 3290  3a4050    ld      a,(#5040)	; Check P1/P2 start 
    // 3293  e660      and     #60
    // 3295  c24b23    jp      nz,#234b
    //-------------------------------
    if (P1START || P2START)
    {
        mainTaskLoop_234b();
        return;
    }
    //-------------------------------
    // 3298  0608      ld      b,#08
    //-------------------------------
    for (uint8_t b = 0; b < 8; b++)
    {
        //-------------------------------
        // 329a  cded32    call    #32ed
        // 329d  10fb      djnz    #329a           ; (-5)
        //-------------------------------
        delay_32ed();
    }
    //-------------------------------
    // 329f  3a4050    ld      a,(#5040)
    // 32a2  e610      and     #10
    // 32a4  c24b23    jp      nz,#234b
    //-------------------------------
    if (IN1_SERVICE != 0)
    {
        mainTaskLoop_234b();
        return;
    }

    //-------------------------------
    // 32a7  1e01      ld      e,#01
    //-------------------------------
    uint8_t e = 1;
    do
    {
        //-------------------------------
        // 32a9  0604      ld      b,#04
        //-------------------------------
        for (uint8_t b = 0; b < 4; b++)
        {
            do
            {
                //-------------------------------
                // 32ab  32c050    ld      (#50c0),a
                // 32ae  cded32    call    #32ed
                //-------------------------------
                kickWatchdog();
                delay_32ed();
                //-------------------------------
                // 32b1  3a0050    ld      a,(#5000)
                // 32b4  a3        and     e
                // 32b5  20f4      jr      nz,#32ab        ; (-12)
                //-------------------------------
            }
            while ((IO_INPUT0 & e) != 0);

            do
            {
                //-------------------------------
                // 32b7  cded32    call    #32ed
                // 32ba  32c050    ld      (#50c0),a
                //-------------------------------
                delay_32ed();
                kickWatchdog();
                //-------------------------------
                // 32bd  3a0050    ld      a,(#5000)
                // 32c0  eeff      xor     #ff
                // 32c2  20f3      jr      nz,#32b7        ; (-13)
                //-------------------------------
            }
            while (IO_INPUT0 == 0);
            //-------------------------------
            // 32c4  10e5      djnz    #32ab           ; (-27)
            //-------------------------------
        }
        //-------------------------------
        // 32c6  cb03      rlc     e
        // 32c8  7b        ld      a,e
        // 32c9  fe10      cp      #10
        // 32cb  daa932    jp      c,#32a9
        //-------------------------------
        e <<= 1;
    }
    while (e < 0x10);

    //-------------------------------
    // 32ce  210040    ld      hl,#4000
    // 32d1  0604      ld      b,#04
    //-------------------------------
    for (uint16_t hl = 0; hl < 0x400; hl++)
    {
        //-------------------------------
        // 32d3  3e40      ld      a,#40
        // 32d5  77        ld      (hl),a
        //-------------------------------
        SCREEN[hl] = 0x40;
        //-------------------------------
        // 32d6  2c        inc     l
        // 32d7  20fc      jr      nz,#32d5        ; (-4)
        // 32d9  24        inc     h
        // 32da  10f7      djnz    #32d3           ; (-9)
        //-------------------------------
    }

    //-------------------------------
    // 32dc  cdf43a    call    #3af4
    //-------------------------------
    madeByNamco_3af4();

    //-------------------------------
    // 32df  32c050    ld      (#50c0),a
    // 32e2  3a4050    ld      a,(#5040)
    // 32e5  e610      and     #10
    // 32e7  cadf32    jp      z,#32df
    //-------------------------------
    while (IN1_SERVICE == 0)
    {
        kickWatchdog();
    }

    //-------------------------------
    // 32ea  c34b23    jp      #234b
    //-------------------------------
    mainTaskLoop_234b ();
}

void delay_32ed (void)
{
    //-------------------------------
    // 32ed  32c050    ld      (#50c0),a
    //-------------------------------
    kickWatchdog();
    //-------------------------------
    // 32f0  210028    ld      hl,#2800
    // 32f3  2b        dec     hl
    // 32f4  7c        ld      a,h
    // 32f5  b5        or      l
    // 32f6  20fb      jr      nz,#32f3        ; (-5)
    // 32f8  c9        ret     
    //-------------------------------
    for (int hl = 0x2800; hl > 0; hl--)
        ;

    usleep (100000);
}
    /*  Bonus life points, 10, 15 or 20 (thousand) */

    //-------------------------------
    // 32f9  30 31 35 31 30 32
    //-------------------------------

    /*  Table of vectors is repeated to allow a loop to count forwards 4 times
     *  from any starting orientation */

    //-------------------------------
    // 32ff  00ff    // RIGHT dy = 0, dx=-1
    // 3301  0100    // DOWN  dy = 1, dx=0
    // 3303  0001    // LEFT  dy = 0, dx=1
    // 3305  ff00    // UP    dy = -1, dx=0
    // 3307  00ff    // RIGHT
    // 3309  0100    // DOWN
    // 330b  0001    // LEFT
    // 330d  ff00    // UP
    //-------------------------------

    /*  Table of move data.  Arranged as 6 x 42 (0x2a) groups.
     *
     *  The first 0x1c values are grouped as 32-bit values that are put
     *  through a shift register to control speed of movement.  So for example
     *  55555555 is move at half-speed, skipping a move every second frame.
     *
     *  Pacman has 4 move registers (normal, poweredup, difficulty1 and
     *  difficulty2) while ghosts have 3 (normal, edible and tunnel) */

    //-------------------------------
    // 330f  55 2a 55 2a // pacman normal - 14 of 32 = 44%
    //       55 55 55 55 // pacman powered - 16 of 32 = 50%
    //       55 2a 55 2a // difficulty2 - 14 if 32 = 44%
    //       52 4a a5 94 // difficulty1 - 13 of 32 = 41%
    //       25 25 25 25 // ghost normal - 12 of 32 = 37.5%
    //       22 22 22 22 // ghost edible - 8 of 32 = 25%
    //       01 01 01 01 // ghost tunnel - 4 of 32 = 12.5%
    //-------------------------------

    /*  Difficulty table - 0xe bytes */

    //-------------------------------
    //       58 02 08 07 60
    // 3330  09 10 0e 68 10 70 17 14  19
    //-------------------------------

    /*  Next move pattern */

    //-------------------------------
    // 3339                              52 4a a5 94 aa 2a 55
    // 3340  55 55 2a 55 2a 52 4a a5  94 92 24 25 49 48 24 22
    // 3350  91 01 01 01 01 00 00 00  00 00 00 00 00 00 00 00
    // 3360  00 00 00 
    // 3363           55 2a 55 2a 55  55 55 55 aa 2a 55 55 55
    // 3370  2a 55 2a 52 4a a5 94 48  24 22 91 21 44 44 08 58
    // 3380  02 34 08 d8 09 b4 0f 58  11 08 16 34 17
    // 338d                                          55 55 55
    // 3390  55 d5 6a d5 6a aa 6a 55  d5 55 55 55 55 aa 2a 55
    // 33a0  55 92 24 92 24 22 22 22  22 a4 01 54 06 f8 07 a8
    // 33b0  0c d4 0d 84 12 b0 13
    // 33b7                       d5  6a d5 6a d6 5a ad b5 d6
    // 33c0  5a ad b5 d5 6a d5 6a aa  6a 55 d5 92 24 25 49 48
    // 33d0  24 22 91 a4 01 54 06 f8  07 a8 0c d4 0d fe ff ff
    // 33e0  ff
    // 33e1     6d 6d 6d 6d 6d 6d 6d  6d b6 6d 6d db 6d 6d 6d
    // 33f0  6d d6 5a ad b5 25 25 25  25 92 24 92 24 2c 01 dc
    // 3400  05 08 07 b8 0b e4 0c fe  ff ff ff

    // 340b  d5 6a d5 6a // pacman normal - 18 of 32 = 56%
    // 340f  d5 6a d5 6a // pacman powered - 18
    // 3413  b6 6d 6d db // diff2 - 21
    // 3417  6d 6d 6d 6d // diff1 - 20
    // 341b  d6 5a ad b5 // ghost normal - 19
    // 341f  48 24 22 91 // ghost edible - 9
    // 3423  92 24 92 24 // ghost tunnel - 10

    // 3427  2c 01 dc 05 08 07 b8 0b  e4 0c fe ff ff ff
    //-------------------------------

    /*  Maze draw data */

    //-------------------------------
    // 3435                 40 fc d0  d2 d2 d2 d2 d2 d2 d2 d2
    // 3440  d4 fc fc fc da 

    // 3445                 02 dc fc  fc fc d0 d2 d2 d2 d2 d6
    // 3450  d8 d2 d2 d2 d2 d4 fc da  09 

    // 3559                              dc fc fc fc da 02 dc
    // 3460  fc fc fc da 05 de e4 05  dc fc da 02 e6 e8 ea 02
    // 3470  e6 ea 02 dc fc fc fc da  02 dc fc fc fc da 02 e6
    // 3480  ea 02 e7 eb 02 e6 ea 02  dc fc da 02 de fc e4 02
    // 3490  de e4 02 dc fc fc fc da  02 dc fc 

    // 349b                                    fc fc da 02 de
    // 34a0  e4 05 de e4 02 dc fc da  02 de fc e4 02 de e4 02
    // 34b0  dc fc fc fc da 02 dc fc  fc fc da 02 de f2 e8 e8
    // 34c0  ea 02 de e4 02 dc fc da  02 e7 e9 eb 02 e7 eb 02
    // 34d0  e7 d2 d2 d2 eb 02 e7 d2  d2 d2 eb 02 e7 

    // 34dd                                          e9 e9 e9
    // 34e0  eb 02 de e4 02 dc fc da  1b de e4 02 dc fc da 02
    // 34f0  e6 e8 f8 02 f6 e8 e8 e8  e8 e8 e8 f8 02 f6 e8 e8
    // 3500  e8 ea 02 e6 f8 02 f6 e8  e8 f4 e4 02 dc fc da 02
    // 3510  de fc e4 02 f7 e9 e9 f5  f3 e9 e9 f9 02 f7 e9 

    // 351f                                                e9
    // 3520  e9 eb 02 de e4 02 f7 e9  e9 f5 e4 02 dc fc da 02
    // 3530  de fc e4 05 de e4 0b de  e4 05 de e4 02 dc fc da
    // 3540  02 de fc e4 02 e6 ea 02  de e4 02 ec d3 d3 d3 ee
    // 3550  02 e6 ea 02 de e4 02 e6  ea 02 de e4 02 dc fc da
    // 3560  02 

    // 3561     e7 e9 eb 02 de e4 02  e7 eb 02 dc fc fc fc da
    // 3570  02 de e4 02 e7 eb 02 de  e4 02 e7 eb 02 dc fc da
    // 3580  06 de e4 05 f0 fc fc fc  da 02 de e4 05 de e4 05
    // 3590  dc fc fa e8 e8 e8 ea 02  de f2 e8 e8 ea 02 ce fc
    // 35a0  fc fc da 

    // 35a3           02 de f2 e8 e8  ea 02 de f2 e8 e8 ea 02
    // 35b0  dc 00 

    // 35b2        00 00 00
    //-------------------------------

    /*  Pill draw data  - 0x1e x 8 = 0xf0 entries */

    //-------------------------------
    // 35b5                 62 01 02  01 01 01 01 0c 01 01 04
    // 35c0  01 01 01 04 04 03 0c 03  03 03 04 04 03 0c 03 01
    // 35d0  01 01 03 04 04 03 0c 06  03 04 04 03 0c 06 03 04
    // 35e0  01 01 01 01 01 01 01 01  01 01 01 01 01 01 01 01
    // 35f0  01 01 01 01 01 01 01 01  01 03 04 04 0f 03 06 04
    // 3600  04 0f 03 06 04 04 01 01  01 0c 03 01 01 01 03 04
    // 3610  04 03 0c 03 03 03 04 04  03 0c 03 03 03 04 01 01
    // 3620  01 01 03 0c 01 01 01 03  01 01 01 08 18 08 18 04
    // 3630  01 01 01 01 03 0c 01 01  01 03 01 01 01 04 04 03
    // 3640  0c 03 03 03 04 04 03 0c  03 03 03 04 04 01 01 01
    // 3650  0c 03 01 01 01 03 04 04  0f 03 06 04 04 0f 03 06
    // 3660  04 01 01 01 01 01 01 01  01 01 01 01 01 01 01 01
    // 3670  01 01 01 01 01 01 01 01  01 01 03 04 04 03 0c 06
    // 3680  03 04 04 03 0c 06 03 04  04 03 0c 03 01 01 01 03
    // 3690  04 04 03 0c 03 03 03 04  01 02 01 01 01 01 0c 01
    // 36a0  01 04 01 01 01                                  
    //-------------------------------

    // 	;; Indirect Lookup table for 2c5e routine  (0x48 entries) 
    //-------------------------------
    // 36a5  1337			; 0         HIGH SCORE
    // 36a7  2337			; 1	    CREDIT   
    // 36a9  3237			; 2	    FREE PLAY
    // 36ab  4137			; 3         PLAYER ONE
    // 36ad  5a37			; 4         PLAYER TWO
    // 36af  6a37			; 5         GAME  OVER
    // 36b1  7a37			; 6         READY?
    // 36b3  8637			; 7	    PUSH START BUTTON
    // 36b5  9d37			; 8         1 PLAYER ONLY 
    // 36b7  b137			; 9         1 OR 2 PLAYERS
    // 36b9  003d			; a  c837   BONUS PAC-MAN FOR   000 Pts
    // 36bb  213d			; b  e937   @ 1980 MIDWAY MFG.CO.
    // 36bd  fd37			; c         CHARACTER / NICKNAME
    // 36bf  673d			; d  1738   "BLINKY" 
    // 36c1  e33d			; e  2538   "BBBBBBBB"
    // 36c3  863d			; f  3238   "PINKY"  
    // 36c5  023e			; 10 3f38   "DDDDDDDD"
    // 36c7  4c38			; 11        . 10 Pts
    // 36c9  5a38			; 12        o 50 Pts
    // 36cb  3c3d			; 13 6838   @ 1980 MIDWAY MFG.CO.
    // 36cd  573d			; 14 7538   -SHADOW
    // 36cf  d33d			; 15 8638   "AAAAAAAA"
    // 36d1  763d			; 16 9838   -SPEEDY
    // 36d3  f23d			; 17 aa38   "CCCCCCCC"
    // 36d5  0100			; 18 
    // 36d7  0200			; 19
    // 36d9  0300			; 1a
    // 36db  bc38			; 1b ce38    100
    // 36dd  c438			; 1c d838    300
    // 36df  ce38			; 1d e238    500
    // 36e1  d838			; 1e ec38    700
    // 36e3  e238			; 1f f638    1000
    // 36e5  ec38			; 20 0039    2000
    // 36e7  f638			; 21 0039    3000
    // 36e9  0039			; 22 0039    5000
    // 36eb  0a39                       ; 23         MEMORY  OK
    // 36ed  1a39			; 24         BAD    R M
    // 36ef  6f39			; 25         FREE  PLAY       
    // 36f1  2a39                       ; 26         1 COIN  1 CREDIT 
    // 36f3  5839			; 27         1 COIN  2 CREDITS
    // 36f5  4139			; 28         2 COINS 1 CREDIT 
    // 36f7  4f3e			; 29 a339    PAC-MAN
    // 36f8  8639			; 2a	     BONUS  NONE
    // 36fb  9739			; 2b         BONUS
    // 36fd  b039			; 2c         TABLE  
    // 36ff  bd39			; 2d         UPRIGHT
    // 3701  ca39			; 2e	     000
    // 3703  a53d			; 2f d339    "INKY"    
    // 3705  213e			; 30 e139    "FFFFFFFF"
    // 3707  c43d			; 31 ee39    "CLYDE"  
    // 3709  403e			; 32 fc39    "HHHHHHHH"
    // 370b  953d			; 33 093a    -BASHFUL  
    // 370d  113e			; 34 1a3a    "EEEEEEEE"
    // 3711  b43d			; 35 2c3a    -POKEY   
    // 3711  303e			; 36 3d3a    "GGGGGGGG"
    //-------------------------------

    /*  Each msg is the same format.  The message number is or'd with #80 to
     *  indicate the message is to be erased.  With n being the length of the msg:
    *
     *  byte 0..1  : Address on the screen the message should be printed.  Or'd
     *              with #8000 means msg is on top or bottom 2 lines of screen.
     *  bytes 2..n+1 : The text of the msg itself
     *  byte  n+2    : 0x2f - end of text
     *  byte  n+3    : 1st colour.  First byte or'd with #80 means all the text is the
     *  same colour (single byte), otherwise it is a string of colours the same length as the
     *  message.
     *  byte  n+4    : 0x2f - end of 1st colour info
     *  byte  n+5    : 2nd colour.  Used when erasing a msg.  Again, if first
     *  byte is or'd with #80 then it is a single byte, otherwise it is a
     *  string. */

    /*  NOTE : code for the msg table is disabled.  I have originally intended
     *  to a build a table that would be compiled in but then opted to just
     *  reference the ROM code instead. */

    #if 0
    uint8_t *msgTable_36a5[] = 
    {
        // 	;; 36a5 Table Entry 0
        // 3713
        {
            0xd4, 0x83,
            'H','I','G','H','@','S','C','O','R','E',
            0x2f, 0x8f, 0x2f, 0x80 
        },
        // 371f  2f 8f 2f 80

        // 	;; 36a5 Table Entry 1
        // 3723  3b 80
        {
            0x3b, 0x80
            'C','R','E','D','I','T','@','@','@',
            0x2f, 0x8f, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 2
        // 3732  3b 80
        {
            0x3b, 0x80
            'F','R','E','E','@','P','L','A','Y', 
            0x2f, 0x8f, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 3
        // 3741  8c 02
        {
            0x8c, 0x02
            'P','L','A','Y','E','R','@','O','N','E', 
            0x2f, 0x85, 
            0x2f, 0x10, 0x10, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x10, 0x10
        },

        // 	;; 36a5 Table Entry 4
        // 375a  8c 02
        {
            0x8c, 0x02
            'P','L','A','Y','E','R','@','T','W','O',
            0x2f, 0x85, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 5
        // 376a  92 02
        {
            0x92, 0x02
            'G','A','M','E','@','@','O','V','E','R',
            0x2f, 0x81, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 6
        // 377a  52 02
        {
            0x52, 0x02
            'R','E','A','D','Y','?', 
            0x2f, 0x89, 0x2f, 0x90
        },

        // 	;; 36a5 Table Entry 7
        // 3786  ee 02
        {
            0xee, 0x02
            'P','U','S','H','@','S','T','A','R','T','@',
            'B','U','T','T','O','N',
            0x2f, 0x87, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 8
        // 379d  b2 02
        {
            0xb2, 0x02
            "1@PLAYER@ONLY "
            0x2f, 0x85, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 9
        // 37b1  b2 02
        {
            0xb2, 0x02
            "1@OR@2@PLAYERS"
            0x2f, 0x85, 0x00, 0x2f 00 80
        },

        // 	;; 36a5 Table Entry ??
        // 37c7  00 96 03
        {
            0x00, 0x96 03
            "BONUS@PUCKMAN@FOR@@@000@]^_"
            0x2f, 0x8e, 0x2f, 0x80
        },

        // 37e9  ba 02
        {
            0xba, 0x02
            '\\','@','(',')','*','+',',','-','.','@','1','9','8','0', 
            0x2f, 0x83, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry c
        // 37fd  c3 02
        {
            0xc3, 0x02
            'C','H','A','R','A','C','T','E','R','@','/',
            '@','N','I','C','K','N','A','M','E',
            0x2f, 0x8f, 0x2f, 0x80
        },

        // 3817  65 01 
        {
            0x65, 0x01 
            '&','A','K','A','B','E','I','&',
            0x2f, 0x81, 0x2f, 0x80
        },

        // 3825  45 01 
        {
            0x45, 0x01 
            '&','M','A','C','K','Y','&',
            0x2f, 0x81, 0x2f, 0x80
        },

        // 3832  48 01 
        {
            0x48, 0x01 
            '&','P','I','N','K','Y','&', 
            0x2f, 0x83, 0x2f, 0x80
        },

        // 383f  48 01 
        {
            0x48, 0x01 
           '&','M','I','C','K','Y','&', 
            0x2f, 0x83, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 11
        // 384c  76 02
        {
            0x76, 0x02
            0x10, '@','1','0','@',']','^','_',
            0x2f, 0x9f, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 12
        // 385a  78 02
        {
            0x78, 0x02
        // 385c  14
            0x14, '@','5','0','@',']','^','_',
            0x2f, 0x9f, 0x2f, 0x80
        },

        // 3868  5d 02
        {
            0x5d, 0x02
            '(',')','*','+',',','-','.', 
            0x2f, 0x83, 0x2f, 0x80 
        },

        // 3875  c5 02
            '@','O','I','K','A','K','E',';',';',';',';', 
            0x2f, 0x81, 0x2f, 0x80 
        },

        // 3886  c5 02 
        {
            0xc5, 0x02 
            '@','U','R','C','H','I','N',';',';',';',';',';',
            0x2f, 0x81, 0x2f, 0x80
        },

        // 3898  c8 02
            '@','M','A','C','H','I','B','U','S','E',';',';',
        // 38a6  2f 83 2f 80 

        // 38aa  c8 02
        {
            0xc8, 0x02
            '@','B','O','M','P',';',';',';',';',';',';',';',
            0x2f, 0x83, 0x2f, 0x80
        },

        // 	;; 36a5 Table Entry 21
        // 38bc  12 02
        {
            0x12, 0x02
            0x81, 0x85,
            0x2f, 0x83, 0x2f, 0x90
        },

        // 	;; 36a5 Table Entry 22
        // 38c4  32 02
        {
            0x32, 0x02
            '@', 0x82, 0x85, '@'
            0x2f, 0x83, 0x2f, 0x90
        },

        // 	;; 36a5 Table Entry 23
        // 38ce  32 02				; OFFSET 
        {
            0x32, 0x02				; OFFSET 
            '@', 0x83, 0x85, '@'
            0x2f, 0x83, 0x2f, 0x90 
        },

        // 	;; 36a5 Table Entry 24
        // 38d8  32 02
        {
            0x32, 0x02
            '@', 0x84, 0x85, '@'
            0x2f, 0x83, 0x2f, 0x90 
        },

        // 38e2  32 02
        {
            0x32, 0x02
            '@', 0x86, 0x8d, '@'
            0x2f, 0x83, 0x2f, 0x90 
        },

        // 38ec  32 02
        {
            0x32, 0x02
            0x87, 0x88, 0x8d, 0x8e 
            0x2f, 0x83, 0x2f, 0x90 
        },

        // 38f6  32 02
        {
            0x32, 0x02
            0x89, 0x8a, 0x8d, 0x8e 
            0x2f, 0x83, 0x2f, 0x90 
        },

        // 3900  32 02
        {
            0x32, 0x02
            0x8b, 0x8c, 0x8d, 0x8e 
            0x2f, 0x83, 0x2f, 0x90 
        },

        // 	;; 36a5 Table Entry 23
        // 390a  04 03 
        {
            0x04, 0x03 
            'M','E','M','O','R','Y','@','@','O','K', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 24
        // 391a  04 03 
        {
            0x04, 0x03 
            'B','A','D','@','@','@','@','R','@','M', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 26
        // 392a  08 03 
        {
            0x08, 0x03 
            '1','@','C','O','I','N','@','@','1','@','C','R','E','D',
            'I','T','@', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 28
        // 3941  08 03 
        {
            0x08, 0x03 
            '2','@','C','O','I','N','S','@','1','@','C','R','E','D',
            'I','T','@', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 27
        // 3958  08 03 
        {
            0x08, 0x03 
            '1','@','C','O','I','N','@','@','2','@','C','R','E','D',
            'I','T','S', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 25
        // 396f  08 03 
        {
            0x08, 0x03 
            'F','R','E','E','@','@','P','L','A','Y','@','@','@','@',
            '@','@','@', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 2a
        // 3986  0a 03 
        {
            0x0a, 0x03 
            'B','O','N','U','S','@','@','N','O','N','E', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 2b
        // 3997  0a 03 
        {
            0x0a, 0x03 
            'B','O','N','U','S','@', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 39a3  0c 03 
        {
            0x0c, 0x03 
            'P','U','C','K','M','A','N', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 2c
        // 39b0  0e 03
        {
            0x0e, 0x03
            'T','A','B','L','E','@','@', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 2d
        // 39bd  0e 03
        {
            0x0e, 0x03
            'U','P','R','I','G','H','T', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry 2e
        // 39ca  0a 02 
        {
            0x0a, 0x02 
            '0','0','0', 
            0x2f, 0x8f, 0x2f, 0x80 
        },

        // 	;; 36a5 Table Entry
        // 39d3  6b 01 
        {
            0x6b, 0x01 
            '&','A','O','S','U','K','E','&', 
            0x2f, 0x85, 0x2f, 0x80 
        },

        // 39e1  4b 01
        {
            0x4b, 0x01
            '&','M','U','C','K','Y','&', 
            0x2f, 0x85, 0x2f, 0x80 
        },
        // 39ee  6e 01
        {
            0x6e, 0x01
            '&','G','U','Z','U','T','A','&', 
            0x2f, 0x87, 0x2f, 0x80 
        },

        // 39fc  4e 01
        {
            0x4e, 0x01
            '&','M','O','C','K','Y','&', 
            0x2f, 0x87, 0x2f, 0x80 
        },

        // 3a09  cb 02
        {
            0xcb, 0x02
            '@','K','I','M','A','G','U','R','E',';',';', 
            0x2f, 0x85, 0x2f, 0x80 
        },

        // 3a1a  cb 02
        {
            0xcb, 0x02
            '@','S','T','Y','L','I','S','T',';',';',';',';', 
            0x2f, 0x85, 0x2f, 0x80 
        },

        // 3a2c  ce 02
        {
            0xce, 0x02
            '@','O','T','O','B','O','K','E',';',';',';', 
            0x2f, 0x87, 0x2f, 0x80 
        },

        // 3a3d  ce 02
        {
            0xce, 0x02
            '@','C','R','Y','B','A','B','Y',';',';',';',';', 
            0x2f, 0x87, 0x2f, 0x80 
        },
        #endif

    /*  Apparently this is the data for the "made by namco" easter egg.  The
     *  data draws the msg using the same format as the maze draw */

    //-------------------------------
    // 3a4f                                                01 
    // 3a50  01 03 01 01 01 03 02 02  02 01 01 01 01 02 04 04 
    // 3a60  04 06 02 02 02 02 04 02  04 04 04 06 02 02 02 02 
    // 3a70  01 01 01 01 02 04 04 04  06 02 02 02 02 06 04 05 
    // 3a80  01 01 03 01 01 01 04 01  01 01 03 01 01 04 01 01 
    // 3a90  01 6c 05 01 01 01 18 04  04 18 05 01 01 01 17 02 
    // 3aa0  03 04 16 04 03 01 01 01  76 01 01 01 01 03 01 01 
    // 3ab0  01 02 04 02 04 0e 02 04  02 04 02 04 0b 01 01 01 
    // 3ac0  02 04 02 01 01 01 01 02  02 02 0e 02 04 02 04 02 
    // 3ad0  01 02 01 0a 01 01 01 01  03 01 01 01 03 01 01 03 
    // 3ae0  04 00
    //-------------------------------

    /*  Test stack used in 325d */
    //-------------------------------
    // 3ae2  02 40 
    // 3ae4  01 3e
    // 3ae6  3d 10
    // 3ae8  40 40
    // 3aea  0e 3d
    // 3aec  3e 10
    // 3aee  c2 43
    // 3af0  01 3e
    // 3ad2  3d 10
    //-------------------------------

/*  draw easter egg */
void madeByNamco_3af4 (void)
{
    //-------------------------------
    // 3af4  21a240    ld      hl,#40a2
    // 3af7  114f3a    ld      de,#3a4f
    //-------------------------------
    uint8_t *hl = &SCREEN[0xa2];
    uint8_t *de = &ROM[0x3a4f];

    while (1)
    {
        //-------------------------------
        // 3afa  3614      ld      (hl),#14
        // 3afc  1a        ld      a,(de)
        // 3afd  a7        and     a
        // 3afe  c8        ret     z
        //-------------------------------
        *hl = 0x14;
        uint8_t a = *de;
        if (*de == 0)
            return;
        //-------------------------------
        // 3aff  13        inc     de
        // 3b00  85        add     a,l
        // 3b01  6f        ld      l,a
        // 3b02  d2fa3a    jp      nc,#3afa
        // 3b05  24        inc     h
        // 3b06  18f2      jr      #3afa           ; (-14)
        //-------------------------------
        de++;
        hl += a;
    }
}

    /*  Fruit table */

    //-------------------------------
    // 3b08  90 14   ; cherry
    // 3b0a  94 0F   ; strawberry
    // 3b0c  98 15   ; 1st orange
    // 3b0e  98 15   ; 2nd orange
    // 3b10  A0 14   ; 1st apple
    // 3b12  A0 14   ; 2nd apple
    // 3b14  A4 17   ; 1st pineapple
    // 3b16  A4 17   ; 2nd pineapple
    // 3b18  A8 09   ; 1st galaxian
    // 3b1a  A8 09   ; 2nd galaxian
    // 3b1c  9C 16   ; 1st bell
    // 3b1e  9C 16   ; 2nd bell
    // 3b20  AC 16   ; 1st key
    // 3b22  AC 16   ; 2nd key
    // 3b24  AC 16   ; 3rd key
    // 3b26  AC 16   ; 4th key
    // 3b28  AC 16   ; 5th key
    // 3b2a  AC 16   ; 6th key
    // 3b2c  AC 16   ; 7th key
    // 3b2e  AC 16   ; 8th key
    //-------------------------------

    /*  Sound effects.  16 groups of 8 bytes.  bytes are:
     *   0 - select  high nybble is frequency scale (<<) for effects
     *   1 - tbd4
     *   2 - freq delta 
     *   3 - offset Lo
     *   4 - offset Hi
     *   5 - tbd8
     *   6 - initial volume (0 to f) or'd with effect type << 4
     *   7 - volume delta
     */

    /*  CH1 effects */
    //-------------------------------
    // 3b30  73 20 00 0c 00 0a 1f 00  72 20 fb 87 00 02 0f 00
    //-------------------------------

    /*  CH2 effects */
    //-------------------------------
    // 3b40  36 20 04 8c 00 00 06 00  36 28 05 8b 00 00 06 00
    // 3b50  36 30 06 8a 00 00 06 00  36 3c 07 89 00 00 06 00
    // 3b60  36 48 08 88 00 00 06 00  24 00 06 08 00 00 0a 00
    // 3b70  40 70 fa 10 00 00 0a 00  70 04 00 00 00 00 08 00
    //-------------------------------

    /*  CH3 effects */
    //-------------------------------
    // 3b80  42 18 fd 06 00 01 0c 00  42 04 03 06 00 01 0c 00
    // 3b90  56 0c ff 8c 00 02 0f 00  05 00 02 20 00 01 0c 00
    // 3ba0  41 20 ff 86 fe 1c 0f ff  70 00 01 0c 00 01 08 00
    //-------------------------------

    /*  Powers of 2 */
    //-------------------------------
    // 3bb0  01 02 04 08 10 20 40 80
    //-------------------------------

    /*  TODO frequency table */
    //-------------------------------
    // 3bb8                           00 57 5c 61 67 6d 74 7b
    // 3bc0  82 8a 92 9a a3 ad b8 c3
    //-------------------------------

    /*  TODO song tables */
    //-------------------------------
    // 3bc8                           d4 3b f3 3b 58 3c 95 3c
    // 3bd0  de 3c df 3c 
    //-------------------------------


    /*  f0 = indrection, load offset from ptr
        f1 = next byte is "selected"
        f2 = next byte is "frequencyInitial"
        f3 = next byte is "volumeInitial"
        f4 = next byte is "type"
        ff = sound effect done

        1f = (&1f) set dir
             (&e0) duration (pow 2)
             (&0f) freq table ix


     */

    //-------------------------------
    // 3bd4  f1 02 f2 03 f3 0f f4 01 82 70 69 82

    // 3be0  70 69 83 70 6a 83 70 6a  82 70 69 82 70 69 89 8b
    // 3bf0  8d 8e ff

    // 3bf3           f1 02 f2 03 f3  0f f4 01 67 50 30 47 30
    // 3c00  67 50 30 47 30 67 50 30  47 30 4b 10 4c 10 4d 10
    // 3c10  4e 10 67 50 30 47 30 67  50 30 47 30 67 50 30 47
    // 3c20  30 4b 10 4c 10 4d 10 4e  10 67 50 30 47 30 67 50
    // 3c30  30 47 30 67 50 30 47 30  4b 10 4c 10 4d 10 4e 10
    // 3c40  77 20 4e 10 4d 10 4c 10  4a 10 47 10 46 10 65 30
    // 3c50  66 30 67 40 70 f0 fb 3b

    // 3c58                           f1 00 f2 02 f3 0f f4 00
    // 3c60  42 50 4e 50 49 50 46 50  4e 49 70 66 70 43 50 4f
    // 3c70  50 4a 50 47 50 4f 4a 70  67 70 42 50 4e 50 49 50
    // 3c80  46 50 4e 49 70 66 70 45  46 47 50 47 48 49 50 49
    // 3c90  4a 4b 50 6e ff

    // 3c95                 f1 01 f2  01 f3 0f f4 00 26 67 26
    // 3ca0  67 26 67 23 44 42 47 30  67 2a 8b 70 26 67 26 67
    // 3cb0  26 67 23 44 42 47 30 67  23 84 70 26 67 26 67 26
    // 3cc0  67 23 44 42 47 30 67 29  6a 2b 6c 30 2c 6d 40 2b
    // 3cd0  6c 29 6a 67 20 29 6a 40  26 87 70 f0 9d 3c

    // 3cde  00
    // 3cdf  00
    // 3ce0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    //-------------------------------

    #if 0
    // 	;; 36a5 Table Entry a
    // 3d00  96 03
    {
        0x96, 0x03
        'B','O','N','U','S','@','P','A','C',';','M','A','N','@','F',
        'O','R','@','@','@','0','0','0','@',']','^','_', 
        0x2f, 0x8e, 0x2f, 0x80
    },

    // 	;; 36a5 Table Entry b
    // 3d21  3a 03
    {
        0x3a, 0x03
        0x5c,'@','1','9','8','0','@','M','I','D','W','A','Y','@',
        'M','F','G','%','C','O','%', 
        0x2f, 0x83, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 13
    // 3d3c  3d 03 
    {
        0x3d, 0x03 
        0x5c,'@','1','9','8','0','@','M','I','D','W','A','Y','@',
        'M','F','G','%','C','O','%',
        0x2f, 0x83, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 14
    // 3d57  c5 02 
    {
        0xc5, 0x02 
        ';','S','H','A','D','O','W','@','@','@',
        0x2f, 0x81, 0x2f, 0x80
    },

    // 	;; 36a5 Table Entry d
    // 3d67  65 01 
    {
        0x65, 0x01 
        '&','B','L','I','N','K','Y','&','@', 
        0x2f, 0x81, 0x2f, 0x80 
    },
    // 
    // 	;; 36a5 Table Entry 16
    // 3d76  c8 02
    {
        0xc8, 0x02
        ';','S','P','E','E','D','Y','@','@','@', 
        0x2f, 0x83, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry f
    // 3d86  68 01 
    {
        0x68, 0x01 
        '&','P','I','N','K','Y','&','@','@', 
        0x2f, 0x83, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 33
    // 3d95  cb 02 
    {
        0xcb, 0x02 
        ';','B','A','S','H','F','U','L','@','@', 
        0x2f, 0x85, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 2f
    // 3da5  6b 01 
    {
        0x6b, 0x01 
        '&','I','N','K','Y','&','@','@','@', 
        0x2f, 0x85, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 35
    // 3db4  ce 02 
    {
        0xce, 0x02 
        ';','P','O','K','E','Y','@','@','@','@', 
        0x2f, 0x87, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 31
    // 3dc4  6e 01
    {
        0x6e, 0x01
        '&','C','L','Y','D','E','&','@','@', 
        0x2f, 0x87, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 15
    // 3dd3  c5 02
    {
        0xc5, 0x02
        ';','A','A','A','A','A','A','A','A',';', 
        0x2f, 0x81, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry e
    // 3de3  65 01
    {
        0x65, 0x01
        '&','B','B','B','B','B','B','B','&', 
        0x2f, 0x81, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 17
    // 3df2  c8 02
    {
        0xc8, 0x02
        ';','C','C','C','C','C','C','C','C',';', 
        0x2f, 0x83, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 10
    // 3e02  68 01 
    {
        0x68, 0x01 
        '&','D','D','D','D','D','D','D','&', 
        0x2f, 0x83, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 34
    // 3e11  cb 02 
    {
        0xcb, 0x02 
        ';','E','E','E','E','E','E','E','E',';', 
        0x2f, 0x85, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 30
    // 3e21  6b 01
    {
        0x6b, 0x01
        '&','F','F','F','F','F','F','F','&', 
        0x2f, 0x85, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 36
    // 3e30  ce 02
    {
        0xce, 0x02
        ';','G','G','G','G','G','G','G','G',';', 
        0x2f, 0x87, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 32
    // 3e40  6e 01
    {
        0x6e, 0x01
        '&','H','H','H','H','H','H','H','&', 
        0x2f, 0x87, 0x2f, 0x80
    },
    // 
    // 	;; 36a5 Table Entry 29
    // 3e4f  0c 03
    {
        0x0c, 0x03
        'P','A','C',';','M','A','N', 
        0x2f, 0x8f, 0x2f, 0x80
    },
    #endif

    //-------------------------------
    // 3e5c                                       00 00 00 00
    // 3e70  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3e80  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3e90  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3ea0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3eb0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3ec0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3ed0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3ee0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3ef0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f00  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f10  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f20  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f30  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f40  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f50  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f60  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f70  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f80  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3f90  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3fa0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3fb0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3fc0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3fd0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3fe0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
    // 3ff0  00 00 00 00 00 00 00 00  00 00                  
    //-------------------------------

    //-------------------------------
    // 3ffa  0030				; Interrupt Vector 3000 
    // 3ffc  8d00				; Interrupt Vector 008d 
    //-------------------------------

    //-------------------------------
    // 3ffe  75 73 ; Checksum data for 4th ROM
    //-------------------------------
