#include "PersonalProjects\C++\Algs\Structures\Node\Node.h"
#include "PersonalProjects\C++\Algs\Structures\binaryTree\Tree.cpp"

void vectSort(std::vector<int> *vect);

int main(int argc, char const *argv[])
{
    std::vector<int> treeVals = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

    // vectSort(&treeVals);

    Tree *test = new Tree(&treeVals);

    return 0;
}

void vectSort(std::vector<int> *vect)
{
    int n = (*vect).size();

    int pole[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (pole[j] < pole[j - 1])
            {
                int temp = pole[j];
                pole[j] = pole[j - 1];
                pole[j - 1] = temp;
            }
            else
                break;
        }
    }

    for (int i = 0; i < n; i++)
        (*vect).pop_back();

    for (int i = 0; i < n; i++)
        (*vect).push_back(pole[i]);
}
