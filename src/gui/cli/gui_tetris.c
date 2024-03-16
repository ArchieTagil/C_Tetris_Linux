#include "gui_tetris.h"

int main() {
    win_init();
    // print_overlay();
    // getch();
    game_loop();
    endwin();
}

void game_loop() {
    bool break_flag = TRUE;
    tetris_state state = START;

    while (break_flag) {
        int action = getch();
        fsm(state, action, &break_flag);
    }
    
}

