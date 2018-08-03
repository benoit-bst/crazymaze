#include <maze/maze.h>

#include <cassert>

namespace cm {

/**
 * @brief Constructor
 */
maze::maze(const uint32_t width, const uint32_t height)
: _directions({0,1,2,3}), // N,E,S,W
  _dx({-2, 0, 2, 0}),
  _dy({0, 2, 0, -2}),
  _ddx({-1, 0, 1, 0}),
  _ddy({0, 1, 0, -1}),
  _width(width),
  _height(height),
  _is_path(false)
{
    assert((width % 2) != 0 && "width need to be odd");
    assert((height % 2) != 0 && "height need to be odd");

    // matrix alloc
    _matrix.resize(height);
    _visited.resize(height);
    for (uint i = 0; i < _matrix.size(); ++i)
    {
      _matrix[i].resize(width);
      _visited[i].resize(width);
    }
}

/**
 * @brief Destructor
 */
maze::~maze()
{

}

/**
 * @brief generate the complete random maze
 *
 * 1. Default maze creation
 * 2. Add random doors
 * 3. Backtracking algorithm to create path
 *    - Recursive Backtracking Algorithm
 *    - Dethp-First Search Algorithm
 */
void maze::random_maze(const dig_maze_algorithm dma)
{
    _is_path = false;
    bool is_created = false;
    do {
        initialize_matrix();

        // We start to dig at random (x,y) position
        uint32_t start_x = common::random_number(2, _height-1);
        if (start_x % 2 == 0)
            start_x--;
        uint32_t start_y = common::random_number(2, _width-1);
        if (start_y % 2 == 0)
            start_y--;

        // Dig maze wih selected algorithm
        _matrix[start_x][start_y] = empty_value;
        dig_maze(start_x, start_y, dma);

        is_created = create_random_doors();

    } while (!is_created);
}

/**
 * @brief Find shortest path with depth-first search algorithm
 */
bool maze::find_path()
{
    if (_is_path)
        return true;

    // Init visited
    for (unsigned int i = 0; i < _height; ++i) {
        for (unsigned int  j = 0; j < _width; ++j) {
            if (_matrix[i][j] != empty_value)
                _visited[i][j] = true;
        }
    }

    // Mark the source cell as visited
    _visited[_entrance.first][_entrance.second+1] = true;

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
            if (is_valid(x, y) && (!_visited[x][y]))
            {
                // mark cell as visited and enqueue it
                _visited[x][y] = true;
                node adj_cell = {curr.path, curr.length + 1};
                adj_cell.path.push_back({x, y});
                q.push(adj_cell);
            }
        }
    }

    // Draw shortest path_height
    for (const auto& cell: curr.path) {
        _matrix[cell.first][cell.second] = visited_value;
    }

    return _is_path;
}

/**
 * @brief clean path in the maze
 */
void maze::clean_path()
{
    if (_is_path) {
        for (unsigned int i = 1; i < _height - 1; i++) {
            for (unsigned int j = 1; j < _width - 1; j++) {
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
bool maze::is_path()
{
   return _is_path;
}

/**
 * @brief Return entrance coords
 */
Coord maze::entrance()
{
    return _entrance;
}

/**
 * @brief Return exit coords
 */
Coord maze::exit()
{
    return _exit;
}

/**
 * @brief Return entrance coords
 */
uint32_t maze::maze_width()
{
    return _width;
}

/**
 * @brief Return exit coords
 */
uint32_t maze::maze_height()
{
    return _height;
}

/**
 * @brief Print internal maze
 */
void maze::print_maze(const printing_type type)
{
    for(size_t i = 0; i < _height; ++i) {
      for(size_t j = 0; j < _width; ++j) {
          // input
          if ((i == _entrance.first) && (j == _entrance.second)){
              cout << termcolor::red;
          }
          // ouput
          else if ((i == _exit.first) && (j == _exit.second)){
              cout << termcolor::red;
          }
          // borders
          else if ((i == 0) || (j == 0) || (i == _height-1) || (j == _width-1)) {
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
              cout << common::unicode_characters(_matrix[i][j]);
          }
          else {
              cout << _matrix[i][j];
          }

      }
      cout << "\n";
    }
}

/**
 * @brief return the maze char matrix
 */
vector<vector<char>>& maze::matrix()
{
    return _matrix;
}

/**
 * @brief Create full initial maze
 */
void maze::initialize_matrix()
{
    // Create border
    for (size_t i = 0; i < _height; ++i) {
        _matrix[i][0] = border;
        _matrix[i][_width - 1] = border;
    }
    for (size_t i = 0; i < _width; ++i) {
        _matrix[0][i] = border;
        _matrix[_height - 1][i] = border;
    }

    // Fill maze
    for(size_t i = 1; i < _height - 1; ++i) {
        for(size_t j = 1; j < _width - 1; ++j) {

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

            _visited[i][j] = false;
        }
    }
}

/**
 * @brief Create entrance and exit in the maze
 */
bool maze::create_random_doors()
{
    // generate entrance (even)
    _entrance = {common::random_number(1, _height-1), 0};
    if (_entrance.first % 2 == 0)
        _entrance.first--;

    // generate exit (even)
    _exit = {common::random_number(1, _height-1), _width-1};
    if (_exit.first % 2 == 0)
        _exit.first--;

    // Is not on valid cell
    // It is a possible case. Backtring can create dead cell.
    // The dead cell can be the start or the end cell.
    // In this case you have to relaunch the carve passage
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
 * @brief Is a valid cell
 */
bool maze::is_valid(const uint32_t x, const uint32_t y)
{
   return (x > 0) && (x < _height) && (y > 0) && (y < _width);
}

/**
 * @brief Dig maze algorithm
 */
void maze::dig_maze(const uint32_t start_x, const uint32_t start_y, const dig_maze_algorithm dma)
{
    switch (dma) {
        case dig_maze_algorithm::RBA:
            recursive_backtracking_algorithm(start_x, start_y);
            break;
        case dig_maze_algorithm::DFSA:
            recursive_backtracking_algorithm(start_x, start_y);
            break;
        default:
            recursive_backtracking_algorithm(start_x, start_y);

    }
}

/**
 *
 *
 */
void maze::deep_first_search_algorithm(int x, int y)
{

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
void maze::recursive_backtracking_algorithm(int x, int y)
{
    // Shuffle direction
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::shuffle(_directions.begin(), _directions.end(), rng);

    // For each direction
    for (const auto & dir: _directions) {

        // new cell
        uint32_t nx = x + _dx[dir];
        uint32_t ny = y + _dy[dir];

        // border
        uint32_t nnx = x + _ddx[dir];
        uint32_t nny = y + _ddy[dir];

        if ( is_valid(nx,ny) && (_matrix[nx][ny] == default_value) ) {

            _matrix[nx][ny] = _matrix[nnx][nny] = empty_value;

            recursive_backtracking_algorithm(nx, ny);
        }
    }
}

} // namespace cm
