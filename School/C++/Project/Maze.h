#pragma once
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <unordered_map>
#include <vector>

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

        Node *m_PrevNode;

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
            m_PrevNode = nullptr;
        }
    };

    Node *m_Current;
    Node *m_MazeNodes[3481];

    std::queue<Node *> m_Neighbours;
    std::vector<Node *> m_Intersections;

    uint32_t m_MazeMaxDim = 59;

public:
    Maze(float scale);

    void ClearMaze(float mazeScale);
    void ResetPath(float mazeScale);
    void RandomizeMazePrim(float scale);
    void RandomizeMazeKruskal(float scale);
    void DrawMaze(SDL_Renderer *rend, float mazeScale);

    void RandomizeMaze(uint32_t choice, float scale);

    bool PathFind(uint32_t algId, float mazeScale);

    bool PathFindDFS(float mazeScale);
    bool PathFindBFS(float mazeScale);
    bool PathFindRandom(float MazeScale);

    Node *GetMazeNode(uint32_t id) { return m_MazeNodes[id]; }
};
