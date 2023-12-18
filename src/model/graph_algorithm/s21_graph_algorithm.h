#ifndef S21_GRAPH_ALGORTHM_H_
#define S21_GRAPH_ALGORTHM_H_

#include <climits>
#include <ctime>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <random>
#include <stack>
#include <stdexcept>
#include <vector>

#include "../exceptions.h"
#include "../graph/s21_graph.h"

namespace s21 {
class GraphAlgorithms {
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

public:
  GraphAlgorithms() = default;
  GraphAlgorithms(Graph &graph) : graph_(graph) {}
  ~GraphAlgorithms() = default;

  std::vector<int> DepthFirstSearch(Graph &graph, int startVertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int startVertex);

  // 2 part
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  S21Matrix GetShortestPathsBetweenAllVertices(Graph &graph);

  // 3 part
  S21Matrix GetLeastSpanningTree(Graph &graph);

  // 4 part
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
  void PrintResultTSP();

private:
  Graph &graph_;
  int num_of_vert_ = graph_.GetMatrix().get_cols();
  int num_of_visited_vert_ = 0;
  std::vector<int> visited_vert_;
  S21Matrix pheromones_;
  TsmResult result_{{}, INFINITY};

  const double kDefaultPheromone = 10;
  const double kEvaporation = 0.2;
  const int kAlpha = 1;
  const int kBetta = 1;
  const int kInf = 101;
  const int kIterationsAnts = 500;
  bool dead_end_flag_ = false;
  int ants_ = 0;

  bool NotVisited(int i);
  double AdditiveForPheromones(int current_length);
  double Probability(int current, int next);
  double RandomForProbability();
  int FindNextVertex(int current);
  int RandomVert();
  void RecordingResult(int current_length);
  void StartInitialization(Graph &graph);
  void UpdatePheromones(int current_length);
};

} // namespace s21
#endif // S21_GRAPH_ALGORTHM_H_
