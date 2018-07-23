#include <gtest/gtest.h>

#include <crazy_maze/maze.h>
#include <random>

using namespace cm;

static const int N = 31;
static const int M = 101;

/*
  Tests maze_generator with random square size
*/
/* TEST(maze_generator_tests, multi_square_size){ */

/*   // N and M have to be odd */
/*   maze<N, M> my_maze; */

/*   my_maze.generate_random_maze(); */
/*   my_maze.print_maze(); */

/* } */
/*
  Tests maze_genrator with random square size
*/
TEST(find_path_tests, multi_find_path){

  // N and M have to be odd
  maze<N, M> my_maze;

  my_maze.generate_random_maze();
  my_maze.print_maze();
  bool is_path = my_maze.find_path();
  my_maze.print_maze();

}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

