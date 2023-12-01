#include "PersonalProjects\C++\Algs\Structures\Node\Node.h"
#include <vector>

class Tree
{
private:
    Node *root;
    int depth;
    int maxVal;
    int minVal;

public:
    Tree();
    Tree(std::vector<int> *vect);
    void addNode(int value);
    void isBalanced();
    void treeFromVector(double start, double end, std::vector<int> *vect);
    Node *getNodeByValue(int val);
    Node *getNextNode(double start, double end, std::vector<int> *vect);
};