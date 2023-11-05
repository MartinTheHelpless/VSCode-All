#pragma once
#include "huffCode.h"

huffCode::huffCode(std::ifstream *input)
{

    char c;
    (*input) >> std::noskipws;

    for (int i = 0; i < 256; i++)
        this->frequencies[i] = 0;

    while ((*input) >> c)
        this->frequencies[int(c)]++;

    (*input).clear(); // clear fail and eof bits
    (*input).seekg(0, std::ios::beg);

    createTree();

    int treeDepth = getTreeDepth(this->root) - 1;

    int valueMap[256][treeDepth];

    mapTree(this->root, "");
}

void huffCode::createTree()
{
    int maxCount = 0;
    int nodeCount = 0;
    int totalCount = 0;

    for (int i = 0; i < 256; i++)
    {
        totalCount += this->frequencies[i];
        if (maxCount < this->frequencies[i])
            maxCount = this->frequencies[i];
        if (this->frequencies[i] > 0)
            nodeCount++;
    }

    Node *nodeBook[nodeCount];

    int position = 0;

    for (int i = 1; i < maxCount + 1; i++)
        for (int j = 0; j < 256; j++)
            if (this->frequencies[j] == i)
                nodeBook[position++] = new Node(this->frequencies[j], std::string() + char(j));

    Node *tmp = nullptr;

    for (int i = 1; i < totalCount + 1; i++)
        for (int j = 0; j < nodeCount; j++)
            if (nodeBook[j]->getValue() == i)
                if (tmp == nullptr)
                    tmp = nodeBook[j];
                else
                {
                    int sumVal = nodeBook[j]->getValue() + tmp->getValue();

                    Node *tmpNode;

                    if (tmp->getLChild() == nullptr && tmp->getRChild() == nullptr)
                        tmpNode = new Node(sumVal, tmp->getCrs() + nodeBook[j]->getCrs(), tmp, nodeBook[j]);
                    else
                        tmpNode = new Node(sumVal, nodeBook[j]->getCrs() + tmp->getCrs(), nodeBook[j], tmp);

                    nodeBook[j] = tmpNode;
                    tmp = nullptr;
                }

    int tmpVal = 0;

    for (int i = 0; i < nodeCount; i++)

        if (tmpVal < nodeBook[i]->getValue())
        {
            tmpVal = nodeBook[i]->getValue();
            tmp = nodeBook[i];
        }

    this->root = tmp;
}

Node *huffCode::getRootNode()
{
    return this->root;
}

int huffCode::getTreeDepth(Node *node)
{
    if (node->getLChild() == nullptr && node->getRChild() == nullptr)
        return 1;
    else
    {
        int l = getTreeDepth(node->getLChild());

        int r = getTreeDepth(node->getRChild());

        if (r > l)
            return 1 + r;
        else
            return 1 + l;
    }
}

void huffCode::mapTree(Node *node, std::string dirs)
{

    if (node->getLChild() == nullptr && node->getRChild() == nullptr)
    {
        int pos = int(node->getCrs()[0]);

        for (int i = 0; i < 8; i++)
            this->valueMap[pos][i] = (dirs[i] == '0' || dirs[i] == '1' ? dirs[i] - '0' : 6);
    }
    else
    {
        if (node->getLChild() != nullptr)
            mapTree(node->getLChild(), dirs + "0");
        if (node->getRChild() != nullptr)
            mapTree(node->getRChild(), dirs + "1");
    }
}

void huffCode::createOutput(std::ifstream *input, std::ofstream *output)
{

    char c;

    while ((*input) >> c)
    {
        for (int i = 0; i < 8; i++)
        {
            if (this->valueMap[int(c)][i] == 0 || this->valueMap[int(c)][i] == 1)
            {
                (*output) << this->valueMap[int(c)][i];
            }
            else
                break;
        }
    }
}
