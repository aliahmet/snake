//
// Created by Ali Ahmet on 1/13/18.
//
#include <deque>


#ifndef NCURSES_SNAKE_SNAKE_H
#define NCURSES_SNAKE_SNAKE_H


struct Point {
    Point(int y, int x);

    int y;
    int x;

    Point copy(){
        return *(new Point(y,x));
    }
};

class Snake {
public:
    int LEFT = 0,
        RIGHT = 1,
        DOWN = 2,
        UP = 3;

    int  direction;
    std::deque<Point> joints;

    Snake() {
        std::deque<Point> joints;
        direction = DOWN;
    }


    Point next(int w, int h){
        Point front = joints.front().copy();
        if(direction == LEFT){
            front.x -= 2;
        } else if(direction == RIGHT){
            front.x += 2;
        } else if(direction == UP){
            front.y -= 1;
        } else if(direction == DOWN){
            front.y += 1;
        }

        if(front.x == w)
            front.x = 1;
        if(front.y == h-1)
            front.y = 1;

        if(front.x == -1)
            front.x = w-2;
        if(front.y == 0)
            front.y = h-2;
        
        return  front;

    }

    char head_char() {
        if(direction == LEFT){
            return '<';
        } else if(direction == RIGHT){
            return '>';
        } else if(direction == UP){
            return 'A';
        } else { // if(direction == DOWN){
            return 'V';
        }
    }
};


#endif //NCURSES_SNAKE_SNAKE_H
