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
 *  Constant definitions to replace address values and other consts 
 */
#define ISRTASK_INC_LEVEL_STATE        0
#define ISRTASK_INC_MAIN_SUB2        1
#define ISRTASK_INC_INTRO_STATE        2
#define ISRTASK_INC_KILLED_STATE        3
#define ISRTASK_RESET_FRUIT     4
#define ISRTASK_DISPLAY_READY         6
#define ISRTASK_INC_SCENE1_STATE         7
#define ISRTASK_INC_SCENE2_STATE         8
#define ISRTASK_INC_SCENE3_STATE         9

#define TASK_CLEAR_SCREEN       0x00
#define TASK_MAZE_COLOURS       0x01
#define TASK_DRAW_MAZE         0x02
#define TASK_DRAW_PILLS         0x03
#define TASK_INIT_POSITIONS         0x04
#define TASK_BLINKY_SUBSTATE 0x05
#define TASK_CLEAR_COLOUR         0x06
#define TASK_RESET_GAME_STATE         0x07
#define TASK_SCATTER_CHASE_BLINKY 0x08
#define TASK_SCATTER_CHASE_PINKY 0x09
#define TASK_SCATTER_CHASE_INKY 0x0a
#define TASK_SCATTER_CHASE_CLYDE 0x0b
#define TASK_HOME_RANDOM_BLINKY 0x0c
#define TASK_HOME_RANDOM_PINKY 0x0d
#define TASK_HOME_RANDOM_INKY 0x0e
#define TASK_HOME_RANDOM_CLYDE 0x0f
#define TASK_SETUP_GHOST_TIMERS         0x10
#define TASK_CLEAR_GHOST_STATE          0x11
#define TASK_CLEAR_PILLS                0x12
#define TASK_CLEAR_PILLS_SCREEN         0x13
#define TASK_CONFIGURE_GAME             0x14
#define TASK_UPDATE_PILLS               0x15
#define TASK_PACMAN_ORIENT              0x17
#define TASK_CLEAR_SCORES               0x18
#define TASK_ADD_TO_SCORE               0x19
#define TASK_BOTTOM_COLOUR              0x1a
#define TASK_FRUIT_HISTORY              0x1b
#define TASK_DISPLAY_MSG 0x1c
#define TASK_DISPLAY_CREDITS 0x1d
#define TASK_RESET_POSITIONS 0x1e
#define TASK_SHOW_BONUS_LIFE_SCORE 0x1f

#define MSG_HIGHSCORE           0
#define MSG_CREDIT              1
#define MSG_FREEPLAY            2
#define MSG_PLAYER1             3
#define MSG_PLAYER2             4
#define MSG_GAMEOVER            5
#define MSG_READY               6
#define MSG_PUSHSTART           7
#define MSG_ONEPLAYER           8
#define MSG_ONEORTWOPLAYER      9
#define MSG_BONUS_PACMAN        0x0a
#define MSG_COPYRIGHT1          0x0b
#define MSG_NICKNAME            0x0c
#define MSG_10PTS               0x11
#define MSG_50PTS               0x12
#define MSG_COPYRIGHT2          0x0b
#define MSG_100PTS              0x1b
#define MSG_5000PTS             0x22
#define MSG_BADROMRAM           0x24
#define MSG_NOCOINS             0x25
#define MSG_PACMAN              0x29
#define MSG_BONUS_NONE          0x2a
#define MSG_BONUS               0x2b
#define MSG_TABLE               0x2c
#define MSG_000                 0x2e

#define CHAR_PILL       0x10
#define CHAR_POWERUP    0x14
#define CHAR_SPACE      0x40
#define CHAR_MAZE_MASK  0xc0  // Maze characters are 0xc0-0xff

#define GHOST_STATE_ALIVE               0
#define GHOST_STATE_DEAD                1 // eyes
#define GHOST_STATE_ENTER_HOUSE         2
#define GHOST_STATE_HOUSE_MOVE          3 // move left (inky) or right (clyde)

#define GHOST_BLINKY    1
#define GHOST_PINKY     2
#define GHOST_INKY      3
#define GHOST_CLYDE     4
#define DEMO_PACMAN     5

#define ORIENT_RIGHT    0
#define ORIENT_DOWN     1
#define ORIENT_LEFT     2
#define ORIENT_UP       3

#define ORIENT_VERTICAL 1  // mask, 1 and 3 are vertical, 0 and 2 are horizontal

#define IMG_MIRROR 0x80
#define IMG_INVERT 0x40

#define SUBSTATE_IN_HOUSE          0
#define SUBSTATE_CHASE             1
#define SUBSTATE_LEAVING_HOUSE     2
#define SUBSTATE_HOUSE_MOVE        3

#define MAIN_STATE_INIT         0
#define MAIN_STATE_DEMO         1
#define MAIN_STATE_CREDIT       2
#define MAIN_STATE_PLAY         3

#define RESET_STATE_RESET   0
#define RESET_STATE_DONE    1

#define CREDIT_STATE_PUSH_START_MSG  0
#define CREDIT_STATE_CHECK_START     1
#define CREDIT_STATE_PLAYER1_READY   2
#define CREDIT_STATE_RESET           4

#define LEVEL_STATE_PLAY_GAME 3
#define LEVEL_STATE_GAME_OVER 9
#define LEVEL_STATE_x 12
#define LEVEL_STATE_x2 14

/*  Values used by schedISRTask */
// #define TIMER_TENTHS    0x40
#define TIMER_TENTHS    0x40
// #define TIMER_SECONDS   0x80

/* sprites:

   ghost = 0x1c / 0x1d = frightened
           0x22 - 0x27 = normal, 4 directions, 2 animations
*/
