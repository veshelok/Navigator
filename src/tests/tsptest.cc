#include <gtest/gtest.h>

#include "../model/exceptions.h"
#include "../model/graph/s21_graph.h"
#include "../model/graph_algorithm/s21_graph_algorithm.h"
#include "../model/matrix/s21_matrix.h"

TEST(TSP, T1) {
  s21::Graph temp;
  temp.LoadGraphFromFile("./tests/textsfortest/test_1.txt");
  s21::GraphAlgorithms temp_alg(temp);
  ASSERT_TRUE(temp_alg.SolveTravelingSalesmanProblem(temp).distance < 300);
}

TEST(TSP, T2) {
  s21::Graph temp;
  temp.LoadGraphFromFile("./tests/textsfortest/test_0.txt");
  s21::GraphAlgorithms temp_alg(temp);
  EXPECT_THROW(temp_alg.SolveTravelingSalesmanProblem(temp),
               s21::TheSolutionIsmpossible);
}

TEST(TSP, T3) {
  s21::Graph temp;
  temp.LoadGraphFromFile("./tests/textsfortest/test_2.txt");
  s21::GraphAlgorithms temp_alg(temp);
  ASSERT_TRUE(temp_alg.SolveTravelingSalesmanProblem(temp).distance < 85);
}
