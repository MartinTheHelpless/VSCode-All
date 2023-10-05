#pragma once
#include "Node.h"
#include <vector>

class Tree
{
private:
    std::vector<Node *> nodes;
    Node *rootNode;
    int totalLevels;

public:
    Tree(std::vector<int> *vect);
    void printTree();
    void addNode(Node *node);
    Node *getNextNode(std::vector<int> *vect, int start, int end);
    void treeFromVector(std::vector<int> *vect, int start, int end);
};