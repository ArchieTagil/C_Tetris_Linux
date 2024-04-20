CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 

ALL_FUNC = $(wildcard ./gui/cli/*.c)
TESTS_FUNC = $(wildcard ../tests/*.c ../tests/tetris_tests/*.c)
TETRIS_LIB_FUNC = brick_game/out/tetris.o brick_game/out/helpers.o
ALL_C_FILES = $(wildcard ../tests/*.c ../tests/tetris_tests/*.c ./gui/cli/*.c ./brick_game/tetris/*.c)

LIBS = -lcheck -lm -lpthread -lrt -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov

all: clean s21_tetris.a install
	@./bin/tetris

install: clean s21_tetris.a
	@$(CC) $(CFLAGS) -L. $(ALL_FUNC) -lncurses -ltetris -g -o ./bin/tetris
	rm ./brick_game/out/*.o

uninstall:
	rm ./bin/tetris

test: clean s21_tetris.a
	@$(CC) $(CFLAGS) -L. $(TESTS_FUNC) -ltetris -o ./bin/tetris_test $(LIBS)
	@./bin/tetris_test

dvi:
	@doxygen docs/Doxyfile
	@open docs/html/index.html

dist: clean
	@mkdir ../distrib
	@tar -zcvf ../distrib/tetris.tar.gz *

gcov_report: clean
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TESTS_FUNC) ./brick_game/tetris/*.c $(LIBS) -o ./bin/tetris --coverage
	@./bin/tetris
	@lcov -t "s21_tetris" -o tetris.info -c -d .
	@genhtml -o report tetris.info
	@open report/index.html
	@rm -rf ./bin/*.gcno ./bin/*gcda


brick_game/out/%.o: brick_game/tetris/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

s21_tetris.a: $(TETRIS_LIB_FUNC)
	@ar rc libtetris.a brick_game/out/*.o
	@ranlib libtetris.a

clean:
	@rm -f brick_game/out/* libtetris.a bin/tetris ./bin/*.gcno ./bin/*.gcda *.gcno *.gcda tetris.info ./bin/tetris_test
	@rm -fr report ./docs/html ../distrib

check:
	@cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_FUNC) brick_game/tetris/*.c

style:
	clang-format -n -style=google $(ALL_C_FILES)

style_repair:
	clang-format -i -style=google $(ALL_C_FILES)


leaks: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./bin/tetris_test