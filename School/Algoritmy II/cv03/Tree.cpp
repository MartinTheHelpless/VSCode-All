#pragma once
#include "Tree.h"

Tree::Tree(std::vector<int> *vect)
{

    for (int i = 0; i < (*vect).size(); i++)
        this->nodes.push_back((*vect)[i]);

    this->treeFromVector(0, vect->size());
}

void Tree::printTree()
{
}

void Tree::addNode(Node *node)
{
}

Node *Tree::getNextNode(double start, double end)
{
    if (start < end)
    {
        double tmpCeil = ceil((start + end) / 2);
        double tmpFloor = floor((start + end) / 2);
        bool used = false;

        for (int i = 0; i < this->usedValues.size(); i++)
        {
            if (this->usedValues[i] == this->nodes[tmpFloor])
            {
                used = true;
                break;
            }
        }

        if (used)
            return NULL;
        else
        {
            this->usedValues.push_back(this->nodes[tmpFloor]);
            return new Node(this->nodes[tmpFloor], getNextNode(start, tmpFloor == end ? tmpFloor - 1 : tmpFloor), getNextNode((tmpCeil == start ? tmpCeil + 1 : tmpCeil), end));
        }
    }
    else
        return NULL;
}

void Tree::treeFromVector(double start, double end)
{

    for (int i = 1; (end + 1) >= pow(2, i); i++)
        this->totalLevels = i + 1;

    int values[this->nodes.size()];

    for (int i = 0; i < this->nodes.size(); i++)
        values[i] = this->nodes[i];

    std::cout << "The tree will have " << this->totalLevels << " total levels." << std::endl;

    double tmpVal = ceil((start + end - 1) / 2);

    this->rootNode = new Node(this->nodes[tmpVal]);
    this->usedValues.push_back(this->nodes[tmpVal]);
    this->rootNode->addLeftSubTree(getNextNode(0, tmpVal));
    this->rootNode->addRightSubTree(getNextNode(tmpVal, end));
}
