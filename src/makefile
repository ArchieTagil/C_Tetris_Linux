CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 

ALL_FUNC = $(wildcard ./gui/cli/*.c)
TETRIS_LIB_FUNC = brick_game/out/tetris.o brick_game/out/helpers.o

det_OS = -lcheck -lm -lpthread -lrt -lsubunit

all: clean s21_tetris.a install
	@./tetris

install:
	@$(CC) -L. $(ALL_FUNC) -lncurses -ltetris -g -o tetris

brick_game/out/%.o: brick_game/tetris/%.c
	@$(CC) -g -c $< -o $@

s21_tetris.a: $(TETRIS_LIB_FUNC)
	@ar rc libtetris.a brick_game/out/*.o
	@ranlib libtetris.a

clean:
	@rm -f brick_game/out/* libtetris.a tetris

leaks:
	valgrind ./tetris