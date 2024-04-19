#ifndef DEFINES_TETRIS
#define DEFINES_TETRIS

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/// @brief Tetris field Heigh. As was said in the requirement
#define ROWS_COUNT 20
/// @brief Tetris field Width. As was said in the requirement
#define COLS_COUNT 10

/// @brief Figure field Heigh.
#define FIGURE_ROWS 4
/// @brief Figure field Width.
#define FIGURE_COLS 4

/// @brief FSM States
typedef enum {
    BEFORE_START,
    SPAWN,
    MOVING,
    PAUSE,
    GAME_OVER,
    EXIT_STATE
} tetris_state;

/** @brief Avaliable user actions: \n
 * ENTER - Start (Start the game) \n
 * P - Pause (Pause Game) \n
 * ESC - Terminate (exit the program) \n
 * LEFT ROW - Left (move left) \n
 * RIGHT ROW - Right (move right) \n
 * UP ROW - Up (Do nothing) \n
 * DOWN ROW - Down (speed up figure) \n
 * SPACE - Action (Rotate Figure)
 */
typedef enum {
    Start, /*!< ENTER - Start the game */
    Pause, /*!< P - Pause Game */
    Terminate, /*!< ESC - exit the program */
    Left, /*!< LEFT ROW - move left */
    Right, /*!< RIGHT ROW - move right */
    Up, /*!< UP ROW - Do nothing */
    Down, /*!< DOWN ROW speed up figure */
    Action /*!< SPACE - Rotate Figure */
} UserAction_t;

/// @brief Main structure from the task. It shows current situation in the game
typedef struct {
    int **field; /*!< Pointer to matrix with field of the game with current state on it */
    int **next; /*!< Keep pointer to the matrix with next figure */
    int score; /*!< Current score of the game */
    int high_score; /*!< Best score of the game */
    int level; /*!< Current difficulty level */
    int speed; /*!< Current figure  speed */
    int pause; /*!< Is the game on pause or not (boolean) */
} GameInfo_t;

/** @brief Additional structure 
 * 
 */
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

///@brief Allocate memory for game_info fields and for current figure fields. Also it fills the fields with zero value.
///@param GameInfo_t function takes one parametr - object of GameInfo_t and change it.
///@return return nothing.
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
void shift_down(figure *current_figure);
int is_collision(figure current_figure, GameInfo_t game_info);
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
void update_level(GameInfo_t *game_info);
void update_speed(GameInfo_t *game_info);
void save_high_score(int score_value);
int read_high_score();
void perform_moving(GameInfo_t *game_info, figure *current_figure, tetris_state *state);
void perform_spawn(GameInfo_t *game_info, figure *current_figure, tetris_state *state);
void perform_game_over(GameInfo_t *game_info);
void perform_pause(tetris_state *state);

#endif