if(ENABLE_TESTING)

    MESSAGE(STATUS  "[maze] Compile tests")

    set(COVERAGE OFF CACHE BOOL "Coverage")

    # Add google test
    include(gtest.cmake)
    find_package (Threads)

    # Compilation Flags
    set(CRAZYMAZE_TEST_FLAGS "-O3 -std=c++11 -Wall -Wextra")

    # ThreadPool tests
    add_executable(maze_generator_tests maze_generator_tests.cc)
    target_link_libraries(maze_generator_tests PRIVATE gtest maze ${CMAKE_THREAD_LIBS_INIT})
    set_target_properties(maze_generator_tests PROPERTIES COMPILE_FLAGS ${CRAZYMAZE_TEST_FLAGS})

    if (COVERAGE)
        target_compile_options(maze_generator_tests PRIVATE --coverage)
        target_link_libraries(maze_generator_tests PRIVATE --coverage)
    endif()

endif()

