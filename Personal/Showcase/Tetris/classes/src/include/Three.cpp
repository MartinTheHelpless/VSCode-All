#include "Three.h"

Three::Three(char (&shape)[3][3], int x, int y) : Block(x, y)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m_Shape[i][j] = shape[i][j];
}

void Three::DeleteFromBoard(char (&board)[22][10])
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            board[i + m_Y][j + m_X] = '.';
}

void Three::DrawOnBoard(char (&board)[22][10])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_Shape[i][j] != '.' && i + m_X >= 0)
                board[i + m_Y][j + m_X] = m_Shape[i][j];
}

int Three::CheckSideFree(char (&board)[22][10], int side)
{
    if (side > 0)
        side = 2;
    else
        side = 0;

    bool freeSide = true;

    for (int i = 0; i < 3; i++)
        if (m_Shape[i][side] != '.')
        {
            freeSide = false;
            break;
        }

    if (freeSide)
    {
        if (side > 0)
            return 10 - 2;
        else
            return -1;
    }
    else
    {
        if (side > 0)
            return 10 - 3;
        else
            return 0;
    }
}

void Three::DrawGhostPiece(char (&board)[22][10])
{
    int y = m_Y;

    while (!CheckPositionIsFinal(board))
        y++;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_Shape[i][j] != '.')
                board[i + y][j + m_X] = 'e';
}

void Three::RemoveGhostPiece(char (&board)[22][10])
{
    int y = m_Y;

    while (!CheckPositionIsFinal(board))
        y++;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_Shape[i][j] != '.' && i + y >= 0)
                board[i + y][j + m_X] = '.';
}

bool Three::CheckPositionIsFinal(char (&board)[22][10])
{
    bool stop = false;

    for (int i = 0; i < 3 && !stop; i++)
        for (int j = 0; j < 3; j++)
            if (m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != 'e' && board[i + m_Y][j + m_X] != '.' || i + m_Y > 22)
            {
                stop = true;
                break;
            }

    return stop;
}

void Three::CheckIfRotatableR(char (&board)[22][10])
{
    int rotatedMat[3][3];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            rotatedMat[j][2 - i] = m_Shape[i][j];

    bool rotatable = true;

    for (int i = 0; i < 3 && rotatable; i++)
        for (int j = 0; j < 3 && rotatable; j++)
            if (rotatedMat[i][j] != '.' && board[i + m_X][j + m_Y] != '.' && j + m_X < 10)
                rotatable = false;

    if (rotatable)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                m_Shape[i][j] = rotatedMat[i][j];
}

void Three::CheckIfRotatableL(char (&board)[22][10])
{
    int rotatedMat[3][3];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            rotatedMat[2 - j][i] = m_Shape[i][j];

    bool rotatable = true;

    for (int i = 0; i < 3 && rotatable; i++)
        for (int j = 0; j < 3 && rotatable; j++)
            if (rotatedMat[i][j] != '.' && board[i + m_X][j + m_Y] != '.' && j + m_X < 10)
                rotatable = false;

    if (rotatable)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                m_Shape[i][j] = rotatedMat[i][j];
}
