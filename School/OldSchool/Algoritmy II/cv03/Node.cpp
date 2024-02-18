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

Node *Node::getRSubNode()
{
    return this->rSubNode;
}

Node *Node::getLSubNode()
{
    return this->lSubNode;
}

int Node::getValue()
{
    return this->value;
}

void Node::setLevel(int level)
{
    this->nodeLevel = level;
}

int Node::getLevel()
{
    return this->nodeLevel;
}

void Node::addLeftSubTree(Node *node)
{
    this->lSubNode = node;
}

void Node::addRightSubTree(Node *node)
{
    this->rSubNode = node;
}

void Node::setBalance(int balance)
{
    this->balance = balance;
}

int Node::calculateBalance()
{

    int lDepth = maxDepth(this->lSubNode);
    int rDepth = maxDepth(this->rSubNode);

    return lDepth - rDepth;
}

int Node::getBalance()
{
    return this->balance;
}

int Node::maxDepth(Node *node)
{
    if (node == NULL)
        return 0;
    else
    {

        int lDepth = maxDepth(node->lSubNode);
        int rDepth = maxDepth(node->rSubNode);

        node->setBalance(lDepth - rDepth);

        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}