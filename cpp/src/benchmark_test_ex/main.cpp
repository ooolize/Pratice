/*
 * @Description:
 * @Author: lize
 * @Date: 2024-06-16
 * @LastEditors: lize
 */

#include <benchmark/benchmark.h>

#include <random>
#include <vector>

#include "benchmark_test2.h"
#include "benchmark_test3.h"
#include "benchmark_test_ex.h"

// TODO: 为了避免组访问偏差，增加了8字节。性能只增加了3%?

constexpr size_t offset = 0;
constexpr size_t len = 0x0400;
constexpr size_t row = 0x0400;
constexpr size_t col = 0x0400;
// 创建随机数引擎（使用默认种子）
static std::default_random_engine engine;
// 创建均匀分布对象，生成0到100之间的随机整数
static std::uniform_int_distribution<int> distribution(10, 100);
static void TEST_ADD_1(benchmark::State& state) {
  for (auto s : state) {  // NOLINT
    auto res = add1(Matrix(len, len, distribution(engine)),
                    Matrix(len, len, distribution(engine)));
  }
}
static void TEST_ADD_2(benchmark::State& state) {
  for (auto s : state) {  // NOLINT
    auto res = add2(Matrix(len, len, distribution(engine)),
                    Matrix(len, len, distribution(engine)));
  }
}

static void TEST_MULTI_2(benchmark::State& state) {
  auto m1 = Matrix(row, col, distribution(engine));
  auto m2 = Matrix(col, row, distribution(engine));
  for (auto s : state) {  // NOLINT
    auto res = multi2(m1, m2);
  }
}

static void TEST_MULTI_3(benchmark::State& state) {
  auto m1 = Matrix(row + offset, col + offset, distribution(engine));
  auto m2 = Matrix(col + offset, row + offset, distribution(engine));
  for (auto s : state) {  // NOLINT
    auto res = multi2(m1, m2);
  }
}

// BENCHMARK(TEST_ADD_1);
// BENCHMARK(TEST_ADD_2);
// vector在内存中是连续存储的，理论上说multi1(按行遍历)应该比multi2(按列遍历)快。
// eg: 32kB 8-way 组相联 缓存行64B
// 0000 0000 0000
// group | Byte
// 使用高地址2^6位确定组号，低地址2^3位确定路和缓存行内偏移

//  ----L1Cache----
//         way: 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
// group1:
// ...
// group64:
// 对于4kB(1024元素*8int)的矩阵行，L1Cache只能存储8(way)个元素。按列遍历会造成L1Cache的命中率降低。

// 那为什么multi2比multi1快？一定是存在"机制" 有利于列频繁访问的情况。
// dangdang~ L3Cache的地址映射不仅限于<12,6>来映射组号，还包含一些高位的地址
// 来做哈希。这使得列元素不会存储在L3的固定组中，而是会分散在不同的组中。
// 这种机制的影响是如此的大，以至于multi2的
// l1/l2的cache命中率低的影响被掩盖了，反而超过了multi1。

BENCHMARK(TEST_MULTI_2)->Repetitions(20);
BENCHMARK(TEST_MULTI_3)->Repetitions(20);
// BENCHMARK(TEST_MULTI_2);
BENCHMARK_MAIN();
