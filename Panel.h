//
// Created by Ali Ahmet on 1/7/18.
//
#include <vector>
#include <curses.h>

#ifndef NCURSES_SNAKE_PANEL_H
#define NCURSES_SNAKE_PANEL_H

class Panel {
public:
    // Static Elements
    static std::vector<Panel *> all_panels;

    static void refresh_all();

    int getWidth() {
        return getmaxx(win);
    }

    int getHeigth() {
        return getmaxy(win);
    }


    // Fields
    int height, width;
    WINDOW *win;

    // Constructor
    Panel(int _height, int _width, int y_start, int x_start);


    // Methods
    void refresh();

private:
    void normalize_sizes();

};


#endif //NCURSES_SNAKE_PANEL_H
