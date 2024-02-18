#pragma once
#include "Tree.h"

Tree::Tree(std::vector<int> *vect)
{
    this->treeFromVector(0, vect->size(), vect);

    this->rootNode->setLevel(this->totalLevels);
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

void Tree::displayTreeLevels()
{
    for (int i = this->totalLevels; i > 0; i--)
    {
        std::cout << "\nTree nodes on " << i << ". level : " << std::endl;
        for (int o = 0; o < this->nodes.size(); o++)
        {
            if (this->nodes[o]->getLevel() == i)
                std::cout << "-- " << this->nodes[o]->getValue() << " --";
        }
    }
}

void Tree::displayTree()
{
    printTree("", this->rootNode, false);
}

void Tree::setLevels(Node *node, int maxLevel)
{
    node->setLevel(maxLevel);

    if (node->getLSubNode() != NULL)
        setLevels(node->getLSubNode(), maxLevel - 1);

    if (node->getRSubNode() != NULL)
        setLevels(node->getRSubNode(), maxLevel - 1);
}

void Tree::addNode(int value)
{

    Node *tmpNode = this->rootNode;

    if (this->getNodeByValue(value) == NULL)
    {
        while (true)
        {
            if (tmpNode->getValue() > value && tmpNode->getLSubNode() == NULL)
            {
                Node *AddedNode = new Node(value, NULL, NULL);
                this->nodes.push_back(AddedNode);
                this->usedValues.push_back(value);
                tmpNode->addLeftSubTree(AddedNode);
                for (int i = 1; this->nodes.size() >= pow(2, i); i++)
                    this->totalLevels = i + 1;
                break;
            }
            else if (tmpNode->getValue() > value && tmpNode->getLSubNode() != NULL)
            {
                tmpNode = tmpNode->getLSubNode();
            }
            else if (tmpNode->getValue() < value && tmpNode->getRSubNode() == NULL)
            {
                Node *AddedNode = new Node(value, NULL, NULL);
                this->nodes.push_back(AddedNode);
                this->usedValues.push_back(value);
                tmpNode->addRightSubTree(AddedNode);
                for (int i = 1; this->nodes.size() >= pow(2, i); i++)
                    this->totalLevels = i + 1;
                break;
                break;
            }
            else if (tmpNode->getValue() < value && tmpNode->getRSubNode() != NULL)
            {
                tmpNode = tmpNode->getRSubNode();
            }
        }
        this->setLevels(this->rootNode, this->totalLevels);

        this->isBalanced();
    }
    else
        std::cout << "This node is already present in the tree." << std::endl;
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

Node *Tree::getNodeByValue(int val)
{

    Node *tmp = this->rootNode;
    while (tmp != NULL)
    {
        if (val > tmp->getValue())
            tmp = tmp->getRSubNode();
        else if (val < tmp->getValue())
            tmp = tmp->getLSubNode();
        else
            return tmp;
    }

    std::cout << "This value is not in the tree yet." << std::endl;
    return NULL;
}

void Tree::treeFromVector(double start, double end, std::vector<int> *vect)
{

    for (int i = 1; end >= pow(2, i); i++)
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

int Tree::getMaxLevel()
{
    return this->totalLevels;
}

void Tree::isBalanced()
{

    this->rootNode->setBalance(this->rootNode->calculateBalance());

    bool balanced = true;

    for (int i = 0; i < this->nodes.size(); i++)
        if (abs(this->nodes[i]->getBalance()) > 1)
        {
            std::cout << "Imbalance on node: " << this->nodes[i]->getValue() << " --- balance factor: " << this->nodes[i]->getBalance() << std::endl;
            balanced = false;
        }

    balanced ? std::cout << "Tree is properly balanced. " << std::endl : std::cout << "";
}

void Tree::balanceTree()
{
    for (int i = 1; i <= this->totalLevels; i++)
    {
        for (int o = 0; o < this->nodes.size(); o++)
        {
            if (this->nodes[o]->getLevel() == i && this->nodes[o]->getBalance() > 1)
            {

                Node *tmpNode = this->rootNode;

                while (tmpNode->getLSubNode()->getValue() != this->nodes[o]->getValue() && tmpNode->getRSubNode()->getValue() != this->nodes[o]->getValue())
                {
                    if (this->nodes[o]->getValue() > tmpNode->getValue())
                        tmpNode = tmpNode->getRSubNode();
                    else
                        tmpNode = tmpNode->getLSubNode();
                }

                if (tmpNode->getRSubNode()->getValue() == this->nodes[o]->getValue())
                {
                    tmpNode->addRightSubTree(this->nodes[o]->getLSubNode());
                    this->nodes[o]->getLSubNode()->addRightSubTree(this->nodes[o]);
                    this->nodes[o]->addLeftSubTree(NULL);
                }
                else if (tmpNode->getLSubNode()->getValue() == this->nodes[o]->getValue())
                {
                    tmpNode->addLeftSubTree(this->nodes[o]->getLSubNode());
                    this->nodes[o]->getLSubNode()->addRightSubTree(this->nodes[o]);
                    this->nodes[o]->addLeftSubTree(NULL);
                }
            }
            else if (this->nodes[o]->getLevel() == i && this->nodes[o]->getBalance() < -1)
            {
                Node *tmpNode = this->rootNode;

                while (tmpNode->getLSubNode()->getValue() != this->nodes[o]->getValue() && tmpNode->getRSubNode()->getValue() != this->nodes[o]->getValue())
                {
                    if (this->nodes[o]->getValue() > tmpNode->getValue())
                        tmpNode = tmpNode->getRSubNode();
                    else
                        tmpNode = tmpNode->getLSubNode();
                }

                if (tmpNode->getRSubNode()->getValue() == this->nodes[o]->getValue())
                {
                    tmpNode->addRightSubTree(this->nodes[o]->getRSubNode());
                    this->nodes[o]->getRSubNode()->addLeftSubTree(this->nodes[o]);
                    this->nodes[o]->addRightSubTree(NULL);
                }
                else if (tmpNode->getLSubNode()->getValue() == this->nodes[o]->getValue())
                {
                    tmpNode->addLeftSubTree(this->nodes[o]->getRSubNode());
                    this->nodes[o]->getRSubNode()->addLeftSubTree(this->nodes[o]);
                    this->nodes[o]->addRightSubTree(NULL);
                }
            }
            this->rootNode->setBalance(this->rootNode->calculateBalance());
            this->setLevels(this->rootNode, this->totalLevels);
        }
    }
}
