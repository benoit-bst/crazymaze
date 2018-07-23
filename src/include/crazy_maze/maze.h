#pragma once

#include <array>
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
template<size_t N, size_t M>
class maze
{

public:

    // type of printing
    // ascii or unicode
    enum class printing_type {
        ascii,
        unicode
    };

    explicit maze();
    ~maze();

    void random_maze();

    bool find_path();
    void clean_path();
    bool is_path();

    Coord entrance();
    Coord exit();

    void print_maze(const printing_type type = printing_type::ascii);

    maze(const maze &) = delete;
    maze& operator=(const maze &) = delete;

    maze(maze&& other) = delete;
    maze& operator=(maze&& other) = delete;

private:

    vector<int> _directions;
    vector<int> _dx;
    vector<int> _dy;
    vector<int> _ddx;
    vector<int> _ddy;
    array<array<char, M>, N> _matrix;
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

/**
 * @brief Constructor
 */
template<size_t N, size_t M>
maze<N, M>::maze()
: _directions({0,1,2,3}), // N,E,S,W
  _dx({-2, 0, 2, 0}),
  _dy({0, 2, 0, -2}),
  _ddx({-1, 0, 1, 0}),
  _ddy({0, 1, 0, -1}),
  _is_path(false)
{
    _rng.seed(std::random_device()());
}

/**
 * @brief Destructor
 */
template<size_t N, size_t M>
maze<N, M>::~maze()
{

}

/**
 * @brief generate the complete random maze
 *
 * 1. Default maze creation
 * 2. backtracking algorithm to create path
 * 3. Add random doors
 */
template<size_t N, size_t M>
void maze<N, M>::random_maze()
{
    _is_path = false;
    bool is_created = false;
    do {
        initialize_matrix();

        // We start to dig at x=1 and y=1
        _matrix[1][1] = empty_value;
        carve_passage(1, 1);

        is_created = create_random_doors();

    } while (!is_created);
}

/**
 * @brief
 */
template<size_t N, size_t M>
bool maze<N, M>::find_path()
{
    if (_is_path)
        return true;

    // Temporary matrix for BFS
    array<array<bool, M>, N> visited{};

    // Init visited
    for (unsigned int i = 0; i < N; ++i) {
        for (unsigned int  j = 0; j < M; ++j) {
            if (_matrix[i][j] != empty_value)
                visited[i][j] = true;
        }
    }

    // Mark the source cell as visited
    visited[_entrance.first][_entrance.second+1] = true;

    // Create queue
    struct node {
        list<Coord> path;
        uint32_t length;
    };

    queue<node> q;

    // Add first cell
    node s;
    s.path.push_front({_entrance.first, _entrance.second+1});
    s.length = 0;
    q.push(s);

    node curr;
    while (!q.empty())
    {
        // Current element
        curr = q.front();
        Coord pt = curr.path.back();

        // If we have reached the destination cell,
        if (pt.first == _exit.first && pt.second == _exit.second - 1) {
            _is_path = true;
            break;
        }

        // Otherwise dequeue the front cell in the queue
        // and enqueue its adjacent cells
        q.pop();

        for (const auto & dir: _directions) {

            uint32_t x = pt.first  + _ddx[dir];
            uint32_t y = pt.second + _ddy[dir];

            // if adjacent cell is valid, has path and
            // not visited yet, enqueue it.
            if (is_valid(x, y) && (!visited[x][y]))
            {
                // mark cell as visited and enqueue it
                visited[x][y] = true;
                node adj_cell = {curr.path, curr.length + 1};
                adj_cell.path.push_back({x, y});
                q.push(adj_cell);
            }
        }
    }

    // Draw shortest path
    for (const auto& cell: curr.path) {
        _matrix[cell.first][cell.second] = visited_value;
    }

    return _is_path;
}

/**
 * @brief clean path in the maze
 */
template<size_t N, size_t M>
void maze<N, M>::clean_path()
{
    if (_is_path) {
        for (unsigned int i = 1; i < N - 1; i++) {
            for (unsigned int j = 1; j < M - 1; j++) {
                if (_matrix[i][j] == visited_value)
                    _matrix[i][j] = empty_value;
            }
        }
        _is_path = false;
    }
}

/**
 * @brief If path is finded
 */
template<size_t N, size_t M>
bool maze<N, M>::is_path()
{
   return _is_path;
}

/**
 * @brief Return entrance coords
 */
template<size_t N, size_t M>
Coord maze<N, M>::entrance()
{
    return _entrance;
}

/**
 * @brief Return exit coords
 */
template<size_t N, size_t M>
Coord maze<N, M>::exit()
{
    return _exit;
}

/**
 * @brief Print internal maze
 */
template<size_t N, size_t M>
void maze<N, M>::print_maze(const printing_type type)
{
    for(size_t i = 0; i < N; ++i) {
      for(size_t j = 0; j < M; ++j) {
          // input
          if ((i == _entrance.first) && (j == _entrance.second)){
              cout << termcolor::red;
          }
          // ouput
          else if ((i == _exit.first) && (j == _exit.second)){
              cout << termcolor::red;
          }
          // borders
          else if ((i == 0) || (j == 0) || (i == N-1) || (j == M-1)) {
              cout << termcolor::green;
          }
          // path
          else if (_matrix[i][j] == visited_value){
              cout << termcolor::yellow;

          }
          // within the maze
          else {
              cout << termcolor::cyan;
          }
          if (type == printing_type::unicode) {
              cout << unicode_characters(_matrix[i][j]);
          }
          else {
              cout << _matrix[i][j];
          }

      }
      cout << "\n";
    }
}

/**
 * @brief Print internal maze
 */
template<size_t N, size_t M>
std::string  maze<N, M>::unicode_characters(const char characters)
{
    switch (characters) {
        case empty_value:
            return " ";
        case border:
            return border_unicode;
        case cross:
            return cross_unicode;
        case vertical:
            return vertical_unicode;
        case horizontal:
            return horizontal_unicode;
        case visited_value:
            return visited_value_unicode;
        default:
            return visited_value_unicode;
    }
}

/**
 * @brief Create full initial maze
 */
template<size_t N, size_t M>
void maze<N, M>::initialize_matrix()
{
    // Create border
    for (size_t i = 0; i < N; ++i) {
        _matrix[i][0] = border;
        _matrix[i][M - 1] = border;
    }
    for (size_t i = 0; i < M; ++i) {
        _matrix[0][i] = border;
        _matrix[N-1][i] = border;
    }

    // Fill maze
    for(size_t i = 1; i < N - 1; ++i) {
        for(size_t j = 1; j < M - 1; ++j) {

            // Plain line
            if (!(i % 2)) {
                if (!(j % 2)) {
                    _matrix[i][j] = cross;
                } else {
                    _matrix[i][j] = horizontal;
                }
            } else {
                if (j % 2) {
                    _matrix[i][j] = default_value;
                 } else {
                    _matrix[i][j] = vertical;
                }
            }
        }
    }
}

/**
 * @brief Create entrance and exit in the maze
 */
template<size_t N, size_t M>
bool maze<N, M>::create_random_doors()
{
    // generate entrance (even)
    _entrance = {random_number(1, N-1), 0};
    if (_entrance.first % 2 == 0)
        _entrance.first--;

    // generate exit (even)
    _exit = {random_number(1, N-1), M-1};
    if (_exit.first % 2 == 0)
        _exit.first--;

    // Is not on valid cell
    if ( (_matrix[_entrance.first][_entrance.second + 1] != empty_value) ||
         (_matrix[_exit.first][_exit.second - 1] != empty_value) ) {
        return false;
    } else {
        _matrix[_entrance.first][_entrance.second] = 73;
        _matrix[_exit.first][_exit.second] = 79;
        return true;
    }
}

/**
 * @brief Random number generator
 *
 * @param min Minimum bound
 * @param max Maximum boud
 */
template<size_t N, size_t M>
uint32_t maze<N, M>::random_number(const uint32_t min, const uint32_t max)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
    return dist(_rng);
}

/**
 * @brief Is a valid cell
 */
template<size_t N, size_t M>
bool maze<N, M>::is_valid(const uint32_t x, const uint32_t y)
{
   return (x > 0) && (x < N) && (y > 0) && (y < M);
}

/**
 * @brief Recursive backtracking algorithm to dig path within the maze
 *
 * 1. Choose a starting point in the field.
 * 2. Randomly choose a wall at that point and carve a passage through to the adjacent cell,
 *     but only if the adjacent cell has not been visited yet. This becomes the new current cell.
 * 3. If all adjacent cells have been visited, back up to the last cell that has uncarved walls and repeat.
 * 4. The algorithm ends when the process has backed all the way up to the starting point.
 */
template<size_t N, size_t M>
void maze<N, M>::carve_passage(int cx, int cy)
{
    // Shuffle direction
    std::shuffle(_directions.begin(), _directions.end(), _rng);

    // For each direction
    for (const auto & dir: _directions) {

        // new box
        uint32_t nx = cx + _dx[dir];
        uint32_t ny = cy + _dy[dir];

        // border
        uint32_t nnx = cx + _ddx[dir];
        uint32_t nny = cy + _ddy[dir];

        if ( is_valid(nx,ny) && (_matrix[nx][ny] == default_value) ) {

            _matrix[nx][ny] = _matrix[nnx][nny] = empty_value;

            carve_passage(nx, ny);
        }
    }
}

} // namespace cm

