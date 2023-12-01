#include <iostream>
#include <vector>
#include <utility>

class Node
{
private:
    int id;
    std::vector<std::pair<int, Node *>> neighbours; // first = edge value ID, second = Node

public:
    Node(int id)
    {
        this->id = id;
    }

    void addNeigbour(std::pair<int, Node *> pair)
    {
        this->neighbours.push_back(pair);
    }

    void removeNeighbour(std::pair<int, Node *> pair)
    {

        int size = this->neighbours.size();

        std::pair<int, Node *> tmp[size];

        int a = 0;

        for (int i = size; i > 0; i--)
        {
            if (pair == this->neighbours[i])
            {
                this->neighbours.pop_back();
                break;
            }
            else
            {
                tmp[a] = this->neighbours[i];
                a++;
                this->neighbours.pop_back();
            }
        }

        for (int i = 0; i < a; i++)
            this->neighbours.push_back(tmp[i]);
    }

    int getId()
    {
        return this->id;
    }

    std::vector<std::pair<int, Node *>> *getNeighbours()
    {
        return &this->neighbours;
    }
};