#include <gtest/gtest.h>

#include "../model/graph/s21_graph.h"
#include "../model/graph_algorithm/s21_graph_algorithm.h"

TEST(LST, T1) {
    s21::Graph graph;
    graph.LoadGraphFromFile(
            "./tests/textsfortest/test0.txt");
    s21::GraphAlgorithms alg(graph);
    S21Matrix result = alg.GetLeastSpanningTree(graph);
    double tmp[] = {0, 1, 1, 0, 0, 0, 0,
                    1, 0, 0, 1, 1, 0, 0,
                    1, 0, 0, 0, 0, 1, 1,
                    0, 1, 0, 0, 0, 0, 0,
                    0, 1, 0, 0, 0, 0, 0,
                    0, 0, 1, 0, 0, 0, 0,
                    0, 0, 1, 0, 0, 0, 0};
    S21Matrix expected(7, 7, tmp);
    ASSERT_EQ(result.get_rows(), expected.get_rows());
    ASSERT_EQ(result.get_cols(), expected.get_cols());
    for (int i = 0; i < result.get_rows(); ++i) {
        for (int j = 0; j < result.get_cols(); ++j) {
            ASSERT_EQ(result(i, j), expected(i, j));
        }
    }

}

TEST(LST, T2) {
    s21::Graph graph;
    graph.LoadGraphFromFile(
            "./tests/textsfortest/test_0.txt");
    s21::GraphAlgorithms alg(graph);
    S21Matrix result = alg.GetLeastSpanningTree(graph);
    double tmp[] = {0, 0, 0, 0, 3,
                    0, 0, 1, 0, 1,
                    0, 1, 0, 0, 0,
                    0, 0, 0, 0, 1,
                    3, 1, 0, 1, 0};
    S21Matrix expected(5, 5, tmp);
    ASSERT_EQ(result.get_rows(), expected.get_rows());
    ASSERT_EQ(result.get_cols(), expected.get_cols());
    for (int i = 0; i < result.get_rows(); ++i) {
        for (int j = 0; j < result.get_cols(); ++j) {
            ASSERT_EQ(result(i, j), expected(i, j));
        }
    }
}

TEST(LST, T3) {
    s21::Graph graph;
    graph.LoadGraphFromFile(
            "./tests/textsfortest/test_1.txt");
    s21::GraphAlgorithms alg(graph);
    S21Matrix result = alg.GetLeastSpanningTree(graph);
    double tmp[] = {0, 0, 0, 0, 0, 0, 0, 12, 4, 0, 0,
                    0, 0, 0, 0, 0, 0, 72, 0, 0, 0, 12,
                    0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 13,
                    0, 0, 0, 0, 4, 12, 0, 0, 0, 0, 0,
                    0, 0, 0, 4, 0, 0, 0, 9, 0, 0, 0,
                    0, 0, 0, 12, 0, 0, 0, 0, 0, 3, 0,
                    0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    12, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0,
                    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
                    0, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0};
    S21Matrix expected(11, 11, tmp);
    ASSERT_EQ(result.get_rows(), expected.get_rows());
    ASSERT_EQ(result.get_cols(), expected.get_cols());
    for (int i = 0; i < result.get_rows(); ++i) {
        for (int j = 0; j < result.get_cols(); ++j) {
            ASSERT_EQ(result(i, j), expected(i, j));
        }
    }
}

TEST(LST, T4) {
    s21::Graph graph;
    graph.LoadGraphFromFile(
            "./tests/textsfortest/test_2.txt");
    s21::GraphAlgorithms alg(graph);
    S21Matrix result = alg.GetLeastSpanningTree(graph);
    double tmp[] = {0, 0, 0, 0, 16,
                    0, 0, 15, 0, 0,
                    0, 15, 0, 0, 14,
                    0, 0, 0, 0, 4,
                    16, 0, 14, 4, 0};
    S21Matrix expected(5, 5, tmp);
    ASSERT_EQ(result.get_rows(), expected.get_rows());
    ASSERT_EQ(result.get_cols(), expected.get_cols());
    for (int i = 0; i < result.get_rows(); ++i) {
        for (int j = 0; j < result.get_cols(); ++j) {
            ASSERT_EQ(result(i, j), expected(i, j));
        }
    }
}
