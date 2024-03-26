#pragma once
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "Node.h"
#include "defines.h"
#include "DFS_Alg.h"
#include "BFS_Alg.h"
#include "PrimMaze.h"
#include "Random_Alg.h"
#include "KruskalMaze.h"

class Maze
{
private:
    BFSPath m_Bfs;
    DFSPath m_Dfs;
    RandomPath m_Rand;

    Node *m_Current;
    Node *m_MazeNodes[3481];

    std::vector<Node *> m_Intersections;

    uint32_t m_MazeMaxDim = 59;
    uint32_t m_CurrentScale = 59;

    void acceptPrim()
    {
        PrimMaze prim = PrimMaze();
        prim.visit(m_MazeNodes, m_Current, m_CurrentScale);
        ResetPath();
    }

    void acceptKruskal()
    {
        KruskalMaze kruskal = KruskalMaze();
        kruskal.visit(m_MazeNodes, m_Current, m_CurrentScale);
        ResetPath();
    }

    bool acceptBFS()
    {
        if (!m_Bfs.visit(m_Current))
            return false;
        m_Bfs.Clear();
        return true;
    }

    bool acceptDFS()
    {
        if (!m_Dfs.visit(m_Current))
            return false;
        m_Dfs.Clear();
        return true;
    }

    bool acceptRandom()
    {
        if (!m_Rand.visit(m_Current))
            return false;
        m_Rand.Clear();
        return true;
    }

public:
    Maze();

    void ClearMaze();
    void ResetPath();
    void Draw(SDL_Renderer *rend);

    void SetScale(uint32_t scale);
    void RandomizeMaze(uint32_t choice);

    bool PathFind(uint32_t algId);

    Node *GetMazeNode(uint32_t id) { return m_MazeNodes[id]; }
};
