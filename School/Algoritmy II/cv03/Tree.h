#pragma once
#include "Node.cpp"

class Tree
{
private:
    std::vector<int> nodes;
    Node *rootNode;
    int totalLevels;
    std::vector<int> usedValues;

public:
    Tree(std::vector<int> *vect);
    void printTree();
    void addNode(Node *node);
    Node *getNextNode(double start, double end);
    void treeFromVector(double start, double end);
};
