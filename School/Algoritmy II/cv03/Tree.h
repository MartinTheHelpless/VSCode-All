#pragma once
#include "Tree.cpp"

Tree::Tree(std::vector<int> *vect)
{
    this->treeFromVector(vect, 0, vect->size() - 1);
}

void Tree::printTree()
{
}

void Tree::addNode(Node *node)
{
}

Node *Tree::getNextNode(std::vector<int> *vect, int start, int end)
{
    if (start < end)
    {
        return new Node((*vect)[(start + end) / 2], getNextNode(vect, start, end / 2), getNextNode(vect, end / 2, end));
    }
    else
        return NULL;
}

void Tree::treeFromVector(std::vector<int> *vect, int start, int end)
{

    for (int i = 1; (end + 1) >= pow(2, i); i++)
        this->totalLevels = i + 1;

    std::cout << "The tree will have " << this->totalLevels << " total levels." << std::endl;

    this->rootNode = new Node((*vect)[ceil(end / 2)], getNextNode(vect, start, end / 2), getNextNode(vect, end / 2, end));
}
