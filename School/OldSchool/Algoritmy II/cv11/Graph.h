#include "Node.h"

class Graph
{
private:
    std::vector<Node *> nodes;

public:
    Graph(std::vector<std::vector<int>> *mat)
    {

        int size = (*mat).size();

        for (int i = 0; i < size; i++)
            this->nodes.push_back(new Node(i));

        for (int i = 0; i < size; i++)
            for (int j = i + 1; j < size; j++)
                if ((*mat)[i][j] > 0)
                {
                    this->nodes[i]->addNeighbour((*mat)[i][j], this->nodes[j]);
                    this->nodes[j]->addNeighbour((*mat)[i][j], this->nodes[i]);
                }
    }

    void clearGraph()
    {
        int size = this->nodes.size();

        for (int i = size - 1; i >= 0; i--)
        {
            this->nodes[i]->clear();
            this->nodes.pop_back();
        }
    }

    int minDistance(int dist[], bool sptSet[])
    {

        int min = INT_MAX, min_index;

        for (int v = 0; v < this->nodes.size(); v++)
            if (sptSet[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

    void dijkstra(std::vector<std::vector<int>> *graph, int src)
    {

        int graphSize = this->nodes.size();

        int dist[graphSize];

        bool sptSet[graphSize];

        for (int i = 0; i < graphSize; i++)
            dist[i] = INT_MAX, sptSet[i] = false;

        dist[src] = 0;

        for (int count = 0; count < graphSize - 1; count++)
        {

            int u = minDistance(dist, sptSet);

            sptSet[u] = true;

            for (int v = 0; v < graphSize; v++)

                if (!sptSet[v] && (*graph)[u][v] && dist[u] != INT_MAX && dist[u] + (*graph)[u][v] < dist[v])
                    dist[v] = dist[u] + (*graph)[u][v];
        }

        std::cout << "Vertex \t Distance from Source" << std::endl;
        for (int i = 0; i < this->nodes.size(); i++)
            std::cout << i << " \t\t" << dist[i] << std::endl;

        std::cout << "\n";
    }
};