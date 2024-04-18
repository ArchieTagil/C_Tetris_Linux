#ifndef S21_TETRIS_TEST_H
#define S21_TETRIS_TEST_H

#include <check.h>
#include <stdio.h>
#include "../src/brick_game/tetris/tetris.h"


int run_testcase(Suite *testcase);
void run_tests(void);
Suite *tetris_test_suite();
Suite *tetris_helpers_test_suite();
void clean_matrix(int ***matrix, int rows, int cols);

#endif
