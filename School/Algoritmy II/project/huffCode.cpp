#pragma once
#include "huffCode.h"

huffCode::huffCode()
{
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

void huffCode::compress(std::ifstream *input, std::ofstream *output)
{

    char c;
    (*input) >> std::noskipws;

    for (int i = 0; i < 256; i++)
        this->frequencies[i] = 0;

    while ((*input) >> c)
        this->frequencies[int(c)]++;

    (*input).clear();
    (*input).seekg(0, std::ios::beg);

    createTree();

    mapTree(this->root, "");

    // compressed data insertion:

    int bytes = 1;

    for (int i = 0; i < this->root->getCrs().length(); i++)
    {
        (*output).put(this->root->getCrs()[i]);
        (*output).put(char(this->frequencies[int(this->root->getCrs()[i])]));
        bytes++;
    }

    (*output).put(char(0));

    unsigned char currentByte = 0;
    int bitOffset = 7;

    while ((*input) >> c)
    {
        for (int i = 0; i < 8; i++)
        {
            if (this->valueMap[int(c)][i] == 0 || this->valueMap[int(c)][i] == 1)
            {
                if (this->valueMap[int(c)][i] == 1)
                    currentByte |= (1 << bitOffset);

                bitOffset--;
                if (bitOffset < 0)
                {
                    bytes++;
                    (*output).put(currentByte);
                    currentByte = 0;
                    bitOffset = 7;
                }
            }
            else
                break;
        }
    }

    if (bitOffset != 7)
    {
        (*output).put(currentByte);
        bytes++;
    }

    int inBytes = 0;

    for (int i = 0; i < 256; i++)
        inBytes += this->frequencies[i];

    std::cout << std::setprecision(3);
    std::cout << "Original file size: " << inBytes * 8 << "b\nCompressed file size: " << bytes * 8 << "b.\nCompression ratio: " << double(bytes) / double(inBytes) * 100 << "%." << std::endl;
}

void huffCode::decompress(std::ifstream *input, std::ofstream *output)
{

    (*input) >> std::noskipws;

    for (int i = 0; i < 256; i++)
        this->frequencies[i] = 0;

    char check;

    (*input) >> check;

    int origLength = 0;

    while (check != 0)
    {
        int tmp = int(check);
        (*input) >> check;
        this->frequencies[tmp] = int(check);
        origLength += int(check);
        (*input) >> check;
    }

    createTree();

    std::string decomp = "";

    for (int i = 0; (*input) >> check; i++)
        decomp.append(std::string(sizeof(char), check));

    Node *navNode = this->root;

    for (int i = 0; origLength != 0; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // get bit from string

            bool bit = (decomp[i] >> (7 - j)) & 1;

            // move in a tree according to the bit

            if (bit)
                navNode = navNode->getRChild();
            else
                navNode = navNode->getLChild();

            // check if the node is leaf node

            if (navNode->getLChild() == nullptr && navNode->getRChild() == nullptr)
            {
                (*output).put(navNode->getCrs()[0]);
                navNode = this->root;
                origLength--;
                if (origLength == 0)
                    break;
            }
        }
    }
}
