#pragma once
#include "Node.cpp"

class Tree
{
private:
    std::vector<Node *> nodes;
    Node *rootNode;
    int totalLevels;
    std::vector<int> usedValues;

public:
    Tree(std::vector<int> *vect);
    void printTree(std::string prefix, Node *node, bool isLeft);
    void addNode(Node *node);
    Node *getNextNode(double start, double end, std::vector<int> *vect);
    void treeFromVector(double start, double end, std::vector<int> *vect);
    int isBalanced();
    void displayTree();
};
