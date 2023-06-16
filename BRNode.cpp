#include "BRNode.h"

BRNode::BRNode() {
    this -> left = nullptr;
    this -> right = nullptr;
    this -> parent = nullptr;
    this -> color = false;
    this -> key = 0;
}
BRNode::~BRNode() = default;

