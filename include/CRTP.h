/*
 * @Description:
 * @Author: lize
 * @Date: 2024-07-09
 * @LastEditors: lize
 */
#pragma once
#include <iostream>
#include <vector>
extern void subtractfunc();

template <typename Drived>
class Drink {
 public:
  void print() {
    static_cast<Drived*>(this)->print_imp();
  }
};

class Cola : public Drink<Cola> {
  friend Drink;
  void print_imp() {
    subtractfunc();
    // std::cout << "Cola" << std::endl;
  }
};

class Water : public Drink<Water> {
  friend Drink;
  void print_imp() {
    // std::cout << "Water" << std::endl;
  }
};

template <typename T>
void print(Drink<T>& d) {
  d.print();
}

class Red {
 public:
  void showRGB() {
    std::cout << "red" << std::endl;
  }
};
class Yellow {
 public:
  void showRGB() {
    std::cout << "Yellow" << std::endl;
  }
};

template <typename Color>
concept isColor = requires(Color c) { c.showRGB(); };

template <isColor Color>
void showColor(Color c) {
  c.showRGB();
}