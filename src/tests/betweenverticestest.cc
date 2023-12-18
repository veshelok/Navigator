#include <gtest/gtest.h>

#include "../model/exceptions.h"
#include "../model/graph/s21_graph.h"
#include "../model/graph_algorithm/s21_graph_algorithm.h"
#include "../model/matrix/s21_matrix.h"

TEST(ShortestPathsBetweenVertices, T1) {
    s21::Graph temp;
    temp.LoadGraphFromFile("./tests/textsfortest/test_1.txt");
    s21::GraphAlgorithms temp_alg(temp);
    int result = temp_alg.GetShortestPathBetweenVertices(temp, 0, 3);
    ASSERT_EQ(result, 20);
}

TEST(ShortestPathsBetweenVertices, T2) {
    s21::Graph temp;
    temp.LoadGraphFromFile("./tests/textsfortest/test_1.txt");
    s21::GraphAlgorithms temp_alg(temp);
    int result = temp_alg.GetShortestPathBetweenVertices(temp, 5, 6);
    S21Matrix result_all = temp_alg.GetShortestPathsBetweenAllVertices(temp);
    ASSERT_EQ(result, result_all(5, 6));
}

TEST(ShortestPathsBetweenVertices, T3) {
    s21::Graph temp;
    temp.LoadGraphFromFile("./tests/textsfortest/testshotestpath.txt");
    s21::GraphAlgorithms temp_alg(temp);
    int result = temp_alg.GetShortestPathBetweenVertices(temp, 2, 3);
    ASSERT_EQ(result, 0);
}

TEST(ShortestPathsBetweenVertices, T4) {
    s21::Graph temp;
    temp.LoadGraphFromFile("./tests/textsfortest/testshotestpath.txt");
    s21::GraphAlgorithms temp_alg(temp);
    int result = temp_alg.GetShortestPathBetweenVertices(temp, 1, 3);
    ASSERT_EQ(result, 1);
}
