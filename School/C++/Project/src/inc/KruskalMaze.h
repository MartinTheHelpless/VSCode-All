#include <vector>
#include <random>
#include <algorithm>

#include "Node.h"

class Maze;

class KruskalMaze
{
private:
    std::vector<Node *> m_Walls;

public:
    KruskalMaze() {}
    ~KruskalMaze() {}

    void visit(Node *(&maze)[3481], Node *(&current), float scale)
    {

        uint32_t index = 0;

        for (Node *node : maze)
            if ((node->m_ID / static_cast<int>(59) - 1) % 2 +
                    (node->m_ID % static_cast<int>(59) - 1) % 2 ==
                0)
                node->m_Type = 1, node->m_Visited = false, node->m_SetID = index++;
            else
                node->m_Type = 0, node->m_Visited = false;

        maze[static_cast<int>(59) + 1]->m_Type = 2;
        maze[static_cast<int>((scale - 2) * 59 + scale) - 2]->m_Type = 3;

        for (int i = 2; i < scale - 1; i += 2)
            for (int j = 1; j < scale - 1; j += 2)
                m_Walls.push_back(maze[static_cast<int>(59) * i + j]),
                    m_Walls.push_back(maze[static_cast<int>(59) * j + i]);

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(m_Walls.begin(), m_Walls.end(), g);

        while (!m_Walls.empty())
        {
            current = m_Walls.back();
            m_Walls.pop_back();

            if (current->m_TopNeighbour != nullptr && current->m_BottomNeighbour != nullptr && current->m_TopNeighbour->m_Type == 1)
            {
                if (current->m_TopNeighbour->m_SetID != current->m_BottomNeighbour->m_SetID)
                {
                    current->m_Type = 1;

                    uint32_t ID_To_Change = current->m_BottomNeighbour->m_SetID;

                    for (Node *node : maze)
                        if (node->m_SetID == ID_To_Change)
                            node->m_SetID = current->m_TopNeighbour->m_SetID;
                }
            }
            else if (current->m_RightNeighbour != nullptr &&
                     current->m_LeftNeighbour != nullptr &&
                     current->m_RightNeighbour->m_Type == 1)
            {
                if (current->m_RightNeighbour->m_SetID !=
                    current->m_LeftNeighbour->m_SetID)
                {
                    current->m_Type = 1;

                    uint32_t ID_To_Change = current->m_LeftNeighbour->m_SetID;

                    for (Node *node : maze)
                        if (node->m_SetID == ID_To_Change)
                            node->m_SetID = current->m_RightNeighbour->m_SetID;
                }
            }
        }
    }
};