#include <gtest/gtest.h>

#include <crazy_maze/maze.h>
#include <random>

using namespace cm;

static const int N = 31;
static const int M = 101;

/*
 Repeat maze creation
*/
TEST(maze_generator_tests, repeat_generator){

    // N and M have to be odd
    maze<N, M> my_maze;
    for (int i = 0; i < 100; ++i) {
        my_maze.generate_random_maze();
    }
}

/*
  Tests maze_genrator with random square size
*/
TEST(find_path_tests, repeat_find_path){

    // N and M have to be odd
    maze<N, M> my_maze;

    for (int i = 0; i < 500; ++i) {
        my_maze.generate_random_maze();
        ASSERT_EQ(my_maze.is_path(), false);
        bool is_path = my_maze.find_path();
        ASSERT_EQ(is_path, true);
        my_maze.clean_path();
        if (is_path == false) {
            my_maze.print_maze();
        }
    }

}

/*
  Tests maze_genrator with random square size
*/
// TEST(find_path_tests, print_maze){

//     // N and M have to be odd
//     maze<N, M> my_maze;

//     my_maze.generate_random_maze();
//     my_maze.print_maze();
//     std::cout << "\n";
//     my_maze.find_path();
//     my_maze.print_maze();

// }

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

