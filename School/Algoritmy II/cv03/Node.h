#pragma once
#include <math.h>
#include <iostream>
#include <vector>

class Node
{
private:
    int value;
    Node *lSubNode;
    Node *rSubNode;
    int balance;

public:
    Node(int value);
    Node(int value, Node *lSubNode, Node *rSubNode);
    Node *getRSubNode();
    Node *getLSubNode();
    int maxDepth(Node *node);
    int getValue();
    int getBalance();
    void addLeftSubTree(Node *node);
    void addRightSubTree(Node *node);
};