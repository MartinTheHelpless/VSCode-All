#include "Node.h"

class TwoThreeTree
{
private:
    Node *root;

public:
    TwoThreeTree();
    Node *getParentNode(Node *node);
    void insert(int value);
};