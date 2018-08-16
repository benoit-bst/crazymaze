#pragma once

#include <iostream>
#include <utility>
#include <random>
#include <termcolor/termcolor.hpp>

namespace cm {

typedef std::pair<uint, uint> Coord;

// Different ascii characters to represent raw maze
static constexpr char default_value = 46;
static constexpr char empty_value   = 32;
static constexpr char visited_value = 42;
static constexpr char border        = 35;
static constexpr char cross         = 43;
static constexpr char vertical      = 124;
static constexpr char horizontal    = 45;
static constexpr char input         = 73;
static constexpr char output        = 79;

// Equivalent unicode characters to print pretty maze
static const std::string border_unicode        = "\u2588";
static const std::string cross_unicode         = "\u254B";
static const std::string vertical_unicode      = "\u2503";
static const std::string horizontal_unicode    = "\u2501";
static const std::string visited_value_unicode = "\u2588";

class common {
public:
    static std::string unicode_characters(const char characters);
    static void term_color(const char characters);
    static uint32_t random_number(const uint32_t min, const uint32_t max);
};

} // namespace cm

