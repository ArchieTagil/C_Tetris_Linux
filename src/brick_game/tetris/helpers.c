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

void save_high_score(int score_value) {
    FILE *fp;
    fp = fopen("record.txt", "w");
    fprintf(fp, "%d", score_value);
    fclose(fp);
}

int read_high_score() {
    FILE *fp;
    int result = 0;
    if ((fp = fopen("record.txt", "r")) !=NULL) {
        fscanf(fp, "%d", &result);
        fclose(fp);
    }
    return result;
}

int sideway_collision(figure current_figure, UserAction_t action) {
    int result = 0;
    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[i][j] == 1) {
                if (action == Right) {
                    if (i + current_figure.y < 19 && j + current_figure.x + 1 < 10) {
                        if (current_figure.tmp_field[i + current_figure.y][j + current_figure.x + 1] == 1) result = 1;
                    } else {
                        result = 1;
                    }
                }
                if (action == Left) {
                    if (i + current_figure.y < 19 && j + current_figure.x - 1 >= 0) {
                        if (current_figure.tmp_field[i + current_figure.y][j + current_figure.x - 1] == 1) result = 1;
                    } else {
                        result = 1;
                    }
                }
            }
        }
    }
    return result;
}

void game_info_init(GameInfo_t *game_info) {
    alloc_and_init_multidimensional_matrix(&game_info->field, ROWS_COUNT, COLS_COUNT);
    alloc_and_init_multidimensional_matrix(&game_info->next, FIGURE_ROWS, FIGURE_COLS);
    figure *current_figure = get_figure();
    figures_init(current_figure);
    alloc_and_init_multidimensional_matrix(&current_figure->figure_field, FIGURE_ROWS, FIGURE_COLS);
    alloc_and_init_multidimensional_matrix(&current_figure->tmp_field, ROWS_COUNT, COLS_COUNT);
    get_random_next_figure();
    data_init(game_info);
}

void data_init(GameInfo_t *game_info) {
    game_info->score = 0;
    game_info->level = 1;
    game_info->speed = 400;
    game_info->pause = 0;
    game_info->high_score = read_high_score();
}

void clean_field(GameInfo_t *game_info, figure *current_figure) {
    for (size_t i = 0; i < ROWS_COUNT; i++) {
        for (size_t j = 0; j < COLS_COUNT; j++) {
            game_info->field[i][j] = 0;
            current_figure->tmp_field[i][j] = 0;
        }
    }
}

void figures_init(figure *current_figure) {
    int tmp_figures[7][4][4][4] = {
        {
           {{1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}},

           {{1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}},
        
           {{0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}}
        },

        {   
           {{0,1,0,0},
            {0,1,1,1},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,1,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}},

           {{0,1,1,1},
            {0,0,0,1},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,0,1,0},
            {0,0,1,0},
            {0,1,1,0},
            {0,0,0,0}}
        },

        {   
           {{0,0,0,1},
            {0,1,1,1},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0}},

           {{0,1,1,1},
            {0,1,0,0},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,0,0}}
        },

        {   
           {{0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}}
        },

        {   
           {{0,0,1,1},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}},

           {{0,0,1,1},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}}
        },

        {   
           {{0,0,1,0},
            {0,1,1,1},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,0,1,0},
            {0,0,1,1},
            {0,0,1,0},
            {0,0,0,0}},

           {{0,1,1,1},
            {0,0,1,0},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,0,1,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}}
        },

        {   
           {{0,1,1,0},
            {0,0,1,1},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}},

           {{0,1,1,0},
            {0,0,1,1},
            {0,0,0,0},
            {0,0,0,0}},

           {{0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}}
        }
    };
    for (size_t i = 0; i < 7; i++) {
        for (size_t j = 0; j < 4; j++) {
            for (size_t k = 0; k < 4; k++) {
                for (size_t n = 0; n < 4; n++) {
                    current_figure->figures[i][j][k][n] = tmp_figures[i][j][k][n];
                }
            }
        }
    }
}

void alloc_and_init_multidimensional_matrix(int ***matrix, int rows, int cols) {
    *matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        (*matrix)[i] = (int*)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*matrix)[i][j] = 0;
        }
    }
}

void drop_line(int i, figure *current_figure) {
    if (i == 0) {
        for (size_t j = 0; j < COLS_COUNT; j++) {
            current_figure->tmp_field[i][j] = 0;
        }
    } else {
        for (size_t k = i; k > 0; k--) {
            for (size_t j = 0; j < COLS_COUNT; j++) {
                current_figure->tmp_field[k][j] = current_figure->tmp_field[k-1][j];
            }
        }
    }
}

int is_line_filled(int i, figure current_figure) {
    int result = 1;
    for (size_t j = 0; j < COLS_COUNT; j++) {
        if (current_figure.tmp_field[i][j] == 0) result = 0; 
    }
    return result;
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
    for (int i = 0; i < rows; i++) {
        free(ptr[i]);
    }
    free(ptr);
}

void matrix_pointer_copy(int ***dst, int **src, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            (*dst)[i][j] = src[i][j];
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
    for (int i = FIGURE_ROWS-1; i >= 0; i--) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[j][i] == 1 && result_found == 0) {
                result_found = 1;
                result = i;
            }
        }
    }
    return result;
}