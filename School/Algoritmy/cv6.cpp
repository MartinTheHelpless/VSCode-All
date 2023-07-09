#include <iostream>
#include "Graph.cpp"

int main(int argc, char const *argv[])
{

    Graph g;

    g.insertVertex(1);

    std::vector<int> neighbours;
    neighbours.push_back(1);

    g.insertVertex(2, neighbours);

    neighbours.clear();

    neighbours.push_back(1);

    neighbours.push_back(2);

    g.insertVertex(3, neighbours);

    neighbours.clear();

    neighbours.push_back(3);

    g.insertVertex(4, neighbours);

    neighbours.clear();

    neighbours.push_back(3);

    g.insertVertex(5, neighbours);

    neighbours.clear();

    neighbours.push_back(3);

    g.insertVertex(8, neighbours);

    neighbours.clear();

    neighbours.push_back(8);

    g.insertVertex(7, neighbours);

    neighbours.clear();

    neighbours.push_back(8);

    g.insertVertex(6, neighbours);

    neighbours.clear();

    neighbours.push_back(2);

    neighbours.push_back(8);

    g.insertVertex(9, neighbours);

    neighbours.clear();

    neighbours.push_back(9);

    g.insertVertex(10, neighbours);

    std::cout << "Vertex is" << (g.findValueDFS(0) ? "" : "NOT ") << "in graph." << std::endl;

    return 0;
}