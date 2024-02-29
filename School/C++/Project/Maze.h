#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "defines.h"

class Maze
{
private:
    class Node
    {
    public:
        Node *m_TopNeighbour;
        Node *m_BottomNeighbour;
        Node *m_RightNeighbour;
        Node *m_LeftNeighbour;
        uint32_t m_ID;
        uint32_t m_Type; // Wall, free space, start, end ---- 0, 1, 2, 3 respectively

        Node(uint32_t id)
        {
            m_ID = id;

            m_Type = rand() % 2;

            m_TopNeighbour = nullptr;
            m_BottomNeighbour = nullptr;
            m_RightNeighbour = nullptr;
            m_LeftNeighbour = nullptr;
        }
    };

    uint32_t m_Dimension; // Width and height of the grid
    uint32_t m_StartID;   // X and Y start for the patfindiong algorithm
    uint32_t m_EndID;     // X and Y end for the patfindiong algorithm

    Node *m_MazeNodes[3600];

public:
    Maze();

    void DrawMaze(SDL_Renderer *rend, float scale);
    void RandomizeMaze();
    void ClearMaze();

    Node *GetMazeNode(uint32_t id) { return m_MazeNodes[id]; }
};