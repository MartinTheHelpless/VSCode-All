#pragma once
#include "Node.cpp"

class Tree
{
private:
    std::vector<Node *> nodes;
    Node *rootNode;
    int totalLevels;
    std::vector<int> usedValues;
    std::vector<int> sortedValues;

    Node *getNextNode(double start, double end, std::vector<int> *vect);

public:
    Tree(std::vector<int> *vect);
    void printTree(std::string prefix, Node *node, bool isLeft);
    void setLevels(Node *node, int maxLevel);
    void addNode(int value);
    void displayTreeLevels();
    Node *getNodeByValue(int val);
    void treeFromVector(double start, double end, std::vector<int> *vect);
    int getMaxLevel();
    void isBalanced();
    void displayTree();
    void balanceTree();
};
