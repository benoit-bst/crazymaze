# Core Maze library

Contains all algorithms to handle maze :

- A Dethp-First Search algorithm to randomly dig the maze (recursive or not).
- Find the shortest path algorithm with Breadth-first search algorithm.
- Method to print, clean, etc...

The internal matrix container is **Cache friendly** (With a vector) to speed up computing.

```c++
#include <maze/maze.h>

// Create maze
// Be careful, width and height have to be odd
maze my_maze(21,11);

// generate maze
my_maze.random_maze(maze::dig_maze_algorithm::DFS);

// Retrieve internal flat matrix (is a vector)
auto matrix = my_maze.matrix();
std::cout << "This char : " << matrix[my_maze.convert_coords(1, 1)] << std::endl;

// Print with ascii characters
my_maze.print_maze();

// Find and create shortest path in the maze
my_maze.find_path();

// Print with unicode characters
my_maze.print_maze(maze::printing_type::unicode);
```
Look at the tests for more examples

## Todo

- Implement a finding path method with A* algorithm.

## Library integration

Active modern c++ flag in your compiler like -std=c++11 and put in your cmake file :

```bash
add_subdirectory(maze)
include_directories(${maze_header_dir})
include_directories(${termcolor_SOURCE_DIR}/include)
```

