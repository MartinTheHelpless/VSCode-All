#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"

class huffCode
{
private:
    int frequencies[256];

    Node *root;

public:
    huffCode(std::ifstream *input);
    void createTree();
    Node *getRootNode();
    int getTreeDepth(Node *node);
};