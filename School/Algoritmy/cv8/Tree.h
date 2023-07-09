#pragma once

class Tree
{

public:
    class Node
    {
    public:
        int value;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(int value)
        {
            this->value = value;
        }
    };

    Node *root = nullptr;

    void insertValue(int value);
    void insertValueInner(Node *&root, int value);
};
