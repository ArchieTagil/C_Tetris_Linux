#include "gui_tetris.h"

int main() {
    win_init();
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    tetris_state *state = get_current_state();
    *state = BEFORE_START;
    game_info_init(game_info);
    // GameInfo_t game_info = updateCurrentState();
    print_state(*game_info);
    // printw("%d", game_info->next[1][1]);
    print_overlay();

    game_loop();
    free_multidimensional_matrix(game_info->field, ROWS_COUNT);
    free_multidimensional_matrix(game_info->next, FIGURE_ROWS);
    free_multidimensional_matrix(current_figure->tmp_field, ROWS_COUNT);
    free_multidimensional_matrix(current_figure->figure_field, FIGURE_ROWS);
    endwin();
}

void game_loop() {
    tetris_state *state = get_current_state();
    timeout(400);

    while (*state != EXIT_STATE) {
        int action = getch();
        mvprintw(1, 45, "current state is %d ", *state);
        switch (action) {
        case ESC:
            userInput(Terminate, 0);
            break;
        case ENTER:
            userInput(Start, 0);
            break;
        case KEY_UP:
            userInput(Up, 0);
            break;
        case KEY_DOWN:
            userInput(Down, 0);
            break;
        case KEY_LEFT:
            userInput(Left, 0);
            break;
        case KEY_RIGHT:
            userInput(Right, 0);
            break;
        case ' ':
            userInput(Action, 0);
            break;
        case 'p':
            userInput(Pause, 0);
            break;
        case 'P':
            userInput(Pause, 0);
            break;
        }
        GameInfo_t game_info = updateCurrentState();
        print_state(game_info);
    }
}

void print_state(GameInfo_t game_info) {
    clear_window();
    for (size_t i = 0; i < ROWS_COUNT; i++) {
        for (size_t j = 0; j < COLS_COUNT; j++) {
            use_default_colors();
            start_color();
            init_pair(0, COLOR_WHITE, -1);
            init_pair(3, COLOR_BLACK, COLOR_YELLOW);
            attron(COLOR_PAIR(3));
            if (game_info.field[i][j] == 1) mvprintw(i + 1, j * 2 + 1, "  ");
            attrset(COLOR_PAIR(0));
        }
    }

    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            use_default_colors();
            start_color();
            init_pair(0, COLOR_WHITE, -1);
            init_pair(1, COLOR_BLACK, COLOR_RED);
            attron(COLOR_PAIR(1));
            if (game_info.next[i][j] == 1) mvprintw(i + 3, 26 + j * 2 + 1, "  ");
            attrset(COLOR_PAIR(0));
        }
    }
}

void clear_window() {
    for (size_t i = 0; i < ROWS_COUNT; i++) {
        for (size_t j = 0; j < COLS_COUNT * 2; j++) {
            mvprintw(i + 1, j + 1, "*");
        }
    }

    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            mvprintw(i + 3, 26 + j * 2 + 1, "  ");
        }
    }
}

