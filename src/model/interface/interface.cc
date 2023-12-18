#include "interface.h"

namespace s21 {

void Interface::start() {
  std::cout << "Welcome to the console interface of the project!" << std::endl;
  char input;
  while (true) {
    std::cout << std::endl << "Choose an option:" << std::endl;
    std::cout << "1. Loading the original graph from a file" << std::endl;
    std::cout << "2. Graph traversal in breadth with output of the result to "
                 "the console"
              << std::endl;
    std::cout << "3. Graph traversal in depth with output of the result to the "
                 "console"
              << std::endl;
    std::cout << "4. Searching for the shortest path between any two vertices "
                 "and displaying the result to the console"
              << std::endl;
    std::cout
        << "5. Searching for the shortest paths between all pairs of vertices "
           "in the graph with the output of the resulting matrix to the console"
        << std::endl;
    std::cout << "6. Searching for the minimal spanning tree in the graph with "
                 "the output of the resulting adjacency matrix to the console"
              << std::endl;
    std::cout << "7. Solving the salesman problem with the output of the "
                 "resulting route and its length to the console"
              << std::endl;
    std::cout << "press \'q\' to end the program" << std::endl;
    std::cout << "Enter option number: ";
    std::cin >> input;
    if (graph_obj_.graph_.IsEmpty() && input >= '2' && input <= '7') {
      std::cout << "Empty graph..." << std::endl;
    } else if (input == '1') {
      try {
        std::cout << "specify the path to the file:" << std::endl;
        std::string file_path;
        std::cin >> file_path;
        graph_obj_.LoadGraphFromFile(file_path);
      } catch (const s21::FileDoesNotExists &err) {
        std::cout << err.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
      }
    } else if (input == '2') {
      s21::GraphAlgorithms alg(graph_obj_);
      auto result = alg.DepthFirstSearch(graph_obj_, 0);
      std::cout << "Depth First Search result: " << std::endl;
      for (auto &it : result) {
        std::cout << it << " ";
      }
      std::cout << std::endl;
    } else if (input == '3') {
      s21::GraphAlgorithms alg(graph_obj_);
      auto result = alg.BreadthFirstSearch(graph_obj_, 0);
      std::cout << "Breadth First Search result: " << std::endl;
      for (auto &it : result) {
        std::cout << it << " ";
      }
      std::cout << std::endl;
    } else if (input == '4') {
      s21::GraphAlgorithms alg(graph_obj_);
      int v1, v2;
      std::cout << "specify vertices: ";
      std::cin >> v1 >> v2;
      if (!std::cin.fail() && v1 >= 1 && v1 <= graph_obj_.graph_.get_rows() &&
          v2 >= 1 && v1 <= graph_obj_.graph_.get_cols()) {
        std::cout << "Distance between vertices: " << std::endl;
        auto result = alg.GetShortestPathBetweenVertices(graph_obj_, --v1, --v2);
        std::cout << result << std::endl;
      } else {
        std::cout << "Vertices specified incorrectly" << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
      }
    } else if (input == '5') {
      s21::GraphAlgorithms alg(graph_obj_);
      auto result = alg.GetShortestPathsBetweenAllVertices(graph_obj_);
      result.PrintMatrix();
    } else if (input == '6') {
      s21::GraphAlgorithms alg(graph_obj_);
      auto result = alg.GetLeastSpanningTree(graph_obj_);
      result.PrintMatrix();
    } else if (input == '7') {
      s21::GraphAlgorithms alg(graph_obj_);
      auto result = alg.SolveTravelingSalesmanProblem(graph_obj_);
      std::cout << "TSM result:" << std::endl;
      for (auto &it : result.vertices) {
        std::cout << it << " ";
      }
      std::cout << std::endl << "distance: " << result.distance << std::endl;
    } else if (input == 'q') {
      std::cout << "End of the program..." << std::endl;
      break;
    } else {
      std::cout << "Invalid input. Try again." << std::endl << std::endl;
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    }
  }
}

} // namespace s21
