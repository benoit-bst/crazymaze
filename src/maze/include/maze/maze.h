#pragma once

#include <vector>
#include <queue>
#include <list>
#include <algorithm>

#include "common.hpp"

using namespace std;

namespace cm {

/**
 * @brief maze class provide methods to play with maze's algorithm
 *
 * Methods :
 * - Backtring algorithm to create maze
 * - Printing Maze in Raw mode or Unicode mode
 * - Finding the shortest path with BFS algorithm
 *
 *  @example Raw maze (10x10)
 *
 * I : Input
 * O : Output
 * * : path
 *
 *  #####################
 *  I*|     |   |       #
 *  #*+-+ + + + +-+-+-+ #
 *  #***| |   |*******| #
 *  #-+*+-+-+-+*+-+-+*+ #
 *  # |*|***|***| |***  #
 *  # +*+*+*+*+-+ +*+-+-#
 *  # |*|*|*|***| |*|  *O
 *  # +*+*+*+-+*+ +*+-+*#
 *  #  ***|*****|  *****#
 *  #####################
 *
 */
class maze
{

public:

    // type of printing
    // ascii or unicode
    enum class printing_type {
        ascii,
        unicode
    };

    explicit maze(const uint32_t width, const uint32_t height);
    ~maze();

    void random_maze();

    bool find_path();
    void clean_path();
    bool is_path();

    Coord entrance();
    Coord exit();

    uint32_t maze_width();
    uint32_t maze_height();

    void print_maze(const printing_type type = printing_type::ascii);

    maze(const maze &) = delete;
    maze& operator=(const maze &) = delete;

    maze(maze&& other) = delete;
    maze& operator=(maze&& other) = delete;

private:

    vector<uint32_t> _directions;
    vector<int32_t> _dx;
    vector<int32_t> _dy;
    vector<int32_t> _ddx;
    vector<int32_t> _ddy;

    vector<vector<char>> _matrix;
    vector<vector<bool>> _visited;

    uint32_t _width;
    uint32_t _height;

    Coord _entrance;
    Coord _exit;
    std::mt19937 _rng;
    bool _is_path;

    void initialize_matrix();
    bool create_random_doors();
    bool is_valid(const uint32_t x, const uint32_t y);
    std::string unicode_characters(const char characters);
    uint32_t random_number(const uint32_t min, const uint32_t max);
    void carve_passage(int cx = 0, int cy = 0);
};

} // namespace cm

