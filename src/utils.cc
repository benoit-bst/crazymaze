#include "utils.h"

namespace utils {

void convert_char(const char simple_char)
{
    switch (simple_char) {
        case default_value:
            attron(COLOR_PAIR(4));
            addch(ACS_BULLET);
            attroff(COLOR_PAIR(4));
            break;
        case empty_value:
            attron(COLOR_PAIR(4));
            addch(ACS_CKBOARD);
            attroff(COLOR_PAIR(4));
            break;
        case visited_value:
            attron(COLOR_PAIR(5));
            addch(ACS_DIAMOND);
            attroff(COLOR_PAIR(5));
            break;
        case cm::border:
            attron(COLOR_PAIR(2));
            addch(ACS_CKBOARD);
            attroff(COLOR_PAIR(2));
            break;
        case cross:
            attron(COLOR_PAIR(2));
            addch(ACS_PLUS);
            attroff(COLOR_PAIR(2));
            break;
        case vertical:
            attron(COLOR_PAIR(2));
            addch(ACS_VLINE);
            attroff(COLOR_PAIR(2));
            break;
        case horizontal:
            attron(COLOR_PAIR(2));
            addch(ACS_HLINE);
            attroff(COLOR_PAIR(2));
            break;
        case input:
            attron(COLOR_PAIR(3));
            addch(ACS_CKBOARD);
            attroff(COLOR_PAIR(3));
            break;
        case output:
            attron(COLOR_PAIR(3));
            addch(ACS_CKBOARD);
            attroff(COLOR_PAIR(3));
            break;
        default:
            attron(COLOR_PAIR(4));
            addch(ACS_CKBOARD);
            attroff(COLOR_PAIR(4));
            break;
    }
}

void init_color()
{
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_BLACK);
    init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(9, COLOR_RED, COLOR_GREEN);
    init_pair(10, COLOR_RED, COLOR_WHITE);
}

MainChoice convert_main_choice(const int choice)
{
    switch (choice) {
        case 1:
            return MainChoice::demo;
            break;
        case 2:
            return MainChoice::play;
            break;
        case 3:
            return MainChoice::exit;
            break;
        default:
            return MainChoice::exit;
            break;
    }
}

MazeChoice convert_maze_choice(const int choice)
{
    switch (choice) {
        case 1:
            return MazeChoice::small;
            break;
        case 2:
            return MazeChoice::medium;
            break;
        case 3:
            return MazeChoice::large;
            break;
        case 4:
            return MazeChoice::extra_large;
            break;
        case 5:
            return MazeChoice::exit;
            break;
        default:
            return MazeChoice::small;
            break;
    }
}

pair<int, int> convert_maze_size(const MazeChoice maze_choice)
{
    switch (maze_choice) {
        case MazeChoice::small:
            return make_pair<int, int>(27, 9);
        case MazeChoice::medium:
            return make_pair<int, int>(51, 15);
        case MazeChoice::large:
            return make_pair<int, int>(81, 27);
        case MazeChoice::extra_large:
            return make_pair<int, int>(171, 41);
        default:
            return make_pair<int, int>(27, 9);
    }
}

bool is_valid(cm::maze& maze, uint x, uint y)
{
    auto& matrix = maze.matrix();
    if (matrix[maze.convert_coords(x, y)] == cm::empty_value ||
        matrix[maze.convert_coords(x, y)] == cm::visited_value)
        return true;
    else
        return false;
}

void move_cursor(cm::maze& maze)
{
    int offset = 1;
    bool show_path = false;
    queue<Coord> my_path;
    auto entrance = maze.entrance();
    auto exit = maze.exit();
    auto current_position = make_pair<uint, uint>(entrance.first + 0, entrance.second + 1);

    if (is_valid(maze, current_position.first, current_position.second)) {
        attron(COLOR_PAIR(1));
        mvaddch(current_position.first + offset, current_position.second + offset, ACS_CKBOARD);
        attroff(COLOR_PAIR(1));
        refresh();
    } else {
        return;
    }

    keypad(stdscr, TRUE);
    int ch;
    do {
        ch = getch();

        switch (ch) {
            case KEY_UP:
            case 'k':
            case 'K':
                if (is_valid(maze, current_position.first - 1, current_position.second + 0)) {
                    mvaddch(current_position.first + offset, current_position.second + offset, ACS_DIAMOND);
                    current_position.first--;
                    mvaddch(current_position.first + offset, current_position.second + offset, ACS_CKBOARD);
                    refresh();
                }
                 break;
            case KEY_DOWN:
            case 'j':
            case 'J':
                if (is_valid(maze,  current_position.first + 1, current_position.second + 0)) {
                    mvaddch(current_position.first + offset, current_position.second + offset, ACS_DIAMOND);
                    current_position.first++;
                    mvaddch(current_position.first + offset, current_position.second + offset, ACS_CKBOARD);
                    refresh();
                }
                 break;
                break;
            case KEY_LEFT:
            case 'h':
            case 'H':
                if (is_valid(maze, current_position.first + 0, current_position.second - 1)) {
                    mvaddch(current_position.first + offset, current_position.second + offset, ACS_DIAMOND);
                    current_position.second--;
                    mvaddch(current_position.first + offset, current_position.second + offset, ACS_CKBOARD);
                    refresh();
                }
                break;
            case KEY_RIGHT:
            case 'l':
            case 'L':
                if (is_valid(maze, current_position.first + 0, current_position.second + 1)) {
                    mvaddch(current_position.first + offset, current_position.second + offset, ACS_DIAMOND);
                    current_position.second++;
                    mvaddch(current_position.first + offset, current_position.second + offset, ACS_CKBOARD);
                    refresh();
                }
                break;
            case 'p':
            case 'P':
                if (show_path == false) {
                    maze.find_path();
                    auto mat = maze.matrix();
                    for (uint i = 0; i < mat.size(); ++i) {
                        if (mat[i] == visited_value) {
                            mvaddch(std::floor(i/maze.maze_width()) + offset, (i %  maze.maze_width()) + offset, ACS_BULLET);
                        }
                    }
                    show_path = true;
                } else {
                    auto mat = maze.matrix();
                    for (uint i = 0; i < mat.size(); ++i) {
                        if (mat[i] == visited_value) {
                            attron(COLOR_PAIR(4));
                            mvaddch(std::floor(i/maze.maze_width()) + offset, (i %  maze.maze_width()) + offset, ACS_CKBOARD);
                            attroff(COLOR_PAIR(4));
                        }
                    }
                    show_path = false;
                }
                mvaddch(current_position.first + offset, current_position.second + offset, ACS_CKBOARD);
                refresh();
                break;
        }
        if ((current_position.first == exit.first) && (current_position.second == exit.second - 1)) {
            printw("  You win !!! in secs\n ");
            getch();
            keypad(stdscr, FALSE);
            return;
        }

    } while ((ch != 'q') && (ch != 'Q') && (ch != 27));

    keypad(stdscr, FALSE);
}

} // namespace utils
