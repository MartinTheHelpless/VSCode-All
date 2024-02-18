#include <vector>
#include <iostream>

class Node
{
private:
    int value;

public:
    std::vector<std::pair<int, Node *>> neighbours; // first - edge length, second - Node pointer

    Node(int value)
    {
        this->value = value;
    }

    void clear()
    {
        int size = neighbours.size();

        for (int i = size - 1; i >= 0; i--)
            this->neighbours.pop_back();
    }

    void addNeighbour(int length, Node *node)
    {
        this->neighbours.push_back(std::pair<int, Node *>(length, node));
    }

    void removeNeighbour(Node *node)
    {

        std::pair<int, Node *> tmp[neighbours.size()];

        int index = 0;

        for (int i = neighbours.size() - 1; i >= 0; i--)
        {
            if (node == neighbours[i].second)
            {
                neighbours.pop_back();
                break;
            }
            else
            {
                tmp[index++] = neighbours[i];
                neighbours.pop_back();
            }
        }

        for (int i = 0; i < index; i++)
            neighbours.push_back(tmp[i]);
    }

    int getValue()
    {
        return this->value;
    }
};
