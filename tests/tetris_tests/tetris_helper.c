#include "../libtetris_test.h"

START_TEST(test_gameinfo_init) {
    GameInfo_t *game_info = getInstance_GameInfo();
    ck_assert_int_eq(game_info->level, 1);
    ck_assert_int_eq(game_info->speed, 400);
    ck_assert_int_eq(game_info->pause, 0);
    ck_assert_int_eq(game_info->score, 0);
    for (size_t i = 0; i < 20; i++) {
        for (size_t j = 0; j < 10; j++) {
            ck_assert_int_eq(game_info->field[i][j], 0);
        }
    }

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            ck_assert_int_le(game_info->next[i][j], 1);
        }
    }
}

START_TEST(test_figure_init) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    ck_assert_ptr_nonnull(current_figure);
}

START_TEST(test_save_and_read_hight_score) {
    save_high_score(123456);
    int test_var = read_high_score();
    ck_assert_int_eq(test_var, 123456);
}

START_TEST(test_sideway_collision_1) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    for (size_t i = 0; i < FIGURE_ROWS; i++) { //фигура вся из единиц
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            current_figure->figure_field[i][j] = 1;
        }
    }
    current_figure->y = 10;
    current_figure->x = 1;

    for (size_t i = 0; i < ROWS_COUNT; i++) { //рисуем стенки по бокам поля для имитации столкновения
        for (size_t j = 0; j < COLS_COUNT; j++) {
            if (j == 0 || j == 9) current_figure->tmp_field[i][j] = 1;
        }
    }
    
    int test_var = sideway_collision(*current_figure, Left);
    ck_assert_int_eq(test_var, 1);
}

START_TEST(test_sideway_collision_2) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    for (size_t i = 0; i < FIGURE_ROWS; i++) { //фигура вся из единиц
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            current_figure->figure_field[i][j] = 1;
        }
    }
    current_figure->y = 10;
    current_figure->x = 8;

    for (size_t i = 0; i < ROWS_COUNT; i++) { //рисуем стенки по бокам поля для имитации столкновения
        for (size_t j = 0; j < COLS_COUNT; j++) {
            if (j == 0 || j == 9) current_figure->tmp_field[i][j] = 1;
        }
    }
    
    int test_var = sideway_collision(*current_figure, Right);
    ck_assert_int_eq(test_var, 1);
}

START_TEST(test_get_state) {
    tetris_state *current_state = get_current_state();
    ck_assert_ptr_nonnull(current_state);
}

START_TEST(test_clean_figure) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    for (size_t i = 0; i < ROWS_COUNT; i++) { //поле всё из единиц
        for (size_t j = 0; j < COLS_COUNT; j++) {
            game_info->field[i][j] = 1;
        }
    }

    for (size_t i = 0; i < ROWS_COUNT; i++) { //временное поле всё из единиц
        for (size_t j = 0; j < COLS_COUNT; j++) {
            current_figure->tmp_field[i][j] = 1;
        }
    }

    clean_field(game_info, current_figure);

    for (size_t i = 0; i < ROWS_COUNT; i++) { //проверяем, что поле всё из нулей
        for (size_t j = 0; j < COLS_COUNT; j++) {
            ck_assert_int_eq(game_info->field[i][j], 0);
        }
    }

    for (size_t i = 0; i < ROWS_COUNT; i++) { //проверяем, что временное поле всё из нулей
        for (size_t j = 0; j < COLS_COUNT; j++) {
            ck_assert_int_eq(current_figure->tmp_field[i][j], 0);
        }
    }
}

START_TEST(test_is_line_filled) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    for (size_t i = 0; i < ROWS_COUNT; i++) { //нижняя граница заполнена
        for (size_t j = 0; j < COLS_COUNT; j++) {
            if (i == 19) current_figure->tmp_field[i][j] = 1;
        }
    }
    int test_val = is_line_filled(19, *current_figure);
    ck_assert_int_eq(test_val, 1);
}

START_TEST(test_matrix_pointer_copy) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    for (size_t i = 0; i < ROWS_COUNT; i++) { //поле всё из единиц
        for (size_t j = 0; j < COLS_COUNT; j++) {
            game_info->field[i][j] = 1;
        }
    }
    matrix_pointer_copy(&current_figure->tmp_field, game_info->field, 20, 10);

    for (size_t i = 0; i < ROWS_COUNT; i++) { //проверяем, что временное поле всё из единиц
        for (size_t j = 0; j < COLS_COUNT; j++) {
            ck_assert_int_eq(current_figure->tmp_field[i][j], 1);
        }
    }
}

START_TEST(test_figure_pointer_copy) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    for (size_t i = 0; i < FIGURE_ROWS; i++) { //следующая фигура из единиц
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            game_info->next[i][j] = 1;
        }
    }
    figure_pointer_copy(&current_figure->figure_field, game_info->next);

    for (size_t i = 0; i < FIGURE_ROWS; i++) { //проверяем, что временное поле всё из единиц
        for (size_t j = 0; j < FIGURE_COLS; j++) {
            ck_assert_int_eq(current_figure->figure_field[i][j], 1);
        }
    }
}

START_TEST(test_get_figure_bottom) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    clean_matrix(&current_figure->figure_field, 4, 4);
    current_figure->figure_field[3][3] = 1;
    int test_var = get_figure_bottom(*current_figure);
    ck_assert_int_eq(test_var, 3);
}

START_TEST(test_get_figure_left) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    clean_matrix(&current_figure->figure_field, 4, 4);
    current_figure->figure_field[3][3] = 1;
    int test_var = get_figure_left(*current_figure);
    ck_assert_int_eq(test_var, 3);
}

START_TEST(test_get_figure_right) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    clean_matrix(&current_figure->figure_field, 4, 4);
    current_figure->figure_field[3][3] = 1;
    int test_var = get_figure_right(*current_figure);
    ck_assert_int_eq(test_var, 3);
}

START_TEST(test_drop_line_1) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    clean_matrix(&current_figure->tmp_field, 20, 10);
    for (size_t i = 0; i < COLS_COUNT; i++) {
        current_figure->tmp_field[0][i] = 1;
    }
    drop_line(0, current_figure);
    for (size_t i = 0; i < COLS_COUNT; i++) {
        ck_assert_int_eq(current_figure->tmp_field[0][i], 0);
    }
}

START_TEST(test_drop_line_2) {
    GameInfo_t *game_info = getInstance_GameInfo();
    figure *current_figure = get_figure();
    clean_matrix(&current_figure->tmp_field, 20, 10);
    for (size_t i = 0; i < COLS_COUNT; i++) {
        current_figure->tmp_field[19][i] = 1;
    }
    drop_line(19, current_figure);
    for (size_t i = 0; i < COLS_COUNT; i++) {
        ck_assert_int_eq(current_figure->tmp_field[19][i], 0);
    }
}

Suite *tetris_helpers_test_suite() {
  Suite *s = suite_create("\033[42m-=TETRIS TEST=-\033[0m");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test_gameinfo_init);
  tcase_add_test(t, test_figure_init);
  tcase_add_test(t, test_save_and_read_hight_score);
  tcase_add_test(t, test_sideway_collision_1);
  tcase_add_test(t, test_sideway_collision_2);
  tcase_add_test(t, test_get_state);
  tcase_add_test(t, test_clean_figure);
  tcase_add_test(t, test_is_line_filled);
  tcase_add_test(t, test_matrix_pointer_copy);
  tcase_add_test(t, test_figure_pointer_copy);
  tcase_add_test(t, test_get_figure_bottom);
  tcase_add_test(t, test_get_figure_left);
  tcase_add_test(t, test_get_figure_right);
  tcase_add_test(t, test_drop_line_1);
  tcase_add_test(t, test_drop_line_2);
  suite_add_tcase(s, t);
  return s;
}