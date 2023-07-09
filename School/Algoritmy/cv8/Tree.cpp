#include "Tree.h"

void Tree::insertValue(int value)
{

    insertValueInner(this->root, value);
}

void Tree::insertValueInner(Node *&root, int value)
{

    if (root == nullptr)
        root = new Node(value);

    if (root->value == value)
        return;

    if (root->value > value)
        insertValueInner(root->left, value);

    if (root->value < value)
        insertValueInner(root->right, value);
}
