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

void game_info_init(GameInfo_t *game_info) {
    alloc_and_init_multidimensional_matrix(&game_info->field, ROWS_COUNT, COLS_COUNT);
    alloc_and_init_multidimensional_matrix(&game_info->next, FIGURE_ROWS, FIGURE_COLS);
    game_info->score = 0;
    game_info->high_score = 0;
    game_info->level = 0;
    game_info->speed = 0;
    game_info->pause = 0;
    figure *current_figure = get_figure();
    figures_init(current_figure);
    alloc_and_init_multidimensional_matrix(&current_figure->figure_field, FIGURE_ROWS, FIGURE_COLS);
    alloc_and_init_multidimensional_matrix(&current_figure->tmp_field, ROWS_COUNT, COLS_COUNT);
    get_random_next_figure();
}

void figures_init(figure *current_figure) {
    int tmp_figures[7][4][4] = {
        {   {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}},

        {   {0,1,0,0},
            {0,1,1,1},
            {0,0,0,0},
            {0,0,0,0}},

        {   {0,0,0,1},
            {0,1,1,1},
            {0,0,0,0},
            {0,0,0,0}},

        {   {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}},

        {   {0,0,1,1},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}},

        {   {0,0,1,0},
            {0,1,1,1},
            {0,0,0,0},
            {0,0,0,0}},

        {   {0,1,1,0},
            {0,0,1,1},
            {0,0,0,0},
            {0,0,0,0}}
    };
    for (size_t i = 0; i < 7; i++) {
        for (size_t j = 0; j < 4; j++) {
            for (size_t k = 0; k < 4; k++) {
                current_figure->figures[i][j][k] = tmp_figures[i][j][k];
            }        
        }
    }
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

void matrix_pointer_copy(int ***dst, int **src, int r, int c) {
    for (size_t i = 0; i < r; i++) {
        for (size_t j = 0; j < c; j++) {
            (*dst)[i][j] = src[i][j];
        }
    }
}

void print_matrix(int **matrix, int r, int c) {
    for (size_t i = 0; i < r; i++) {
        for (size_t j = 0; j < c; j++) {
            mvprintw(i, 80 + j, "%d", matrix[i][j]);
        }       
    }
}

int get_figure_bottom (figure current_figure) {
    int result = 0;
    int result_found = 0;
    for (int i = FIGURE_ROWS - 1; i >= 0; i--) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[i][j] == 1 && result_found == 0) {
                result_found = 1;
                result = i;
            }
        }
    }
    return result;
}

int get_figure_left (figure current_figure) {
    int result = 0;
    int result_found = 0;
    for (int i = 0; i < FIGURE_ROWS; i++) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[j][i] == 1 && result_found == 0) {
                result_found = 1;
                result = i;
            }
        }
    }
    return result;
}

int get_figure_right (figure current_figure) {
    int result = 0;
    int result_found = 0;
    for (int i = FIGURE_ROWS; i >= 0; i--) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[j][i] == 1 && result_found == 0) {
                result_found = 1;
                result = i;
            }
        }
    }
    return result;
}