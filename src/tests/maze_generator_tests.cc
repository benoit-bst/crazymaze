#include <gtest/gtest.h>

#include <crazy_maze/maze.h>
#include <random>

using namespace cm;

static const int NB_PASS = 400;
static const int N = 31;
static const int M = 101;

/*
  Printing maze
*/
TEST(maze_generator_tests, print_maze){

    // N and M have to be odd
    maze<N, M> my_maze;

    my_maze.random_maze();
    // Print with ascii characters
    my_maze.print_maze();
    std::cout << "\n";
    my_maze.find_path();
    // Print with unicode characters
    my_maze.print_maze(maze<N,M>::printing_type::unicode);
}

/*
 Repeat maze creation
*/
TEST(maze_generator_tests, repeat_generator){

    // N and M have to be odd
    for (int i = 0; i < NB_PASS; ++i) {
        maze<N, M> my_maze;
        my_maze.random_maze();
    }
}

/*
  Repeat finding algorithm
*/
TEST(find_path_tests, repeat_find_path){

    // N and M have to be odd
    maze<N, M> my_maze;

    for (int i = 0; i < NB_PASS; ++i) {

        my_maze.random_maze();
        ASSERT_EQ(my_maze.is_path(), false);
        bool is_path = my_maze.find_path();
        ASSERT_EQ(is_path, true);
        if (is_path == false) {
            my_maze.print_maze();
        }
        my_maze.clean_path();
    }
}

/*
  Tests maze_genrator with random square size
*/
TEST(find_path_tests, find_path){

    {
        // N and M have to be odd
        maze<N, M> my_maze;
        my_maze.random_maze();
        ASSERT_EQ(my_maze.is_path(), false);
        bool is_path = my_maze.find_path();
        ASSERT_EQ(is_path, true);
        my_maze.clean_path();
        ASSERT_EQ(is_path, false);
    }

    {
        // N and M have to be odd
        maze<N, M> my_maze;
        my_maze.random_maze();
        ASSERT_EQ(my_maze.is_path(), false);
        my_maze.clean_path();
        ASSERT_EQ(is_path, false);
        ASSERT_EQ(my_maze.is_path(), false);

    }
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

