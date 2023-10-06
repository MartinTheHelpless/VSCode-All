#pragma once
#include "Tree.cpp"

Tree::Tree(std::vector<int> *vect)
{

    for (int i = 0; i < (*vect).size(); i++)
        this->nodes.push_back((*vect)[i]);

    this->treeFromVector(vect, 0, vect->size() - 1);
}

void Tree::printTree()
{
}

void Tree::addNode(Node *node)
{
}

Node *Tree::getNextNode(std::vector<int> *vect, double start, double end)
{
    if (start < end)
    {
        double tmpCeil = ceil((start + end) / 2);
        double tmpFloor = floor((start + end) / 2);
        return new Node((*vect)[tmpFloor], getNextNode(vect, start, tmpFloor == end ? tmpFloor - 1 : tmpFloor), getNextNode(vect, (tmpCeil == start ? tmpCeil + 1 : tmpCeil), end));
    }
    else
        return nullptr;
}

void Tree::treeFromVector(std::vector<int> *vect, double start, double end)
{

    for (int i = 1; (end + 1) >= pow(2, i); i++)
        this->totalLevels = i + 1;

    std::cout << "The tree will have " << this->totalLevels << " total levels." << std::endl;

    double tmpVal = ceil(end / 2);

    this->rootNode = new Node((*vect)[tmpVal]);
    this->rootNode->addLeftSubTree(getNextNode(vect, start, tmpVal - 1));
    this->rootNode->addRightSubTree(getNextNode(vect, tmpVal + 1, (int(end) % 2 == 0 ? end : end + 1)));
}
