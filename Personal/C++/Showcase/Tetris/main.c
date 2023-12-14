#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef main
#undef main
#endif

struct position
{
    int x;
    int y;
    int baseX;
    int baseY;
};

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int WINDOW_WIDTH = 420; // 14 : 21
const int WINDOW_HEIGHT = 630;

const int BLOCK_SIZE = WINDOW_WIDTH / 14;

const int BORDER_MARGIN = WINDOW_WIDTH / 28;

void drawThreeBlock(SDL_Renderer *rend, int blockType, int rotation, int xShift, int yShift, char block[3][3]);

void drawLineBlock(SDL_Renderer *rend, int rotation, int xShift, int yShift, char line[4][4]);

void drawSquareBlock(SDL_Renderer *rend, int xShift, int yShift);

int main(int argc, char const *argv[])
{

    char line[4][4] = {{'.', 'x', '.', '.'},
                       {'.', 'x', '.', '.'},
                       {'.', 'x', '.', '.'},
                       {'.', 'x', '.', '.'}};

    char block[2][2] = {{'x', 'x'},
                        {'x', 'x'}};

    char threes[5][3][3] = {{{'.', 'x', 'x'},
                             {'x', 'x', '.'},
                             {'.', '.', '.'}},
                            {{'x', 'x', '.'},
                             {'.', 'x', 'x'},
                             {'.', '.', '.'}},
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

    struct position shift;
    shift.baseX = 1 + BLOCK_SIZE * 4 + BORDER_MARGIN;
    shift.baseY = BORDER_MARGIN + 1;
    shift.x = shift.baseX;
    shift.y = shift.baseY;

    int rotation = 0; // 90 degrees * rotation to rotate the blocks
    int blockType = 0;
    int nextBlock = 1 + rand() % 6;
    int r, g, b;

    bool quit = false;
    SDL_Event event;

    Uint32 frameStart, frameTime;

    SDL_Rect border = {BORDER_MARGIN, BORDER_MARGIN, BLOCK_SIZE * 10 + 4, BLOCK_SIZE * 20 + 1};
    SDL_Rect next = {WINDOW_WIDTH - BORDER_MARGIN - 2.5 * BLOCK_SIZE, BORDER_MARGIN, BLOCK_SIZE * 2.5, BLOCK_SIZE * 2.5};

    while (!quit)
    {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
        SDL_RenderDrawRect(rend, &border);
        SDL_RenderDrawRect(rend, &next);

        if (nextBlock < 5)
        {
            if (nextBlock == 0)
                r = 43, g = 179, b = 16;
            else if (nextBlock == 1)
                r = 171, g = 12, b = 36;
            else if (nextBlock == 2)
                r = 86, g = 8, b = 138;
            else if (nextBlock == 3)
                r = 224, g = 123, b = 7;
            else
                r = 6, g = 64, b = 150;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (threes[nextBlock][i][j] == 'x')
                    {
                        SDL_SetRenderDrawColor(rend, r, g, b, 0);
                        SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                        SDL_RenderFillRect(rend, &tmp);
                        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                        SDL_RenderDrawRect(rend, &tmp);
                    }
                }
            }
        }
        else if (nextBlock == 6)
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    SDL_SetRenderDrawColor(rend, 191, 177, 21, 0);
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - 0.25 * BLOCK_SIZE) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                    SDL_RenderDrawRect(rend, &tmp);
                }
            }
        }
        else if (nextBlock == 5)
        {
            for (int i = 0; i < 4; i++)
            {
                SDL_SetRenderDrawColor(rend, 8, 138, 118, 0);
                SDL_Rect tmp = {WINDOW_WIDTH - BORDER_MARGIN - 2.5 * BLOCK_SIZE + 2 * BLOCK_SIZE / 2, 1 + BORDER_MARGIN + (i + 0.5) * BLOCK_SIZE / 2, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
                SDL_RenderFillRect(rend, &tmp);
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                SDL_RenderDrawRect(rend, &tmp);
            }
        }

        SDL_SetRenderDrawColor(rend, 171, 12, 36, 0);

        if (blockType < 5)
            drawThreeBlock(rend, blockType, rotation, shift.x, shift.y, threes[blockType]);
        else if (blockType == 5)
            drawLineBlock(rend, rotation, shift.x, shift.y, line);
        else if (blockType == 6)
            drawSquareBlock(rend, shift.x, shift.y);

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_q:
                    rotation = (rotation + 3) % 4;
                    SDL_Log("Rotation: %d, Block type: %d", rotation, blockType);
                    break;

                case SDLK_e:
                    rotation = (rotation + 1) % 4;
                    SDL_Log("Rotation: %d, Block type: %d", rotation, blockType);
                    break;

                case SDLK_w:

                    break;

                case SDLK_a:
                {
                    shift.x -= BLOCK_SIZE;
                    if (blockType == 6 && shift.x < -BLOCK_SIZE + 4 + BORDER_MARGIN)
                    {
                        shift.x += BLOCK_SIZE;
                    }
                    else if (blockType == 5) // if the block is a line[4][4]
                    {
                        switch (rotation)
                        {
                        case 0:
                            if (shift.x < -2 * BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x < -3 * BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 3:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 3)
                    {
                        switch (rotation)
                        {

                        case 0:
                            if (shift.x < -2 * BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x < (-BLOCK_SIZE + 2 + BORDER_MARGIN))
                            {
                                shift.x += BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 4)
                    {

                        switch (rotation)
                        {

                        case 0:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x < -2 * BLOCK_SIZE + 2 + BORDER_MARGIN)
                            {
                                shift.x += BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 2)
                    {

                        switch (rotation)
                        {

                        case 0:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x < -2 * BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x < (-BLOCK_SIZE + 2 + BORDER_MARGIN))
                            {
                                shift.x += BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 1)
                    {

                        switch (rotation)
                        {

                        case 0:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x < -2 * BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x < (-BLOCK_SIZE + 2 + BORDER_MARGIN))
                            {
                                shift.x += BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 0)
                    {

                        switch (rotation)
                        {

                        case 0:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x < -2 * BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x < (-BLOCK_SIZE + 2 + BORDER_MARGIN))
                            {
                                shift.x += BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x < -BLOCK_SIZE + 2 + BORDER_MARGIN)
                                shift.x += BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }

                    break;
                }

                case SDLK_d:
                {
                    shift.x += BLOCK_SIZE;

                    if (blockType == 6 && shift.x > BLOCK_SIZE * 8 + 4 + BORDER_MARGIN)
                    {
                        shift.x -= BLOCK_SIZE;
                    }
                    else if (blockType == 5) // if the block is a line[4][4]
                    {
                        switch (rotation)
                        {
                        case 0:
                            if (shift.x > BLOCK_SIZE * 8 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x > BLOCK_SIZE * 6 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 3:
                            if (shift.x > BLOCK_SIZE * 6 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 3)
                    {
                        switch (rotation)
                        {

                        case 0:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x > (BLOCK_SIZE * 8 + 4 + BORDER_MARGIN))
                            {
                                shift.x -= BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 4)
                    {

                        switch (rotation)
                        {

                        case 0:
                            if (shift.x > BLOCK_SIZE * 8 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x > (BLOCK_SIZE * 7 + 4 + BORDER_MARGIN))
                            {
                                shift.x -= BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 2)
                    {

                        switch (rotation)
                        {

                        case 0:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x > (BLOCK_SIZE * 7 + 4 + BORDER_MARGIN))
                            {
                                shift.x -= BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x > BLOCK_SIZE * 8 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 1)
                    {

                        switch (rotation)
                        {

                        case 0:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x > (BLOCK_SIZE * 7 + 4 + BORDER_MARGIN))
                            {
                                shift.x -= BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x > BLOCK_SIZE * 8 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }
                    else if (blockType == 0)
                    {

                        switch (rotation)
                        {

                        case 0:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 1:
                            if (shift.x > BLOCK_SIZE * 7 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        case 2:
                            if (shift.x > (BLOCK_SIZE * 7 + 4 + BORDER_MARGIN))
                            {
                                shift.x -= BLOCK_SIZE;
                            }
                            break;

                        case 3:
                            if (shift.x > BLOCK_SIZE * 8 + 4 + BORDER_MARGIN)
                                shift.x -= BLOCK_SIZE;
                            break;

                        default:
                            break;
                        }
                    }

                    break;
                }
                case SDLK_SPACE:
                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;
                    break;
                }
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

void drawThreeBlock(SDL_Renderer *rend, int blockType, int rotation, int xShift, int yShift, char block[3][3])
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
                if (block[i][j] == 'x')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {xShift + 1 + j * BLOCK_SIZE, 1 + i * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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
                if (block[j][i] == 'x')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {xShift + 1 + y * BLOCK_SIZE, 1 + x * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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
                if (block[j][i] == 'x')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {xShift + 1 + x * BLOCK_SIZE, 1 + y * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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
                if (block[i][j] == 'x')
                {
                    SDL_SetRenderDrawColor(rend, r, g, b, 0);
                    SDL_Rect tmp = {xShift + 1 + x * BLOCK_SIZE, 1 + y * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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

void drawLineBlock(SDL_Renderer *rend, int rotation, int xShift, int yShift, char line[4][4])
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
                    SDL_Rect tmp = {xShift + 1 + j * BLOCK_SIZE, 1 + i * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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
                    SDL_Rect tmp = {xShift + 1 + y * BLOCK_SIZE, 1 + x * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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
                    SDL_Rect tmp = {xShift + 1 + x * BLOCK_SIZE, 1 + y * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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
                    SDL_Rect tmp = {xShift + 1 + x * BLOCK_SIZE, 1 + y * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
                    SDL_RenderFillRect(rend, &tmp);
                    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
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

void drawSquareBlock(SDL_Renderer *rend, int xShift, int yShift)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_SetRenderDrawColor(rend, 191, 177, 21, 0);
            SDL_Rect tmp = {xShift + 1 + j * BLOCK_SIZE, 1 + i * BLOCK_SIZE + yShift, BLOCK_SIZE, BLOCK_SIZE};
            SDL_RenderFillRect(rend, &tmp);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            SDL_RenderDrawRect(rend, &tmp);
        }
    }
}
