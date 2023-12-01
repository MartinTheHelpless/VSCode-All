#pragma once
#include <vector>
#include <iostream>
#include <stack>

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

class Graph
{
private:
    std::vector<Vertex *> vertices;

public:
    void insertVertex(int id, std::vector<int> negbourdIds);

    void insertVertex(int id);

    void createDirectedEdge(int from, int to);

    void topologicSort(std::vector<int> &sortedVertices);

    void loadGraph(FILE *graphFile);

    bool process(Vertex *vertex, std::vector<int> &sortedVertices);

    Vertex *findeVertex(int id);

    bool findValueDFS(int id);
};