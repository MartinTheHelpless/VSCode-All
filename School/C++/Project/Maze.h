#pragma once
#include <queue>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include <unordered_map>

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

        bool m_Visited = false;

        uint32_t m_ID;
        uint32_t m_Type = 0; // Wall, free space, start, end ---- 0, 1, 2, 3 respectively
        uint32_t m_SetID = 0;

        Node(uint32_t id)
        {
            m_ID = id;

            m_TopNeighbour = nullptr;
            m_BottomNeighbour = nullptr;
            m_RightNeighbour = nullptr;
            m_LeftNeighbour = nullptr;
        }
    };

    uint32_t m_Dimension;    // Width and height of the grid
    uint32_t m_StartID = 60; // X and Y start for the patfindiong algorithm
    uint32_t m_EndID = 3420; // X and Y end for the patfinding algorithm

    Node *m_Current;
    Node *m_MazeNodes[3481];
    std::queue<Node *> m_Neighbours;
    std::vector<Node *> m_Intersections;

public:
    Maze();

    void ClearMaze();
    void ResetPath();
    void RandomizeMazePrim(float scale);
    void RandomizeMazeKruskal(float scale);
    void DrawMaze(SDL_Renderer *rend, float scale);

    void RandomizeMaze(uint32_t choice, float scale);

    bool PathFind(uint32_t algId);

    bool PathFindDFS();
    bool PathFindBFS();

    Node *GetMazeNode(uint32_t id) { return m_MazeNodes[id]; }
};
