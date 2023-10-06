#pragma once
#include "Node.h"

Node::Node(int value)
{
    this->value = value;
}

Node::Node(int value, Node *lSubNode, Node *rSubNode)
{
    this->value = value;
    this->lSubNode = lSubNode;
    this->rSubNode = rSubNode;
}

int Node::getValue()
{
    return this->value;
}

void Node::addLeftSubTree(Node *node)
{
    this->lSubNode = node;
}

void Node::addRightSubTree(Node *node)
{
    this->rSubNode = node;
}

void Node::countBalance()
{
}