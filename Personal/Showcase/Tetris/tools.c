#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int WINDOW_WIDTH = 420; // 14 : 24
const int WINDOW_HEIGHT = 720;

const int BLOCK_SIZE = WINDOW_WIDTH / 14;

const int BORDER_MARGIN = WINDOW_WIDTH / 28;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 22;

char board[22][10] = {
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};

const char line[4][4][4] = {{{'.', 'c', '.', '.'},
                             {'.', 'c', '.', '.'},
                             {'.', 'c', '.', '.'},
                             {'.', 'c', '.', '.'}},
                            {{'.', '.', '.', '.'},
                             {'.', '.', '.', '.'},
                             {'c', 'c', 'c', 'c'},
                             {'.', '.', '.', '.'}},
                            {{'.', '.', 'c', '.'},
                             {'.', '.', 'c', '.'},
                             {'.', '.', 'c', '.'},
                             {'.', '.', 'c', '.'}},
                            {{'.', '.', '.', '.'},
                             {'c', 'c', 'c', 'c'},
                             {'.', '.', '.', '.'},
                             {'.', '.', '.', '.'}}};

const char blocks[2][2] = {{'y', 'y'},
                           {'y', 'y'}};

const char lSquig[4][3][3] = {{{'r', 'r', '.'},
                               {'.', 'r', 'r'},
                               {'.', '.', '.'}},
                              {{'.', '.', 'r'},
                               {'.', 'r', 'r'},
                               {'.', 'r', '.'}},
                              {{'.', '.', '.'},
                               {'r', 'r', '.'},
                               {'.', 'r', 'r'}},
                              {{'.', 'r', '.'},
                               {'r', 'r', '.'},
                               {'r', '.', '.'}}};

const char rSquig[4][3][3] = {{{'.', 'g', 'g'},
                               {'g', 'g', '.'},
                               {'.', '.', '.'}},
                              {{'.', 'g', '.'},
                               {'.', 'g', 'g'},
                               {'.', '.', 'g'}},
                              {{'.', '.', '.'},
                               {'.', 'g', 'g'},
                               {'g', 'g', '.'}},
                              {{'g', '.', '.'},
                               {'g', 'g', '.'},
                               {'.', 'g', '.'}}};

const char tBlock[4][3][3] = {{{'.', 'p', '.'},
                               {'p', 'p', 'p'},
                               {'.', '.', '.'}},
                              {{'.', 'p', '.'},
                               {'.', 'p', 'p'},
                               {'.', 'p', '.'}},
                              {{'.', '.', '.'},
                               {'p', 'p', 'p'},
                               {'.', 'p', '.'}},
                              {{'.', 'p', '.'},
                               {'p', 'p', '.'},
                               {'.', 'p', '.'}}};

const char rLblock[4][3][3] = {{{'.', 'o', '.'},
                                {'.', 'o', '.'},
                                {'.', 'o', 'o'}},
                               {{'.', '.', '.'},
                                {'o', 'o', 'o'},
                                {'o', '.', '.'}},
                               {{'o', 'o', '.'},
                                {'.', 'o', '.'},
                                {'.', 'o', '.'}},
                               {{'.', '.', 'o'},
                                {'o', 'o', 'o'},
                                {'.', '.', '.'}}};

const char lLblock[4][3][3] = {{{'.', 'b', '.'},
                                {'.', 'b', '.'},
                                {'b', 'b', '.'}},
                               {{'b', '.', '.'},
                                {'b', 'b', 'b'},
                                {'.', '.', '.'}},
                               {{'.', 'b', 'b'},
                                {'.', 'b', '.'},
                                {'.', 'b', '.'}},
                               {{'.', '.', '.'},
                                {'b', 'b', 'b'},
                                {'.', '.', 'b'}}};

void deleteThreeFromBoard(const char three[3][3], int shiftX, int shiftY)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (three[i][j] != '.')
                board[i + shiftY][j + shiftX] = '.';
}

void deleteLineFromBoard(const char line[4][4], int shiftX, int shiftY)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (line[i][j] != '.')
                board[i + shiftY][j + shiftX] = '.';
}

void deleteSquareFromBoard(int shiftX, int shiftY)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            board[i + shiftY][j + shiftX] = '.';
}

void drawThreeOnBoard(const char three[3][3], int shiftX, int shiftY)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (three[i][j] != '.' && i + shiftY >= 0)
                board[i + shiftY][j + shiftX] = three[i][j];
}

void drawLineOnBoard(const char line[4][4], int shiftX, int shiftY)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (line[i][j] != '.')
                board[i + shiftY][j + shiftX] = line[i][j];
}

void drawSqareOnBoard(int shiftX, int shiftY)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            board[i + shiftY][j + shiftX] = 'y';
}

void drawBoard(SDL_Renderer *rend, int x, int y)
{

    int r, g, b;

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (board[i][j])
            {
            case 'r': // Red
                r = 171, g = 12, b = 36;
                break;

            case 'g': // Green
                r = 43, g = 179, b = 16;
                break;

            case 'p': // Purple
                r = 86, g = 8, b = 138;
                break;

            case 'o': // Orange
                r = 224, g = 123, b = 7;
                break;

            case 'b': // Blue
                r = 6, g = 64, b = 150;
                break;

            case 'y': // Yellow
                r = 191, g = 177, b = 21;
                break;

            case 'c': // Cyan
                r = 8, g = 138, b = 118;
                break;

            case 'e': // Grey
                r = 150, g = 150, b = 150;
                break;

            default:
                r = 0, g = 0, b = 0;
                break;
            }

            SDL_SetRenderDrawColor(rend, r, g, b, 0);
            SDL_Rect rect = {x + j * BLOCK_SIZE, y + i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
            SDL_RenderFillRect(rend, &rect);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
            SDL_RenderDrawRect(rend, &rect);
        }
    }
}

void drawNextBlockWindow(SDL_Renderer *rend, int nextBlock)
{

    int r, g, b;

    if (nextBlock == 0)
    {
        r = 171, g = 12, b = 36;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (lSquig[0][i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 1.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                    SDL_RenderDrawRect(rend, &tmp);
                }
            }
        }
    }
    else if (nextBlock == 1)
    {

        r = 43, g = 179, b = 16;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (rSquig[0][i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 1.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                    SDL_RenderDrawRect(rend, &tmp);
                }
            }
        }
    }
    else if (nextBlock == 2)
    {

        r = 86, g = 8, b = 138;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (tBlock[0][i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 1.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                    SDL_RenderDrawRect(rend, &tmp);
                }
            }
        }
    }
    else if (nextBlock == 3)
    {
        r = 171, g = 12, b = 36;
        r = 86, g = 8, b = 138;
        r = 224, g = 123, b = 7;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (rLblock[0][i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 1.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                    SDL_RenderDrawRect(rend, &tmp);
                }
            }
        }
    }
    else if (nextBlock == 4)
    {
        r = 6, g = 64, b = 150;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (lLblock[0][i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 1.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                    SDL_RenderDrawRect(rend, &tmp);
                }
            }
        }
    }
    else if (nextBlock == 5)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                SDL_SetRenderDrawColor(rend, 191, 177, 21, 0);
                SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - 0.25 * BLOCK_SIZE) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 1.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                SDL_RenderFillRect(rend, &tmp);
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                SDL_RenderDrawRect(rend, &tmp);
            }
        }
    }
    else if (nextBlock == 6)
    {
        for (int i = 0; i < 4; i++)
        {
            SDL_SetRenderDrawColor(rend, 8, 138, 118, 0);
            SDL_Rect tmp = {WINDOW_WIDTH - BORDER_MARGIN - 2.5 * BLOCK_SIZE + 2 * BLOCK_SIZE / 2, 1 + BLOCK_SIZE + BORDER_MARGIN + (i + 0.5) * BLOCK_SIZE / 2, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
            SDL_RenderFillRect(rend, &tmp);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            SDL_RenderDrawRect(rend, &tmp);
        }
    }
}

void drawThreeGhostPiece(const char three[3][3], int shiftX, int shiftY)
{

    while (!threesPositionIsFinal(three, shiftX, shiftY + 1))
        shiftY++;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (three[i][j] != '.')
                board[i + shiftY][j + shiftX] = 'e';
}

void drawSquareGhostPiece(int shiftX, int shiftY)
{
    while (!squarePositionIsFinal(shiftX, shiftY + 1))
        shiftY++;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            board[i + shiftY][j + shiftX] = 'e';
}

void drawLineGhostPiece(const char line[4][4], int shiftX, int shiftY)
{
    while (!linePositionIsFinal(line, shiftX, shiftY + 1))
        shiftY++;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (line[i][j] != '.')
                board[i + shiftY][j + shiftX] = 'e';
}

void removeThreeGhostPiece(const char three[3][3], int shiftX, int shiftY)
{

    while (!threesPositionIsFinal(three, shiftX, shiftY + 1))
        shiftY++;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (three[i][j] != '.' && i + shiftY >= 0)
                board[i + shiftY][j + shiftX] = '.';
}

void removeSquareGhostPiece(int shiftX, int shiftY)
{

    while (!squarePositionIsFinal(shiftX, shiftY + 1))
        shiftY++;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            board[i + shiftY][j + shiftX] = '.';
}

void removeLineGhostPiece(const char line[4][4], int shiftX, int shiftY)
{

    while (!linePositionIsFinal(line, shiftX, shiftY + 1))
        shiftY++;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (line[i][j] != '.')
                board[i + shiftY][j + shiftX] = '.';
}

int checkThreeSideFree(const char three[3][3], int side)
{

    if (side > 0)
        side = 2;
    else
        side = 0;

    bool freeSide = true;

    for (int i = 0; i < 3; i++)
        if (three[i][side] != '.')
        {
            freeSide = false;
            break;
        }

    if (freeSide)
    {
        if (side > 0)
            return BOARD_WIDTH - 2;
        else
            return -1;
    }
    else
    {
        if (side > 0)
            return BOARD_WIDTH - 3;
        else
            return 0;
    }
}

int checkLineSideFree(const char line[4][4], int side)
{

    if (side > 0)
        side = 2;
    else
        side = 1;

    bool freeSide = true;

    for (int i = 0; i < 4; i++)
        if (line[i][side] != '.')
        {
            freeSide = false;
            break;
        }

    if (freeSide)
    {
        if (side > 1)
            return BOARD_WIDTH - side;
        else
            return -2;
    }
    else
    {
        if (side > 1)
            return BOARD_WIDTH - 3;
        else
            return -1;
    }
}

bool threesPositionIsFinal(const char three[3][3], int shiftX, int shiftY)
{

    bool stop = false;

    for (int i = 0; i < 3 && !stop; i++)
        for (int j = 0; j < 3; j++)
            if (three[i][j] != '.' && board[i + shiftY][j + shiftX] != 'e' && board[i + shiftY][j + shiftX] != '.' || i + shiftY > BOARD_HEIGHT)
            {
                stop = true;
                break;
            }

    return stop;
}

bool squarePositionIsFinal(int shiftX, int shiftY)
{
    bool stop = false;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (board[i + shiftY][j + shiftX] != '.' && board[i + shiftY][j + shiftX] != 'e' || i + shiftY > BOARD_HEIGHT)
            {
                stop = true;
                break;
            }

    return stop;
}

bool linePositionIsFinal(const char line[4][4], int shiftX, int shiftY)
{
    bool stop = false;

    for (int i = 0; i < 4 && !stop; i++)
        for (int j = 0; j < 4; j++)
            if (line[i][j] != '.' && board[i + shiftY][j + shiftX] != 'e' && board[i + shiftY][j + shiftX] != '.' || i + shiftY > BOARD_HEIGHT)
            {
                stop = true;
                break;
            }

    return stop;
}

bool isThreeRotatable(const char three[3][3], int shiftX, int shiftY)
{

    bool rotatable = true;

    for (int i = 0; i < 3 && rotatable; i++)
        for (int j = 0; j < 3 && rotatable; j++)
            if (three[i][j] != '.' && board[i + shiftY][j + shiftX] != '.' && j + shiftX < BOARD_WIDTH)
                rotatable = false;

    return rotatable;
}

bool isLineRotatable(const char line[4][4], int shiftX, int shiftY)
{
    bool rotatable = true;

    for (int i = 0; i < 4 && rotatable; i++)
        for (int j = 0; j < 4 && rotatable; j++)
            if (line[i][j] != '.' && board[i + shiftY][j + shiftX] != '.' && j + shiftX < BOARD_WIDTH)
                rotatable = false;

    return rotatable;
}
