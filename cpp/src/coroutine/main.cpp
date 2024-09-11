/*
 * @Description:
 * @Author: lize
 * @Date: 2024-09-07
 * @LastEditors: lize
 */
#include <fmt/core.h>

#include <coroutine>
#include <iostream>
#include <thread>

// co_await expr  expr需要是一个awaitable对象.
// awaitable对象 可能是重载了operator co_await的对象，
// 也可以是拥有await_ready、await_suspend、await_resume三个方法的对象
class Awaitable {
 public:
  // 判断在调用时是否已经准备好，
  // 如果准备好则返回true，否则返回false 进入await_suspend。
  bool await_ready() {
    return false;
  }
  // 挂起后那么接下来要去哪里? 根据返回值
  // 如果void 那就是无条件返回给调用者
  // 如果bool 那就是返回true则控制权返回给调用者，返回false则继续执行该协程
  // 如果是某个协程句柄，那就是跳转到该协程
  // 另外 handle实参是父协程的协程句柄
  void await_suspend(std::coroutine_handle<> handle) {
    std::cout << "await_suspend" << std::endl;
    std::jthread(
      [](std::coroutine_handle<> handle) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        handle.resume();
      },
      handle)
      .detach();
  }

  // 返回值是co_await表达式的值
  void await_resume() {
    std::cout << "await_resume" << std::endl;
  }
};

// promise对象 提供一系列控制点
class Promise {
 public:
  // 协程调用时 先构造promise对象，通过get_return_object返回协程句柄
  auto get_return_object() {
    return std::coroutine_handle<Promise>::from_promise(*this);
  }
  auto initial_suspend() noexcept {
    return std::suspend_always{};
  }
  auto final_suspend() noexcept {
    return std::suspend_always{};
  }
  // co_return 调用时执行， 执行后析构协程局部变量 进入 final_suspend
  // void return_void() {
  // }
  // 同上 两个只能出现其中一个
  void return_value(int value) {
    _value = value;
  }

  // co_yield 调用时执行 返回一个awaiter
  auto yield_value(int value) {
    _value = value;
    return std::suspend_always{};
  }
  void unhandled_exception() {
  }

  int _value{};
};

class WorldPromise {
 public:
  // 协程调用时 先构造promise对象，通过get_return_object返回Future
  auto get_return_object() {
    return std::coroutine_handle<WorldPromise>::from_promise(*this);
  }
  auto initial_suspend() noexcept {
    return std::suspend_always{};
  }
  auto final_suspend() noexcept {
    return std::suspend_always{};
  }
  // co_return 调用时执行， 执行后析构协程局部变量 进入 final_suspend
  // void return_void() {
  // }
  // 同上 两个只能出现其中一个
  void return_value(int value) {
  }

  // co_yield 调用时执行
  auto yield_value(int value) {
    return std::suspend_always{};
  }
  void unhandled_exception() {
  }
};

class WorldTask {
 public:
  using promise_type = WorldPromise;
  WorldTask(std::coroutine_handle<WorldPromise> handle)  // NOLINT
    : _handle(handle) {
  }
  auto operator co_await() {
    return Awaitable{};
  }
  std::coroutine_handle<WorldPromise> _handle;
};

class Task {
 public:
  // 编译时 编译器通过promise_type确定promise类型
  using promise_type = Promise;

  // 隐式转换promise.get_return_object()返回的协程句柄
  Task(std::coroutine_handle<Promise> handle) : _handle(handle) {  // NOLINT
  }
  int getValue() {
    return _handle.promise()._value;
  }
  // 协程句柄
  std::coroutine_handle<Promise> _handle;
};

WorldTask world() {
  std::cout << "world" << std::endl;
  co_return 422;
}

// 协程体
Task hello() {
  // 在此处构建协程帧/promise对象
  std::cout << "hello" << std::endl;

  co_yield 421;  // 等价于 co_await promise.yield_value(value)
  // co_await 接受一个表达式，表达式的类型必须是一个awaitable对象
  // awaitable对象 回答了三个问题
  // 1. 在调用时是否已经准备好
  // 2. 挂起(hello)后怎么恢复
  // 3. 返回值是什么
  fmt::print("====before world\n");
  co_await world();
  fmt::print("====after world\n");
  co_yield 422;  // 等价于 co_await promise.yield_value(value)

  // co_return;  // 等价于 promise.return_void();
  // co_return 42;  // 等价于 promise.return_value(42);
}

int main() {
  auto t = hello();
  // std::cout << t.getValue() << std::endl;
  fmt::print("1 value: {}\n", t.getValue());
  t._handle.resume();
  fmt::print("2 value: {}\n", t.getValue());
  t._handle.resume();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  fmt::print("3 value: {}\n", t.getValue());
};

// 问题 如何返回一个值
// 用协程替代线程
// 如何挂起一个线程
// 如果resume一个 正在执行的协程 会发生什么---未定义行为

// 协程可以用来简化错误处理，需要多次判错误的地方 使用co_yield处理
// 如果出错直接打断协程