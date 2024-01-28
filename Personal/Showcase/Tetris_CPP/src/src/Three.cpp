#include "../include/Three.h"
#include <iostream>

Three::Three(const char (&shape)[3][3], int x, int y) : Block(x, y)
{

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m_Shape[i][j] = shape[i][j];
}

void Three::DeleteFromBoard(char (&board)[22][10])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_Shape[i][j] != '.')
                board[i + m_Y][j + m_X] = '.';
}

void Three::DrawOnBoard(char (&board)[22][10])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_Shape[i][j] != '.')
                board[i + m_Y][j + m_X] = m_Shape[i][j];
}

int Three::CheckSideFree(char (&board)[22][10], int side)
{
    if (side > 0)
        side = 2;
    else
        side = 0;

    bool freeSide = true;

    for (int i = 0; i < 3 && freeSide; i++)
        if (m_Shape[i][side] != '.')
            freeSide = false;

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

    while (!CheckPositionIsFinal(board, y + 1))
        y++;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_Shape[i][j] != '.')
                board[i + y][j + m_X] = 'e';
}

void Three::RemoveGhostPiece(char (&board)[22][10])
{
    int y = m_Y;

    while (!CheckPositionIsFinal(board, y + 1))
        y++;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_Shape[i][j] != '.' && i + y >= 0)
                board[i + y][j + m_X] = '.';
}

bool Three::CheckPositionIsFinal(char (&board)[22][10])
{
    bool final = false;

    for (int i = 2; i >= 0 && !final; i--)
        for (int j = 0; j < 3 && !final; j++)
            if (m_Shape[i][j] != '.' && i + m_Y > 21 || m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != '.' && board[i + m_Y][j + m_X] != 'e')
                final = true;

    return final;
}

bool Three::CheckPositionIsFinal(char (&board)[22][10], int y)
{
    bool final = false;

    for (int i = 2; i >= 0 && !final; i--)
        for (int j = 0; j < 3 && !final; j++)
            if (m_Shape[i][j] != '.' && i + y > 21 || m_Shape[i][j] != '.' && board[i + y][j + m_X] != '.' && board[i + y][j + m_X] != 'e')
                final = true;

    return final;
}

void Three::CheckIfRotatableR(char (&board)[22][10])
{
    char storeMat[3][3];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            storeMat[i][j] = m_Shape[i][j];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m_Shape[2 - j][i] = storeMat[i][j];

    bool rotatable = true;

    int minX = CheckSideFree(board, 0);
    int maxX = CheckSideFree(board, 1);

    if (GetX() > maxX)
    {
        for (int i = 0; i < 3 && rotatable; i++)
            for (int j = 0; j < 3 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + maxX] != '.' && board[i + m_Y][j + maxX] != 'e')
                    rotatable = false;

        if (rotatable)
            SetX(maxX);
    }
    else if (GetX() < minX)
    {
        for (int i = 0; i < 3 && rotatable; i++)
            for (int j = 0; j < 3 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + minX] != '.' && board[i + m_Y][j + minX] != 'e')
                    rotatable = false;

        if (rotatable)
            SetX(minX);
    }
    else
    {
        for (int i = 0; i < 3 && rotatable; i++)
            for (int j = 0; j < 3 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != '.' && board[i + m_Y][j + m_X] != 'e')
                    rotatable = false;
    }

    if (!rotatable)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                m_Shape[i][j] = storeMat[i][j];
    }
}

void Three::CheckIfRotatableL(char (&board)[22][10])
{

    char storeMat[3][3];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            storeMat[i][j] = m_Shape[i][j];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m_Shape[j][2 - i] = storeMat[i][j];

    bool rotatable = true;

    int minX = CheckSideFree(board, 0);
    int maxX = CheckSideFree(board, 1);

    if (GetX() > maxX)
    {
        for (int i = 0; i < 3 && rotatable; i++)
            for (int j = 0; j < 3 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + maxX] != '.' && board[i + m_Y][j + maxX] != 'e')
                    rotatable = false;

        if (rotatable)
            SetX(maxX);
    }
    else if (GetX() < minX)
    {
        for (int i = 0; i < 3 && rotatable; i++)
            for (int j = 0; j < 3 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + minX] != '.' && board[i + m_Y][j + minX] != 'e')
                    rotatable = false;

        if (rotatable)
            SetX(minX);
    }
    else
    {
        for (int i = 0; i < 3 && rotatable; i++)
            for (int j = 0; j < 3 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != '.' && board[i + m_Y][j + m_X] != 'e')
                    rotatable = false;
    }

    if (!rotatable)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                m_Shape[i][j] = storeMat[i][j];
    }
}
