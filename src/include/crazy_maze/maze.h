#pragma once

#include <array>
#include <utility>
#include <algorithm>

#include <termcolor/termcolor.hpp>

using namespace std;

namespace cm {

// ascii code to represent maze
static const char default_value = 46;
static const char empty_value = 32;
static const char visited_value = 42;
static const char border = 35;
static const char cross = 43;
static const char vertical = 124;
static const char horizontal = 45;

/**
 * @brief maze
 *
 *
 * -------- y
 * |
 * |
 * |
 * |
 * x
 */
template<size_t N, size_t M>
class maze
{

public:

    explicit maze();
    ~maze();

    void generate_random_maze();
    bool find_path();
    void clean_path();
    void is_path();
    pair<uint32_t, uint32_t> entrance();
    pair<uint32_t, uint32_t> exit();
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
    bool _path;

    void initialize_matrix();
    void create_random_doors();
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
  _path(false)
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
 * 2. Add random doors
 * 3. backtracking algorithm to create path
 */
template<size_t N, size_t M>
void maze<N, M>::generate_random_maze()
{
    _path = false;
    initialize_matrix();

    create_random_doors();

    // We start to dig at x=1 and y=1
    _matrix[1][1] = empty_value;
    carve_passage(1, 1);
}

/**
 * @brief
 */
template<size_t N, size_t M>
bool maze<N, M>::find_path()
{
    // Is not on valid box
    if ( (_matrix[_entrance.first][_entrance.second + 1] != empty_value) &&
         (_matrix[_exit.first][_exit.second - 1] != empty_value) )
        return _path = false;

    // Temporary matrix for BFS
    array<array<bool, M-2>, N-2> visited;
    for(auto& row: visited) {
        for(auto& val: row) val = false;
    }

    visited[_entrance.first-1][_entrance.second] = true;


        //int BFS(int mat[][COL], Point src, Point dest)
        //{
        //
        // check source and destination cell
        // of the matrix have value 1
        // if (!mat[src.x][src.y] || !mat[dest.x][dest.y])
        //    return INT_MAX;
        //
        // bool visited[ROW][COL];
        // memset(visited, false, sizeof visited);
        //
        // Mark the source cell as visited
        // visited[src.x][src.y] = true;
        //
        // Create a queue for BFS
        // queue<queueNode> q;
        //
        // distance of source cell is 0
        // queueNode s = {src, 0};
        // q.push(s);  // Enqueue source cell
        //
        // Do a BFS starting from source cell
        // while (!q.empty())
        // {
        //     queueNode curr = q.front();
        //     Point pt = curr.pt;
        //
        //      If we have reached the destination cell,
        //      we are done
        //      if (pt.x == dest.x && pt.y == dest.y)
        //          return curr.dist;
        //
        //      Otherwise dequeue the front cell in the queue
        //      and enqueue its adjacent cells
        //      q.pop();
        //
        //      for (int i = 0; i < 4; i++)
        //      {
        //          int row = pt.x + rowNum[i];
        //          int col = pt.y + colNum[i];
        //
        //          // if adjacent cell is valid, has path and
        //          // not visited yet, enqueue it.
        //          if (isValid(row, col) && mat[row][col] && !visited[row][col])
        //          {
        //              // mark cell as visited and enqueue it
        //              visited[row][col] = true;
        //              queueNode Adjcell = { {row, col},
        //              curr.dist + 1 };
        //              q.push(Adjcell);
        //           }
        //       }
        //}
        //
        ////return -1 if destination cannot be reached
        //return INT_MAX;
        //}
}

/**
 * @brief clean path in the maze
 */
template<size_t N, size_t M>
void maze<N, M>::clean_path()
{
    if (_path) {
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < M - 1; j++) {
                if (_matrix[i][j] == visited_value)
                    _matrix[i][j] = empty_value;
            }
        }
        _path = false;
    }
}

/**
 * @brief If path is finded
 */
template<size_t N, size_t M>
void maze<N, M>::is_path()
{
   return  _path;
}

/**
 * @brief Return entrance coords
 */
template<size_t N, size_t M>
pair<uint32_t, uint32_t> maze<N, M>::entrance()
{
    return _entrance;
}

/**
 * @brief Return exit coords
 */
template<size_t N, size_t M>
pair<uint32_t, uint32_t> maze<N, M>::exit()
{
    return _exit;
}

/**
 * @brief Print internal maze
 */
template<size_t N, size_t M>
void maze<N, M>::print_maze()
{
    for(size_t i = 0; i < N; ++i) {
      for(size_t j = 0; j < M; ++j) {
          // input
          if ((i == _entrance.first) && (j == _entrance.second)){
              cout << termcolor::red << unicode_characters(_matrix[i][j]);
          }
          // ouput
          else if ((i == _exit.first) && (j == _exit.second)){
              cout << termcolor::red << unicode_characters(_matrix[i][j]);
          }
          // borders
          else if ((i == 0) || (j == 0) || (i == N-1) || (j == M-1)) {
              cout << termcolor::green << unicode_characters(_matrix[i][j]);
          }
          // within the maze
          else {
              cout << termcolor::cyan << unicode_characters(_matrix[i][j]);
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
            return "\u2588";
        case cross:
            return "\u254B";
        case vertical:
            return "\u2503";
        case horizontal:
            return "\u2501";
        case visited_value:
            return "\u25A0";
        default:
            return "\u2588";
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
void maze<N, M>::create_random_doors()
{
    // generate entrance (even)
    _entrance = {random_number(1, N-1), 0};
    if (_entrance.first % 2 == 0)
        _entrance.first--;
    _matrix[_entrance.first][_entrance.second] = 73;

    // generate exit (even)
    _exit = {random_number(1, N-1), M-1};
    if (_exit.first % 2 == 0)
        _exit.first--;
    _matrix[_exit.first][_exit.second] = 79;
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

        if ( ((nx < N) && (nx > 0)) && ((ny < M) && (ny > 0)) && (_matrix[nx][ny] == default_value) ) {

            _matrix[nnx][nny] = empty_value;
            _matrix[nx][ny] = empty_value;

            carve_passage(nx, ny);
        }
    }
}

} // namespace cm

