#ifndef S21_GRAPH_H_
#define S21_GRAPH_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../exceptions.h"
#include "../matrix/s21_matrix.h"
#include "../stack/s21_stack.h"

namespace s21 {
constexpr int kDefaultCost = 0;
class Graph {
public:
  explicit Graph() = default;
  ~Graph() = default;
  Graph(int V) { this->V = V; }
  Graph(const Graph &) = delete;
  Graph(Graph &&) = delete;
  Graph &operator=(const Graph &) = delete;
  Graph &operator=(Graph &&) = delete;

  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);

  // additional func
  void AddEdge(int u, int v);
  std::vector<int> GetAdjacentVertices(int vertex);
  S21Matrix GetMatrix() { return graph_; }
  int GetNumVertices() const { return graph_.get_rows(); }

private:
  S21Matrix graph_;
  std::vector<std::pair<int, int>> edges;
  int V;
  friend class Interface;
};

} // namespace s21

#endif // S21_GRAPH_H_
