#include "s21_graph_algorithm.h"

#include "../stack/s21_queue.h"

namespace s21 {

std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                        int startVertex) {
  std::vector<int> visited;
  Stack<int> stack;
  stack.Push(startVertex);
  while (!stack.Empty()) {
    int vertex = stack.Top();
    stack.Pop();
    if (std::find(visited.begin(), visited.end(), vertex) == visited.end()) {
      visited.push_back(vertex);
      std::vector<int> adjacentVertices = graph.GetAdjacentVertices(vertex);
      for (int i = adjacentVertices.size() - 1; i >= 0; i--) {
        if (std::find(visited.begin(), visited.end(), adjacentVertices[i]) ==
            visited.end()) {
          stack.Push(adjacentVertices[i]);
        }
      }
    }
  }
  return visited;
}

std::vector<int> s21::GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                          int startVertex) {
  std::vector<int> visited;
  Queue<int> queue;
  queue.Push(startVertex);
  visited.push_back(startVertex);
  while (!queue.Empty()) {
    int vertex = queue.Front();
    queue.Pop();
    for (int adjVertex : graph.GetAdjacentVertices(vertex)) {
      if (std::find(visited.begin(), visited.end(), adjVertex) ==
          visited.end()) {
        visited.push_back(adjVertex);
        queue.Push(adjVertex);
      }
    }
  }
  return visited;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  std::vector<int> distance(num_of_vert_, kInf);
  distance[vertex1] = 0;
  std::vector<int> prev(num_of_vert_, -1);
  std::vector<bool> used(num_of_vert_);
  int min_dist = 0;
  int min_vertex = vertex1;
  while (min_dist < kInf) {
    int i = min_vertex;
    used[i] = true;
    for (int j = 0; j < num_of_vert_; ++j) {
      if (distance[i] + graph.GetMatrix()(i, j) < distance[j])
        distance[j] = distance[i] + graph.GetMatrix()(i, j);
    }
    min_dist = kInf;
    for (int j = 0; j < num_of_vert_; ++j) {
      if (!used[j] && distance[j] < min_dist) {
        min_dist = distance[j];
        min_vertex = j;
      }
    }
  }
  return distance[vertex2];
}

S21Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  int n = graph.GetMatrix().get_cols();
  S21Matrix result = graph.GetMatrix();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        if ((graph.GetMatrix()(i, j) >
             graph.GetMatrix()(i, k) + graph.GetMatrix()(k, j)) &&
            (graph.GetMatrix()(i, k) != 0 && graph.GetMatrix()(k, j) != 0)) {
          result(i, j) = graph.GetMatrix()(i, k) + graph.GetMatrix()(k, j);
        }
      }
    }
  }
  return result;
}

S21Matrix s21::GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
  S21Matrix matrix = graph.GetMatrix();
  int num_ver = matrix.get_cols();
  S21Matrix res(num_ver, num_ver);
  res.ToZero();
  int no_edge = 0;
  std::vector<bool> selected(num_ver);
  selected[0] = true;
  int x, y;
  while (no_edge < num_ver - 1) {
    int min = INT_MAX;
    x = 0;
    y = 0;
    for (int i = 0; i < num_ver; ++i) {
      if (selected.at(i)) {
        for (int j = 0; j < num_ver; ++j) {
          if (!selected.at(j) && matrix(i, j)) {
            if (min > matrix(i, j)) {
              min = matrix(i, j);
              x = i;
              y = j;
            }
          }
        }
      }
    }
    res(x, y) = matrix(x, y);
    res(y, x) = matrix(x, y);
    selected[y] = true;
    no_edge++;
  }
  return res;
}

} // namespace s21
