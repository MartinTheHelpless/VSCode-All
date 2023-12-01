#include "Graph.h"

int main(int argc, char const *argv[])
{

    std::vector<std::vector<int>> matrix1 = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}};

    Graph *test = new Graph(&matrix1);

    Node *root = test->getPrimTree();

    std::cout << "End" << std::endl;

    return 0;
}
