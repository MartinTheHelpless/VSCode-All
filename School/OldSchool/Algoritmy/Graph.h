#pragma once
#include <vector>
#include <stack>

class Graph
{
private:
    class Vertex
    {
    public:
        int id;

        std::vector<Vertex *> neighbours;

        int color = 0;

        Vertex(int id)
        {
            this->id = id;
        }
    };

    std::vector<Vertex *> vertices;

public:
    void insertVertex(int id, std::vector<int> negbourdIds);

    void insertVertex(int id);

    void createDirectedEdge(int from, int to);

    void topologicSort(std::vector<int> &sortedVertices);

    bool process(Vertex *vertex, std::vector<int> &sortedVertices);

    Vertex *findeVertex(int id);

    bool findValueDFS(int id);
};