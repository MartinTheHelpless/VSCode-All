#include "Graph.h"

Vertex *Graph::findeVertex(int id)
{

    for (auto vertex : vertices)
        if (vertex->id == id)
            return vertex;

    return nullptr;
}

void Graph::insertVertex(int id)
{
    this->vertices.push_back(new Vertex(id));
}

void Graph::insertVertex(int id, std::vector<int> neigbourIds)
{
    Vertex *newVertex = new Vertex(id);
    this->vertices.push_back(newVertex);

    for (auto nId : neigbourIds)
    {
        Vertex *neighbour = findeVertex(nId);
        if (neighbour != nullptr)
        {
            newVertex->neighbours.push_back(neighbour);

            if (newVertex->id != neighbour->id)
                neighbour->neighbours.push_back(newVertex);
        }
    }
}

void Graph::createDirectedEdge(int from, int to)
{

    Vertex *fromV = findeVertex(from);
    Vertex *toV = findeVertex(to);

    if (fromV != nullptr && toV != nullptr)
    {
        fromV->neighbours.push_back(toV);
    }
}

void Graph::topologicSort(std::vector<int> &sortedVertices)
{

    if (!process(vertices.front(), sortedVertices))
        sortedVertices.clear();

    return;
}

void Graph::loadGraph(FILE *graphFile)
{
    int lines = 0;
    int c = getc(graphFile);
    while (c != EOF)
    {
        lines++;
        c = getc(graphFile);
    }
    std::cout << lines << std::endl;
}

bool Graph::process(Vertex *vertex, std::vector<int> &sortedVertices)
{

    if (vertex->color == 2)
        return true;
    else if (vertex->color == 1)
        return false;

    vertex->color = 1;

    for (auto neighbour : vertex->neighbours)
        if (!process(neighbour, sortedVertices))
            return false;

    vertex->color = 2;
    sortedVertices.emplace(sortedVertices.begin(), vertex->id);
    return true;
}

bool Graph::findValueDFS(int id)
{
    Vertex *current = vertices.front();
    std::stack<Vertex *> stack;

    stack.push(current);
    current->color = 1;
    while (!stack.empty())
    {
        current = stack.top();
        stack.pop();

        current->color = 2;

        if (current->id == id)
            return true;

        for (auto neighbour : current->neighbours)
        {
            if (neighbour->color == 0)
            {
                neighbour->color = 1;
                stack.push(neighbour);
            }
        }
    }

    return false;
}
