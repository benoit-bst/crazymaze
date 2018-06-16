cmake_minimum_required(VERSION 3.2)

project(crazymaze)

# Path for include
set(crazymaze_headers_dir ${crazymaze_SOURCE_DIR}/include CACHE STRING "crazymaze headers dir")
include_directories( ${crazymaze_SOURCE_DIR}/include )

# Third party
add_subdirectory(third_party)
include_directories(${termcolor_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${crazymaze_SOURCE_DIR}/include")

#Tests
add_subdirectory(tests)
