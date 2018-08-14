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

Choice convert_choice(const int choice)
{
    switch (choice) {
        case 1:
            return Choice::demo;
            break;
        case 2:
            return Choice::play;
            break;
        case 3:
            return Choice::exit;
            break;
        default:
            return Choice::exit;
            break;
    }
}

} // namespace utils
