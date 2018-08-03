#include <gtest/gtest.h>

#include <maze/maze.h>
#include <random>

using namespace cm;

static constexpr int NB_PASS = 400;
static constexpr int N = 101;
static constexpr int M = 31;

/*
  Printing maze
*/
TEST(maze_generator_tests, print_maze){

    // N and M have to be odd
    maze my_maze(N, M);

    my_maze.random_maze(maze::dig_maze_algorithm::RBA);
    // Print with ascii characters
    my_maze.print_maze();
    std::cout << "\n";
    my_maze.find_path();
    // Print with unicode characters
    my_maze.print_maze(maze::printing_type::unicode);
}

/*
 Repeat maze creation
*/
TEST(maze_generator_tests, repeat_generator){

    // N and M have to be odd.
    // warning, RBA is a recursive function,
    // so be carefull with the stack...

    // RBA
    {
        for (int i = 0; i < NB_PASS; ++i) {

            // N and M have to be odd
            uint N = common::random_number(5, 50);
            if (N % 2 == 0)
                N--;
            uint M = common::random_number(5, 50);
            if (M % 2 == 0)
                M--;
            maze my_maze(N, M);
            my_maze.random_maze(maze::dig_maze_algorithm::RBA);
        }
    }

    // DFSA
    {
        for (int i = 0; i < NB_PASS; ++i) {

            // N and M have to be odd
            uint N = common::random_number(5, 50);
            if (N % 2 == 0)
                N--;
            uint M = common::random_number(5, 50);
            if (M % 2 == 0)
                M--;
            maze my_maze(N, M);
            my_maze.random_maze(maze::dig_maze_algorithm::DFSA);
        }
    }
}

/*
  Repeat finding algorithm
*/
TEST(find_path_tests, repeat_find_path){

    // N and M have to be odd.
    // warning, RBA is a recursive function,
    // so be carefull with the stack...

    // RBA
    {
        for (int i = 0; i < NB_PASS; ++i) {

            // N and M have to be odd.
            // warning, RBA is a recursive function,
            // so be carefull with the stack...
            uint N = common::random_number(5, 50);
            if (N % 2 == 0)
                N--;
            uint M = common::random_number(5, 50);
            if (M % 2 == 0)
                M--;
            maze my_maze(N, M);
            my_maze.random_maze(maze::dig_maze_algorithm::RBA);
            ASSERT_EQ(my_maze.is_path(), false);
            bool is_path = my_maze.find_path();
            ASSERT_EQ(is_path, true);
            if (is_path == false) {
                my_maze.print_maze();
            }
            my_maze.clean_path();
        }
    }

    // DFSA
    {
        for (int i = 0; i < NB_PASS; ++i) {

            // N and M have to be odd.
            // warning, RBA is a recursive function,
            // so be carefull with the stack...
            uint N = common::random_number(5, 50);
            if (N % 2 == 0)
                N--;
            uint M = common::random_number(5, 50);
            if (M % 2 == 0)
                M--;
            maze my_maze(N, M);
            my_maze.random_maze(maze::dig_maze_algorithm::DFSA);
            ASSERT_EQ(my_maze.is_path(), false);
            bool is_path = my_maze.find_path();
            ASSERT_EQ(is_path, true);
            if (is_path == false) {
                my_maze.print_maze();
            }
            my_maze.clean_path();
        }
    }
}

/*
  find_path tests
*/
TEST(find_path_tests, find_path){

    {
        // N and M have to be odd
        maze my_maze(N, M);
        my_maze.random_maze(maze::dig_maze_algorithm::RBA);
        ASSERT_EQ(my_maze.is_path(), false);
        bool is_path = my_maze.find_path();
        ASSERT_EQ(is_path, true);
        my_maze.clean_path();
        ASSERT_EQ(my_maze.is_path(), false);
    }

    {
        // N and M have to be odd
        maze my_maze(N, M);
        my_maze.random_maze(maze::dig_maze_algorithm::RBA);
        ASSERT_EQ(my_maze.is_path(), false);
        my_maze.clean_path();
        ASSERT_EQ(my_maze.is_path(), false);
    }
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

