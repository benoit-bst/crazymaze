#pragma once

#include <array>
#include <utility>
#include <algorithm>

#include <termcolor/termcolor.hpp>

using namespace std;

namespace cm {

static const char default_value = 46;
static const char visited_value = 32;
static const char border = 35;
static const char cross = 43;
static const char vertical = 124;
static const char horizontal = 45;

/**
 * @brief maze
 */
template<size_t N, size_t M>
class maze
{

public:

    explicit maze();
    ~maze();

    void generate_random_maze();
    void print_maze();


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
    pair<uint32_t, uint32_t> _entrance;
    pair<uint32_t, uint32_t> _exit;
    std::mt19937 _rng;

    void initialize_matrix();
    void create_random_doors();
    uint32_t random_number(uint32_t min, uint32_t max);
    void carve_passage(int cx = 0, int cy = 0);

};

/**
 * @brief
 */
template<size_t N, size_t M>
maze<N, M>::maze()
{
    _directions = {0,1,2,3};
    _dx = {-2, 0, 2, 0};
    _dy = {0, 2, 0, -2};
    _ddx = {-1, 0, 1, 0};
    _ddy = {0, 1, 0, -1};
    _rng.seed(std::random_device()());
}

/**
 * @brief
 */
template<size_t N, size_t M>
maze<N, M>::~maze()
{

}

/**
 * @brief
 */
template<size_t N, size_t M>
void maze<N, M>::generate_random_maze()
{
    initialize_matrix();

    create_random_doors();

    _matrix[1][1] = visited_value;
    carve_passage(1, 1);
}

/**
 * @brief
 */
template<size_t N, size_t M>
void maze<N, M>::print_maze()
{
    for(size_t i = 0; i < N; ++i) {
      for(size_t j = 0; j < M; ++j) {
          if ((i == _entrance.first) && (j == _entrance.second)){
              cout << termcolor::red << _matrix[i][j];
          }
          else if ((i == _exit.first) && (j == _exit.second)){
              cout << termcolor::red << _matrix[i][j];
          }
          else if ((i == 0) || (j == 0) || (i == N-1) || (j == M-1)) {
              cout << termcolor::green << _matrix[i][j];
          }
          else {
              cout << termcolor::cyan << _matrix[i][j];
          }
      }
      cout << "\n";
    }
}

/**
 * @brief
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
 * @brief
 */
template<size_t N, size_t M>
void maze<N, M>::create_random_doors()
{
    _entrance = {random_number(1, N-1), 0};
    _exit = {random_number(1, N-1), M-1};
    if (_entrance.first % 2 == 0) {
        _entrance.first--;
    }
    if (_exit.first % 2 == 0) {
        _exit.first--;
    }
    _matrix[_entrance.first][_entrance.second] = 73;
    _matrix[_exit.first][_exit.second] = 79;
}
/**
 * @brief
 */
template<size_t N, size_t M>
uint32_t maze<N, M>::random_number(uint32_t min, uint32_t max)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
    return dist(_rng);
}

/**
 * @brief
 * The depth-first search algorithm of maze generation is frequently implemented using backtracking:

    Make the initial cell the current cell and mark it as visited

    While there are unvisited cells

    If the current cell has any neighbours which have not been visited
        Choose randomly one of the unvisited neighbours
        Push the current cell to the stack
        Remove the wall between the current cell and the chosen cell
        Make the chosen cell the current cell and mark it as visited
    Else if stack is not empty
        Pop a cell from the stack
        Make it the current cell
 */
template<size_t N, size_t M>
void maze<N, M>::carve_passage(int cx, int cy)
{
    // Shuffle direction
    std::shuffle(_directions.begin(), _directions.end(), _rng);

    // For each direction
    for (const auto & dir: _directions) {

        uint32_t nx = cx + _dx[dir];
        uint32_t ny = cy + _dy[dir];

        uint32_t nnx = cx + _ddx[dir];
        uint32_t nny = cy + _ddy[dir];

        if ( ((nx < N) && (nx > 0)) && ((ny < M) && (ny > 0)) && (_matrix[nx][ny] == default_value) ) {

            _matrix[nnx][nny] = visited_value;
            _matrix[nx][ny] = visited_value;

            carve_passage(nx, ny);
        }
    }
}

} // namespace cm
