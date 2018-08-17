#pragma once

#include <utility>
#include <ncurses.h>   // graphic lib for term
#include <maze/maze.h> // maze core lib

using namespace cm;

enum class MainChoice {
    demo,
    play,
    exit
};

enum class MazeChoice {
    small,
    medium,
    large,
    extra_large,
    exit
};

namespace utils {

void convert_char(const char simple_char);
void init_color();
MainChoice convert_main_choice(const int choice);
MazeChoice convert_maze_choice(const int choice);
pair<int, int> convert_maze_size(const MazeChoice maze_choice);
bool is_valid(vector<char>& matrix, uint width, uint x, uint y);
void move_cursor(cm::maze& maze);

template<std::size_t SIZE>
void print_menu(WINDOW *menu_win, const uint highlight, const array<string, SIZE>& menu)
{
    uint x = 1, y = 1;

    //box(menu_win, 0, 0);
    for(uint i = 0; i < menu.size(); ++i)
    {   if(highlight == i + 1) /* High light the present choice */
        {   wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", menu[i].c_str());
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", menu[i].c_str());
        ++y;
    }
    wrefresh(menu_win);
}

template<std::size_t SIZE>
int handle_menu(const array<string, SIZE>& menu,
                const uint height,
                const uint width,
                const uint start_y,
                const uint start_x)
{
    WINDOW *menu_win;
    uint highlight = 1;
    uint choice = 0;
    uint c;

    menu_win = newwin(height, width, start_y, start_x);
    keypad(menu_win, TRUE);
    print_menu<SIZE>(menu_win, highlight, menu);

    // main loop
    while(1) {
        c = wgetch(menu_win);
        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = menu.size();
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == menu.size())
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                mvprintw(24, 0, "Please select and press enter");
                if (c == 27)
                    endwin();
                    exit(1);
                refresh();
                break;
        }
        print_menu<SIZE>(menu_win, highlight, menu);
        if(choice != 0) // User did a choice come out of the infinite loop
            break;
    }
    clrtoeol();
    refresh();
    endwin();

    return choice;
}

} // namespace utils
