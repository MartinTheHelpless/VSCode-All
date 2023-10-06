#pragma once
#include "Tree.h"

Tree::Tree(std::vector<int> *vect)
{
    this->treeFromVector(0, vect->size(), vect);
}

void Tree::printTree(std::string prefix, Node *node, bool isLeft)
{

    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "'--");

        // print the value of the node
        std::cout << node->getValue() << std::endl;

        // enter the next tree level - left and right branch
        printTree(prefix + (isLeft ? "|   " : "    "), node->getRSubNode(), true);
        printTree(prefix + (isLeft ? "|   " : "    "), node->getLSubNode(), false);
    }
}

void Tree::displayTree()
{
    printTree("", this->rootNode, false);
}

void Tree::addNode(Node *node)
{
}

Node *Tree::getNextNode(double start, double end, std::vector<int> *vect)
{
    if (start < end)
    {
        double tmpCeil = ceil((start + end) / 2);
        double tmpFloor = floor((start + end) / 2);
        bool used = false;

        for (int i = 0; i < this->usedValues.size(); i++)
        {
            if (this->usedValues[i] == (*vect)[tmpFloor])
            {
                used = true;
                break;
            }
        }

        if (used)
            return NULL;
        else
        {
            this->usedValues.push_back((*vect)[tmpFloor]);
            Node *tmpNode = new Node((*vect)[tmpFloor], getNextNode(start, tmpFloor == end ? tmpFloor - 1 : tmpFloor, vect), getNextNode((tmpCeil == start ? tmpCeil + 1 : tmpCeil), end, vect));
            this->nodes.push_back(tmpNode);
            return tmpNode;
        }
    }
    else
        return NULL;
}

void Tree::treeFromVector(double start, double end, std::vector<int> *vect)
{

    for (int i = 1; (end + 1) >= pow(2, i); i++)
        this->totalLevels = i + 1;

    int values[(*vect).size()];

    for (int i = 0; i < (*vect).size(); i++)
        values[i] = (*vect)[i];

    std::cout << "The tree will have " << this->totalLevels << " total levels." << std::endl;

    double tmpVal = ceil((start + end - 1) / 2);

    this->rootNode = new Node((*vect)[tmpVal]);
    this->nodes.push_back(this->rootNode);
    this->usedValues.push_back((*vect)[tmpVal]);
    this->rootNode->addLeftSubTree(getNextNode(0, tmpVal, vect));
    this->rootNode->addRightSubTree(getNextNode(tmpVal, end, vect));
}

int Tree::isBalanced()
{

    for (int i = 0; i < this->nodes.size(); i++)
    {
        if (abs(this->nodes[i]->getBalance()) > 1)
        {
            std::cout << "This tree is not properly balanced." << std::endl;
            return 1;
        }
    }

    std::cout << "This tree is properly balanced." << std::endl;

    return 0;
}
