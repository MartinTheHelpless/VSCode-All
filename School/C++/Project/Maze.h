#pragma once
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

    Node *m_MazeNodes[3481];
    Node *m_Current;
    std::vector<Node *> m_Intersections;

public:
    Maze();

    void DrawMaze(SDL_Renderer *rend, float scale);
    void RandomizeMaze();
    void ClearMaze();
    void ResetPath();

    bool PathFind(uint32_t algId);

    bool PathFindDFS();
    bool PathFindBFS();
    bool PathFindAStar();
    bool PathFindDijkstra();

    Node *GetMazeNode(uint32_t id) { return m_MazeNodes[id]; }
};
