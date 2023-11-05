#include "TwoThreeTree.cpp"
#include <vector>

int main(int argc, char const *argv[])
{

    TwoThreeTree *tree = new TwoThreeTree();

    std::vector<int> values = {64, 13, 93, 12, 20, 61, 58, 37, 47, 77, 81, 68, 35, 7, 34};

    for (int i = 0; i < values.size(); i++)
        tree->insert(values[i]);

    return 0;
}
