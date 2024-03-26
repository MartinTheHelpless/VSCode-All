#include <vector>
#include <algorithm>
#include <random>

#include "Node.h"

class Maze;

class RandomPath
{
private:
    std::vector<Node *> m_Intersections;

public:
    RandomPath() {}
    ~RandomPath() {}

    bool visit(Node *(&current))
    {
        auto AddNeighboursToVector = [](Node *current, std::vector<Node *> &neighbours) -> void
        {
            if (current->m_TopNeighbour != nullptr &&
                current->m_TopNeighbour->m_Type != 0 &&
                !current->m_TopNeighbour->m_Visited)
            {
                current->m_TopNeighbour->m_PrevNode = current;
                neighbours.push_back(current->m_TopNeighbour);
            }

            if (current->m_RightNeighbour != nullptr &&
                current->m_RightNeighbour->m_Type != 0 &&
                !current->m_RightNeighbour->m_Visited)
            {
                current->m_RightNeighbour->m_PrevNode = current;
                neighbours.push_back(current->m_RightNeighbour);
            }

            if (current->m_BottomNeighbour != nullptr &&
                current->m_BottomNeighbour->m_Type != 0 &&
                !current->m_BottomNeighbour->m_Visited)
            {
                current->m_BottomNeighbour->m_PrevNode = current;
                neighbours.push_back(current->m_BottomNeighbour);
            }

            if (current->m_LeftNeighbour != nullptr &&
                current->m_LeftNeighbour->m_Type != 0 &&
                !current->m_LeftNeighbour->m_Visited)
            {
                current->m_LeftNeighbour->m_PrevNode = current;
                neighbours.push_back(current->m_LeftNeighbour);
            }
        };

        AddNeighboursToVector(current, m_Intersections);

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(m_Intersections.begin(), m_Intersections.end(), g);

        if (current->m_Type != 3)
        {
            current = m_Intersections.back();
            current->m_Visited = true;
            m_Intersections.pop_back();
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

    void Clear() { m_Intersections.clear(); }
};