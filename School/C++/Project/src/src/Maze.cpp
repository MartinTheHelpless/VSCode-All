#include "../inc/Maze.h"

Maze::Maze()
{

    m_Bfs = BFSPath();

    for (int i = 0; i < 3481; i++)
        m_MazeNodes[i] = new Node(i);

    m_MazeNodes[static_cast<int>(m_MazeMaxDim) + 1]->m_Type = 2;
    m_MazeNodes[static_cast<int>(m_MazeMaxDim * m_MazeMaxDim - m_MazeMaxDim) - 2]->m_Type = 3;

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

    m_Current = m_MazeNodes[static_cast<int>(m_MazeMaxDim) + 1];
    m_Current->m_Visited = true;
}

void Maze::Draw(SDL_Renderer *rend)
{
    if (static_cast<int>(m_CurrentScale) % 2 == 0)
        m_CurrentScale--;

    for (int i = 0; i < m_CurrentScale; i++)
        for (int j = 0; j < m_CurrentScale; j++)
        {
            switch (m_MazeNodes[i * static_cast<int>(59) + j]->m_Type)
            {
            case 0:
                SDL_SetRenderDrawColor(rend, 13, 36, 74, 0);
                break;

            case 1:
                if (m_MazeNodes[i * static_cast<int>(59) + j]->m_Visited)
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

            SDL_Rect tmp = {
                static_cast<int>(WINDOW_MARGIN + j * (600.0f / m_CurrentScale)),
                static_cast<int>(WINDOW_MARGIN + i * (600.0f / m_CurrentScale)),
                static_cast<int>((600.0f / m_CurrentScale) * 0.9f),
                static_cast<int>((600.0f / m_CurrentScale) * 0.9f)};
            SDL_RenderFillRect(rend, &tmp);
        }
}

void Maze::RandomizeMaze(uint32_t choice)
{
    ClearMaze();

    switch (choice)
    {
    case 0:

        break;

    case 1:
        acceptPrim();
        break;

    case 2:
        acceptKruskal();
        break;

    default:
        break;
    }
}

void Maze::SetScale(uint32_t scale)
{
    m_CurrentScale = scale;

    if (static_cast<int>(m_CurrentScale) % 2 == 0)
        m_CurrentScale--;

    ClearMaze();
}

void Maze::ClearMaze()
{
    for (int i = 0; i < 3481; i++)
        m_MazeNodes[i]->Reset();

    m_MazeNodes[static_cast<int>(m_CurrentScale) + 1]->m_Type = 2;
    m_MazeNodes[static_cast<int>(m_CurrentScale * m_CurrentScale - m_CurrentScale) - 2]->m_Type = 3;

    m_Current = m_MazeNodes[static_cast<int>(m_MazeMaxDim) + 1];
    m_Current->m_Visited = true;
}

void Maze::ResetPath()
{
    for (Node *node : m_MazeNodes)
    {
        node->m_Visited = false;
        if (node->m_PrevNode != nullptr)
        {
            node->m_PrevNode = nullptr;
            node->m_Type = 1;
        }
    }

    m_Intersections.clear();

    m_Current = m_MazeNodes[60];

    m_Current = m_MazeNodes[static_cast<int>(m_MazeMaxDim) + 1];
    m_Current->m_Visited = true;
}

bool Maze::PathFind(uint32_t algId)
{
    switch (algId)
    {
    case 0:
        return acceptDFS();
        break;

    case 1:
        return acceptBFS();
        break;

    case 2:
        return acceptRandom();
        break;
    default:
        break;
    }

    return true;
}
