#include <vector>
#include <random>
#include <algorithm>

#include "Node.h"

class Maze;

class PrimMaze
{
private:
    std::vector<std::pair<Node *, uint32_t>> m_Walls;

public:
    PrimMaze() {}
    ~PrimMaze() {}

    void visit(Node *(&maze)[3481], Node *(&current), float scale)
    {

        auto AddWallsToVector =
            [scale](Node *current,
                    std::vector<std::pair<Node *, uint32_t>> &m_Walls) -> void
        {
            if (current->m_TopNeighbour != nullptr &&
                current->m_TopNeighbour->m_Type == 0 &&
                current->m_TopNeighbour->m_ID > 59)
                m_Walls.push_back({current->m_TopNeighbour, 0});

            if (current->m_RightNeighbour != nullptr &&
                current->m_RightNeighbour->m_Type == 0 &&
                current->m_RightNeighbour->m_ID + 1 % 59 != 0)
                m_Walls.push_back({current->m_RightNeighbour, 1});

            if (current->m_BottomNeighbour != nullptr &&
                current->m_BottomNeighbour->m_Type == 0 &&
                current->m_BottomNeighbour->m_ID < 3421)
                m_Walls.push_back({current->m_BottomNeighbour, 2});

            if (current->m_LeftNeighbour != nullptr &&
                current->m_LeftNeighbour->m_Type == 0 &&
                current->m_LeftNeighbour->m_ID % 59 != 0)
                m_Walls.push_back({current->m_LeftNeighbour, 3});
        };

        for (Node *node : maze)
            if ((node->m_ID / static_cast<int>(59) - 1) % 2 +
                    (node->m_ID % static_cast<int>(59) - 1) % 2 ==
                0)
                node->m_Type = 1, node->m_Visited = false;
            else
                node->m_Type = 0, node->m_Visited = false;

        maze[static_cast<int>(59) + 1]->m_Type = 2;
        maze[static_cast<int>(scale * 59 - 118 + scale) - 2]->m_Type = 3;

        current = maze[static_cast<int>(59) + 1];

        AddWallsToVector(current, m_Walls);

        std::random_device rd;
        std::mt19937 g(rd());

        while (!m_Walls.empty())
        {
            std::shuffle(m_Walls.begin(), m_Walls.end(), g);

            Node *wall = m_Walls.back().first;
            uint32_t direction = m_Walls.back().second;
            m_Walls.pop_back();

            if (wall->m_TopNeighbour != nullptr && wall->m_BottomNeighbour != nullptr &&
                wall->m_TopNeighbour->m_Type == 1)
            {
                if (!wall->m_TopNeighbour->m_Visited ||
                    !wall->m_BottomNeighbour->m_Visited)
                {
                    wall->m_Type = 1;
                    wall->m_TopNeighbour->m_Visited = true;
                    wall->m_BottomNeighbour->m_Visited = true;

                    if (direction == 0)
                        current = wall->m_TopNeighbour;
                    else if (direction == 2)
                        current = wall->m_BottomNeighbour;

                    AddWallsToVector(current, m_Walls);
                }
            }
            else if (wall->m_RightNeighbour != nullptr &&
                     wall->m_LeftNeighbour != nullptr &&
                     wall->m_RightNeighbour->m_Type == 1)
            {
                if (!wall->m_RightNeighbour->m_Visited ||
                    !wall->m_LeftNeighbour->m_Visited)
                {
                    wall->m_Type = 1;
                    wall->m_RightNeighbour->m_Visited = true;
                    wall->m_LeftNeighbour->m_Visited = true;

                    if (direction == 1)
                        current = wall->m_RightNeighbour;
                    else if (direction == 3)
                        current = wall->m_LeftNeighbour;

                    AddWallsToVector(current, m_Walls);
                }
            }
        }

        for (int j = 0; j < scale; j++)
        {
            maze[static_cast<int>(scale - 1) + 59 * j]->m_Type = 0;
            maze[static_cast<int>(scale - 1) * 59 + j]->m_Type = 0;
        }

        maze[static_cast<int>((scale - 3) * 59 + scale) - 2]->m_Type = 1;
        maze[static_cast<int>((scale - 2) * 59 + scale) - 3]->m_Type = 1;
    }
};