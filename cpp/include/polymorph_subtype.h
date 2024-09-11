/*
 * @Description:
 * @Author: lize
 * @Date: 2024-07-09
 * @LastEditors: lize
 */
#pragma once
#include <iostream>
extern void subtractfunc();
class Polygon {
 public:
  virtual void draw() = 0;
  virtual ~Polygon() {
  }
};

class Triangle : public Polygon {
 public:
  void draw() {
    // std::cout << "Triangle" << std::endl;
    subtractfunc();
  }
};
class Rectangle : public Polygon {
 public:
  void draw() {
    subtractfunc();
    // std::cout << "Rectangle" << std::endl;
  }
};