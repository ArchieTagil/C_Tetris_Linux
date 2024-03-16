#include "tetris.h"

void fsm(tetris_state state, int action, bool *break_flag) {
    if (action == ESC) userInput(Terminate, FALSE);
    
    if (state == START) perform_start(&state);
}

void perform_start(tetris_state *state) {
    //printf("current state is: %s", *state == START ? "ok" : "no");
}

void userInput(UserAction_t action, bool hold) {
    if (action == Terminate) {
        endwin();
        exit(0);
    }
}

GameInfo_t updateCurrentState() {

}
