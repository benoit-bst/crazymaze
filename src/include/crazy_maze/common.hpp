#pragma once

#include <utility>
#include <termcolor/termcolor.hpp>

namespace cm {   

typedef std::pair<uint32_t, uint32_t> Coord;

// Different ascii char to represent raw maze
static const char default_value = 46;
static const char empty_value   = 32;
static const char visited_value = 42;
static const char border        = 35;
static const char cross         = 43;
static const char vertical      = 124;
static const char horizontal    = 45;
static const char input         = 73;
static const char output        = 79;

} // namespace cm

