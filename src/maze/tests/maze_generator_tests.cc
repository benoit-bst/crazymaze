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
TEST(maze_generator_tests, print_maze)
{

    // N and M have to be odd
    maze my_maze(N, M);
    ASSERT_EQ(N, my_maze.maze_width());
    ASSERT_EQ(M, my_maze.maze_height());

    // When maze is not digged,
    // entrance and exit are on {0,0} corrds
    ASSERT_EQ(0, my_maze.entrance().first);
    ASSERT_EQ(0, my_maze.entrance().second);
    ASSERT_EQ(0, my_maze.exit().first);
    ASSERT_EQ(0, my_maze.exit().second);

    my_maze.random_maze(maze::dig_maze_algorithm::DFS);

    auto matrix = my_maze.matrix();

    // in flat matrix {1,1} is equal to 102
    ASSERT_EQ(102, my_maze.convert_coords(1, 1));

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
TEST(maze_generator_tests, repeat_generator)
{

    // N and M have to be odd.
    // warning, RBA is a recursive function,
    // so be carefull with the stack...

    array<maze::dig_maze_algorithm, 2> dma{maze::dig_maze_algorithm::RDFS, maze::dig_maze_algorithm::DFS};

    for (const auto& a : dma) {
        for (size_t i = 0; i < NB_PASS; ++i) {

            // N and M have to be odd
            uint N = common::random_number(5, 50);
            if (N % 2 == 0) N--;
            uint M = common::random_number(5, 50);
            if (M % 2 == 0) M--;
            maze my_maze(N, M);
            my_maze.random_maze(a);
        }
    }
}

/*
 Repeat finding algorithm
*/
TEST(find_path_tests, repeat_find_path)
{

    // N and M have to be odd.
    // warning, RBA is a recursive function,
    // so be carefull with the stack...

    array<maze::dig_maze_algorithm, 2> dma{maze::dig_maze_algorithm::RDFS, maze::dig_maze_algorithm::DFS};

    for (const auto& a : dma) {
        for (size_t i = 0; i < NB_PASS; ++i) {

            // N and M have to be odd.
            // warning, RBA is a recursive function,
            // so be carefull with the stack...
            uint N = common::random_number(5, 50);
            if (N % 2 == 0) N--;
            uint M = common::random_number(5, 50);
            if (M % 2 == 0) M--;
            maze my_maze(N, M);
            my_maze.random_maze(a);
            ASSERT_EQ(my_maze.is_path(), false);
            bool is_path = my_maze.find_path();
            ASSERT_EQ(is_path, true);
            my_maze.clean_path();
        }
    }
}

/*
 find_path tests
*/
TEST(find_path_tests, find_path)
{

    {
        // N and M have to be odd
        maze my_maze(N, M);
        my_maze.random_maze();
        ASSERT_EQ(my_maze.is_path(), false);
        bool is_path = my_maze.find_path();
        ASSERT_EQ(is_path, true);
        my_maze.clean_path();
        ASSERT_EQ(my_maze.is_path(), false);
    }

    {
        // N and M have to be odd
        maze my_maze(N, M);
        my_maze.random_maze();
        ASSERT_EQ(my_maze.is_path(), false);
        my_maze.clean_path();
        ASSERT_EQ(my_maze.is_path(), false);
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
