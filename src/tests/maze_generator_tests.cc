#include <gtest/gtest.h>

#include <crazy_maze/maze.h>
#include <random>

using namespace cm;

static const int N = 30;
static const int M = 100;

/*
  Tests maze_genrator with random square size
*/
TEST(maze_generator_tests, multi_square_size){

  maze<N, M> my_maze;

  my_maze.generate_random_maze();
  my_maze.print_maze();

}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
