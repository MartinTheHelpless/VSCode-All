#include "Node.h"

class Graph
{
private:
    int graphSize;
    Node *start;

    class triple
    {
    public:
        int value;
        int firstID;
        int secondID;
        triple(int value, int first, int second)
        {
            this->value = value;
            this->firstID = first;
            this->secondID = second;
        }
    };

public:
    Graph(std::vector<std::vector<int>> *mat)
    {
        this->graphSize = (*mat).size();

        Node *nodes[this->graphSize];

        for (int i = 0; i < this->graphSize; i++)
            nodes[i] = new Node(i);

        this->start = nodes[0];

        for (int i = 0; i < this->graphSize; i++)
            for (int j = i + 1; j < this->graphSize; j++)
                if ((*mat)[i][j] > 0)
                {
                    nodes[i]->addNeigbour(std::pair<int, Node *>((*mat)[i][j], nodes[j]));
                    nodes[j]->addNeigbour(std::pair<int, Node *>((*mat)[i][j], nodes[i]));
                }
    }

    Node *getPrimTree()
    {

        std::vector<int> visited;

        Node *root = new Node(this->start->getId());

        visited.push_back(root->getId());

        Node *tmp = this->start;

        Node *tree = root;

        while (visited.size() < this->graphSize)
        {

            while (true)
            {

                int value = INT_MAX;
                Node *node;

                for (int i = 0; i < (*tmp->getNeighbours()).size(); i++)
                {
                    if (value > (*tmp->getNeighbours())[i].first)
                    {
                        bool in = false;

                        for (int j = 0; j < visited.size(); j++)
                        {
                            if (visited[j] == (*tmp->getNeighbours())[i].second->getId())
                            {
                                in = true;
                                break;
                            }
                        }

                        if (!in)
                        {
                            value = (*tmp->getNeighbours())[i].first;
                            node = (*tmp->getNeighbours())[i].second;
                        }
                    }
                }

                if (value == INT_MAX)
                {
                    break;
                }
                else
                {
                    Node *next = new Node(node->getId());
                    tree->addNeigbour(std::pair<int, Node *>(value, next));
                    tree = next;
                    tmp = node;
                    visited.push_back(tree->getId());
                }
            }
        }

        return root;
    }
};