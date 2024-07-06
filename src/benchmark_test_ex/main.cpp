/*
 * @Description:
 * @Author: lize
 * @Date: 2024-06-16
 * @LastEditors: lize
 */

#include <benchmark/benchmark.h>

#include <random>
#include <vector>

constexpr size_t len = 0x1000;
constexpr size_t row = 0x04ff;
constexpr size_t col = 0x1000;
// 创建随机数引擎（使用默认种子）
static std::default_random_engine engine;

// 创建均匀分布对象，生成0到100之间的随机整数
static std::uniform_int_distribution<int> distribution(0, 100);
class SquareMatrix {
 public:
  explicit SquareMatrix(size_t len, int num = 0)
    : v_(len, std::vector<int>(len, num)) {
  }

 private:
  std::vector<std::vector<int>> v_{};
};

class Matrix {
 public:
  explicit Matrix(size_t row, size_t col, int num = 0)
    : v_(row, std::vector<int>(col, num)) {
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
          res.v_[j][i] += lhs.v_[i][k] * rhs.v_[k][j];
        }
      }
    }
    return res;
  }

 private:
  std::vector<std::vector<int>> v_{};
};

static void TEST_ADD_1(benchmark::State& state) {
  for (auto _ : state) {
    auto res = add1(Matrix(len, len, distribution(engine)),
                    Matrix(len, len, distribution(engine)));
  }
}
static void TEST_ADD_2(benchmark::State& state) {
  for (auto _ : state) {
    auto res = add2(Matrix(len, len, distribution(engine)),
                    Matrix(len, len, distribution(engine)));
  }
}

static void TEST_MULTI_1(benchmark::State& state) {
  for (auto _ : state) {
    auto res = multi1(Matrix(row, col, distribution(engine)),
                      Matrix(col, row, distribution(engine)));
  }
}
static void TEST_MULTI_2(benchmark::State& state) {
  for (auto _ : state) {
    auto res = multi2(Matrix(row, col, distribution(engine)),
                      Matrix(col, row, distribution(engine)));
  }
}

BENCHMARK(TEST_ADD_1);
BENCHMARK(TEST_ADD_2);
BENCHMARK(TEST_MULTI_1);
BENCHMARK(TEST_MULTI_2);
BENCHMARK_MAIN();
