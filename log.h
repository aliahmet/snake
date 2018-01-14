#include "config.h"
#include "iostream"
#include <fstream>


#ifndef NCURSES_SNAKE_LOG_H
#define NCURSES_SNAKE_LOG_H

class log_stream : public std::ofstream {
public:
    log_stream() {
        open(SNAKE_OUTPUT_FILE_NAME);
    }


    ~log_stream() {
        close();
    }

};

extern log_stream log;

#endif //NCURSES_SNAKE_LOG_H