#include "Tree.h"
#include <cmath>

Tree::Tree()
{
    this->root = nullptr;
    this->depth = 0;
    this->maxVal = INT_MIN;
    this->minVal = INT_MAX;
}

Tree::Tree(std::vector<int> *vect)
{

    this->maxVal = INT_MIN;
    this->minVal = INT_MAX;

    for (int i = 0; i < (*vect).size(); i++)
        if ((*vect)[i] > this->maxVal)
            this->maxVal = (*vect)[i];
        else if ((*vect)[i] < this->minVal)
            this->minVal = (*vect)[i];

    treeFromVector(0, (*vect).size(), vect);
}

void Tree::addNode(int value)
{
}

void Tree::isBalanced()
{
}

void Tree::treeFromVector(double start, double end, std::vector<int> *vect)
{

    int values[(*vect).size()];

    for (int i = 0; i < (*vect).size(); i++)
        values[i] = (*vect)[i];

    double tmpVal = ceil((start + end - 1) / 2);

    this->root = new Node((*vect)[tmpVal]);
    this->root->setlChild(getNextNode(0, tmpVal, vect));
    this->root->setlChild(getNextNode(tmpVal, end, vect));
}

Node *Tree::getNodeByValue(int val)
{
    Node *tmp = this->root;
    int tmpVal = tmp->getValue();
    while (tmpVal != val)
    {
        tmpVal = tmp->getValue();
        if (val > tmpVal)
            tmp = tmp->getrChild();
        else if (val < tmpVal)
            tmp = tmp->getlChild();
        tmpVal = tmp->getValue();
    }
    return tmp;
}

Node *Tree::getNextNode(double start, double end, std::vector<int> *vect)
{
    if (start < end)
    {
        double tmpCeil = ceil((start + end) / 2);
        double tmpFloor = floor((start + end) / 2);

        Node *tmpNode = new Node((*vect)[tmpFloor], getNextNode(start, tmpFloor == end ? tmpFloor - 1 : tmpFloor, vect), getNextNode((tmpCeil == start ? tmpCeil + 1 : tmpCeil), end, vect));
        return tmpNode;
    }
    else
        return NULL;
}
