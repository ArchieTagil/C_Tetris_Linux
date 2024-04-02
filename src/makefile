CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 

ALL_FUNC = $(wildcard ./gui/cli/*.c)
TETRIS_LIB_FUNC = brick_game/out/tetris.o brick_game/out/helpers.o

det_OS = -lcheck -lm -lpthread -lrt -lsubunit

all: clean s21_tetris.a install
	@./bin/tetris

install:
	@$(CC) $(CFLAGS) -L. $(ALL_FUNC) -lncurses -ltetris -g -o ./bin/tetris

brick_game/out/%.o: brick_game/tetris/%.c
	@$(CC) $(CFLAGS) -g -c $< -o $@

s21_tetris.a: $(TETRIS_LIB_FUNC)
	@ar rc libtetris.a brick_game/out/*.o
	@ranlib libtetris.a

clean:
	@rm -f brick_game/out/* libtetris.a bin/tetris

check:
	@cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_FUNC) brick_game/tetris/*.c

leaks:
	valgrind ./tetris