#include "gui_tetris.h"

void win_init() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(2);
}

void print_overlay() {
    print_rectangle(0, 22, 0, 22);
    print_rectangle(0, 22, 23, 41);

    mvprintw(1, 24, " NEXT FIGURE: ");
    print_rectangle(2, 7, 26, 36);

    mvprintw(9, 24, " HIGH SCORE: 000");
    mvprintw(11, 24, " SCORE: 000");
    mvprintw(13, 24, " LEVEL: 00");
    mvprintw(15, 24, " SPEED: 00");
    mvprintw(19, 26, " * PAUSED * ");
    print_running_line();
    print_next_figure();
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
    mvaddch(top_y, left_x, ACS_ULCORNER);

    int i = left_x + 1;

    for (; i < right_x; i++)
        mvaddch(top_y, i, ACS_HLINE);
    mvaddch(top_y, i, ACS_URCORNER);

    for (int i = top_y + 1; i < bottom_y; i++)
    {
        mvaddch(i, left_x, ACS_VLINE);
        mvaddch(i, right_x, ACS_VLINE);
    }

    mvaddch(bottom_y, left_x, ACS_LLCORNER);
    i = left_x + 1;
    for (;i < right_x; i++)
        mvaddch(bottom_y, i, ACS_HLINE);
    mvaddch(bottom_y, i, ACS_LRCORNER);
}

void print_running_line() {
    timeout(150);
    int point_to_appear_in_subwindow = 17;
    int pointer_start_read_string = 1; //need when string must be dissapeared, we read it not from very beggining
    WINDOW *subwindow = newwin(2, 17, 9, 3); //(int nlines, int ncols, int begin_y, int begin_x)
    char *str = "Press enter to start the game. ";
    while (getch() != 10) {
        if (point_to_appear_in_subwindow > 0) mvwprintw(subwindow, 1, point_to_appear_in_subwindow--, "%s", str);
        else mvwprintw(subwindow, 1, point_to_appear_in_subwindow, "%s", &str[pointer_start_read_string++]);
        refresh();
        wrefresh(subwindow);
        if (pointer_start_read_string > 30) {
            pointer_start_read_string = 1;
            point_to_appear_in_subwindow = 15;
        }
    }
    delwin(subwindow);
    timeout(50);
}

void print_next_figure() {
    while (getch() != 10)
    {
        start_color();
        // init_pair(1, COLOR_BLACK, COLOR_RED);
        // init_pair(2, COLOR_BLACK, COLOR_GREEN);
        init_pair(3, COLOR_BLACK, COLOR_YELLOW);
        // attron(COLOR_PAIR(1));
        // mvprintw(4, 3, "    ");
        // mvprintw(5, 5, "    ");

        // attron(COLOR_PAIR(2));
        // mvprintw(8, 8, "  ");
        // mvprintw(9, 6, "      ");

        attron(COLOR_PAIR(3));
        mvprintw(4, 27, "  ");
        mvprintw(5, 27, "        ");
    }
}