#pragma once

class Node
{
private:
    int value;
    Node *lSubNode;
    Node *rSubNode;

public:
    Node(int value);
    void setlSubNode(Node *node);
    void setrSubNode(Node *node);
    Node *getlSubNode();
    Node *getrSubNode();
};
