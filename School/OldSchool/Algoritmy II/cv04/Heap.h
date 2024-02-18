#pragma once
#include <iostream>
#include <vector>
#include "Node.cpp"

class Heap
{
private:
    Node *rootNode;

    std::vector<int> values = {5, 8, 12, 14, 16, 18, 22, 26, 31, 35, 38, 40, 41, 44, 45, 47, 50, 51, 55};

    Node *getNextNode(int nodeIndex, int level);

    void sortVector(std::vector<int> *vect);

    void createHeap();

public:
    Heap();
    int size();
    bool is_empty();
    void print();
    void insert(int value);
    void remove(int value);
};