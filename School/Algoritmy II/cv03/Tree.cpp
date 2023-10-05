#pragma once
#include "Node.h"
#include <vector>

class Tree
{
private:
    std::vector<Node *> nodes;
    Node *topNode;

public:
    Tree();
    void printTree();
    void addNode(Node *node);
    void sortAVLTree();
};