#include <iostream>

class Node
{
public:
    int val1;
    int val2;

    Node *childL;
    Node *childM;
    Node *childR;

    Node(int val1, int val2, Node *childL, Node *childM, Node *childR)
    {
        this->val1 = val1;
        this->val2 = val2;
        this->childL = childL;
        this->childM = childM;
        this->childR = childR;
    }

    Node(int val1, Node *childL, Node *childR)
    {
        this->val1 = val1;
        this->val2 = INT_MAX;
        this->childL = childL;
        this->childR = childR;
        this->childM = nullptr;
    }
};