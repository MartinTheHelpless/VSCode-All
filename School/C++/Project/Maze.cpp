#include "Maze.h"

Maze::Maze()
{
    for (int i = 0; i < 3600; i++)
        m_MazeNodes[i] = new Node(i);

    for (int i = 0; i < 3600; i++)
        if (true)
        {
            if (i % 60 != 0)
            {
                m_MazeNodes[i]->m_LeftNeighbour = m_MazeNodes[i - 1];
                m_MazeNodes[i - 1]->m_RightNeighbour = m_MazeNodes[i];
            }

            if ((i + 1) % 60 != 0)
            {
                m_MazeNodes[i]->m_RightNeighbour = m_MazeNodes[i + 1];
                m_MazeNodes[i + 1]->m_LeftNeighbour = m_MazeNodes[i];
            }

            if (i - 60 >= 0)
            {
                m_MazeNodes[i]->m_TopNeighbour = m_MazeNodes[i - 60];
                m_MazeNodes[i - 60]->m_BottomNeighbour = m_MazeNodes[i];
            }

            if (i + 60 <= 3559)
            {
                m_MazeNodes[i]->m_BottomNeighbour = m_MazeNodes[i + 60];
                m_MazeNodes[i + 60]->m_TopNeighbour = m_MazeNodes[i];
            }
        }
}

void Maze::DrawMaze(SDL_Renderer *rend, float scale)
{

    for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++)
        {
            switch (m_MazeNodes[i * 60 + j]->m_Type)
            {
            case 0:
                SDL_SetRenderDrawColor(rend, 13, 36, 74, 0);
                break;

            case 1:
                SDL_SetRenderDrawColor(rend, 135, 135, 135, 0);
                break;

            case 2:
                SDL_SetRenderDrawColor(rend, 156, 0, 0, 0);
                break;

            case 3:
                SDL_SetRenderDrawColor(rend, 0, 156, 0, 0);
                break;

            default:
                break;
            }

            SDL_Rect tmp = {WINDOW_MARGIN + j * (600.0f / scale), WINDOW_MARGIN + i * (600.0f / scale), (600.0f / scale) * 0.9f, (600.0f / scale) * 0.9f};
            SDL_RenderFillRect(rend, &tmp);
        }
}

void Maze::RandomizeMaze()
{
}

void Maze::ClearMaze()
{
    for (int i = 0; i < 3600; i++)
        m_MazeNodes[i]->m_Type = 1;
}
