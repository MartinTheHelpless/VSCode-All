#include "TwoThreeTree.h"

TwoThreeTree::TwoThreeTree()
{
    root = nullptr;
}

Node *TwoThreeTree::getParentNode(Node *node)
{

    Node *tmpNode = this->root;

    while (tmpNode->childL != node && tmpNode->childM != node && tmpNode->childR != node)
    {
        if (node == tmpNode->childL)
            return tmpNode;
        else if (node == tmpNode->childR)
            return tmpNode;
        else if (node == tmpNode->childM)
            return tmpNode;
        else if (node->val2 > tmpNode->val2)
            tmpNode = tmpNode->childR;
        else if (node->val1 < tmpNode->val1)
            tmpNode = tmpNode->childL;
        else
            tmpNode = tmpNode->childM;
    }
}

void TwoThreeTree::insert(int value)
{
    if (this->root == nullptr)
        this->root = new Node(value, nullptr, nullptr);
    else
    {
        Node *tmpNode = this->root;

        while (true)
        {
            if (value == tmpNode->val1 || value == tmpNode->val2)
            {
                std::cout << "Value already exists in a tree" << std::endl;
                break;
            }

            if (tmpNode->val1 > value)
            {
                if (tmpNode->childL == nullptr)
                    break;
                tmpNode = tmpNode->childL;
            }
            else if (tmpNode->val2 < value)
            {
                if (tmpNode->childR == nullptr)
                    break;
                tmpNode = tmpNode->childR;
            }
            else
            {
                if (tmpNode->childM == nullptr)
                    break;
                tmpNode = tmpNode->childM;
            }
        }

        if (tmpNode->val2 == INT_MAX)
        {
            if (tmpNode->val1 > value)
            {
                tmpNode->val2 = tmpNode->val1;
                tmpNode->val1 = value;
            }
            else if (tmpNode->val1 < value)
                tmpNode->val1 = value;
        }
        else
        {

            int moveValue;

            if (tmpNode->val2 > value)
                moveValue = tmpNode->val2;

            if (tmpNode->val2 < value)
            {
                moveValue = tmpNode->val2;
            }
        }
    }
}
