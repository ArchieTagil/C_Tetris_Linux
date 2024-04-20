#include "libtetris_test.h"

int main(void) {
  GameInfo_t *game_info = getInstance_GameInfo();
  figure *current_figure = get_figure();
  game_info_init(game_info);
  run_tests();
  free_multidimensional_matrix(game_info->field, ROWS_COUNT);
  free_multidimensional_matrix(game_info->next, FIGURE_ROWS);
  free_multidimensional_matrix(current_figure->tmp_field, ROWS_COUNT);
  free_multidimensional_matrix(current_figure->figure_field, FIGURE_ROWS);
  return 0;
}

int run_testcase(Suite *testcase) {
  int result = 1;
  static int counter_testcase = 1;
  if (counter_testcase > 1) counter_testcase++;
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result;
}

void run_tests(void) {
  Suite *list_cases[] = {tetris_helpers_test_suite(), tetris_test_suite(),
                         NULL};
  int number_failed = 0;
  int number_success = 0;
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    if (run_testcase(*current_testcase) != 0)
      number_failed++;
    else
      number_success++;
  }
  printf("\e[32mSuccess: %d\e[0m\n\e[31mFailures: %d\e[0m\n", number_success,
         number_failed);
}

void clean_matrix(int ***matrix, int rows, int cols) {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      (*matrix)[i][j] = 0;
    }
  }
}
