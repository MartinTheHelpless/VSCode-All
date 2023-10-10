#pragma once
#include "Heap.h"
#include <math.h>

Heap::Heap()
{
    this->createHeap();
}

int Heap::size()
{
    return this->values.size();
}

bool Heap::is_empty()
{
    if (this->values.size() == 0)
        return true;
    else
        return false;
}

void Heap::print()
{
    for (int i = 0; i < this->values.size(); i++)
        std::cout << this->values[i] << std::endl;
}

void Heap::insert(int value)
{
    this->values.push_back(value);
    this->sortVector(&(this->values));
    this->createHeap();
}

void Heap::remove(int value)
{

    std::vector<int> temp;

    for (int i = 0; i < this->values.size(); i++)
        temp.push_back(this->values[i]);

    for (int i = 0; this->values.size() != 0; i++)
        this->values.pop_back();

    for (int i = 0; i < temp.size(); i++)
        if (temp[i] != value)
            this->values.push_back(temp[i]);

    createHeap();
}

void Heap::sortVector(std::vector<int> *vect)
{
    int size = (*vect).size();

    int valueArray[size];

    for (int i = size - 1; i >= 0; i--)
    {
        valueArray[i] = (*vect)[i];
        (*vect).pop_back();
    }

    for (int i = 0; i < size; i++)
    {
        int min = INT_MAX;
        int position;
        for (int o = 0; o < size; o++)
        {
            if (valueArray[o] < min)
            {
                min = valueArray[o];
                position = o;
            }
        }
        (*vect).push_back(min);
        valueArray[position] = INT_MAX;
    }
}

Node *Heap::getNextNode(int nodeIndex, int level)
{

    if (nodeIndex > 0)
    {
        Node *tmp = new Node(this->values[nodeIndex]);

        tmp->setlSubNode(getNextNode(nodeIndex - pow(2, level) / 2, level + 1));
        tmp->setrSubNode(getNextNode(nodeIndex - pow(2, level), level + 1));

        return tmp;
    }
    else
        return nullptr;
}

void Heap::createHeap()
{

    int lvls = 1;

    while (this->values.size() > pow(2, lvls))
        lvls++;

    this->rootNode = new Node(this->values[this->values.size() - 1]);

    this->rootNode->setlSubNode(getNextNode(this->values.size() - 2, 2));
    this->rootNode->setrSubNode(getNextNode(this->values.size() - 3, 2));
}
