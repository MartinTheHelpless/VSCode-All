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
    int nodeLevel;

public:
    Node(int value);
    Node(int value, Node *lSubNode, Node *rSubNode);
    Node *getRSubNode();
    Node *getLSubNode();
    int maxDepth(Node *node);
    int getValue();
    void setLevel(int level);
    int getLevel();
    void setBalance(int balance);
    int getBalance();
    int calculateBalance();
    void addLeftSubTree(Node *node);
    void addRightSubTree(Node *node);
};