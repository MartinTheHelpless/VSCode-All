#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Node.h"

class huffCode
{
private:
    int frequencies[256];
    int valueMap[256][8];
    Node *root;

public:
    huffCode();
    void createTree();
    Node *getRootNode();
    int getTreeDepth(Node *node);
    void mapTree(Node *node, std::string dirs);
    void compress(std::ifstream *input, std::ofstream *output);
    void decompress(std::ifstream *input, std::ofstream *output);
};