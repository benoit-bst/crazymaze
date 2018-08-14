cmake_minimum_required(VERSION 3.2)

project(crazymaze)

set(MAIN_SOURCES
    main.cc
    utils.cc
)

# Compil flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -std=c++11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -std=c++11 -Wall -Wextra")

# my maze lib
add_subdirectory(maze)
include_directories(${maze_header_dir})
include_directories(${termcolor_SOURCE_DIR}/include)

# Curses lib for arrow driving game
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Bin
add_executable(${PROJECT_NAME} ${MAIN_SOURCES} ${CURSES_LIBRARIES})
target_link_libraries(${PROJECT_NAME} maze ${CURSES_LIBRARIES})
