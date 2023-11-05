#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"

class huffCode
{
private:
    int frequencies[256];
    int valueMap[256][8];
    Node *root;

public:
    huffCode(std::ifstream *input);
    void createTree();
    Node *getRootNode();
    int getTreeDepth(Node *node);
    void mapTree(Node *node, std::string dirs);
    void createOutput(std::ifstream *input, std::ofstream *output);
};