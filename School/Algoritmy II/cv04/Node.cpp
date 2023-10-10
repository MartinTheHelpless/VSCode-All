#pragma once
#include "Node.h"

Node::Node(int value)
{
    this->value = value;
    this->lSubNode = nullptr;
    this->rSubNode = nullptr;
}

void Node::setlSubNode(Node *node)
{
    this->lSubNode = node;
}

void Node::setrSubNode(Node *node)
{
    this->rSubNode = node;
}

Node *Node::getlSubNode()
{
    return this->lSubNode;
}

Node *Node::getrSubNode()
{
    return this->rSubNode;
}
