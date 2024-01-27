#include "Block.h"

class Square : public Block
{
private:
    char m_Shape[2][2];

public:
    Square(char shape[2][2], int x, int y);

    virtual void DrawOnBoard(char (&board)[22][10]) override;
    virtual void DrawGhostPiece(char (&board)[22][10]) override;
    virtual void DeleteFromBoard(char (&board)[22][10]) override;
    virtual void RemoveGhostPiece(char (&board)[22][10]) override;
    virtual void CheckIfRotatableR(char (&board)[22][10]) override;
    virtual void CheckIfRotatableL(char (&board)[22][10]) override;
    virtual bool CheckPositionIsFinal(char (&board)[22][10]) override;
    virtual int CheckSideFree(char (&board)[22][10], int side) override;
};