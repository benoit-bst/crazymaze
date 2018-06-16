#pragma once

// Std
#include <array>
#include <utility>

using namespace std;

namespace cm {

static const char default_value = 35;

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

    enum class door_type {start, end};

    array<array<char, M>, N> _matrix;
    pair<uint32_t, uint32_t> _start;
    pair<uint32_t, uint32_t> _end;
    std::mt19937 _rng;

    void initialize_matrix();
    pair<uint32_t, uint32_t> create_random_door(const door_type);
    void recursive_division_method();

};

/**
 * @brief
 */
template<size_t N, size_t M>
maze<N, M>::maze()
{
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
    _start = create_random_door(door_type::start);
    _end = create_random_door(door_type::end);
    recursive_division_method();
}

/**
 * @brief
 */
template<size_t N, size_t M>
void maze<N, M>::print_maze()
{
    for(size_t i = 0; i < N; ++i) {
      for(size_t j = 0; j < M; ++j) {
          cout << _matrix[i][j];
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
pair<uint32_t, uint32_t> maze<N, M>::create_random_door(const door_type type)
{
    // distribution in range [1, N]
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,N);
    uint32_t val = dist(_rng);
    if (type == door_type::start) {
        return {val, 0};
    } else {
        return {val, M-1};
    }
}

/**
 * @brief
 */
template<size_t N, size_t M>
void maze<N, M>::recursive_division_method()
{

}

} // namespace cm
