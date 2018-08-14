#pragma once

#include <ncurses.h> // graphic lib for term
#include <maze/maze.h> // maze core lib

using namespace cm;

enum class Choice {
    demo,
    play,
    exit
};

namespace utils {

void convert_char(const char simple_char);
void init_color();
Choice convert_choice(const int choice);

} // namespace utils
