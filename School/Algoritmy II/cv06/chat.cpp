#include <iostream>
#include <vector>

struct TreeNode
{
    int keys[2];           // Array to hold the keys (values) in sorted order
    TreeNode *children[3]; // Array to hold child pointers
    int keyCount;          // Number of keys in this node
};

TreeNode *insert(TreeNode *root, int value)
{
    if (root == nullptr)
    {
        TreeNode *newNode = new TreeNode();
        newNode->keys[0] = value;
        newNode->keyCount = 1;
        return newNode;
    }

    if (root->keyCount == 1)
    {
        // Node has one key
        if (value < root->keys[0])
        {
            root->keys[1] = root->keys[0];
            root->keys[0] = value;
        }
        else
        {
            root->keys[1] = value;
        }
        root->keyCount = 2;
    }
    else if (root->keyCount == 2)
    {
        // Node has two keys
        if (value < root->keys[0])
        {
            // Insert at the left
            TreeNode *newLeft = insert(root->children[0], value);
            if (newLeft != root->children[0])
            {
                // Node split, adjust the parent node
                root->children[2] = root->children[1];
                root->children[1] = root->children[0];
                root->children[0] = newLeft;
                root->keys[2] = root->keys[1];
                root->keys[1] = root->keys[0];
                root->keys[0] = newLeft->keys[0];
                root->keyCount++;
            }
        }
        else if (value < root->keys[1])
        {
            // Insert in the middle
            TreeNode *newMiddle = insert(root->children[1], value);
            if (newMiddle != root->children[1])
            {
                // Node split, adjust the parent node
                root->children[2] = root->children[1];
                root->children[1] = newMiddle;
                root->keys[2] = root->keys[1];
                root->keys[1] = newMiddle->keys[0];
                root->keyCount++;
            }
        }
        else
        {
            // Insert at the right
            TreeNode *newRight = insert(root->children[2], value);
            if (newRight != root->children[2])
            {
                // Node split, adjust the parent node
                root->children[2] = newRight;
                root->keys[2] = newRight->keys[0];
                root->keyCount++;
            }
        }
    }
    return root;
}

int main()
{
    TreeNode *root = nullptr;

    std::vector<int> values = {64, 13, 93, 12, 20, 61, 58, 37, 47, 77, 81, 68, 35, 7, 34};

    for (int i = 0; i < values.size(); i++)
        root = insert(root, values[i]);

    std::cout << "End" << std::endl;

    return 0;
}
