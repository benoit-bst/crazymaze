#pragma once

#include <utility>
#include <termcolor/termcolor.hpp>

namespace cm {

typedef std::pair<uint32_t, uint32_t> Coord;

// Different ascii characters to represent raw maze
static const char default_value = 46;
static const char empty_value   = 32;
static const char visited_value = 42;
static const char border        = 35;
static const char cross         = 43;
static const char vertical      = 124;
static const char horizontal    = 45;
static const char input         = 73;
static const char output        = 79;

// Equivalent unicode characters to print pretty maze
static const std::string border_unicode        = "\u2588";
static const std::string cross_unicode         = "\u254B";
static const std::string vertical_unicode      = "\u2503";
static const std::string horizontal_unicode    = "\u2501";
static const std::string visited_value_unicode = "\u2588";

} // namespace cm

