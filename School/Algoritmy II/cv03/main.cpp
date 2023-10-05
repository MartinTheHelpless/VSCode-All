/*AVL strom(Adelson - Velsky a Landis) je vyvážený binární vyhledávací strom, který udržuje rovnováhu mezi výškou levého a pravého podstromu pro každý uzel.Vaším úkolem je implementovat základní operace pro manipulaci s AVL stromem.

AVL stromy v přednášce : https : // www.cs.vsb.cz/dvorsky/Download/Algorithms/Slides/Czech/TransformAndConquerStrategy.pdf
Slide : 49

- L/R Rotace

std::vector<int> avlVector = {20, 10, 5, 13, 18, 25, 26, 27, 28, 12};

Pro vizualizaci AVL stromu můžete využít : https : // www.cs.usfca.edu/~galles/visualization/AVLtree.html
Hotovou práci po kontrole zasílejte na adresu : radovan.recka.st@vsb.cz
Do předmětu zprávy uveďte : ALGC07_3[]
Odevzdávejte pouze zdrojové a hlavičkové kódy.[]*/

#include "Tree.h"

int main(int argc, char const *argv[])
{
    std::vector<int> avlVector = {20, 10, 5, 13, 18, 25, 26, 27, 28, 12};

    Tree *test = new Tree();

    for (int i = 0; i < avlVector.size(); i++)
    {
        Node *newNode = new Node(avlVector[i], NULL, NULL);
        test->addNode(newNode);
    }

    test->sortAVLTree();

    return 0;
}
