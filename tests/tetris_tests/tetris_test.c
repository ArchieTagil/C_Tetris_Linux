#include "../libtetris_test.h"

void print_matrix(int **matrix, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

START_TEST(test1) {
    tetris_state *state = get_current_state();
    *state = MOVING; 
    userInput(Terminate, 0);
    ck_assert_int_eq(*state, EXIT_STATE);
}

START_TEST(test2) {
    tetris_state *state = get_current_state();
    *state = BEFORE_START; 
    userInput(Start, 0);
    ck_assert_int_eq(*state, SPAWN);
}

START_TEST(test3) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    game_info_init(game_info);
    current_figure->x = 5;

    userInput(Left, 0);
    ck_assert_int_eq(current_figure->x, 4);
}

START_TEST(test4) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    game_info_init(game_info);
    current_figure->x = 5;

    userInput(Right, 0);
    ck_assert_int_eq(current_figure->x, 6);
}

START_TEST(test5) {
    tetris_state *state = get_current_state();
    *state = MOVING; 
    userInput(Pause, 0);
    ck_assert_int_eq(*state, PAUSE);
}

START_TEST(test6) {
    tetris_state *state = get_current_state();
    *state = PAUSE; 
    userInput(Pause, 0);
    ck_assert_int_eq(*state, MOVING);
}

START_TEST(test7) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    game_info_init(game_info);
    current_figure->current_figure_id = 1;
    current_figure->x = 5;
    current_figure->y = 10;
    current_figure->rotate_value = 0;
    figure_copy(&current_figure->figure_field, current_figure->figures[1][0]);
    userInput(Action, 0);
    ck_assert_int_eq(current_figure->rotate_value, 1);

    for (size_t i = 0; i < FIGURE_ROWS; i++) {
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            if (i == 0 && j == 1) ck_assert_int_eq(current_figure->figure_field[i][j], 1);
            else if (i == 0 && j == 2) ck_assert_int_eq(current_figure->figure_field[i][j], 1);
            else if (i == 1 && j == 1) ck_assert_int_eq(current_figure->figure_field[i][j], 1);
            else if (i == 2 && j == 1) ck_assert_int_eq(current_figure->figure_field[i][j], 1);
            else ck_assert_int_eq(current_figure->figure_field[i][j], 0);
        }
    }
}

START_TEST(test8) {
    GameInfo_t *game_info = getInstance_GameInfo();
    game_info_init(game_info);
    tetris_state *state = get_current_state();
    *state = GAME_OVER;
    save_high_score(100);
    game_info->score = 800;
    updateCurrentState();
    int test_val = read_high_score();
    ck_assert_int_eq(test_val, 800);
    ck_assert_int_eq(game_info->high_score, 800);
}

START_TEST(test9) {
    GameInfo_t *game_info = getInstance_GameInfo();
    game_info_init(game_info);
    tetris_state *state = get_current_state();
    *state = SPAWN;
    updateCurrentState();
    ck_assert_int_eq(*state, MOVING);
}

Suite *tetris_test_suite() {
  Suite *s = suite_create("\033[42m-=TETRIS TEST=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test1);
  tcase_add_test(t, test2);
  tcase_add_test(t, test3);
  tcase_add_test(t, test4);
  tcase_add_test(t, test5);
  tcase_add_test(t, test6);
  tcase_add_test(t, test7);
  tcase_add_test(t, test8);
  tcase_add_test(t, test9);
  suite_add_tcase(s, t);
  return s;
}