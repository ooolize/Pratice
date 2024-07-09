/*
 * @Description:
 * @Author: lize
 * @Date: 2024-06-16
 * @LastEditors: lize
 */

#include <benchmark/benchmark.h>

#include <memory>
#include <random>
#include <vector>

#include "CRTP.h"
#include "polymorph_subtype.h"
#include "polymorpy_adhoc.h"
static long long count = 0;
void addfunc() {
  count++;
}
void subtractfunc() {
  count--;
}
// constexpr size_t num = 1 << 12;
// // 创建随机数引擎（使用默认种子）
// static std::default_random_engine engine;
// // 创建均匀分布对象，生成0到100之间的随机整数
// static std::uniform_int_distribution<int> distribution(10, 100);
// static void TEST_SUBTYPE(benchmark::State& state) {
//   std::vector<std::unique_ptr<Polygon>> v;
//   for (size_t i = 0; i < num; i++) {
//     v.push_back(std::make_unique<Triangle>());
//   }
//   for (auto _ : state) {
//     benchmark::DoNotOptimize(
//       std::for_each(v.begin(), v.end(), [](auto& p) { p->draw(); }));
//   }
// }

// static void TEST_ADHOC(benchmark::State& state) {
//   std::vector<Animals> v;
//   for (size_t i = 0; i < num; i++) {
//     v.push_back(Dog());
//   }
//   for (auto _ : state) {
//     benchmark::DoNotOptimize(
//       std::for_each(v.begin(), v.end(), [](auto& p) { roar(p); }));
//   }
// }

// BENCHMARK(TEST_ADHOC)->Repetitions(20);
// BENCHMARK(TEST_SUBTYPE)->Repetitions(20);
// BENCHMARK_MAIN();

int main() {
  // subtype
  std::unique_ptr<Polygon> p = std::make_unique<Triangle>();
  std::unique_ptr<Polygon> p2 = std::make_unique<Rectangle>();
  p->draw();
  p2->draw();

  // adhoc
  Dog d;
  Cat c;
  roar(d);
  roar(c);

  // crtp
  Cola d1;
  Water d2;
  print(d1);
  print(d2);

  // concept
  Red r;
  Yellow y;
  showColor(r);
  showColor(y);
}
