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
 * Generral Methods :
 * - random_maze : create random maze with different algorithm
 * - print_maze : Printing Maze in Raw mode or Unicode mode
 * - finding_path : Finding the shortest path with BFS algorithm
 *
 * @example Raw maze (10x10)
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
        RDFS,      // Recursive Dethp-First Search Algorithm Algorithm
        DFS        // Dethp-First Search Algorithm
    };

    // Shortest path algorithm
    enum class shortest_path_algorithm {
        BFS,        // Breadth_Fisrt search Algorithm
        AS          // A* algorithm
    };

    explicit maze(const uint width, const uint height);
    ~maze();

    void random_maze(const dig_maze_algorithm = dig_maze_algorithm::DFS);

    bool find_path(const shortest_path_algorithm = shortest_path_algorithm::BFS);
    void clean_path();
    bool is_path() const;

    Coord entrance() const;
    Coord exit() const;

    uint maze_width() const;
    uint maze_height() const;

    void print_maze(const printing_type type = printing_type::ascii);
    vector<vector<char>>& matrix();

    maze(const maze &) = delete;
    maze& operator=(const maze &) = delete;

    maze(maze&& other) = delete;
    maze& operator=(maze&& other) = delete;

private:

    // Playing with directions
    // to visit neighbours
    array<uint, 4> _directions;
    const array<int, 4> _dx;
    const array<int, 4> _dy;
    const array<int, 4> _ddx;
    const array<int, 4> _ddy;

    vector<vector<char>> _matrix;  // main matrix
    vector<vector<bool>> _visited; // used to find path

    uint _width;
    uint _height;

    Coord _entrance;
    Coord _exit;
    bool _is_path;

    void initialize_matrix();
    bool create_random_doors();
    bool is_valid(const uint x, const uint y);

    void dig_maze(const uint start_x, const uint start_y,
                  const dig_maze_algorithm dma = dig_maze_algorithm::DFS);
    void shuffle_directions();
    void recursive_deep_first_search_algorithm(const int x, const int y);
    void deep_first_search_algorithm(const int x, const int y);

    bool breadth_first_search_algorithm();
    bool a_start_algorithm();
};

} // namespace cm

