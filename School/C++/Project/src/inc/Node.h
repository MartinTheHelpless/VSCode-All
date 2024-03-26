#pragma once
#include <iostream>
#include <cstdint>

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

    void Reset()
    {
        m_Type = 0;
        m_SetID = 0;
        m_Visited = false;
        m_PrevNode = nullptr;
    }
};
