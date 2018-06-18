#pragma once

#include <array>
#include <utility>
#include <algorithm>

#include <termcolor/termcolor.hpp>

using namespace std;

namespace cm {

static const char default_value = 35;
static const char visited_value = 8;

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

    vector<int> _direction;
    array<array<char, M>, N> _matrix;
    pair<uint32_t, uint32_t> _entrance;
    pair<uint32_t, uint32_t> _exit;
    std::mt19937 _rng;

    void initialize_matrix();
    uint32_t random_number(uint32_t min, uint32_t max);
    void carve_passage(int cx = 0, int cy = 0);

};

/**
 * @brief
 */
template<size_t N, size_t M>
maze<N, M>::maze()
{
    _directions = {1,2,3,4};
    _dx = {-1, 0, 1, 0};
    _dy = {0, 1, 0 -1};
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

    _entrance = {random_number(0, N), 0};
    _exit = {random_number(0, N), M};

    carve_passage(random_number(0, N), random_number(0, M));
}

/**
 * @brief
 */
template<size_t N, size_t M>
void maze<N, M>::print_maze()
{
    for(size_t i = 0; i < N; ++i) {
      for(size_t j = 0; j < M; ++j) {
          cout << termcolor::magenta << _matrix[i][j];
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
  for(size_t i = 0; i < N; ++i) {
      for(size_t j = 0; j < M; ++j) {
          _matrix[i][j] = default_value;
      }
  }
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
    // Current case is visited
    _matrix[cx][cy] = visited_value;

    // Shuffle direction
    std::shuffle(_directions.begin(), _directions.end(), _rng);

    // For each direction
    for (auto & dir: _directions) {

        nx = cx + ;
        ny = cy + ;

    }




}

} // namespace cm
