#pragma once
#include <math.h>

class Node
{
private:
    int value;
    Node *lSubNode;
    Node *rSubNode;
    int balance;

public:
    Node(int value, Node *left, Node *right);
    int getValue();
    void addLeftSubTree(Node *node);
    void addRightSubTree(Node *node);
    void countBalance();
};