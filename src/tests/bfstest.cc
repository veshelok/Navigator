#include <gtest/gtest.h>

#include "../model/graph/s21_graph.h"
#include "../model/graph_algorithm/s21_graph_algorithm.h"

TEST(BFS, T1) {
  s21::Graph graph;
  graph.LoadGraphFromFile(
      "./tests/textsfortest/test0.txt");
  s21::GraphAlgorithms alg(graph);
  std::vector<int> result = alg.BreadthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6};
  ASSERT_EQ(result, expected);
}

TEST(BFS, T2) {
  s21::Graph graph;
  graph.LoadGraphFromFile(
      "./tests/textsfortest/test1.txt");
  s21::GraphAlgorithms alg(graph);
  std::vector<int> result = alg.BreadthFirstSearch(graph, 1);
  std::vector<int> expected = {1, 0, 2, 3, 4};
  ASSERT_EQ(result, expected);
}

TEST(BFS, T3) {
  s21::Graph graph;
  graph.LoadGraphFromFile(
      "./tests/textsfortest/test2.txt");
  s21::GraphAlgorithms alg(graph);
  std::vector<int> result = alg.BreadthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3, 5, 4, 7, 6};
  ASSERT_EQ(result, expected);
}