#ifndef DEFINES_TETRIS
#define DEFINES_TETRIS

#include <ncurses.h>
#include <stdlib.h>

#define ROWS_COUNT 20
#define COLS_COUNT 10

#define FIGURE_ROWS 4
#define FIGURE_COLS 4

typedef enum { //fsm states
    START = 0,
    SPAWN,
    MOVING,
    SHIFTING,
    ATTACHING,
    GAME_OVER
} tetris_state;

typedef enum {
    Start, //ENTER
    Pause, //P
    Terminate, //ESC
    Left, //ROW
    Right, //ROW
    Up, //ROW
    Down, //ROW
    Action //SPACE
} UserAction_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

void fsm(tetris_state state, int action, bool *break_flag);

void print_running_line();
void perform_start(tetris_state *state);
void print_next_figure();
void game_info_init(GameInfo_t *game_info);
GameInfo_t *getInstance_GameInfo();
void alloc_and_init_multidimensional_matrix(int ***matrix, int rows, int cols);

#endif