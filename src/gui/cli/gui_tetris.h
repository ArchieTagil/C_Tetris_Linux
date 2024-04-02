#ifndef GUI_DEFINES_TETRIS
#define GUI_DEFINES_TETRIS
#define ESC 27
#define ENTER 10

#include <ncurses.h>
#include "../../brick_game/tetris/tetris.h"


void win_init();
void print_overlay();
void print_state(GameInfo_t game_info);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void game_loop();
void clear_window();
void update_counters(GameInfo_t game_info);
void do_loop_logic(tetris_state *state, GameInfo_t *game_info);

#endif