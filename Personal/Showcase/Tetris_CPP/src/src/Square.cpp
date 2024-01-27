#include "../include/Square.h"

Square::Square(const char (&shape)[2][2], int x, int y) : Block(x, y)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            m_Shape[i][j] = shape[i][j];
}

void Square::DrawOnBoard(char (&board)[22][10])
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            board[i + m_Y][j + m_X] = 'y';
}

void Square::DrawGhostPiece(char (&board)[22][10])
{
    int y = m_Y;

    while (!CheckPositionIsFinal(board, y + 1))
        y++;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            board[i + y][j + m_X] = 'e';
}

void Square::DeleteFromBoard(char (&board)[22][10])
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            board[i + m_Y][j + m_X] = '.';
}

void Square::RemoveGhostPiece(char (&board)[22][10])
{
    int y = m_Y;

    while (!CheckPositionIsFinal(board, y + 1))
        y++;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (m_Shape[i][j] != '.' && i + y >= 0)
                board[i + y][j + m_X] = '.';
}

void Square::CheckIfRotatableR(char (&board)[22][10])
{
}

void Square::CheckIfRotatableL(char (&board)[22][10])
{
}

bool Square::CheckPositionIsFinal(char (&board)[22][10])
{

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (board[i + m_Y][j + m_X] != '.' && board[i + m_Y][j + m_X] != 'e' || m_Y + 1 > 21)
                return true;

    return false;
}
bool Square::CheckPositionIsFinal(char (&board)[22][10], int y)
{

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (board[i + y][j + m_X] != '.' && board[i + y][j + m_X] != 'e' || y + 1 > 21)
                return true;

    return false;
}

int Square::CheckSideFree(char (&board)[22][10], int side)
{

    if (side == 0)
        return 0;
    else
        return 10 - 2;
}
