/*
 * @Description:
 * @Author: lize
 * @Date: 2024-07-09
 * @LastEditors: lize
 */
#pragma once
#include <variant>
extern void addfunc();
class Dog {};
void roar(const Dog& d) {
  // std::cout << "Dog" << std::endl;
  addfunc();
}
class Cat {};
void roar(const Cat& c) {
  // std::cout << "Cat" << std::endl;
  addfunc();
}
using Animals = std::variant<Dog, Cat>;

void roar(const Animals& t) {
  std::visit([](const auto& p) { roar(p); }, t);
}
