#include "tetris.h"

void get_random_next_figure() {
    figure *current_figure = get_figure();
    GameInfo_t *game_info = getInstance_GameInfo();
    srand(time(NULL));
    int figure_id = rand() % 7;
    mvprintw(20, 40, "%d", figure_id);
    figure_copy(&game_info->next, current_figure->figures[figure_id]);
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
        mvprintw(5, 45, "i_right = %d", i_right);
        mvprintw(6, 45, "current_figure x = %d", current_figure->x);

        if (current_figure->x + i_right < 9) {
            current_figure->x++;
        }
    }
}

GameInfo_t updateCurrentState() {
    GameInfo_t *game_info = getInstance_GameInfo();
    tetris_state *state = get_current_state();
    figure *current_figure = get_figure();

    if (*state == SPAWN) {
        figure_pointer_copy(&current_figure->figure_field, game_info->next);
        matrix_pointer_copy(&current_figure->tmp_field, game_info->field, ROWS_COUNT, COLS_COUNT);
        current_figure->x = 3;
        current_figure->y = 0;
        get_random_next_figure();
        place_figure_on_the_field(game_info, *current_figure);
        *state = MOVING;
    }

    if (*state == MOVING) {
        if (is_collision(*current_figure, *game_info) == 0) {
            shift_down(current_figure);
        }
        else {
            //shift_up(current_figure);
            *state = SPAWN;
        }
        matrix_pointer_copy(&game_info->field, current_figure->tmp_field, ROWS_COUNT, COLS_COUNT);
        place_figure_on_the_field(game_info, *current_figure);
        print_matrix(current_figure->tmp_field, 20, 10);
    }
    
    return *game_info;
}

int is_collision(figure current_figure, GameInfo_t game_info) {
    // ### Возвращаемые коды:
    // ### 0 - столкновения нет
    // ### 1 - столкновение с полом (начинаем новый spawn)
    // ### 2 - столкновение со стенкой слева или справа (ничего не делаем, опускаем фигуру ниже)

    int i_bottom = get_figure_bottom(current_figure);
    
    

    if (current_figure.y + i_bottom > 18) { //позция верхнего левого угла + координата точки по у > нижней границы поля
        return 1; 
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