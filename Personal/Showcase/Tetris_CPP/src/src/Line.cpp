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
    {

        for (int i = 0; i < 4; i++)
            if (m_Shape[i][3] != '.')
                return 10 - 4;

        for (int i = 0; i < 4; i++)
            if (m_Shape[i][2] != '.')
                return 10 - 3;

        return 10 - 2;
    }
    else
    {
        for (int i = 0; i < 4; i++)
            if (m_Shape[i][0] != '.')
                return 0;

        for (int i = 0; i < 4; i++)
            if (m_Shape[i][1] != '.')
                return -1;

        return -2;
    }
    return 0;
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
    int storeMat[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            storeMat[i][j] = m_Shape[i][j];

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m_Shape[i][j] = storeMat[j][3 - i];

    bool rotatable = true;

    int minX = CheckSideFree(board, 0);
    int maxX = CheckSideFree(board, 1);

    if (GetX() > maxX)
    {
        for (int i = 0; i < 4 && rotatable; i++)
            for (int j = 0; j < 4 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + maxX] != '.' && board[i + m_Y][j + maxX] != 'e' && j + maxX < 10)
                    rotatable = false;

        if (rotatable)
            SetX(maxX);
    }
    else if (GetX() < minX)
    {
        for (int i = 0; i < 4 && rotatable; i++)
            for (int j = 0; j < 4 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + minX] != '.' && board[i + m_Y][j + minX] != 'e' && j + minX < 10)
                    rotatable = false;

        if (rotatable)
            SetX(minX);
    }
    else
    {
        for (int i = 0; i < 4 && rotatable; i++)
            for (int j = 0; j < 4 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != '.' && board[i + m_Y][j + m_X] != 'e' && j + m_X < 10)
                    rotatable = false;
    }

    if (!rotatable)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m_Shape[i][j] = storeMat[i][j];
    }
}

void Line::CheckIfRotatableL(char (&board)[22][10])
{
    int storeMat[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            storeMat[i][j] = m_Shape[i][j];

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m_Shape[i][j] = storeMat[3 - j][i];

    bool rotatable = true;

    int minX = CheckSideFree(board, 0);
    int maxX = CheckSideFree(board, 1);

    if (GetX() > maxX)
    {
        for (int i = 0; i < 4 && rotatable; i++)
            for (int j = 0; j < 4 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + maxX] != '.' && board[i + m_Y][j + maxX] != 'e' && j + maxX < 10)
                    rotatable = false;

        if (rotatable)
            SetX(maxX);
    }
    else if (GetX() < minX)
    {
        for (int i = 0; i < 4 && rotatable; i++)
            for (int j = 0; j < 4 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + minX] != '.' && board[i + m_Y][j + minX] != 'e' && j + minX < 10)
                    rotatable = false;

        if (rotatable)
            SetX(minX);
    }
    else
    {
        for (int i = 0; i < 4 && rotatable; i++)
            for (int j = 0; j < 4 && rotatable; j++)
                if (m_Shape[i][j] != '.' && board[i + m_Y][j + m_X] != '.' && board[i + m_Y][j + m_X] != 'e' && j + m_X < 10)
                    rotatable = false;
    }

    if (!rotatable)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m_Shape[i][j] = storeMat[i][j];
    }
}

bool Line::CheckPositionIsFinal(char (&board)[22][10])
{
    bool stop = false;

    for (int i = 0; i < 4 && !stop; i++)
        for (int j = 0; j < 4 && !stop; j++)
            if (m_Shape[i][j] != '.' && (i + m_Y >= 22 || board[i + m_Y][j + m_X] != 'e' && board[i + m_Y][j + m_X] != '.'))
                stop = true;

    return stop;
}

bool Line::CheckPositionIsFinal(char (&board)[22][10], int y)
{
    bool stop = false;

    for (int i = 0; i < 4 && !stop; i++)
        for (int j = 0; j < 4 && !stop; j++)
            if (m_Shape[i][j] != '.' && (i + y >= 22 || board[i + y][j + m_X] != 'e' && board[i + y][j + m_X] != '.'))
                stop = true;

    return stop;
}