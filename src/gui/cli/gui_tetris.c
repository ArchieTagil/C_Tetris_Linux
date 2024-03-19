#include "gui_tetris.h"

int main() {
    win_init();
    // static int var1 = 5;
    print_overlay();
    // getch();
    GameInfo_t *game_info = getInstance_GameInfo();
    game_info_init(game_info);

    printw("%d", game_info->next[1][1]);

    game_loop();
    endwin();
}

void game_loop() {
    bool break_flag = TRUE;
    tetris_state state = START;
    // GameInfo_t game_info;

    while (break_flag) {
        int action = getch();
        switch (action) {
        case ESC:
            userInput(Terminate, 0);
            break;
        case KEY_UP:
            userInput(Up, 0);
            break;
        case KEY_DOWN:
            userInput(Down, 0);
            break;
        case KEY_LEFT:
            userInput(Left, 0);
            break;
        case KEY_RIGHT:
            userInput(Right, 0);
            break;
        case ' ':
            userInput(Action, 0);
            break;
        case 'p':
            userInput(Pause, 0);
            break;
        case 'P':
            userInput(Pause, 0);
            break;
        }
        // GameInfo_t updateCurrentState();
    }
    
}

