

/*
 * @Description:
 * @Author: lize
 * @Date: 2024-06-25
 * @LastEditors: lize
 */
#include <vector>

class Node {
 public:
  Node(int val) : val_(val) {
  }
  friend Node operator+(const Node& lhs, const Node& rhs) {
    return Node(lhs.val_ + rhs.val_);
  }
  friend Node operator*(const Node& lhs, const Node& rhs) {
    return Node(lhs.val_ * rhs.val_);
  }
  Node operator+=(const Node& rhs) {
    val_ += rhs.val_;
    return *this;
  }
  int val_{};
};

class SquareMatrix {
 public:
  explicit SquareMatrix(size_t len, int num = 0)
    : v_(len, std::vector<Node>(len, num)) {
  }

 private:
  std::vector<std::vector<Node>> v_{};
};

class Matrix {
 public:
  explicit Matrix(size_t row, size_t col, int num = 0)
    : v_(row, std::vector<Node>(col, num)) {
  }
  friend Matrix add1(const Matrix& lhs, const Matrix& rhs) {
    Matrix res(lhs.v_.size(), lhs.v_[0].size());
    for (size_t i = 0; i < lhs.v_.size(); ++i) {
      for (size_t j = 0; j < lhs.v_[i].size(); ++j) {
        res.v_[i][j] = lhs.v_[i][j] + rhs.v_[i][j];
      }
    }
    return res;
  }

  friend Matrix add2(const Matrix& lhs, const Matrix& rhs) {
    Matrix res(lhs.v_.size(), lhs.v_[0].size());
    for (size_t i = 0; i < lhs.v_.size(); ++i) {
      for (size_t j = 0; j < lhs.v_[i].size(); ++j) {
        res.v_[j][i] = lhs.v_[i][j] + rhs.v_[i][j];
      }
    }
    return res;
  }

  friend Matrix multi1(const Matrix& lhs, const Matrix& rhs) {
    Matrix res(lhs.v_.size(), rhs.v_[0].size());
    for (size_t i = 0; i < lhs.v_.size(); ++i) {
      for (size_t j = 0; j < rhs.v_[0].size(); ++j) {
        for (size_t k = 0; k < rhs.v_[0].size(); ++k) {
          res.v_[i][j] += lhs.v_[i][k] * rhs.v_[k][j];
        }
      }
    }
    return res;
  }

  friend Matrix multi2(const Matrix& lhs, const Matrix& rhs) {
    Matrix res(lhs.v_.size(), rhs.v_[0].size());
    for (size_t i = 0; i < lhs.v_.size(); ++i) {
      for (size_t j = 0; j < rhs.v_[0].size(); ++j) {
        for (size_t k = 0; k < rhs.v_[0].size(); ++k) {
          res.v_[j][i] += lhs.v_[j][k] * rhs.v_[k][i];
        }
      }
    }
    return res;
  }

 private:
  std::vector<std::vector<Node>> v_{};
};