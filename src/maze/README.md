# Core Maze library

Contains all algorithms to handle maze :

- A Dethp-First Search algorithm to randomly dig the maze (recursive or not).
- Find the shortest path algorithm with Breadth-first search algorithm.
- Method to print, clean, etc...

The internal matrix container is **Cache friendly** (With a vector) to speed up computing.

## Todo

- Implement a finding path method with A* algorithm.

## Library integration

Active modern c++ flag in your compiler like -std=c++11 and put in your cmake file :

```bash
add_subdirectory(maze)
include_directories(${maze_header_dir})
include_directories(${termcolor_SOURCE_DIR}/include)
```

