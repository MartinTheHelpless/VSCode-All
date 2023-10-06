/*AVL strom(Adelson - Velsky a Landis) je vyvážený binární vyhledávací strom, který udržuje rovnováhu mezi výškou levého a pravého podstromu pro každý uzel.Vaším úkolem je implementovat základní operace pro manipulaci s AVL stromem.

AVL stromy v přednášce : https : // www.cs.vsb.cz/dvorsky/Download/Algorithms/Slides/Czech/TransformAndConquerStrategy.pdf
Slide : 49

- L/R Rotace

std::vector<int> avlVector = {20, 10, 5, 13, 18, 25, 26, 27, 28, 12};

Pro vizualizaci AVL stromu můžete využít : https : // www.cs.usfca.edu/~galles/visualization/AVLtree.html
Hotovou práci po kontrole zasílejte na adresu : radovan.recka.st@vsb.cz
Do předmětu zprávy uveďte : ALGC07_3[]
Odevzdávejte pouze zdrojové a hlavičkové kódy.[]*/

#include "Tree.cpp"

void sortVector(std::vector<int> *vect);

int main(int argc, char const *argv[])
{
    std::vector<int> avlVector = {20, 10, 5, 13, 18, 25, 26, 27, 28, 12};

    sortVector(&avlVector);

    for (int i = 0; i < avlVector.size() - 1; i++)
        if (avlVector[i] > avlVector[i + 1])
        {
            std::cout << "Vector is not sorted properly !!!" << std::endl;
            return 1;
        }

    Tree *tree = new Tree(&avlVector);

    std::cout << "Tree finished" << std::endl;

    tree->setLevels(tree->getNodeByValue(20), tree->getMaxLevel());

    tree->isBalanced();

    tree->displayTreeLevels();

    std::cout << "\n\n";

    std::cout << "Adding node 24" << std::endl;

    tree->addNode(24);

    std::cout << "Adding node 15" << std::endl;

    tree->addNode(15);

    tree->displayTree();

    return 0;
}

void sortVector(std::vector<int> *vect)
{
    // Vector is sorted here, to make the tree creation easier. Could be in the tree.h module
    // but I decidet it would be okay like this

    int size = (*vect).size();

    int valueArray[size];

    for (int i = size - 1; i >= 0; i--)
    {
        valueArray[i] = (*vect)[i];
        (*vect).pop_back();
    }

    for (int i = 0; i < size; i++)
    {
        int min = INT_MAX;
        int position;
        for (int o = 0; o < size; o++)
        {
            if (valueArray[o] < min)
            {
                min = valueArray[o];
                position = o;
            }
        }
        (*vect).push_back(min);
        valueArray[position] = INT_MAX;
    }
    size = (*vect).size();
}
