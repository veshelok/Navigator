#include <gtest/gtest.h>

#include "../model/exceptions.h"
#include "../model/graph/s21_graph.h"
#include "../model/graph_algorithm/s21_graph_algorithm.h"
#include "../model/matrix/s21_matrix.h"

TEST(ShortestPathsBetweenAllVertices, T1) {
  s21::Graph temp;
  temp.LoadGraphFromFile("./tests/textsfortest/test_1.txt");
  s21::GraphAlgorithms temp_alg(temp);
  S21Matrix result = temp_alg.GetShortestPathsBetweenAllVertices(temp);
  ASSERT_EQ(result(0, 3), 20);
}

TEST(ShortestPathsBetweenAllVertices, T2) {
  s21::Graph temp;
  temp.LoadGraphFromFile("./tests/textsfortest/test_1.txt");
  s21::GraphAlgorithms temp_alg(temp);
  S21Matrix result = temp_alg.GetShortestPathsBetweenAllVertices(temp);
  ASSERT_EQ(result(0, 2), 20);
}

TEST(ShortestPathsBetweenAllVertices, T3) {
  s21::Graph temp;
  temp.LoadGraphFromFile("./tests/textsfortest/test_1.txt");
  s21::GraphAlgorithms temp_alg(temp);
  S21Matrix result = temp_alg.GetShortestPathsBetweenAllVertices(temp);
  ASSERT_FALSE(result(0, 3) == temp.GetMatrix()(0, 3));
}