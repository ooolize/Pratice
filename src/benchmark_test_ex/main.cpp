/*
 * @Description:
 * @Author: lize
 * @Date: 2024-06-16
 * @LastEditors: lize
 */

#include <benchmark/benchmark.h>

#include <random>
#include <vector>
// Register the function as a benchmark
// using Matrix = std::vector<std::vector<int>>;
constexpr size_t len = 0x1000;
// 创建随机数引擎（使用默认种子）
std::default_random_engine engine;

// 创建均匀分布对象，生成0到100之间的随机整数
std::uniform_int_distribution<int> distribution(0, 100);
class Matrix {
 public:
  explicit Matrix(size_t len, int num = 0)
    : v_(len, std::vector<int>(len, num)) {
  }
  friend Matrix add1(const Matrix& lhs, const Matrix& rhs) {
    Matrix res(lhs.v_.size());
    for (size_t i = 0; i < lhs.v_.size(); ++i) {
      for (size_t j = 0; j < lhs.v_[i].size(); ++j) {
        res.v_[i][j] = lhs.v_[i][j] + rhs.v_[i][j];
      }
    }
    return res;
  }

  friend Matrix add2(const Matrix& lhs, const Matrix& rhs) {
    Matrix res(lhs.v_.size());
    for (size_t i = 0; i < lhs.v_.size(); ++i) {
      for (size_t j = 0; j < lhs.v_[i].size(); ++j) {
        res.v_[j][i] = lhs.v_[j][i] + rhs.v_[j][i];
      }
    }
    return res;
  }

 private:
  std::vector<std::vector<int>> v_;
};
static void ReadByRow(benchmark::State& state) {
  for (auto _ : state) {
    auto res = add1(Matrix(len, distribution(engine)),
                    Matrix(len, distribution(engine)));
  }
}
static void ReadByCol(benchmark::State& state) {
  for (auto _ : state) {
    auto res = add2(Matrix(len, distribution(engine)),
                    Matrix(len, distribution(engine)));
  }
}
BENCHMARK(ReadByRow);
BENCHMARK(ReadByCol);
BENCHMARK_MAIN();