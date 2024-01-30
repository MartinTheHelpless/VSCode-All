#include <stdbool.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "src/include/Three.h"
#include "src/include/Line.h"
#include "src/include/Square.h"

#ifdef main
#undef main
#endif

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int WINDOW_WIDTH = 420; // 14 : 24
const int WINDOW_HEIGHT = 720;

const int BLOCK_SIZE = WINDOW_WIDTH / 14;

const int BORDER_MARGIN = WINDOW_WIDTH / 28;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 22;

const int BASE_X = 4;
const int BASE_Y = 0;

// ------------------------------------------------------------------------------------------------------
// ------------------------------------- SHAPE AND BOARD DEFINITION -------------------------------------
// ------------------------------------------------------------------------------------------------------
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
const char lSquig[3][3] = {{'r', 'r', '.'},
                           {'.', 'r', 'r'},
                           {'.', '.', '.'}};
const char rSquig[3][3] = {{'.', 'g', 'g'},
                           {'g', 'g', '.'},
                           {'.', '.', '.'}};
const char tBlock[3][3] = {{'.', 'p', '.'},
                           {'p', 'p', 'p'},
                           {'.', '.', '.'}};
const char rLblock[3][3] = {{'.', 'o', '.'},
                            {'.', 'o', '.'},
                            {'.', 'o', 'o'}};
const char lLblock[3][3] = {{'.', 'b', '.'},
                            {'.', 'b', '.'},
                            {'b', 'b', '.'}};
const char line[4][4] = {{'.', 'c', '.', '.'},
                         {'.', 'c', '.', '.'},
                         {'.', 'c', '.', '.'},
                         {'.', 'c', '.', '.'}};
const char square[2][2] = {{'y', 'y'},
                           {'y', 'y'}};
// ------------------------------------------------------------------------------------------------------
// ---------------------------------- END OF SHAPE AND BOARD DEFINITION ---------------------------------
// ------------------------------------------------------------------------------------------------------

void drawBoard(SDL_Renderer *rend, int x, int y);

void drawNextBlockWindow(SDL_Renderer *rend, int nextBlock);

Block *GetRandomBlock(int &type);

int CheckForFullRows();

bool endGame(int &type);

int main(int argc, char const *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window)
    {
        SDL_Log("Unable to initialize SDL Window\n");
        return 1;
    }

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!rend)
    {
        SDL_Log("Unable to initialize SDL Renderer \n");
        SDL_DestroyWindow(window);
        return 1;
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Font could not be loaded.");
        return 1;
    }

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);

    TTF_Font *font = TTF_OpenFont("src/Aller_Rg.ttf", 30);

    SDL_Color fontColor = {255, 255, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Score: ", fontColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
    SDL_free(textSurface);

    SDL_Surface *tmp;
    SDL_Texture *scoreRes;

    SDL_Rect scoreText = {WINDOW_WIDTH / 2 - BLOCK_SIZE * 4, BORDER_MARGIN / 2, BLOCK_SIZE * 4, BLOCK_SIZE};
    SDL_Rect scRect = {WINDOW_WIDTH / 2, BORDER_MARGIN / 2, BLOCK_SIZE * 2, BLOCK_SIZE};
    SDL_Rect border = {BORDER_MARGIN, BORDER_MARGIN + BLOCK_SIZE, BLOCK_SIZE * BOARD_WIDTH + 2, BLOCK_SIZE * BOARD_HEIGHT + 2};
    SDL_Rect next = {WINDOW_WIDTH - BORDER_MARGIN - int(BLOCK_SIZE / 0.4), BORDER_MARGIN + BLOCK_SIZE, int(BLOCK_SIZE * 2.5), int(BLOCK_SIZE * 2.5)};

    Uint32 frameStart, frameTime, lastDrop = 0, dropDelay = 1000;

    bool quit = false;
    SDL_Event event;

    int nextBlock = rand() % 7, score = 0;

    Block *current = GetRandomBlock(nextBlock);

    // ------------------------------------------------------------------------------------------
    // ---------------------------- GAME LOOP ---------------------------------------------------
    // ------------------------------------------------------------------------------------------

    while (!quit)
    {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        char value[6];
        sprintf(value, "%d", score);

        tmp = TTF_RenderText_Solid(font, value, fontColor);
        scoreRes = SDL_CreateTextureFromSurface(rend, tmp);

        SDL_RenderCopy(rend, scoreRes, NULL, &scRect);
        SDL_RenderCopy(rend, textTexture, NULL, &scoreText);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(rend, &border);
        SDL_RenderDrawRect(rend, &next);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                {

                    int minX = current->CheckSideFree(board, 0);

                    current->DeleteFromBoard(board);
                    current->RemoveGhostPiece(board);

                    current->DecrementX();

                    if (current->GetX() < minX)
                        current->SetX(minX);

                    if (current->CheckPositionIsFinal(board))
                        current->IncrementX();

                    break;
                }

                case SDLK_d:
                {
                    int maxX = current->CheckSideFree(board, 1);

                    current->DeleteFromBoard(board);
                    current->RemoveGhostPiece(board);

                    current->IncrementX();

                    if (current->GetX() > maxX)
                        current->SetX(maxX);

                    if (current->CheckPositionIsFinal(board))
                        current->DecrementX();

                    break;
                }

                case SDLK_q:
                {

                    current->DeleteFromBoard(board);
                    current->RemoveGhostPiece(board);

                    current->CheckIfRotatableL(board);

                    break;
                }

                case SDLK_e:
                {
                    current->DeleteFromBoard(board);
                    current->RemoveGhostPiece(board);

                    current->CheckIfRotatableR(board);

                    break;
                }

                case SDLK_s:
                {
                    lastDrop = SDL_GetTicks();

                    current->DeleteFromBoard(board);

                    current->IncrementY();

                    if (current->CheckPositionIsFinal(board))
                    {
                        score += 35;

                        current->DecrementY();
                        quit = endGame(nextBlock);
                        current->DrawOnBoard(board);
                        current = GetRandomBlock(nextBlock);
                        int fullRows = CheckForFullRows();
                        score += 165 * fullRows;
                        dropDelay -= 20 * fullRows;
                        if (dropDelay < 200)
                            dropDelay = 200;
                    }
                    break;
                }

                case SDLK_SPACE:
                {
                    score += 35;

                    current->DeleteFromBoard(board);
                    current->RemoveGhostPiece(board);

                    while (!current->CheckPositionIsFinal(board, current->GetY() + 1))
                        current->IncrementY();

                    quit = endGame(nextBlock);
                    current->DrawOnBoard(board);
                    current = GetRandomBlock(nextBlock);
                    int fullRows = CheckForFullRows();
                    score += 165 * fullRows;
                    dropDelay -= 20 * fullRows;
                    if (dropDelay < 200)
                        dropDelay = 200;

                    break;
                }
                default:
                    break;
                }

                break;

            default:
                break;
            }
        }

        current->DrawGhostPiece(board);
        current->DrawOnBoard(board);

        drawBoard(rend, BORDER_MARGIN + 1, BORDER_MARGIN + 1 + BLOCK_SIZE);

        drawNextBlockWindow(rend, nextBlock);

        SDL_RenderPresent(rend);

        SDL_FreeSurface(tmp);
        SDL_DestroyTexture(scoreRes);

        if (SDL_GetTicks() > lastDrop + dropDelay)
        {
            lastDrop = SDL_GetTicks();

            current->DeleteFromBoard(board);

            current->IncrementY();

            if (current->CheckPositionIsFinal(board))
            {
                current->DecrementY();
                current->DrawOnBoard(board);
                quit = endGame(nextBlock);
                current = GetRandomBlock(nextBlock);
                int fullRows = CheckForFullRows();
                score += 165 * fullRows;
                dropDelay -= 20 * fullRows;
                if (dropDelay < 200)
                    dropDelay = 200;
            }
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
    }

    // ------------------------------------------------------------------------------------------
    // ---------------------------- END OF GAME LOOP --------------------------------------------
    // ------------------------------------------------------------------------------------------

    std::cout << "Game Over !\nYour score is: " << score << std::endl;

    SDL_Quit();
    SDL_DestroyTexture(textTexture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);

    return 0;
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

            SDL_SetRenderDrawColor(rend, r, g, b, 255);
            SDL_Rect rect = {x + j * BLOCK_SIZE, y + i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
            SDL_RenderFillRect(rend, &rect);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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
                if (lSquig[i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 255);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - int(BLOCK_SIZE * 0.5)) + 1 + (j - 3) * int(BLOCK_SIZE * 0.5), 1 + (i + 0.5) * int(BLOCK_SIZE * 0.5) + BORDER_MARGIN + int(BLOCK_SIZE * 1.5), int(BLOCK_SIZE * 0.5), int(BLOCK_SIZE * 0.5)};
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
                if (rSquig[i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 255);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - int(BLOCK_SIZE * 0.5)) + 1 + (j - 3) * int(BLOCK_SIZE * 0.5), 1 + (i + 0.5) * int(BLOCK_SIZE * 0.5) + BORDER_MARGIN + int(BLOCK_SIZE * 1.5), int(BLOCK_SIZE * 0.5), int(BLOCK_SIZE * 0.5)};
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
                if (tBlock[i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 255);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - int(BLOCK_SIZE * 0.5)) + 1 + (j - 3) * int(BLOCK_SIZE * 0.5), 1 + (i + 0.5) * int(BLOCK_SIZE * 0.5) + BORDER_MARGIN + int(BLOCK_SIZE * 1.5), int(BLOCK_SIZE * 0.5), int(BLOCK_SIZE * 0.5)};
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
                if (rLblock[i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 255);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - int(BLOCK_SIZE * 0.5)) + 1 + (j - 3) * int(BLOCK_SIZE * 0.5), 1 + (i + 0.5) * int(BLOCK_SIZE * 0.5) + BORDER_MARGIN + int(BLOCK_SIZE * 1.5), int(BLOCK_SIZE * 0.5), int(BLOCK_SIZE * 0.5)};
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
                if (lLblock[i][j] != '.')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 255);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - int(BLOCK_SIZE * 0.5)) + 1 + (j - 3) * int(BLOCK_SIZE * 0.5), 1 + (i + 0.5) * int(BLOCK_SIZE * 0.5) + BORDER_MARGIN + int(BLOCK_SIZE * 1.5), int(BLOCK_SIZE * 0.5), int(BLOCK_SIZE * 0.5)};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
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
                SDL_SetRenderDrawColor(rend, 191, 177, 21, 255);
                SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE / 4) + 1 + (j - 3) * BLOCK_SIZE / 2, 1 + (i + 0.5) * BLOCK_SIZE / 2 + BORDER_MARGIN + BLOCK_SIZE * 1.5, BLOCK_SIZE / 2, BLOCK_SIZE / 2};
                SDL_RenderFillRect(rend, &tmp);
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                SDL_RenderDrawRect(rend, &tmp);
            }
        }
    }
    else if (nextBlock == 6)
    {
        for (int i = 0; i < 4; i++)
        {
            SDL_SetRenderDrawColor(rend, 8, 138, 118, 255);
            SDL_Rect tmp = {WINDOW_WIDTH - BORDER_MARGIN - int(2.5 * BLOCK_SIZE) + BLOCK_SIZE, 1 + BLOCK_SIZE + BORDER_MARGIN + (i + 0.5) * BLOCK_SIZE / 2, int(BLOCK_SIZE * 0.5), int(BLOCK_SIZE * 0.5)};
            SDL_RenderFillRect(rend, &tmp);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
            SDL_RenderDrawRect(rend, &tmp);
        }
    }
}

Block *GetRandomBlock(int &type)
{

    Block *block;

    switch (type)
    {
    case 0:

        block = new Three(lSquig, BASE_X, BASE_Y);
        break;

    case 1:

        block = new Three(rSquig, BASE_X, BASE_Y);
        break;

    case 2:

        block = new Three(tBlock, BASE_X, BASE_Y);
        break;

    case 3:

        block = new Three(rLblock, BASE_X, BASE_Y);
        break;

    case 4:

        block = new Three(lLblock, BASE_X, BASE_Y);
        break;

    case 5:

        block = new Square(square, BASE_X, BASE_Y);
        break;

    case 6:

        block = new Line(line, BASE_X, BASE_Y);
        break;

    default:
        break;
    }

    int next = rand() % 7;

    while (type == next)
        next = rand() % 7;

    type = next;
    return block;
}

int CheckForFullRows()
{
    int rowsFull = 0;

    for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
    {
        bool rowFull = true;

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (board[i][j] == '.' || board[i][j] == 'e')
            {
                rowFull = false;
                break;
            }
        }
        if (rowFull)
        {
            rowsFull++;
            for (int a = 0; a < BOARD_WIDTH; a++)
                board[i][a] = '.';

            for (int t = i; t > 0; t--)
                for (size_t a = 0; a < BOARD_WIDTH; a++)
                    board[t][a] = board[t - 1][a];
            i++;
        }
    }
    return rowsFull;
}

bool endGame(int &type)
{
    if (type == 6)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 10; j++)
                if (board[i][j] != '.' && board[i][j] != 'e')
                    return true;
    }
    else
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 10; j++)
                if (board[i][j] != '.' && board[i][j] != 'e')
                    return true;
    return false;
}