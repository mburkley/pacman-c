#define ISRTASK_INC_LEVEL_STATE        0
#define ISRTASK_INC_MAIN_SUB2        1
#define ISRTASK_INC_MAIN_SUB1        2
#define ISRTASK_INC_KILLED_STATE        3
#define ISRTASK_RESET_FRUIT     4
#define ISRTASK_DISPLAY_READY         6
#define ISRTASK_INC_SCENE1_STATE         7
#define ISRTASK_INC_SCENE2_STATE         8
#define ISRTASK_INC_SCENE3_STATE         9

#define TASK_CLEAR_SCREEN       0x00
#define TASK_FLASH_MAZE         0x01  // ???? TODO
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
#define TASK_CLEAR_GHOST_STATE 0x11
#define TASK_CLEAR_PILLS 0x12
#define TASK_CLEAR_PILLS_SCREEN 0x13
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

#define GHOST_ALIVE     0
#define GHOST_DEAD      1

#define GHOST_BLINKY    1
#define GHOST_PINKY    2
#define GHOST_INKY    3
#define GHOST_CLYDE    4

