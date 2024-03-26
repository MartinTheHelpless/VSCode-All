#include <queue>

#include "Node.h"

class Maze;

class BFSPath
{
private:
    std::queue<Node *> m_Neighbours;

public:
    BFSPath() {}
    ~BFSPath() {}

    bool visit(Node *(&current))
    {
        auto AddNeighboursToVector = [](Node *current, std::queue<Node *> &neighbours) -> void
        {
            if (current->m_TopNeighbour != nullptr &&
                current->m_TopNeighbour->m_Type != 0 &&
                !current->m_TopNeighbour->m_Visited)
            {
                current->m_TopNeighbour->m_PrevNode = current;
                neighbours.push(current->m_TopNeighbour);
            }

            if (current->m_RightNeighbour != nullptr &&
                current->m_RightNeighbour->m_Type != 0 &&
                !current->m_RightNeighbour->m_Visited)
            {
                current->m_RightNeighbour->m_PrevNode = current;
                neighbours.push(current->m_RightNeighbour);
            }

            if (current->m_BottomNeighbour != nullptr &&
                current->m_BottomNeighbour->m_Type != 0 &&
                !current->m_BottomNeighbour->m_Visited)
            {
                current->m_BottomNeighbour->m_PrevNode = current;
                neighbours.push(current->m_BottomNeighbour);
            }

            if (current->m_LeftNeighbour != nullptr &&
                current->m_LeftNeighbour->m_Type != 0 &&
                !current->m_LeftNeighbour->m_Visited)
            {
                current->m_LeftNeighbour->m_PrevNode = current;
                neighbours.push(current->m_LeftNeighbour);
            }
        };

        AddNeighboursToVector(current, m_Neighbours);

        if (current->m_Type != 3)
        {
            current = m_Neighbours.front();
            current->m_Visited = true;
            m_Neighbours.pop();
            return false;
        }
        else
        {
            Node *tmp = current;
            current = current->m_PrevNode;
            tmp->m_PrevNode = nullptr;

            while (current->m_PrevNode != nullptr && current->m_Type != 2)
            {
                current->m_Type = 2;
                current = current->m_PrevNode;
            }

            return true;
        }
    }

    void Clear()
    {
        while (!m_Neighbours.empty())
            m_Neighbours.pop();
    }
};