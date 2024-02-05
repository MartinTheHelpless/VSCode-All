#pragma once
#include <SDL2/SDL.h>

class Block
{
protected:
    int m_X;
    int m_Y;

public:
    Block(int x, int y) : m_X(x), m_Y(y) {}

    int GetX();
    int GetY();
    void SetX(int x);
    void SetY(int y);
    void IncrementX();
    void IncrementY();
    void DecrementX();
    void DecrementY();

    virtual void DrawOnBoard(char (&board)[22][10]) = 0;
    virtual void DrawGhostPiece(char (&board)[22][10]) = 0;
    virtual void DeleteFromBoard(char (&board)[22][10]) = 0;
    virtual void RemoveGhostPiece(char (&board)[22][10]) = 0;
    virtual void CheckIfRotatableR(char (&board)[22][10]) = 0;
    virtual void CheckIfRotatableL(char (&board)[22][10]) = 0;
    virtual bool CheckPositionIsFinal(char (&board)[22][10]) = 0;
    virtual bool CheckPositionIsFinal(char (&board)[22][10], int y) = 0;

    virtual int CheckSideFree(char (&board)[22][10], int side) = 0;
};