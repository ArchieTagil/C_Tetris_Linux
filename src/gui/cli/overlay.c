#include "gui_tetris.h"

void win_init() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(50);
}

void print_overlay() {
  GameInfo_t *game_info = getInstance_GameInfo();
  print_rectangle(0, 21, 0, 22);
  print_rectangle(0, 21, 23, 42);

  mvprintw(1, 24, " NEXT FIGURE: ");
  print_rectangle(2, 7, 26, 36);

  mvprintw(9, 24, " HIGH SCORE: %-5d", game_info->high_score);
  mvprintw(11, 24, " SCORE:      %-5d", game_info->score);
  mvprintw(13, 24, " LEVEL: %2d", game_info->level);
  print_running_line();
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
  mvaddch(top_y, i, ACS_URCORNER);

  for (i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(bottom_y, i, ACS_LRCORNER);
}

void print_running_line() {
  timeout(150);
  int point_to_appear_in_subwindow = 17;
  int pointer_start_read_string = 1;  // need when string must be dissapeared,
                                      // we read it not from very beggining
  WINDOW *subwindow =
      newwin(2, 17, 9, 3);  //(int nlines, int ncols, int begin_y, int begin_x)
  char *str = "Press enter to start the game. ";

  tetris_state *state = get_current_state();

  while (*state == BEFORE_START) {
    if (point_to_appear_in_subwindow > 0)
      mvwprintw(subwindow, 1, point_to_appear_in_subwindow--, "%s", str);
    else
      mvwprintw(subwindow, 1, point_to_appear_in_subwindow, "%s",
                &str[pointer_start_read_string++]);
    refresh();
    wrefresh(subwindow);
    if (pointer_start_read_string > 30) {
      pointer_start_read_string = 1;
      point_to_appear_in_subwindow = 15;
    }
    int key = getch();
    if (key == ENTER) userInput(Start, 0);
    if (key == ESC) userInput(Terminate, 0);
  }
  delwin(subwindow);
  timeout(50);
}