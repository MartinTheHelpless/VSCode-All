#include "Maze.h"

Maze::Maze()
{
    for (int i = 0; i < 3481; i++)
        m_MazeNodes[i] = new Node(i);

    m_MazeNodes[m_StartID]->m_Type = 2;
    m_MazeNodes[m_EndID]->m_Type = 3;

    for (int i = 0; i < 3481; i++)
        if (true)
        {
            if (i % 59 != 0)
            {
                m_MazeNodes[i]->m_LeftNeighbour = m_MazeNodes[i - 1];
                m_MazeNodes[i - 1]->m_RightNeighbour = m_MazeNodes[i];
            }

            if ((i + 1) % 59 != 0)
            {
                m_MazeNodes[i]->m_RightNeighbour = m_MazeNodes[i + 1];
                m_MazeNodes[i + 1]->m_LeftNeighbour = m_MazeNodes[i];
            }

            if (i - 59 >= 0)
            {
                m_MazeNodes[i]->m_TopNeighbour = m_MazeNodes[i - 59];
                m_MazeNodes[i - 59]->m_BottomNeighbour = m_MazeNodes[i];
            }

            if (i + 59 <= 3420)
            {
                m_MazeNodes[i]->m_BottomNeighbour = m_MazeNodes[i + 59];
                m_MazeNodes[i + 59]->m_TopNeighbour = m_MazeNodes[i];
            }
        }

    m_Current = m_MazeNodes[m_StartID];
    m_Current->m_Visited = true;
}

void Maze::DrawMaze(SDL_Renderer *rend, float scale)
{

    for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++)
        {
            switch (m_MazeNodes[i * 59 + j]->m_Type)
            {
            case 0:
                SDL_SetRenderDrawColor(rend, 13, 36, 74, 0);
                break;

            case 1:
                if (m_MazeNodes[i * 59 + j]->m_Visited)
                    SDL_SetRenderDrawColor(rend, 252, 152, 3, 0);
                else
                    SDL_SetRenderDrawColor(rend, 135, 135, 135, 0);
                break;

            case 2:
                SDL_SetRenderDrawColor(rend, 0, 156, 0, 0);
                break;

            case 3:
                SDL_SetRenderDrawColor(rend, 156, 0, 0, 0);
                break;

            default:
                break;
            }

            SDL_Rect tmp = {static_cast<int>(WINDOW_MARGIN + j * (600.0f / scale)), static_cast<int>(WINDOW_MARGIN + i * (600.0f / scale)),
                            static_cast<int>((600.0f / scale) * 0.9f), static_cast<int>((600.0f / scale) * 0.9f)};
            SDL_RenderFillRect(rend, &tmp);
        }
}

void Maze::RandomizeMaze()
{

    auto AddWallsToVector = [](Node *current, std::vector<std::pair<Node *, uint32_t>> &walls) -> void
    {
        if (current->m_TopNeighbour != nullptr && current->m_TopNeighbour->m_Type == 0 && current->m_TopNeighbour->m_ID > 59)
            walls.push_back({current->m_TopNeighbour, 0});

        if (current->m_RightNeighbour != nullptr && current->m_RightNeighbour->m_Type == 0 && current->m_RightNeighbour->m_ID + 1 % 59 != 0)
            walls.push_back({current->m_RightNeighbour, 1});

        if (current->m_BottomNeighbour != nullptr && current->m_BottomNeighbour->m_Type == 0 && current->m_BottomNeighbour->m_ID < 3421)
            walls.push_back({current->m_BottomNeighbour, 2});

        if (current->m_LeftNeighbour != nullptr && current->m_LeftNeighbour->m_Type == 0 && current->m_LeftNeighbour->m_ID % 59 != 0)
            walls.push_back({current->m_LeftNeighbour, 3});
    };

    for (Node *node : m_MazeNodes)
        if ((node->m_ID / 59 - 1) % 2 + (node->m_ID % 59 - 1) % 2 == 0)
            node->m_Type = 1,
            node->m_Visited = false;
        else
            node->m_Type = 0,
            node->m_Visited = false;

    std::vector<std::pair<Node *, uint32_t>> walls;

    m_MazeNodes[m_StartID]->m_Type = 2;
    m_MazeNodes[m_EndID]->m_Type = 3;

    m_Current = m_MazeNodes[m_StartID];

    AddWallsToVector(m_Current, walls);

    while (!walls.empty())
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(walls.begin(), walls.end(), g);

        Node *wall = walls.back().first;
        uint32_t direction = walls.back().second;
        walls.pop_back();

        if (wall->m_TopNeighbour != nullptr && wall->m_TopNeighbour->m_Type == 1)
        {
            if (!wall->m_TopNeighbour->m_Visited || !wall->m_BottomNeighbour->m_Visited)
            {
                wall->m_Type = 1;
                wall->m_TopNeighbour->m_Visited = true;
                wall->m_BottomNeighbour->m_Visited = true;

                if (direction == 0)
                    m_Current = wall->m_TopNeighbour;
                else if (direction == 2)
                    m_Current = wall->m_BottomNeighbour;

                AddWallsToVector(m_Current, walls);
            }
        }
        else if (wall->m_RightNeighbour != nullptr && wall->m_RightNeighbour->m_Type == 1)
        {
            if (!wall->m_RightNeighbour->m_Visited || !wall->m_LeftNeighbour->m_Visited)
            {
                wall->m_Type = 1;
                wall->m_RightNeighbour->m_Visited = true;
                wall->m_LeftNeighbour->m_Visited = true;

                if (direction == 1)
                    m_Current = wall->m_RightNeighbour;
                else if (direction == 3)
                    m_Current = wall->m_LeftNeighbour;

                AddWallsToVector(m_Current, walls);
            }
        }
    }

    ResetPath();
}

void Maze::ClearMaze()
{
    for (int i = 0; i < 3481; i++)
        m_MazeNodes[i]->m_Type = 0,
        m_MazeNodes[i]->m_Visited = false;

    m_MazeNodes[m_StartID]->m_Type = 2;
    m_MazeNodes[m_EndID]->m_Type = 3;

    m_Current = m_MazeNodes[m_StartID];
    m_Current->m_Visited = true;
}

void Maze::ResetPath()
{
    for (Node *node : m_MazeNodes)
        node->m_Visited = false;

    m_Intersections.clear();
    m_Current = m_MazeNodes[m_StartID];
}

bool Maze::PathFind(uint32_t algId)
{

    switch (algId)
    {
    case 0:
        return PathFindDFS();
        break;

    case 1:
        /* code */
        break;

    case 2:
        /* code */
        break;

    case 3:
        /* code */
        break;

    default:
        break;
    }

    return true;
}

bool Maze::PathFindDFS()
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

    if (GetWayCount(m_Current) > 1)
        m_Intersections.push_back(m_Current);
    else if (GetWayCount(m_Current) == 0)
    {
        if (m_Intersections.empty())
            return true;

        m_Current = m_Intersections.back();
        m_Intersections.pop_back();
        return false;
    }

    for (int i = 0; i < 4; i++)
    {
        Node *tmp = GetDirNeighbour(m_Current, i);

        if (tmp != nullptr && !tmp->m_Visited && tmp->m_Type != 0)
        {
            m_Current = tmp;
            m_Current->m_Visited = true;
            break; // Stop after finding the first unvisited neighbor
        }
    }

    if (m_Current->m_ID == m_EndID)
        return true;

    return false;
}
