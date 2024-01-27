#include "../include/Line.h"

Line::Line(const char (&shape)[4][4], int x, int y) : Block(x, y)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m_Shape[i][j] = shape[i][j];
}

void Line::DeleteFromBoard(char (&board)[22][10])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (m_Shape[i][j] != '.')
                board[i + m_Y][j + m_X] = '.';
}

void Line::DrawOnBoard(char (&board)[22][10])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (m_Shape[i][j] != '.')
                board[i + m_Y][j + m_X] = m_Shape[i][j];
}

int Line::CheckSideFree(char (&board)[22][10], int side)
{
    if (side > 0)
        side = 2;
    else
        side = 1;

    bool freeSide = true;

    for (int i = 0; i < 4; i++)
        if (m_Shape[i][side] != '.')
        {
            freeSide = false;
            break;
        }

    if (freeSide)
    {
        if (side > 1)
            return 10 - side;
        else
            return -2;
    }
    else
    {
        if (side > 1)
            return 10 - 3;
        else
            return -1;
    }
}

void Line::DrawGhostPiece(char (&board)[22][10])
{
    int y = m_Y;

    while (!CheckPositionIsFinal(board, y + 1))
        y++;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (m_Shape[i][j] != '.')
                board[i + y][j + m_X] = 'e';
}

void Line::RemoveGhostPiece(char (&board)[22][10])
{
    int y = m_Y;

    while (!CheckPositionIsFinal(board, y + 1))
        y++;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (m_Shape[i][j] != '.')
                board[i + y][j + m_X] = '.';
}

void Line::CheckIfRotatableR(char (&board)[22][10])
{
    int rotatedMat[4][4];

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            rotatedMat[j][3 - i] = m_Shape[i][j];

    bool rotatable = true;

    for (int i = 0; i < 4 && rotatable; i++)
        for (int j = 0; j < 4 && rotatable; j++)
            if (m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != '.' && j + m_X < 10)
                rotatable = false;
}

void Line::CheckIfRotatableL(char (&board)[22][10])
{
    int rotatedMat[4][4];

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            rotatedMat[3 - j][i] = m_Shape[i][j];

    bool rotatable = true;

    for (int i = 0; i < 4 && rotatable; i++)
        for (int j = 0; j < 4 && rotatable; j++)
            if (m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != '.' && j + m_X < 10)
                rotatable = false;

    if (rotatable)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m_Shape[i][j] = rotatedMat[i][j];
    }
}

bool Line::CheckPositionIsFinal(char (&board)[22][10])
{
    bool stop = false;

    for (int i = 0; i < 4 && !stop; i++)
        for (int j = 0; j < 4 && !stop; j++)
            if (m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != 'e' && board[i + m_Y][j + m_X] != '.' || i + m_Y > 22)
                stop = true;

    return stop;
}

bool Line::CheckPositionIsFinal(char (&board)[22][10], int y)
{
    bool stop = false;

    for (int i = 0; i < 4 && !stop; i++)
        for (int j = 0; j < 4 && !stop; j++)
            if (m_Shape[i][j] != '.' && board[i + y][j + m_X] != 'e' && board[i + y][j + m_X] != '.' || i + y > 22)
                stop = true;

    return stop;
}
