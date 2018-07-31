cmake_minimum_required(VERSION 3.2)

project(maze)

SET(MAZE_SOURCES
    src/maze.cc
)

# Compilation Flags
set(CRAZYMAZE_FLAGS "-std=c++11")

# Third party
add_subdirectory(third_party)
include_directories(${termcolor_SOURCE_DIR}/include)

# Path for include
set(maze_headers_dir ${maze_SOURCE_DIR}/include CACHE STRING "maze headers dir")
include_directories( ${maze_SOURCE_DIR}/include )

set(MAZE_LIBRARIES ${maze_SOURCE_DIR}/${MAZE_SOURCES} CACHE STRING "maze headers dir")

# my maze lib
add_library(${PROJECT_NAME} STATIC ${MAZE_SOURCES})
target_include_directories(${PROJECT_NAME} INTERFACE "${maze_SOURCE_DIR}/include")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${CRAZYMAZE_FLAGS})

#Tests
add_subdirectory(tests)
