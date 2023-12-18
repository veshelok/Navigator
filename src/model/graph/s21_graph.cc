#include "s21_graph.h"

void s21::Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw s21::FileDoesNotExists();
  }
  int n;
  file >> n;
  S21Matrix graph(n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      file >> graph(i, j);
    }
  }

  graph_ = std::move(graph);
  file.close();
}

void s21::Graph::AddEdge(int u, int v) {
  edges.push_back(std::make_pair(u, v));
}

void s21::Graph::ExportGraphToDot(std::string filename) {
  std::ofstream out(filename);
  out << "digraph G {\n";
  for (int i = 0; i < V; ++i) {
    out << "    " << i << ";\n";
  }
  for (auto edge : edges) {
    out << "    " << edge.first << " -> " << edge.second << ";\n";
  }
  out << "}\n";
  out.close();
}

std::vector<int> s21::Graph::GetAdjacentVertices(int vertex) {
  std::vector<int> adjacentVertices;
  for (int i = 0; i < graph_.get_cols(); i++) {
    if (graph_(i, vertex) != 0) {
      adjacentVertices.push_back(i);
    }
  }
  return adjacentVertices;
}
