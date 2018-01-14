//
// Created by Ali Ahmet on 1/7/18.
//

#include "Panel.h"

void Panel::normalize_sizes() {
    int row_cnt, col_cnt;
    getmaxyx(stdscr, row_cnt, col_cnt);
    if (height == 0)
        height = row_cnt;
    if (width == 0)
        width = col_cnt;
}

void Panel::refresh() {
    wrefresh(win);
}

void Panel::refresh_all() {
    for (Panel *p: all_panels)
        p->refresh();
}

Panel::Panel(int _height, int _width, int y_start, int x_start) : height(_height), width(_width) {
    win = newwin(_height, _width, y_start, x_start);
    Panel::all_panels.push_back(this);
    normalize_sizes();

}

std::vector<Panel *> Panel::all_panels;

