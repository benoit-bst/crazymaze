#pragma once

#include <vector>
#include <array>
#include <queue>
#include <list>
#include <algorithm>

#include "common.h"

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

    // Dig maze algorithm
    enum class dig_maze_algorithm {
        RBA,        // Recursive Backtracking Algorithm
        DFSA        // Dethp-First Search Algorithm
    };

    explicit maze(const uint32_t width, const uint32_t height);
    ~maze();

    void random_maze(const dig_maze_algorithm = dig_maze_algorithm::DFSA);

    bool find_path();
    void clean_path();
    bool is_path();

    Coord entrance();
    Coord exit();

    uint32_t maze_width();
    uint32_t maze_height();

    void print_maze(const printing_type type = printing_type::ascii);
    vector<vector<char>>& matrix();

    maze(const maze &) = delete;
    maze& operator=(const maze &) = delete;

    maze(maze&& other) = delete;
    maze& operator=(maze&& other) = delete;

private:

    array<uint32_t, 4> _directions;
    array<int32_t, 4> _dx;
    array<int32_t, 4> _dy;
    array<int32_t, 4> _ddx;
    array<int32_t, 4> _ddy;

    vector<vector<char>> _matrix;
    vector<vector<bool>> _visited;

    uint32_t _width;
    uint32_t _height;

    Coord _entrance;
    Coord _exit;
    bool _is_path;

    void initialize_matrix();
    void dig_maze(const uint32_t start_x, const uint32_t start_y, const dig_maze_algorithm dma = dig_maze_algorithm::DFSA);
    void recursive_backtracking_algorithm(int x, int y);
    void deep_first_search_algorithm(int x, int y);
    bool create_random_doors();
    bool is_valid(const uint32_t x, const uint32_t y);
};

} // namespace cm

