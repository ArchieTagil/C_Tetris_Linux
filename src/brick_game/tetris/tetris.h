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

/** @brief Main structure from the task. It shows current situation in the game \n
 * Implement as Singleton
 */
typedef struct {
    int **field; /*!< Pointer to matrix with field of the game with current state on it */
    int **next; /*!< Keep pointer to the matrix with next figure */
    int score; /*!< Current score of the game */
    int high_score; /*!< Best score of the game */
    int level; /*!< Current difficulty level */
    int speed; /*!< Current figure  speed */
    int pause; /*!< Is the game on pause or not (boolean) */
} GameInfo_t;

/** @brief Additional structure to keep different values \n
 * Implement also as Singleton
 */
typedef struct {
    int **figure_field; /*!< Pointer to the matrix with current figure */
    int x, y; /*!< Top Left position of figure on the game field */
    int **tmp_field; /*!< Temprorary field where we can move figure as we wish and don't worry about how it looks. For example if after rotate figure intersect some obstacke it'll be ok, we can cancel rotate operation and don't show this on the main field in GameInfo_t structure*/
    int rotate_value; /*!< Number of second value of the array with figures. Show which matrix we need to use for current rotate situation (0-3 values) */
    int current_figure_id; /*!< Number of first value of the array with figures. Show which figure will be drawn. */
    int next_figure_id; /*!< Number of first value of the array with figures. Show which figure will be drawn in the window of next figure. And what figure will be spawn next. */
    int figures[7][4][4][4]; /*!< Source array with all possible figures. */
} figure;

/** @brief Base function from the task. It perform any actions which described in UserAction_t.
 *  @param action - UserAction value and if it was hold.
 *  @return return nothing.
 */
void userInput(UserAction_t action, int hold);

/** @brief Perform one frame of playing time.
 *  @return return nothing.
 */
GameInfo_t updateCurrentState();

/** @brief Allocate memory for game_info fields and for current figure fields. Also it fills the fields with zero value.
 *  @param GameInfo_t function takes one parametr - object of GameInfo_t and change it.
 *  @return return nothing.
 */
void game_info_init(GameInfo_t *game_info);

/** @brief Function to get single instance of our GameInfo_t.
 *  @return return Single GameInfo_t Instance.
 */
GameInfo_t *getInstance_GameInfo();

/** @brief Allocate memory for any matrix.
 *  @param matrix - pointer to the two-dimensional matrix.
 *  @param rows - needed number of rows.
 *  @param cols - needed number of cols.
 *  @return return nothing.
 */
void alloc_and_init_multidimensional_matrix(int ***matrix, int rows, int cols);

/** @brief Free memory for any matrix and fill it with zero values.
 *  @param matrix - pointer to the two-dimensional matrix.
 *  @param rows - count of rows to free.
 *  @return return nothing.
 */
void free_multidimensional_matrix(int **ptr, int rows);

/** @brief Get single instance of current FSM state
 *  @return tetris state.
 */
tetris_state *get_current_state();

/** @brief Copy the values from one matrix 4x4 to another one.
 *  @param dst - pointer to the destination two-dimensional matrix.
 *  @param src - source matrix.
 *  @return return nothing.
 */
void figure_copy(int ***dst, int src[FIGURE_ROWS][FIGURE_ROWS]);

/** @brief Copy the values from one matrix 4x4 to another one.
 *  @param dst - pointer to the destination two-dimensional matrix.
 *  @param src - pointer to the source matrix.
 *  @return return nothing.
 */
void figure_pointer_copy(int ***dst, int **src);

/** @brief Place the random figure (from 1 to 7), from the base array "figures[7][4][4][4]" to the "next" field of GameInfo_t instance with rotate value 0.
 *  @return return nothing.
 */
void get_random_next_figure();

/** @brief Get the single instance of current figure object.
 *  @return return single figure instance.
 */
figure *get_figure();

/** @brief Copy the values from the matrix with current figure to the field by x, y coordinates.
 *  @param game_info - pointer to the single instanse of GameInfo_t object (we will change the field in it). 
 *  @param current_figure - instance of current figure object (we need the field with figure).
 *  @return return nothing.
 */
void place_figure_on_the_field(GameInfo_t *game_info, figure current_figure);

/** @brief Increase y position of figure to shift it down.
 *  @param current_figure - instance of current figure object.
 *  @return return nothing.
 */
void shift_down(figure *current_figure);

/** @brief Check if the brick of figure at the same place as brick of obstacle on the temroray field.
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @param current_figure - instance of current figure object.
 *  @return return 1 if yes or 0 if not.
 */
int is_collision(figure current_figure, GameInfo_t game_info);

/** @brief Copy the values from the any matrix to the same size matrix.
 *  @param dst - pointer to the destination matrix
 *  @param src - pointer to the source matrux
 *  @param r - count of rows
 *  @param c - count of cols
 *  @return return nothing.
 */
void matrix_pointer_copy(int ***dst, int **src, int r, int c);

/** @brief Fill the basic array of "tmp_figures[7][4][4][4]" with all possible figures and its rotate versions.
 *  @param current_figure - pointer to the instance of current figure object.
 *  @return return nothing.
 */
void figures_init(figure *current_figure);

/** @brief Find the very bottom brick of the figure
 *  @param current_figure - instance of current figure object.
 *  @return return the y value of very bottom brick of the figure.
 */
int get_figure_bottom (figure current_figure);

/** @brief Find the very left brick of the figure
 *  @param current_figure - instance of current figure object.
 *  @return return the x value of very left brick of the figure.
 */
int get_figure_left (figure current_figure);

/** @brief Find the very right brick of the figure
 *  @param current_figure - instance of current figure object.
 *  @return return the x value of very right brick of the figure.
 */
int get_figure_right (figure current_figure);

/** @brief Change rotate value of the current figue by next one and copy matrix with next rotated figure to the figure.field
 *  @param current_figure - instance of current figure object.
 *  @return nothing
 */
void rotate_figure(figure *current_figure);

/** @brief remove filled lines from the field and increase score
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @param current_figure - pointer to the single instance of current figure object.
 *  @return return nothing.
 */
void clean_lines(figure *current_figure, GameInfo_t *game_info);

/** @brief Check if line filled. 
 *  @param i - y position of checked line.
 *  @param current_figure - pointer to the single instance of current figure object.
 *  @return return nothing.
 */
int is_line_filled(int i, figure current_figure);

/** @brief Perform removing line and shift all lines above down. 
 *  @param i - y position of line.
 *  @param current_figure - pointer to the single instance of current figure object.
 *  @return return nothing.
 */
void drop_line(int i, figure *current_figure);

/** @brief Check if the figure inside the figure matrix go beyond borders after user action (move left or right). 
 *  @param action - current user action 
 *  @param current_figure - pointer to the single instance of current figure object.
 *  @return return 1 if figure moved beyond borders or 0 if not.
 */
int sideway_collision(figure current_figure, UserAction_t action);

/** @brief Calculate and increase game score according the task.
 *  @param count_killed_lines - number of removed lines at once
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @return return nothing.
 */
void increase_score(int count_killed_lines, GameInfo_t *game_info);

/** @brief Check if after rotate figure it matched with the brick on the field
 *  @param matrix - matrix with the rotated figure
 *  @param current_figure - instance with the source figure
 *  @return return 1 if matched or 0 if not.
 */
int is_rotate_collision(int **matrix, figure current_figure);

/** @brief Fill the single GameInfo_t object with started values.
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @return return nothing.
 */
void data_init(GameInfo_t *game_info);

/** @brief Fill field of the game and tmp field with zero.
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @param current_figure - pointer to the single instance with the figure
 *  @return nothing
 */
void clean_field(GameInfo_t *game_info, figure *current_figure);

/** @brief Increase level according the score
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @return nothing
 */
void update_level(GameInfo_t *game_info);

/** @brief Increase game speed according the level
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @return nothing
 */
void update_speed(GameInfo_t *game_info);

/** @brief Save some value to file
 *  @param score_value - score value to be saved. 
 *  @return nothing
 */
void save_high_score(int score_value);

/** @brief Read score value from file
 *  @return readed value from file
 */
int read_high_score();

/** @brief Perform moving figure (it include additional helpers operations like update level, speed, clean lines after moving and so on).
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @param current_figure - pointer to the single instanse of current figure
 *  @param state - pointer to the single instanse of tetris state
 *  @return nothing
 */
void perform_moving(GameInfo_t *game_info, figure *current_figure, tetris_state *state);

/** @brief Put figure on the field, change state to Moving or Game Over and create next figure.
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @param current_figure - pointer to the single instanse of current figure
 *  @param state - pointer to the single instanse of tetris state
 *  @return nothing
 */
void perform_spawn(GameInfo_t *game_info, figure *current_figure, tetris_state *state);

/** @brief Save game score to the high score if it needs.
 *  @param game_info - pointer to the single instanse of GameInfo_t object. 
 *  @return nothing
 */
void perform_game_over(GameInfo_t *game_info);

/** @brief Pause the game if it at Movind state or resume game if it on Pause state.
 *  @param state - pointer to the single instanse of tetris state
 *  @return nothing
 */
void perform_pause(tetris_state *state);

#endif