#pragma once
#include "Block.h"

class Three : public Block
{
private:
    char m_Shape[3][3];

public:
    Three(const char (&shape)[3][3], int x, int y);

    virtual void DrawOnBoard(char (&board)[22][10]) override;
    virtual void DrawGhostPiece(char (&board)[22][10]) override;
    virtual void DeleteFromBoard(char (&board)[22][10]) override;
    virtual void RemoveGhostPiece(char (&board)[22][10]) override;
    virtual void CheckIfRotatableR(char (&board)[22][10]) override;
    virtual void CheckIfRotatableL(char (&board)[22][10]) override;
    virtual bool CheckPositionIsFinal(char (&board)[22][10]) override;
    virtual bool CheckPositionIsFinal(char (&board)[22][10], int y) override;

    virtual int CheckSideFree(char (&board)[22][10], int side) override;
};