/*
 * @Description:
 * @Author: lize
 * @Date: 2024-06-25
 * @LastEditors: lize
 */
#pragma once
#include <iostream>
#include <memory>
#include <vector>
class GraphNode {
 public:
  using GraphNodeUPtr = std::unique_ptr<GraphNode>;
  using GraphNodeSPtr = std::shared_ptr<GraphNode>;
  constexpr static size_t CHILD_NUM = 5;
  GraphNode(int data);
  void init(size_t layer = 2);
  // 更新节点的和
  void updateSum(int sum, bool dirty);

  void print();
  void setChildValue(size_t index, int value);

  int _sum;
  bool _dirty;

 private:
  int _data;
  std::vector<GraphNodeUPtr> _nodes;
};