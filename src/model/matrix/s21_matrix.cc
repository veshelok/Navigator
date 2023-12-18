#include "s21_matrix.h"

int S21Matrix::get_cols() const { return cols_; }
int S21Matrix::get_rows() const { return rows_; }

void S21Matrix::set_row(int rows) {
  S21Matrix a(rows, cols_);
  int temp = rows;
  if (rows_ < rows)
    temp = rows_;
  for (int i = 0; i < temp; ++i) {
    for (int j = 0; j < cols_; ++j) {
      a.matrix_[i][j] = matrix_[i][j];
    }
  }
  Clear();
  rows_ = rows;
  CreateMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = a.matrix_[i][j];
    }
  }
}

void S21Matrix::set_col(int cols) {
  S21Matrix a(rows_, cols);
  int temp = cols;
  if (rows_ < cols)
    temp = cols_;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < temp; ++j) {
      a.matrix_[i][j] = matrix_[i][j];
    }
  }
  Clear();
  cols_ = cols;
  CreateMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = a.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (cols <= 0 || rows <= 0) {
    throw std::invalid_argument("error");
  }
  CreateMatrix();
}

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  if (&other == this) {
    throw std::out_of_range("error");
  }
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_)
    Clear();
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::Clear() {
  for (int i = 0; i < rows_; i++) {
    delete matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols, double data[]) {
  rows_ = rows;
  cols_ = cols;
  CreateMatrix();
  int count = 0;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = data[count];
      ++count;
    }
  }
}

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{0};
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    result = false;
  }
  if (result == true) {
    for (int i = 0; i < this->rows_ && result; ++i) {
      for (int j = 0; j < this->cols_ && result; ++j) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          result = false;
        }
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("sizes of matrix aren't the same");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("sizes of matrix aren't the same");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = num * matrix_[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::logic_error("sizes of matrix aren't the same");
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  cols_ = other.cols_;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = res.matrix_[i][j];
    }
  }
  res.Clear();
}

S21Matrix S21Matrix::GetMinor(int rows, int cols) const {
  if (rows_ != cols_) {
    throw std::logic_error("sizes of matrix aren't the same");
  }
  S21Matrix temp(rows_ - 1, cols_ - 1);
  int r = 0;
  for (int i = 0; i < temp.rows_; ++i) {
    if (i == rows)
      r = 1;
    int k = 0;
    for (int j = 0; j < temp.cols_; ++j) {
      if (j == cols)
        k = 1;
      temp.matrix_[i][j] = matrix_[i + r][j + k];
    }
  }
  return temp;
}

double S21Matrix::determinant() {
  if (rows_ <= 0 || rows_ != cols_) {
    throw std::out_of_range("sizes of matrix aren't the same");
  }
  double result = 0.0;
  if (cols_ == 1) {
    result = matrix_[0][0];
  } else if (cols_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < cols_; ++i) {
      S21Matrix temp = this->GetMinor(0, i);
      result += matrix_[0][i] * pow(-1.0, i) * temp.determinant();
    }
  }
  return result;
}

void S21Matrix::ToZero() const {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::PrintMatrix() const {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << std::left << std::setw(6) << matrix_[i][j];
    }
    std::cout << std::endl;
  }
}

bool S21Matrix::IsEmpty() {
  if (matrix_ == nullptr)
    return true;
  return false;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}

S21Matrix &S21Matrix::operator+(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    Clear();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix operator*(const S21Matrix &other, const double other1) {
  S21Matrix res(other);
  res.MulNumber(other1);
  return res;
}

S21Matrix operator*(const double other1, const S21Matrix &other) {
  S21Matrix res(other);
  res.MulNumber(other1);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res = (*this);
  res.MulMatrix(other);
  return res;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("error");
  }
  return matrix_[i][j];
}
