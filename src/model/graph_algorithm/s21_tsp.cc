#include "s21_graph_algorithm.h"

s21::GraphAlgorithms::TsmResult
s21::GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  StartInitialization(graph);
  bool flag = true;
  double current_length = 0;
  for (int k = 0; k < kIterationsAnts; ++k) {
    for (int l = 0; l < ants_; ++l) {
      dead_end_flag_ = false;
      current_length = 0;
      int current = RandomVert();
      visited_vert_.clear();
      visited_vert_.push_back(current);
      ++num_of_visited_vert_;
      int next = FindNextVertex(current);
      visited_vert_.push_back(next);
      ++num_of_visited_vert_;
      current_length += graph_.GetMatrix()(current, next);

      for (int i = 1; i < num_of_vert_ - 1; ++i) {
        current = next;
        next = FindNextVertex(current);
        ++num_of_visited_vert_;
        if ((graph_.GetMatrix()(current, next) != 0) &&
            (graph_.GetMatrix()(current, next) != kInf)) {
          visited_vert_.push_back(next);
          current_length += graph_.GetMatrix()(current, next);
        }
      }
      if ((graph_.GetMatrix()(next, visited_vert_.front()) != 0) &&
          (graph_.GetMatrix()(next, visited_vert_.front()) != kInf)) {
        visited_vert_.push_back(visited_vert_.front());
        current_length += graph_.GetMatrix()(next, visited_vert_.front());
      } else {
        dead_end_flag_ = true;
      }
      if ((current_length < result_.distance) && (!dead_end_flag_)) {
        flag = false;
        RecordingResult(current_length);
      }
    }
    if (flag) {
      throw TheSolutionIsmpossible();
    }
    UpdatePheromones(current_length);
  }
  return result_;
}

void s21::GraphAlgorithms::RecordingResult(int current_length) {
  std::vector<int> temp(visited_vert_);
  for (int i = 0; i < temp.size(); ++i) {
    temp[i] += 1;
  }
  result_.distance = current_length;
  result_.vertices = temp;
}

void s21::GraphAlgorithms::StartInitialization(Graph &graph) {
  num_of_vert_ = graph.GetMatrix().get_cols();
  ants_ = num_of_vert_;
  S21Matrix tmp_pheromones(num_of_vert_, num_of_vert_);
  for (int i = 0; i < num_of_vert_; ++i) {
    for (int j = 0; j < num_of_vert_; ++j) {
      tmp_pheromones(i, j) = kDefaultPheromone;
    }
  }
  pheromones_ = tmp_pheromones;
}

void s21::GraphAlgorithms::UpdatePheromones(int current_length) {
  double t = AdditiveForPheromones(current_length);
  S21Matrix tmp_pheromones(pheromones_);
  for (int i = 0; i < tmp_pheromones.get_rows(); ++i) {
    for (int j = 0; j < tmp_pheromones.get_cols(); ++j) {
      tmp_pheromones(i, j) = (1 - kEvaporation) * pheromones_(i, j);
    }
  }
  std::vector<int>::iterator next = visited_vert_.begin() + 1,
                             current = visited_vert_.begin();
  for (; next != visited_vert_.end(); ++current, ++next) {
    tmp_pheromones(*current, *next) =
        (1 - kEvaporation) * pheromones_(*current, *next) + t;
    tmp_pheromones(*next, *current) =
        (1 - kEvaporation) * pheromones_(*next, *current) + t;
  }
  pheromones_ = tmp_pheromones;
}

double s21::GraphAlgorithms::AdditiveForPheromones(int current_length) {
  double Q = 0;
  double t = 0;
  for (int i = 0; i < num_of_vert_; ++i) {
    for (int j = 0; j < num_of_vert_; ++j) {
      Q += graph_.GetMatrix()(i, j);
    }
  }
  t = (Q / (num_of_vert_ * num_of_vert_)) / current_length;
  return t;
}

int s21::GraphAlgorithms::FindNextVertex(int current) {
  double p_current = 0;
  double p_before = 0;
  double random_number = RandomForProbability();
  int next_vertex = visited_vert_.front();

  for (int i = 0; i < num_of_vert_; ++i) {
    if ((graph_.GetMatrix()(current, i) != 0) &&
        (graph_.GetMatrix()(current, i) != kInf) && NotVisited(i)) {
      p_before = p_current;
      p_current += Probability(current, i);
      if ((random_number > p_before) && (random_number <= p_current)) {
        next_vertex = i;
      }
    }
  }
  if ((num_of_visited_vert_ != num_of_vert_) &&
      (next_vertex == visited_vert_.front())) {
    dead_end_flag_ = true;
    return 0;
  }
  return next_vertex;
}

double s21::GraphAlgorithms::Probability(int current, int next) {
  double sum = 0;
  for (int j = 0; j < num_of_vert_; ++j) {
    if (NotVisited(j) && (graph_.GetMatrix()(current, j) != 0) &&
        (graph_.GetMatrix()(current, j) != kInf)) {
      sum += pow(pheromones_(current, j), kAlpha) * 1 /
             pow(graph_.GetMatrix()(current, j), kBetta);
    }
  }
  return pow(pheromones_(current, next), kAlpha) * 1 /
         pow(graph_.GetMatrix()(current, next), kBetta) / sum;
}

bool s21::GraphAlgorithms::NotVisited(int i) {
  for (std::vector<int>::iterator iter = visited_vert_.begin();
       iter != visited_vert_.end(); ++iter) {
    if (*iter == i) {
      return false;
    }
  }
  return true;
}

int s21::GraphAlgorithms::RandomVert() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(
      0, num_of_vert_ - 1);
  return (static_cast<double>(dist(rng)));
}

double s21::GraphAlgorithms::RandomForProbability() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);
  return (static_cast<double>(dist(rng))) / 100;
}

void s21::GraphAlgorithms::PrintResultTSP() {
  std::cout << result_.distance << " - distance" << std::endl;
  for (int i = 0; i < num_of_vert_ + 1; ++i) {
    std::cout << result_.vertices[i] << " - ";
  }
  std::cout << std::endl;
}
