/*
 * @Description:
 * @Author: lize
 * @Date: 2024-09-11
 * @LastEditors: lize
 */

#include <fmt/core.h>

#include <coroutine>
#include <future>
#include <iterator>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

#include "utils/lztime.h"

class GPromise {
 public:
  auto initial_suspend() {
    return std::suspend_never{};
  }
  auto final_suspend() {
    return std::suspend_never{};
  }
  auto get_return_object() {
    return std::coroutine_handle<GPromise>::from_promise(*this);
  }
  void unhandled_exception() noexcept {
  }
};
class Generator {
 public:
  using promise_type = GPromise;
  Generator(std::coroutine_handle<promise_type> h) : _h(h) {  // NOLINT
  }

 private:
  std::coroutine_handle<promise_type> _h;
};

template <std::random_access_iterator Iter>
int parall_sum(Iter begin, Iter end) {
  auto len = std::distance(begin, end);
  if (len == 0) {
    return 0;
  }
  auto mid = begin + len / 2;
  auto forward_part = std::async(
    [](auto b, auto m) { return std::accumulate(b, m + 1, 0); }, begin, mid);
  auto backward_part = parall_sum<Iter>(mid + 1, end);
  return forward_part.get() + backward_part;
}

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  std::vector<int> v(100 * 1000 * 1000, dis(gen));
  auto start = lz::rdtsc();
  int sum = parall_sum(v.begin(), v.end());
  auto end = lz::rdtsc();

  fmt::print("time1: {}\n", lz::spendTimeNs(start, end, 3.69));
  fmt::print("sum: {}\n", sum);

  auto start2 = lz::rdtsc();
  int sum2 = std::accumulate(v.begin(), v.end(), 0);
  auto end2 = lz::rdtsc();

  fmt::print("time2: {}\n", lz::spendTimeNs(start2, end2, 3.69));
  fmt::print("sum2: {}\n", sum2);
};