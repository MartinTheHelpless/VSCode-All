#include <iostream>

class Node
{
private:
    int value;
    int balance;
    int subDepth;
    Node *lChild;
    Node *rChild;

public:
    Node(int value);
    Node(int value, Node *lChild, Node *rChild);
    int getDepth();
    int getBalance();
    int getValue();
    Node *getlChild();
    Node *getrChild();
    void setlChild(Node *child);
    void setrChild(Node *child);
};
