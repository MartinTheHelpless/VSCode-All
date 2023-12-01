#include <iostream>
#include "Graph.cpp"

int main(int argc, char const *argv[])
{

    Graph *g = new Graph();

    g->insertVertex(1);
    g->insertVertex(2);
    g->insertVertex(3);
    g->insertVertex(4);
    g->insertVertex(5);
    g->insertVertex(6);
    g->insertVertex(7);
    g->insertVertex(8);
    g->insertVertex(9);
    g->insertVertex(10);

    g->createDirectedEdge(1, 2);
    g->createDirectedEdge(1, 3);
    g->createDirectedEdge(2, 3);
    g->createDirectedEdge(2, 9);
    g->createDirectedEdge(3, 4);
    g->createDirectedEdge(3, 5);
    g->createDirectedEdge(3, 8);
    g->createDirectedEdge(8, 6);
    g->createDirectedEdge(8, 7);
    g->createDirectedEdge(8, 9);
    g->createDirectedEdge(9, 10);

    // std::cout << "Vertex " << (g->findValueDFS(7) ? "" : "NOT ") << "found." << std::endl;

    std::vector<int> sortedVertices;

    g->topologicSort(sortedVertices);

    std::cout << "Topologically sorted vector sortedVertices: " << std::endl;

    for (auto sortedVertex : sortedVertices)
    {
        std::cout << sortedVertex << std::endl;
    }

    return 0;
}
