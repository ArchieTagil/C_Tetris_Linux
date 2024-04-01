#ifndef DEFINES_TETRIS
#define DEFINES_TETRIS

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define ROWS_COUNT 20
#define COLS_COUNT 10

#define FIGURE_ROWS 4
#define FIGURE_COLS 4

typedef enum { //fsm states
    BEFORE_START,
    SPAWN,
    MOVING,
    SHIFTING,
    PAUSE,
    GAME_OVER,
    EXIT_STATE
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

typedef struct {
    int **figure_field;
    int x, y; //верхний левый угол
    int **tmp_field;
    int rotate_value;
    int current_figure_id;
    int next_figure_id;
    int figures[7][4][4][4];
} figure;

void userInput(UserAction_t action, int hold);
GameInfo_t updateCurrentState();

void print_running_line();
void print_next_figure();
void game_info_init(GameInfo_t *game_info);
GameInfo_t *getInstance_GameInfo();
void alloc_and_init_multidimensional_matrix(int ***matrix, int rows, int cols);
void free_multidimensional_matrix(int **ptr, int rows);
tetris_state *get_current_state();
void figure_copy(int ***dst, int src[FIGURE_ROWS][FIGURE_ROWS]);
void figure_pointer_copy(int ***dst, int **src);
void get_random_next_figure();
figure *get_figure();
void place_figure_on_the_field(GameInfo_t *game_info, figure current_figure);
void shift_left(figure *current_figure);
void shift_right(figure *current_figure);
void shift_down(figure *current_figure);
void shift_up(figure *current_figure);
int is_collision(figure current_figure, GameInfo_t game_info);
void print_matrix(int **matrix, int r, int c);
void matrix_pointer_copy(int ***dst, int **src, int r, int c);
void figures_init(figure *current_figure);
int get_figure_bottom (figure current_figure);
int get_figure_left (figure current_figure);
int get_figure_right (figure current_figure);
void rotate_figure(figure *current_figure);
void clean_lines(figure *current_figure, GameInfo_t *game_info);
int is_line_filled(int i, figure current_figure);
void drop_line(int i, figure *current_figure);
int sideway_collision(figure current_figure, UserAction_t action);
void increase_score(int count_killed_lines, GameInfo_t *game_info);
int is_rotate_collision(int **matrix, figure current_figure);
void data_init(GameInfo_t *game_info);
void clean_field(GameInfo_t *game_info, figure *current_figure);

#endif