#include <gtest/gtest.h>

#include "../model/graph/s21_graph.h"
#include "../model/graph_algorithm/s21_graph_algorithm.h"

TEST(DFS, T1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/textsfortest/test0.txt");
  s21::GraphAlgorithms alg(graph);
  std::vector<int> result = alg.DepthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 3, 4, 2, 5, 6};
  ASSERT_EQ(result, expected);
}

TEST(DFS, T2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/textsfortest/test1.txt");
  s21::GraphAlgorithms alg(graph);
  std::vector<int> result = alg.DepthFirstSearch(graph, 1);
  std::vector<int> expected = {1, 0, 2, 3, 4};
  ASSERT_EQ(result, expected);
}

TEST(DFS, T3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/textsfortest/test2.txt");
  s21::GraphAlgorithms alg(graph);
  std::vector<int> result = alg.DepthFirstSearch(graph, 0);
  std::vector<int> expected = {0, 1, 2, 3, 4, 6, 5, 7};
  ASSERT_EQ(result, expected);
}

TEST(GetAdjacentVerticesTest, T4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("./tests/textsfortest/newtemp.txt");
  // Test adjacent vertices of vertex 0
  std::vector<int> adj0 = graph.GetAdjacentVertices(0);
  std::vector<int> expected0 = {1, 3};
  ASSERT_EQ(adj0, expected0);

  // Test adjacent vertices of vertex 1
  std::vector<int> adj1 = graph.GetAdjacentVertices(1);
  std::vector<int> expected1 = {0, 3};
  ASSERT_EQ(adj1, expected1);

  // Test adjacent vertices of vertex 2
  std::vector<int> adj2 = graph.GetAdjacentVertices(3);
  std::vector<int> expected2 = {0, 1, 2};
  ASSERT_EQ(adj2, expected2);

  // Test adjacent vertices of vertex 3
  std::vector<int> adj3 = graph.GetAdjacentVertices(2);
  std::vector<int> expected3 = {3};
  ASSERT_EQ(adj3, expected3);
}
