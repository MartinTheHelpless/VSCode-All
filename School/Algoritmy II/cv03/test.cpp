#include <iostream>

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    int height; // Height of the node

    TreeNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    TreeNode *root;

    // Helper functions for rotations
    TreeNode *rightRotate(TreeNode *node);
    TreeNode *leftRotate(TreeNode *node);
    TreeNode *leftRightRotate(TreeNode *node);
    TreeNode *rightLeftRotate(TreeNode *node);

    int height(TreeNode *node);
    int balanceFactor(TreeNode *node);

    TreeNode *insert(TreeNode *node, int data);

public:
    AVLTree() : root(nullptr) {}

    void insert(int data);
    void display();
};

// Implement AVL tree rotation functions
TreeNode *AVLTree::rightRotate(TreeNode *y)
{
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

// Implement the leftRotate, leftRightRotate, and rightLeftRotate functions similarly.

// Insertion function
TreeNode *AVLTree::insert(TreeNode *node, int data)
{
    if (node == nullptr)
    {
        return new TreeNode(data);
    }

    if (data < node->data)
    {
        node->left = insert(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
    }
    else
    {
        // Duplicate values are not allowed in a BST.
        return node;
    }

    // Update height of current node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Get the balance factor and perform rotations if needed
    int balance = balanceFactor(node);

    // Left Heavy
    if (balance > 1)
    {
        if (data < node->left->data)
        {
            return rightRotate(node);
        }
        else
        {
            return leftRightRotate(node);
        }
    }

    // Right Heavy
    if (balance < -1)
    {
        if (data > node->right->data)
        {
            return leftRotate(node);
        }
        else
        {
            return rightLeftRotate(node);
        }
    }

    return node;
}

// Public insert function
void AVLTree::insert(int data)
{
    root = insert(root, data);
}

// Display function (in-order traversal)
void inOrderTraversal(TreeNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    inOrderTraversal(node->left);
    std::cout << node->data << " ";
    inOrderTraversal(node->right);
}

void AVLTree::display()
{
    inOrderTraversal(root);
    std::cout << std::endl;
}

int main()
{
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    tree.display(); // Display the AVL tree

    return 0;
}
