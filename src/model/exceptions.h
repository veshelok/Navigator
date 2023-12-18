#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

namespace s21 {

class FileDoesNotExists : public std::exception {
 public:
  [[nodiscard]] const char *what() const noexcept override {
    return "File does not exists";
  }
};
class TheSolutionIsmpossible : public std::exception {
 public:
  [[nodiscard]] const char *what() const noexcept override {
    return "The solution is impossible";
  }
};
}  // namespace s21
#endif  // EXCEPTIONS_H_
