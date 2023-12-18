#ifndef INTERFACE_INTERFACE_H_
#define INTERFACE_INTERFACE_H_

#include <iostream>

#include "../graph/s21_graph.h"
#include "../graph_algorithm/s21_graph_algorithm.h"

namespace s21 {
class Interface {
public:
  Interface() = default;
  void start();

private:
  s21::Graph graph_obj_;
};

} // namespace s21
#endif // INTERFACE_INTERFACE_H_
