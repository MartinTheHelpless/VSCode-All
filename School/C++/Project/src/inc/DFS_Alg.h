#include <vector>

#include "Node.h"

class Maze;

class DFSPath
{
private:
    std::vector<Node *> m_Intersections;

public:
    DFSPath() {}
    ~DFSPath() {}

    bool visit(Node *(&current))
    {
        auto GetDirNeighbour = [](Node *current, uint32_t direction) -> Node *
        {
            switch (direction)
            {
            case 0:
                return current->m_BottomNeighbour;
                break;

            case 1:
                return current->m_RightNeighbour;
                break;

            case 2:
                return current->m_TopNeighbour;
                break;

            case 3:
                return current->m_LeftNeighbour;
                break;

            default:
                break;
            }

            return nullptr;
        };

        auto GetWayCount = [GetDirNeighbour](Node *current) -> uint32_t
        {
            uint32_t count = 0;

            for (int i = 0; i < 4; i++)
            {
                Node *tmp = GetDirNeighbour(current, i);

                if (tmp != nullptr && !tmp->m_Visited && tmp->m_Type != 0)
                    count++;
            }
            return count;
        };

        if (GetWayCount(current) > 1)
            m_Intersections.push_back(current);
        else if (GetWayCount(current) == 0)
        {
            if (m_Intersections.empty())
                return true;

            current = m_Intersections.back();
            m_Intersections.pop_back();
            return false;
        }

        for (int i = 0; i < 4; i++)
        {
            Node *tmp = GetDirNeighbour(current, i);

            if (tmp != nullptr && !tmp->m_Visited && tmp->m_Type != 0)
            {
                tmp->m_PrevNode = current;
                current = tmp;
                current->m_Visited = true;
                break; // Stop after finding the first unvisited neighbor
            }
        }

        if (current->m_Type == 3)
        {
            Node *tmp = current;
            current = current->m_PrevNode;
            tmp->m_PrevNode = nullptr;

            while (current->m_PrevNode != nullptr)
            {
                current->m_Type = 2;
                current = current->m_PrevNode;
            }

            return true;
        }

        return false;
    }

    void Clear() { m_Intersections.clear(); }
};