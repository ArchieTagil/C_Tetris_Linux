#include "tetris.h"

GameInfo_t *getInstance_GameInfo() {
    static GameInfo_t game_info;
    return &game_info;
}

void fsm(tetris_state state, int action, bool *break_flag) {
    if (state == START) perform_start(&state);
}

void perform_start(tetris_state *state) {
    //printf("current state is: %s", *state == START ? "ok" : "no");
}

void userInput(UserAction_t action, bool hold) {
    if (action == Terminate) {
        endwin();
        exit(0);
    }
}

GameInfo_t updateCurrentState() {

}

void game_info_init(GameInfo_t *game_info) {
    alloc_and_init_multidimensional_matrix(&game_info->field, ROWS_COUNT, COLS_COUNT);
    alloc_and_init_multidimensional_matrix(&game_info->next, FIGURE_ROWS, FIGURE_COLS);
    game_info->score = 0;
    game_info->high_score = 0;
    game_info->level = 0;
    game_info->speed = 0;
    game_info->pause = 0;
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
