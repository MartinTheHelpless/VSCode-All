#include "Node.h"

Node::Node(int value)
{
    this->value = value;
    this->lChild = nullptr;
    this->rChild = nullptr;
}

Node::Node(int value, Node *lChild, Node *rChild)
{
    this->value = value;
    this->lChild = lChild;
    this->rChild = rChild;
}

int Node::getDepth()
{
    return this->subDepth;
}

int Node::getBalance()
{
    return this->balance;
}

int Node::getValue()
{
    return this->value;
}

Node *Node::getlChild()
{
    return this->lChild;
}

Node *Node::getrChild()
{
    return this->rChild;
}

void Node::setlChild(Node *child)
{
    this->lChild = child;
}

void Node::setrChild(Node *child)
{
    this->rChild = child;
}
