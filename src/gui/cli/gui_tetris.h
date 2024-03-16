#ifndef GUI_DEFINES_TETRIS
#define GUI_DEFINES_TETRIS

#include <ncurses.h>
#include "../../brick_game/tetris/tetris.h"

void win_init();
void print_overlay();
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void game_loop();

#endif