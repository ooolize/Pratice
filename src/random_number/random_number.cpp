

/*
 * @Description:
 * @Author: lize
 * @Date: 2024-06-25
 * @LastEditors: lize
 */
#include "dirty_flag.h"

GraphNode::GraphNode(int data) : _sum(data), _dirty(false), _data(data) {
}

void GraphNode::init(size_t layer) {
  if (layer == 0) {
    return;
  }
  for (size_t i = 0; i < CHILD_NUM; i++) {
    auto node = std::make_unique<GraphNode>(_data + i);
    node->init(layer - 1);
    _nodes.push_back(std::move(node));
  }
}

void GraphNode::print() {
  std::cout << "data: " << _data << " sum: " << _sum << std::endl;
  for (auto& node : _nodes) {
    node->print();
  }
}

void GraphNode::setChildValue(size_t index, int value) {
  if (index < _nodes.size()) {
    _nodes[index]->_data = value;
    _nodes[index]->_dirty = true;
  }
}

void GraphNode::updateSum(int sum, bool dirty) {
  _dirty |= dirty;
  if (dirty) {
    _sum = sum + _data;
    std::cout << "dirty!" << std::endl;
  }
  for (auto& node : _nodes) {
    node->updateSum(_sum, _dirty);
  }
}