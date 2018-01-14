#include "game.h"

void Game::init_snake() {

    s.joints.push_front(*(new Point(6, 5)));
    s.joints.push_front(*(new Point(7, 5)));
    s.joints.push_front(*(new Point(8, 5)));

    mvwprintw(game.win, 6, 5, "%c", SNAKE_JOINT_CHAR);
    mvwprintw(game.win, 7, 5, "%c", SNAKE_JOINT_CHAR);
    mvwprintw(game.win, 8, 5, "%c", SNAKE_JOINT_CHAR);

}

void Game::init_panels() {
    box(game.win, 0, 0);
    food.x = 13;
    food.y = 21;
}

int Game::run() {
    init_snake();
    init_panels();


    for (int i = 0; i < 10000 && !exit_game; i++) {
        int input = getch();
        switch (input) {
            default:
                log << "Unhandled press:" << input << std::endl;
                break;


            case ERR:
                break;

            case 'q':
            case 'Q':
                exit_game = true;
                break;


            case 'x':
            case 'X':
                log << "Head location x=" << s.joints.front().x << " y=" << s.joints.front().y << std::endl;
                break;

            case 'g':
            case 'G':
                log << "Food location x=" << food.x << " y=" << food.y << std::endl;
                break;
            case 'f':
            case 'F':
                exit_game = failed = 1;
                break;

            case KEY_DOWN:
                if (s.direction != s.UP)
                    s.direction = s.DOWN;

                break;

            case KEY_UP:
                if (s.direction != s.DOWN)
                    s.direction = s.UP;
                break;

            case KEY_LEFT:
                if (s.direction != s.RIGHT)
                    s.direction = s.LEFT;
                break;


            case KEY_RIGHT:
                if (s.direction != s.LEFT)
                    s.direction = s.RIGHT;
                break;


            case 'p':
            case 'P':

                int p_y_start = (game.getHeigth()) / 2 - 4;
                int p_x_start = game.getWidth() / 2 - 4;

                mvwprintw(game.win, p_y_start - 1, p_x_start, "+--------+");
                mvwprintw(game.win, p_y_start, p_x_start, "| PAUSED |");
                mvwprintw(game.win, p_y_start + 1, p_x_start, "+--------+");
                Panel::refresh_all();
                timeout(-1);
                getch();
                timeout(0);

                mvwprintw(game.win, p_y_start - 1, p_x_start, "          ");
                mvwprintw(game.win, p_y_start, p_x_start, "          ");
                mvwprintw(game.win, p_y_start + 1, p_x_start, "          ");
                break;
        }


        mvwprintw(game.win, s.joints.front().y, s.joints.front().x, "%c", SNAKE_JOINT_CHAR);

        Point new_front = s.next(game.getWidth(), game.getHeigth());
        for (auto p: s.joints) {
            if (p.x == new_front.x and p.y == new_front.y) {
                exit_game = 1;
                failed = 1;
            }
        }
        s.joints.push_front(new_front);


        mvwprintw(game.win, 2, 2, "Head{x=%d y=%d}", new_front.x, new_front.y);


        if (new_front.x == food.x and food.y == new_front.y) {
            do {

                food.x = 1 + rand() % (game.getWidth() - 2);
                food.x += food.x % 2 - 1;
                food.y = 1 + rand() % (game.getHeigth() - 2);
                score += 10;
                for (auto p: s.joints) {
                    if (p.x == food.x and p.y == food.y)
                        continue;
                }

                log << "Food moved x=" << food.x << " y=" << food.y << std::endl;
                break;
            } while (1);
            mvwprintw(game.win, new_front.y, new_front.x, "%c", 'X');
        } else {

            Point leave = s.joints.back();
            mvwprintw(game.win, leave.y, leave.x, " ");
            s.joints.pop_back();

            mvwprintw(game.win, new_front.y, new_front.x, "%c", s.head_char());
        }
        mvwprintw(game.win, food.y, food.x, "%c", SNAKE_FOOD_CHAR);
        mvwprintw(game.win, 3, 3, "%d", input);
        mvwprintw(game.win, 3, 6, "%d", s.direction);
        mvwprintw(scores.win, 0, 1, "Score: %08d", score);


        Panel::refresh_all();
        while (getch() != -1);
        usleep(SNAKE_GAME_WAIT); // Shorter delay between movements
    }

    if (failed) {
        for (int t = 0; t < 4; t++) {
            for (auto p: s.joints) {
                mvwprintw(game.win, p.y, p.x, "%c", (t % 2) ? SNAKE_JOINT_CHAR : ' ');
                Panel::refresh_all();
            }
            usleep(10 * SNAKE_GAME_WAIT); // Shorter delay between movements
        }

    }

    std::cout << Panel::all_panels.size() << std::endl;
    return 0;
}

Game::Game(): scores(1, 0, 0, 0), game(
        std::min(31, getmaxy(stdscr)),
        std::min(61, getmaxx(stdscr)),
        1, 0) {

}
