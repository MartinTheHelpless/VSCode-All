#include <iostream>

struct Node
{
    int data1;
    int data2;
    Node *left;
    Node *middle;
    Node *right;
    Node *parent;

    Node(int val) : data1(val), data2(-1), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}
};

class TwoThreeTree
{
private:
    Node *root;

    void splitNode(Node *node)
    {
        Node *parent = node->parent;
        if (parent == nullptr)
        {
            Node *newRoot = new Node(node->data2);
            newRoot->left = new Node(node->data1);
            newRoot->right = new Node(node->data2);
            newRoot->left->parent = newRoot;
            newRoot->right->parent = newRoot;
            root = newRoot;
            delete node;
            return;
        }

        Node *grandparent = parent->parent;
        if (parent->data2 == -1)
        {
            if (node->data1 < parent->data1)
            {
                parent->data2 = parent->data1;
                parent->data1 = node->data1;
                parent->middle = new Node(node->data2);
            }
            else
            {
                parent->data2 = node->data1;
                parent->middle = new Node(node->data2);
            }
            delete node;
            return;
        }

        if (parent->data1 < grandparent->data1)
        {
            grandparent->data2 = grandparent->data1;
            grandparent->data1 = parent->data1;
            grandparent->left = new Node(parent->data2);
            grandparent->middle = parent->middle;
            grandparent->right = new Node(parent->data2);
            grandparent->left->parent = grandparent;
            grandparent->middle->parent = grandparent;
            grandparent->right->parent = grandparent;
        }
        else
        {
            grandparent->data2 = parent->data1;
            grandparent->right = new Node(parent->data2);
            grandparent->right->parent = grandparent;
        }

        delete parent;
        splitNode(grandparent);
    }

public:
    TwoThreeTree() : root(nullptr) {}

    void insert(int value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
        }
        else
        {
            insert(root, value);
        }
    }

    void insert(Node *node, int value)
    {
        if (node->data2 == -1)
        {
            if (value < node->data1)
            {
                node->data2 = node->data1;
                node->data1 = value;
            }
            else
            {
                node->data2 = value;
            }
        }
        else
        {
            if (value < node->data1)
            {
                insert(node->left, value);
            }
            else if (value > node->data2)
            {
                insert(node->right, value);
            }
            else
            {
                insert(node->middle, value);
            }
        }

        splitNode(node);
    }

    bool search(int value)
    {
        return search(root, value);
    }

    bool search(Node *node, int value)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->data1 == value || (node->data2 != -1 && node->data2 == value))
        {
            return true;
        }
        else if (value < node->data1)
        {
            return search(node->left, value);
        }
        else if (node->data2 != -1 && value < node->data2)
        {
            return search(node->middle, value);
        }
        else
        {
            return search(node->right, value);
        }
    }

    void remove(int value)
    {
        root = remove(root, value);
    }

    Node *remove(Node *node, int value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (value < node->data1)
        {
            node->left = remove(node->left, value);
        }
        else if (node->data2 != -1 && value < node->data2)
        {
            node->middle = remove(node->middle, value);
        }
        else if (node->data1 == value)
        {
            node->data1 = findMin(node->right);
            node->right = remove(node->right, node->data1);
        }
        else
        {
            node->right = remove(node->right, value);
        }

        return node;
    }

    int findMin(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node->data1;
    }
};

int main()
{
    TwoThreeTree tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(15);
    tree.insert(20);
    tree.insert(25);
    tree.insert(30);
    tree.insert(35);

    int valueToSearch = 20;
    if (tree.search(valueToSearch))
    {
        std::cout << valueToSearch << " found in the tree." << std::endl;
    }
    else
    {
        std::cout << valueToSearch << " not found in the tree." << std::endl;
    }

    int valueToRemove = 15;
    tree.remove(valueToRemove);

    if (tree.search(35))
    {
        std::cout << valueToRemove << " found in the tree." << std::endl;
    }
    else
    {
        std::cout << valueToRemove << " not found in the tree." << std::endl;
    }

    return 0;
}
