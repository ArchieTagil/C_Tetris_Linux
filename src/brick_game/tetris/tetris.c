#include "tetris.h"

GameInfo_t *getInstance_GameInfo() {
    static GameInfo_t game_info;
    return &game_info;
}

tetris_state *get_current_state() {
    static tetris_state state;
    return &state;
}

figure *get_figure() {
    static figure current_figure;
    return &current_figure;
}

void get_random_next_figure() {
    int figures[7][4][4] = {
        {   {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}},
            
        {   {0,0,0,0},
            {0,1,0,0},
            {0,1,1,1},
            {0,0,0,0}},
            
        {   {0,0,0,0},
            {0,0,0,1},
            {0,1,1,1},
            {0,0,0,0}},
            
        {   {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}},
            
        {   {0,0,0,0},
            {0,0,1,1},
            {0,1,1,0},
            {0,0,0,0}},
            
        {   {0,0,0,0},
            {0,0,1,0},
            {0,1,1,1},
            {0,0,0,0}},
            
        {   {0,0,0,0},
            {0,1,1,0},
            {0,0,1,1},
            {0,0,0,0}}
};

    GameInfo_t *game_info = getInstance_GameInfo();
    srand(time(NULL));
    int figure_id = rand() % 7;
    mvprintw(20, 40, "%d", figure_id);
    figure_copy(&game_info->next, figures[figure_id]);
}

void userInput(UserAction_t action, bool hold) {
    tetris_state *state = get_current_state();

    if (action == Terminate) {
        *state = EXIT_STATE;
    }

    if (action == Start) {
        if (*state == BEFORE_START) {
            *state = SPAWN;
        }
    }
}

GameInfo_t updateCurrentState() {
    GameInfo_t *game_info = getInstance_GameInfo();
    tetris_state *state = get_current_state();
    figure *current_figure = get_figure();

    if (*state == SPAWN) {
        figure_pointer_copy(&current_figure->figure_field, game_info->next);
        current_figure->x = 3;
        current_figure->y = 0;
        get_random_next_figure();
        place_figure_on_the_field(game_info, *current_figure);
        *state = MOVING;
    }

    if (*state == MOVING) {
        if (is_collision(*current_figure, *game_info) == false) shift_down(current_figure);
        place_figure_on_the_field(game_info, *current_figure);
    }
    
    return *game_info;
}

bool is_collision(figure current_figure, GameInfo_t game_info) {
    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[i][j] == 1) //ячейка включена в фигуре
                mvprintw(9, 45, "current_figure.y = %d, i = %ld", current_figure.y, i);
                if (current_figure.y + (3 - i) > 19) { //позция верхнего левого угла + координата точки по у > нижней границы поля
                    return true;
            }
        }
    }
    return false;
}

void shift_left(figure *current_figure) {
    current_figure->x--;
} 

void shift_right(figure *current_figure) {
    current_figure->x++;
} 

void shift_down(figure *current_figure) {
    current_figure->y++;
} 

void shift_up(figure *current_figure) {
    current_figure->y--;
} 

void place_figure_on_the_field(GameInfo_t *game_info, figure current_figure) {
    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[i][j] == 1) game_info->field[i + current_figure.y][j + current_figure.x] = current_figure.figure_field[i][j];
        }
        
    } 
 }

void game_info_init(GameInfo_t *game_info) {
    alloc_and_init_multidimensional_matrix(&game_info->field, ROWS_COUNT, COLS_COUNT);
    alloc_and_init_multidimensional_matrix(&game_info->next, FIGURE_ROWS, FIGURE_COLS);
    game_info->score = 0;
    game_info->high_score = 0;
    game_info->level = 0;
    game_info->speed = 0;
    game_info->pause = 0;
    get_random_next_figure();

    figure *current_figure = get_figure();
    alloc_and_init_multidimensional_matrix(&current_figure->figure_field, FIGURE_ROWS, FIGURE_COLS);
}

void alloc_and_init_multidimensional_matrix(int ***matrix, int rows, int cols) {
    *matrix = (int**)malloc(rows * sizeof(int*));
    for (size_t i = 0; i < rows; i++) {
        (*matrix)[i] = (int*)malloc(cols * sizeof(int));
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            (*matrix)[i][j] = 0;
        }
    }
}

void figure_copy(int ***dst, int src[FIGURE_ROWS][FIGURE_ROWS]) {
    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            (*dst)[i][j] = src[i][j];
        }
    }
}

void figure_pointer_copy(int ***dst, int **src) {
    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            (*dst)[i][j] = src[i][j];
        }
    }
}

void free_multidimensional_matrix(int **ptr, int rows) {
    for (size_t i = 0; i < rows; i++) {
        free(ptr[i]);
    }
    free(ptr);
}
