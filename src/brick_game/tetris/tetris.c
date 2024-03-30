#include "tetris.h"

void get_random_next_figure() {
    figure *current_figure = get_figure();
    GameInfo_t *game_info = getInstance_GameInfo();
    srand(time(NULL));
    int figure_id = rand() % 7;
    mvprintw(20, 40, "%d", figure_id);
    current_figure->next_figure_id = figure_id;
    figure_copy(&game_info->next, current_figure->figures[figure_id][0]);
}

void userInput(UserAction_t action, int hold) {
    tetris_state *state = get_current_state();
    figure *current_figure = get_figure();

    if (action == Terminate) {
        *state = EXIT_STATE;
    }

    if (action == Start) {
        if (*state == BEFORE_START) {
            *state = SPAWN;
        }
    }

    if (action == Left) {
        int i_left = get_figure_left(*current_figure);
        if (current_figure->x + i_left > 0) {
            current_figure->x--;
        }      
    }

    if (action == Right) {
        int i_right = get_figure_right(*current_figure);
        if (current_figure->x + i_right < 9) {
            current_figure->x++;
        }
    }

    if (action == Action) {
        figure *current_figure = get_figure();
        rotate_figure(current_figure);
    }
}

GameInfo_t updateCurrentState() {
    GameInfo_t *game_info = getInstance_GameInfo();
    tetris_state *state = get_current_state();
    figure *current_figure = get_figure();

    if (*state == SPAWN) {
        figure_pointer_copy(&current_figure->figure_field, game_info->next); //переносим фигуру из next на матрицу фигуры для current_figure
        current_figure->current_figure_id = current_figure->next_figure_id; //id из следующей фигуры делаем текущим
        current_figure->rotate_value = 0; //инициализируем начальный индекс вращения фигуры
        matrix_pointer_copy(&current_figure->tmp_field, game_info->field, ROWS_COUNT, COLS_COUNT); //заполняем временное поле препятствиями из оригинального поля
        current_figure->x = 3;
        current_figure->y = 0;
        get_random_next_figure();
        place_figure_on_the_field(game_info, *current_figure);
        *state = MOVING;
    }

    if (*state == MOVING) {
        clean_lines(current_figure, game_info);
        mvprintw(8, 45, "current figure id = %d", current_figure->current_figure_id);
        mvprintw(9, 45, "next figure id = %d", current_figure->next_figure_id);
        mvprintw(10, 45, "rotate index = %d", current_figure->rotate_value);

        int collision_code = is_collision(*current_figure, *game_info);

        if (collision_code == 0) {
            shift_down(current_figure);
        } else if (collision_code == 1) {
            *state = SPAWN;
        } else if (collision_code == 2) {
            *state = SPAWN;
        }

        matrix_pointer_copy(&game_info->field, current_figure->tmp_field, ROWS_COUNT, COLS_COUNT);
        place_figure_on_the_field(game_info, *current_figure);
        print_matrix(current_figure->tmp_field, 20, 10);

    }
    return *game_info;
}

void clean_lines(figure *current_figure, GameInfo_t *game_info) {
    for (int i = ROWS_COUNT - 1; i >= 0; i--) {
        while (is_line_filled(i, *current_figure) == 1) {
            drop_line(i, current_figure);
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

void rotate_figure(figure *current_figure) {
    int tmp_matrix[4][4] = {0};
    int new_rotate_index = 0; 
    if (current_figure->rotate_value == 3) {
        new_rotate_index = 0;
    } else {
        new_rotate_index = current_figure->rotate_value + 1;    
    }
    current_figure->rotate_value = new_rotate_index;
    figure_copy(&current_figure->figure_field, current_figure->figures[current_figure->current_figure_id][current_figure->rotate_value]);
}

int is_collision(figure current_figure, GameInfo_t game_info) {
    int i_bottom = get_figure_bottom(current_figure);

    if (current_figure.y + i_bottom > 18) { //позция верхнего левого угла + координата точки по у > нижней границы поля
        return 1; 
    }

    for (int i = 0; i < FIGURE_ROWS; i++) {
        for (int j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[i][j] == 1) { // Если в поле фигуры блок == 1 т.е. фигура присутствует
                if (current_figure.tmp_field[i + current_figure.y + 1][j + current_figure.x] == 1) { //И если во временном поле с препятствием на этом же месте есть занятый блок
                    figure_pointer_copy(&current_figure.tmp_field, game_info.field); //помещаем фигуру на поле с препятствиями
                    return 2; //новое поле с прорисованной фигурой
                }
            }
        }
    }
    return 0; //столкновений ни с чем нет
}

void place_figure_on_the_field(GameInfo_t *game_info, figure current_figure) {
    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            if (current_figure.figure_field[i][j] == 1) game_info->field[i + current_figure.y][j + current_figure.x] = current_figure.figure_field[i][j];
        }
    } 
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