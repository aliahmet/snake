#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <unistd.h>
#include "game.h"

bool is_screen_large_enough() {
    int row_cnt, col_cnt;
    getmaxyx(stdscr, row_cnt, col_cnt);
    if (SNAKE_GAME_DEBUG)
        fprintf(stdout, "Expected %dx%d got %dx%d\n", SNAKE_GAME_MIN_FRAME_HEIGHT, SNAKE_GAME_MIN_FRAME_WIDTH, row_cnt,
                col_cnt);
    return row_cnt >= SNAKE_GAME_MIN_FRAME_HEIGHT && col_cnt >= SNAKE_GAME_MIN_FRAME_WIDTH;

}

int main() {

    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    curs_set(FALSE);
    int _res = 0;



    int row_cnt, col_cnt;

    getmaxyx(stdscr, row_cnt, col_cnt);
    log << "Height=" << row_cnt << " Width=" << col_cnt << std::endl;


    if (is_screen_large_enough()) {
        try {
            log << "File: " << __FILE__ << " Line: " << __LINE__ << std::endl;

            log << "File: " << __FILE__ << " Line: " << __LINE__ << std::endl;
            Game game;
            _res = game.run();
            log << "File: " << __FILE__ << " Line: " << __LINE__ << std::endl;

        } catch (const std::exception &e) {
            endwin(); // Restore normal terminal behavior
            throw e;
            return 1;
        }
    } else {
        std::cerr << "Screen is not large enough!" << std::endl;

    }
    endwin();
    return _res;
}