#include "tetris.h"

void get_random_next_figure() {
    figure *current_figure = get_figure();
    GameInfo_t *game_info = getInstance_GameInfo();
    srand(time(NULL));
    int figure_id = rand() % 7;
    current_figure->next_figure_id = figure_id;
    figure_copy(&game_info->next, current_figure->figures[figure_id][0]);
}

void userInput(UserAction_t action, int hold) {
    tetris_state *state = get_current_state();
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    if (action == Terminate) {
        *state = EXIT_STATE;
    }
    if (action == Start && hold == 0) {
        if (*state == BEFORE_START || *state == GAME_OVER) {
            clean_field(game_info, current_figure);
            game_info->level = 1;
            game_info->score = 0;
            *state = SPAWN;
        }
    }
    if (action == Left) {
        int i_left = get_figure_left(*current_figure);
        if (current_figure->x + i_left > 0 && sideway_collision(*current_figure, action) == 0) {
            current_figure->x--;
        }      
    }
    if (action == Right) {
        int i_right = get_figure_right(*current_figure);
        if (current_figure->x + i_right < 9 && sideway_collision(*current_figure, action) == 0) {
            current_figure->x++;
        }
    }
    if (action == Action) {
        rotate_figure(current_figure);
    }
    if (action == Pause) {
        perform_pause(state);
    }
    if (action == Down) {
        game_info->speed = 25;
    }
}

void perform_pause(tetris_state *state) {
    if (*state == PAUSE) {
        *state = MOVING;
        return;
    }

    if (*state == MOVING) {
        *state = PAUSE;
    }
}

GameInfo_t updateCurrentState() {
    GameInfo_t *game_info = getInstance_GameInfo();
    tetris_state *state = get_current_state();
    figure *current_figure = get_figure();
    if (*state == SPAWN) {
        perform_spawn(game_info, current_figure, state);
    }
    if (*state == MOVING) {
        perform_moving(game_info, current_figure, state);
    }
    if (*state == GAME_OVER) {
        perform_game_over(game_info);
    }
    return *game_info;
}

void perform_game_over(GameInfo_t *game_info) {
        if (game_info->score > read_high_score()) {
            save_high_score(game_info->score);
            game_info->high_score = game_info->score;
        }
}

void perform_spawn(GameInfo_t *game_info, figure *current_figure, tetris_state *state) {
        game_info->speed = 435 - 100 * game_info->level;
        figure_pointer_copy(&current_figure->figure_field, game_info->next);
        current_figure->current_figure_id = current_figure->next_figure_id;
        current_figure->rotate_value = 0;
        matrix_pointer_copy(&current_figure->tmp_field, game_info->field, ROWS_COUNT, COLS_COUNT);
        current_figure->x = 3;
        current_figure->y = 0;
        get_random_next_figure();
        place_figure_on_the_field(game_info, *current_figure);
        if (is_collision(*current_figure, *game_info) != 0) {
            *state = GAME_OVER;
        } else {
            *state = MOVING;
        }
}

void perform_moving(GameInfo_t *game_info, figure *current_figure, tetris_state *state) {
        update_level(game_info);
        update_speed(game_info);
        int collision_code = is_collision(*current_figure, *game_info);
        if (collision_code == 0) {
            shift_down(current_figure);
        }
        else
            *state = SPAWN;
        matrix_pointer_copy(&game_info->field, current_figure->tmp_field, ROWS_COUNT, COLS_COUNT);
        place_figure_on_the_field(game_info, *current_figure);
        clean_lines(current_figure, game_info);
}

void update_level(GameInfo_t *game_info) {
    if (game_info->level < 10) game_info->level = game_info->score / 600 + 1;
}

void update_speed(GameInfo_t *game_info) {
    if (game_info->speed != 25) game_info->speed = 435 - 35 * game_info->level;
}

void clean_lines(figure *current_figure, GameInfo_t *game_info) {
    int count_killed_lines = 0;
    for (int i = ROWS_COUNT - 1; i >= 0; i--) {
        while (is_line_filled(i, *current_figure) == 1) {
            drop_line(i, current_figure);
            count_killed_lines++;
        }
    }
    increase_score(count_killed_lines, game_info);
}

void increase_score(int count_killed_lines, GameInfo_t *game_info) {
    if (count_killed_lines == 1) game_info->score += 100;
    if (count_killed_lines == 2) game_info->score += 300;
    if (count_killed_lines == 3) game_info->score += 700;
    if (count_killed_lines >= 4) game_info->score += 750;
}

void rotate_figure(figure *current_figure) {
    int **tmp_matrix;
    alloc_and_init_multidimensional_matrix(&tmp_matrix, FIGURE_ROWS, FIGURE_COLS);

    int new_rotate_index = 0; 
    if (current_figure->rotate_value == 3) {
        new_rotate_index = 0;
    } else {
        new_rotate_index = current_figure->rotate_value + 1;    
    }
    figure_copy(&tmp_matrix, current_figure->figures[current_figure->current_figure_id][new_rotate_index]);
    if (is_rotate_collision(tmp_matrix, *current_figure) == 0) {
        current_figure->rotate_value = new_rotate_index;
        figure_copy(&current_figure->figure_field, current_figure->figures[current_figure->current_figure_id][current_figure->rotate_value]);
    }
    free_multidimensional_matrix(tmp_matrix, FIGURE_ROWS);
}

int is_rotate_collision(int **matrix, figure current_figure) {
    int result = 0;
    for (int i = 0; i < FIGURE_ROWS; i++) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            if (matrix[i][j] == 1) {
                if (i + current_figure.y > 19 || j + current_figure.x < 0 || j + current_figure.x > 9) {
                    result = 1;
                } else {
                    if (current_figure.tmp_field[i + current_figure.y][j + current_figure.x] == 1) {
                        result = 1;
                    }
                }
            }
        }
    }
    return result;
}

int is_collision(figure current_figure, GameInfo_t game_info) {
    int i_bottom = get_figure_bottom(current_figure);

    if (current_figure.y + i_bottom > 18) {
        return 1; 
    }

    for (int i = 0; i < FIGURE_ROWS; i++) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[i][j] == 1) {
                if (current_figure.tmp_field[i + current_figure.y + 1][j + current_figure.x] == 1) {
                    figure_pointer_copy(&current_figure.tmp_field, game_info.field);
                    return 1;
                }
            }
        }
    }
    return 0;
}

void place_figure_on_the_field(GameInfo_t *game_info, figure current_figure) {
    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[i][j] == 1) game_info->field[i + current_figure.y][j + current_figure.x] = current_figure.figure_field[i][j];
        }
    } 
 }

void shift_down(figure *current_figure) {
    current_figure->y++;
} 