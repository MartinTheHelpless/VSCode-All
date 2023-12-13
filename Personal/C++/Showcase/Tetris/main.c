#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef main
#undef main
#endif

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int WINDOW_WIDTH = 420; // 14 : 21
const int WINDOW_HEIGHT = 630;

const int BLOCK_SIZE = WINDOW_WIDTH / 14;

const int BORDER_MARGIN = WINDOW_WIDTH / 28;

int main(int argc, char const *argv[])
{

    char line[4][4] = {{'.', 'x', '.', '.'},
                       {'.', 'x', '.', '.'},
                       {'.', 'x', '.', '.'},
                       {'.', 'x', '.', '.'}};

    // SDL_Log("Size of a char line: %d", sizeof(line) / sizeof(char));

    char block[2][2] = {{'x', 'x'},
                        {'x', 'x'}};

    char threes[5][3][3] = {{{'.', '.', '.'},
                             {'.', 'x', 'x'},
                             {'x', 'x', '.'}},
                            {{'.', '.', '.'},
                             {'x', 'x', '.'},
                             {'.', 'x', 'x'}},
                            {{'.', 'x', '.'},
                             {'x', 'x', 'x'},
                             {'.', '.', '.'}},
                            {{'.', 'x', '.'},
                             {'.', 'x', '.'},
                             {'.', 'x', 'x'}},
                            {{'.', 'x', '.'},
                             {'.', 'x', '.'},
                             {'x', 'x', '.'}}};

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

    SDL_Surface *tmpSurface = IMG_Load("src/imgs/TetrisIcon.png");
    SDL_SetWindowIcon(window, tmpSurface);
    SDL_free(tmpSurface);

    /*
    tmpSurface = IMG_Load("src/imgs/RedBlock.png");
    SDL_Texture *RedBlock = SDL_CreateTextureFromSurface(rend, tmpSurface);

    tmpSurface = IMG_Load("src/imgs/BlueBlock.png");
    SDL_Texture *BlueBlock = SDL_CreateTextureFromSurface(rend, tmpSurface);

    tmpSurface = IMG_Load("src/imgs/GreenBlock.png");
    SDL_Texture *GreenBlock = SDL_CreateTextureFromSurface(rend, tmpSurface);

    tmpSurface = IMG_Load("src/imgs/OrangeBlock.png");
    SDL_Texture *OrangeBlock = SDL_CreateTextureFromSurface(rend, tmpSurface);

    tmpSurface = IMG_Load("src/imgs/PurpleBlock.png");
    SDL_Texture *PurpleBlock = SDL_CreateTextureFromSurface(rend, tmpSurface);
    */

    int rotation = 0; // 90 degrees * rotation to rotate the blocks
    int blockType = 0;

    bool quit = false;
    SDL_Event event;

    Uint32 frameStart, frameTime;

    SDL_Rect border = {BORDER_MARGIN, BORDER_MARGIN, BLOCK_SIZE * 10 + 2, BLOCK_SIZE * 20 + 1};

    while (!quit)
    {

        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
        SDL_RenderDrawRect(rend, &border);

        SDL_SetRenderDrawColor(rend, 171, 12, 36, 0);

        if (blockType < 5)
        {
            int r, g, b;

            if (blockType == 0)
                r = 43, g = 179, b = 16;
            else if (blockType == 1)
                r = 171, g = 12, b = 36;
            else if (blockType == 2)
                r = 86, g = 8, b = 138;
            else if (blockType == 3)
                r = 224, g = 123, b = 7;
            else
                r = 6, g = 64, b = 150;

            switch (rotation)
            {
            case 0:
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                        if (threes[blockType][i][j] == 'x')
                        {
                            SDL_SetRenderDrawColor(rend, r, g, b, 0);
                            SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + j * BLOCK_SIZE, BORDER_MARGIN + 1 + (i + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                            SDL_RenderFillRect(rend, &tmp);
                            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                            SDL_RenderDrawRect(rend, &tmp);
                        }
                }
                break;
            }

            case 1:
            {
                int x = 0;
                int y = 0;
                for (int j = 2; j >= 0; j--)
                {
                    for (int i = 0; i < 3; i++)
                        if (threes[blockType][j][i] == 'x')
                        {
                            SDL_SetRenderDrawColor(rend, r, g, b, 0);
                            SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + y * BLOCK_SIZE, BORDER_MARGIN + 1 + (x + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                            SDL_RenderFillRect(rend, &tmp);
                            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                            SDL_RenderDrawRect(rend, &tmp);
                            x++;
                        }
                        else
                            x++;
                    x = 0;
                    y++;
                }
                break;
            }

            case 2:
            {
                int x = 0;
                int y = 0;
                for (int j = 2; j >= 0; j--)
                {
                    for (int i = 2; i >= 0; i--)
                        if (threes[blockType][j][i] == 'x')
                        {
                            SDL_SetRenderDrawColor(rend, r, g, b, 0);
                            SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + x * BLOCK_SIZE, BORDER_MARGIN + 1 + (y + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                            SDL_RenderFillRect(rend, &tmp);
                            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                            SDL_RenderDrawRect(rend, &tmp);
                            x++;
                        }
                        else
                            x++;
                    x = 0;
                    y++;
                }
                break;
            }

            case 3:
            {
                int x = 0;
                int y = 0;
                for (int j = 2; j >= 0; j--)
                {
                    for (int i = 0; i < 3; i++)
                        if (threes[blockType][i][j] == 'x')
                        {
                            SDL_SetRenderDrawColor(rend, r, g, b, 0);
                            SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + x * BLOCK_SIZE, BORDER_MARGIN + 1 + (y + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                            SDL_RenderFillRect(rend, &tmp);
                            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                            SDL_RenderDrawRect(rend, &tmp);
                            x++;
                        }
                        else
                            x++;
                    x = 0;
                    y++;
                }
                break;
            }
            default:
                break;
            }
        }
        else if (blockType == 5)
        {

            switch (rotation % 4)
            {
            case 0:
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                        if (line[i][j] == 'x')
                        {
                            SDL_SetRenderDrawColor(rend, 8, 138, 118, 0);
                            SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + j * BLOCK_SIZE, BORDER_MARGIN + 1 + (i + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                            SDL_RenderFillRect(rend, &tmp);
                            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                            SDL_RenderDrawRect(rend, &tmp);
                        }
                }
                break;
            }

            case 1:
            {
                int x = 0;
                int y = 0;
                for (int j = 3; j >= 0; j--)
                {
                    for (int i = 0; i < 4; i++)
                        if (line[j][i] == 'x')
                        {
                            SDL_SetRenderDrawColor(rend, 8, 138, 118, 0);
                            SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + y * BLOCK_SIZE, BORDER_MARGIN + 1 + (x + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                            SDL_RenderFillRect(rend, &tmp);
                            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                            SDL_RenderDrawRect(rend, &tmp);
                            x++;
                        }
                        else
                            x++;
                    x = 0;
                    y++;
                }
                break;
            }

            case 2:
            {
                int x = 0;
                int y = 0;
                for (int j = 3; j >= 0; j--)
                {
                    for (int i = 3; i >= 0; i--)
                        if (line[j][i] == 'x')
                        {
                            SDL_SetRenderDrawColor(rend, 8, 138, 118, 0);
                            SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + x * BLOCK_SIZE, BORDER_MARGIN + 1 + (y + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                            SDL_RenderFillRect(rend, &tmp);
                            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                            SDL_RenderDrawRect(rend, &tmp);
                            x++;
                        }
                        else
                            x++;
                    x = 0;
                    y++;
                }
                break;
            }

            case 3:
            {
                int x = 0;
                int y = 0;
                for (int j = 3; j >= 0; j--)
                {
                    for (int i = 0; i < 4; i++)
                        if (line[i][j] == 'x')
                        {
                            SDL_SetRenderDrawColor(rend, 8, 138, 118, 0);
                            SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + x * BLOCK_SIZE, BORDER_MARGIN + 1 + (y + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                            SDL_RenderFillRect(rend, &tmp);
                            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                            SDL_RenderDrawRect(rend, &tmp);
                            x++;
                        }
                        else
                            x++;
                    x = 0;
                    y++;
                }
                break;
            }
            default:
                break;
            }
        }
        else if (blockType == 6)
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    SDL_SetRenderDrawColor(rend, 191, 177, 21, 0);
                    SDL_Rect tmp = {BORDER_MARGIN + 4 * BLOCK_SIZE + 1 + j * BLOCK_SIZE, BORDER_MARGIN + 1 + (i + 10) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
                    SDL_RenderDrawRect(rend, &tmp);
                }
            }
        }

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    rotation = (rotation + 3) % 4;
                    break;

                case SDLK_d:
                    rotation = (rotation + 1) % 4;
                    break;

                case SDLK_w:

                    break;

                case SDLK_SPACE:
                    rotation = 0;
                    blockType = rand() % 7;
                    break;

                default:
                    break;
                }
                break;
            default:
                break;
            }

        SDL_RenderPresent(rend);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);

    return 0;
}
