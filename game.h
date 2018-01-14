#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <unistd.h>

#include "log.h"
#include "config.h"
#include "Snake.h"
#include "Panel.h"
#include "Food.h"


#ifndef NCURSES_SNAKE_GAME_H
#define NCURSES_SNAKE_GAME_H
class
Game {
public:
    Game();
    bool exit_game = FALSE;
    bool failed = FALSE;
    Snake s;
    Panel scores, game;
    Food food;
    int score = 0;

    void init_snake();

    void init_panels();

    int run();


};

#endif //NCURSES_SNAKE_GAME_H


