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

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

char board[20][10] = {
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

char line[4][4][4] = {{{'.', 'c', '.', '.'},
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

char blocks[2][2] = {{'y', 'y'},
                     {'y', 'y'}};

char lSquig[4][3][3] = {{{'r', 'r', '.'},
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

char rSquig[4][3][3] = {{{'.', 'g', 'g'},
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

char tBlock[4][3][3] = {{{'.', 'p', '.'},
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

char rLblock[4][3][3] = {{{'.', 'o', '.'},
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

char lLblock[4][3][3] = {{{'.', 'b', '.'},
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

void deleteThreeFromBoard(char three[3][3], int shiftX, int shiftY);

void deleteLineFromBoard(char line[4][4], int shiftX, int shiftY);

void deleteSquareFromBoard(int shiftX, int shiftY);

void drawThreeOnBoard(char three[3][3], int shiftX, int shiftY);

void drawLineOnBoard(char line[4][4], int shiftX, int shiftY);

void drawSqareOnBoard(int shiftX, int shiftY);

void drawBoard(SDL_Renderer *rend, int x, int y);

void drawNextBlockWindow(SDL_Renderer *rend, int nextBlock);

int checkThreeSideFree(char three[3][3], int side);

int checkLineSideFree(char line[4][4], int side);

bool threesPositionIsFinal(char three[3][3], int shiftX, int shiftY);

bool squarePositionIsFinal(int shiftX, int shiftY);

bool linePositionIsFinal(char line[4][4], int shiftX, int shiftY);

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

    SDL_Surface *tmpSurface = IMG_Load("src/imgs/TetrisIcon.png");
    SDL_SetWindowIcon(window, tmpSurface);
    SDL_free(tmpSurface);

    struct position shift;
    shift.baseX = 4;
    shift.baseY = 0;
    shift.x = shift.baseX;
    shift.y = shift.baseY;

    int rotation = 0; // 90 degrees * rotation to rotate the blocks
    int blockType = 0;
    int nextBlock = 1 + rand() % 6;
    int r, g, b;
    int dropDelay = 1000;

    bool quit = false;
    SDL_Event event;

    Uint32 frameStart, frameTime, lastDrop;

    SDL_Rect border = {BORDER_MARGIN, BORDER_MARGIN, BLOCK_SIZE * BOARD_WIDTH + 2, BLOCK_SIZE * BOARD_HEIGHT + 2};
    SDL_Rect next = {WINDOW_WIDTH - BORDER_MARGIN - 2.5 * BLOCK_SIZE, BORDER_MARGIN, BLOCK_SIZE * 2.5, BLOCK_SIZE * 2.5};

    while (!quit)
    {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
        SDL_RenderDrawRect(rend, &border);
        SDL_RenderDrawRect(rend, &next);

        switch (blockType)
        {
        case 0:
            drawThreeOnBoard(lSquig[rotation], shift.x, shift.y);
            break;

        case 1:
            drawThreeOnBoard(rSquig[rotation], shift.x, shift.y);
            break;

        case 2:
            drawThreeOnBoard(tBlock[rotation], shift.x, shift.y);
            break;

        case 3:
            drawThreeOnBoard(rLblock[rotation], shift.x, shift.y);
            break;

        case 4:
            drawThreeOnBoard(lLblock[rotation], shift.x, shift.y);
            break;

        case 5:
            drawSqareOnBoard(shift.x, shift.y);
            break;

        case 6:
            drawLineOnBoard(line[rotation], shift.x, shift.y);
            break;

        default:
            break;
        }

        drawBoard(rend, BORDER_MARGIN + 1, BORDER_MARGIN + 1);

        drawNextBlockWindow(rend, nextBlock);

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_e:
                {
                    int minX;
                    int maxX;

                    switch (blockType)
                    {
                    case 0:
                        deleteThreeFromBoard(lSquig[rotation], shift.x, shift.y);

                        rotation = (rotation + 3) % 4;

                        minX = checkThreeSideFree(lSquig[rotation], 0);
                        maxX = checkThreeSideFree(lSquig[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 1:
                        deleteThreeFromBoard(rSquig[rotation], shift.x, shift.y);

                        rotation = (rotation + 3) % 4;

                        minX = checkThreeSideFree(rSquig[rotation], 0);
                        maxX = checkThreeSideFree(rSquig[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 2:
                        deleteThreeFromBoard(tBlock[rotation], shift.x, shift.y);

                        rotation = (rotation + 3) % 4;

                        minX = checkThreeSideFree(tBlock[rotation], 0);
                        maxX = checkThreeSideFree(tBlock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 3:
                        deleteThreeFromBoard(rLblock[rotation], shift.x, shift.y);

                        rotation = (rotation + 3) % 4;

                        minX = checkThreeSideFree(rLblock[rotation], 0);
                        maxX = checkThreeSideFree(rLblock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 4:
                        deleteThreeFromBoard(lLblock[rotation], shift.x, shift.y);

                        rotation = (rotation + 3) % 4;

                        minX = checkThreeSideFree(lLblock[rotation], 0);
                        maxX = checkThreeSideFree(lLblock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 5:
                        deleteSquareFromBoard(shift.x, shift.y);

                        rotation = (rotation + 3) % 4;

                        break;

                    case 6:

                        deleteLineFromBoard(line[rotation], shift.x, shift.y);

                        rotation = (rotation + 3) % 4;

                        if (rotation == 0 || rotation == 2)
                        {
                            minX = checkLineSideFree(line[rotation], 0);
                            maxX = checkLineSideFree(line[rotation], 1);

                            if (shift.x > maxX)
                                shift.x = maxX;
                            else if (shift.x < minX)
                                shift.x = minX;
                        }
                        else if (shift.x < 0)
                            shift.x = 0;
                        else if (shift.x > BOARD_WIDTH - 4)
                            shift.x = BOARD_WIDTH - 4;

                        break;

                    default:
                        break;
                    }

                    break;
                }
                case SDLK_q:
                {
                    int minX;
                    int maxX;

                    switch (blockType)
                    {
                    case 0:
                        deleteThreeFromBoard(lSquig[rotation], shift.x, shift.y);

                        rotation = (rotation + 1) % 4;

                        minX = checkThreeSideFree(lSquig[rotation], 0);
                        maxX = checkThreeSideFree(lSquig[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 1:
                        deleteThreeFromBoard(rSquig[rotation], shift.x, shift.y);

                        rotation = (rotation + 1) % 4;

                        minX = checkThreeSideFree(rSquig[rotation], 0);
                        maxX = checkThreeSideFree(rSquig[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 2:
                        deleteThreeFromBoard(tBlock[rotation], shift.x, shift.y);

                        rotation = (rotation + 1) % 4;

                        minX = checkThreeSideFree(tBlock[rotation], 0);
                        maxX = checkThreeSideFree(tBlock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 3:
                        deleteThreeFromBoard(rLblock[rotation], shift.x, shift.y);

                        rotation = (rotation + 1) % 4;

                        minX = checkThreeSideFree(rLblock[rotation], 0);
                        maxX = checkThreeSideFree(rLblock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 4:
                        deleteThreeFromBoard(lLblock[rotation], shift.x, shift.y);

                        rotation = (rotation + 1) % 4;

                        minX = checkThreeSideFree(lLblock[rotation], 0);
                        maxX = checkThreeSideFree(lLblock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;
                        else if (shift.x < minX)
                            shift.x = minX;

                        break;

                    case 5:
                        deleteSquareFromBoard(shift.x, shift.y);

                        rotation = (rotation + 1) % 4;

                        break;
                    case 6:
                        deleteLineFromBoard(line[rotation], shift.x, shift.y);

                        rotation = (rotation + 1) % 4;

                        if (rotation == 0 || rotation == 2)
                        {
                            minX = checkLineSideFree(line[rotation], 0);
                            maxX = checkLineSideFree(line[rotation], 1);

                            if (shift.x > maxX)
                                shift.x = maxX;
                            else if (shift.x < minX)
                                shift.x = minX;
                        }
                        else if (shift.x < 0)
                            shift.x = 0;
                        else if (shift.x > BOARD_WIDTH - 4)
                            shift.x = BOARD_WIDTH - 4;

                        break;

                    default:
                        break;
                    }

                    // SDL_Log("Rotation: %d, Block type: %d", rotation, blockType);
                    break;
                }
                case SDLK_s:
                {
                    switch (blockType)
                    {

                    case 0:
                        deleteThreeFromBoard(lSquig[rotation], shift.x, shift.y);

                        shift.y++;

                        if (threesPositionIsFinal(lSquig[rotation], shift.x, shift.y))
                        {

                            drawThreeOnBoard(lSquig[rotation], shift.x, shift.y - 1);
                            shift.x = shift.baseX;
                            shift.y = shift.baseY;
                            rotation = 0;
                            blockType = nextBlock;
                            while (nextBlock == blockType)
                                nextBlock = rand() % 7;
                        }
                        break;

                    case 1:
                        deleteThreeFromBoard(rSquig[rotation], shift.x, shift.y);

                        shift.y++;

                        if (threesPositionIsFinal(rSquig[rotation], shift.x, shift.y))
                        {

                            drawThreeOnBoard(rSquig[rotation], shift.x, shift.y - 1);
                            shift.x = shift.baseX;
                            shift.y = shift.baseY;
                            rotation = 0;
                            blockType = nextBlock;
                            while (nextBlock == blockType)
                                nextBlock = rand() % 7;
                        }
                        break;

                    case 2:
                        deleteThreeFromBoard(tBlock[rotation], shift.x, shift.y);

                        shift.y++;

                        if (threesPositionIsFinal(tBlock[rotation], shift.x, shift.y))
                        {

                            drawThreeOnBoard(tBlock[rotation], shift.x, shift.y - 1);
                            shift.x = shift.baseX;
                            shift.y = shift.baseY;
                            rotation = 0;
                            blockType = nextBlock;
                            while (nextBlock == blockType)
                                nextBlock = rand() % 7;
                        }
                        break;

                    case 3:
                        deleteThreeFromBoard(rLblock[rotation], shift.x, shift.y);

                        shift.y++;

                        if (threesPositionIsFinal(rLblock[rotation], shift.x, shift.y))
                        {

                            drawThreeOnBoard(rLblock[rotation], shift.x, shift.y - 1);
                            shift.x = shift.baseX;
                            shift.y = shift.baseY;
                            rotation = 0;
                            blockType = nextBlock;
                            while (nextBlock == blockType)
                                nextBlock = rand() % 7;
                        }
                        break;

                    case 4:
                        deleteThreeFromBoard(lLblock[rotation], shift.x, shift.y);

                        shift.y++;

                        if (threesPositionIsFinal(lLblock[rotation], shift.x, shift.y))
                        {

                            drawThreeOnBoard(lLblock[rotation], shift.x, shift.y - 1);
                            shift.x = shift.baseX;
                            shift.y = shift.baseY;
                            rotation = 0;
                            blockType = nextBlock;
                            while (nextBlock == blockType)
                                nextBlock = rand() % 7;
                        }
                        break;

                    case 5:
                        deleteSquareFromBoard(shift.x, shift.y);

                        shift.y++;

                        if (squarePositionIsFinal(shift.x, shift.y))
                        {

                            drawSqareOnBoard(shift.x, shift.y - 1);
                            shift.x = shift.baseX;
                            shift.y = shift.baseY;
                            rotation = 0;
                            blockType = nextBlock;
                            while (nextBlock == blockType)
                                nextBlock = rand() % 7;
                        }
                        break;

                    case 6:
                        deleteLineFromBoard(line[rotation], shift.x, shift.y);

                        shift.y++;

                        if (linePositionIsFinal(line[rotation], shift.x, shift.y))
                        {

                            drawLineOnBoard(line[rotation], shift.x, shift.y - 1);

                            shift.x = shift.baseX;
                            shift.y = shift.baseY;
                            rotation = 0;
                            blockType = nextBlock;
                            while (nextBlock == blockType)
                                nextBlock = rand() % 7;
                        }
                        break;

                    default:
                        break;
                    }

                    for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
                    {
                        bool rowFull = true;

                        for (int j = 0; j < BOARD_WIDTH; j++)
                        {
                            if (board[i][j] == '.')
                            {
                                rowFull = false;
                                break;
                            }
                        }
                        if (rowFull)
                        {
                            for (int a = 0; a < BOARD_WIDTH; a++)
                                board[i][a] = '.';

                            for (int t = i; t > 0; t--)
                            {
                                for (size_t a = 0; a < BOARD_WIDTH; a++)
                                {
                                    board[t][a] = board[t - 1][a];
                                }
                            }
                            i++;
                        }
                    }

                    break;
                }
                case SDLK_a:
                {
                    int minX;
                    int maxX;

                    switch (blockType)
                    {
                    case 0:
                        deleteThreeFromBoard(lSquig[rotation], shift.x, shift.y);

                        shift.x--;

                        minX = checkThreeSideFree(lSquig[rotation], 0);

                        if (shift.x < minX)
                            shift.x = minX;

                        if (threesPositionIsFinal(lSquig[rotation], shift.x, shift.y))
                            shift.x++;

                        break;

                    case 1:
                        deleteThreeFromBoard(rSquig[rotation], shift.x, shift.y);

                        shift.x--;

                        minX = checkThreeSideFree(rSquig[rotation], 0);

                        if (shift.x < minX)
                            shift.x = minX;

                        if (threesPositionIsFinal(rSquig[rotation], shift.x, shift.y))
                            shift.x++;

                        break;

                    case 2:
                        deleteThreeFromBoard(tBlock[rotation], shift.x, shift.y);

                        shift.x--;

                        minX = checkThreeSideFree(tBlock[rotation], 0);

                        if (shift.x < minX)
                            shift.x = minX;

                        if (threesPositionIsFinal(tBlock[rotation], shift.x, shift.y))
                            shift.x++;

                        break;

                    case 3:
                        deleteThreeFromBoard(rLblock[rotation], shift.x, shift.y);

                        shift.x--;

                        minX = checkThreeSideFree(rLblock[rotation], 0);

                        if (shift.x < minX)
                            shift.x = minX;

                        if (threesPositionIsFinal(rLblock[rotation], shift.x, shift.y))
                            shift.x++;

                        break;

                    case 4:
                        deleteThreeFromBoard(lLblock[rotation], shift.x, shift.y);

                        shift.x--;

                        minX = checkThreeSideFree(lLblock[rotation], 0);

                        if (shift.x < minX)
                            shift.x = minX;

                        if (threesPositionIsFinal(lLblock[rotation], shift.x, shift.y))
                            shift.x++;

                        break;

                    case 5:
                        deleteSquareFromBoard(shift.x, shift.y);

                        shift.x--;

                        if (shift.x < 0)
                            shift.x = 0;

                        if (squarePositionIsFinal(shift.x, shift.y))
                            shift.x++;

                        break;

                    case 6:
                        deleteLineFromBoard(line[rotation], shift.x, shift.y);

                        shift.x--;

                        if (rotation == 0 || rotation == 2)
                        {
                            minX = checkLineSideFree(line[rotation], 0);

                            if (shift.x < minX)
                                shift.x = minX;
                        }
                        else if (shift.x < 0)
                            shift.x = 0;
                        else if (shift.x > BOARD_WIDTH - 4)
                            shift.x = BOARD_WIDTH - 4;

                        if (linePositionIsFinal(line[rotation], shift.x, shift.y))
                            shift.x++;

                        break;

                    default:
                        break;
                    }

                    break;
                }

                case SDLK_d:
                {
                    int minX;
                    int maxX;

                    switch (blockType)
                    {
                    case 0:
                        deleteThreeFromBoard(lSquig[rotation], shift.x, shift.y);

                        shift.x++;

                        maxX = checkThreeSideFree(lSquig[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;

                        if (threesPositionIsFinal(lSquig[rotation], shift.x, shift.y))
                            shift.x--;
                        break;

                    case 1:
                        deleteThreeFromBoard(rSquig[rotation], shift.x, shift.y);

                        shift.x++;

                        maxX = checkThreeSideFree(rSquig[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;

                        if (threesPositionIsFinal(rSquig[rotation], shift.x, shift.y))
                            shift.x--;

                        break;

                    case 2:
                        deleteThreeFromBoard(tBlock[rotation], shift.x, shift.y);

                        shift.x++;

                        maxX = checkThreeSideFree(tBlock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;

                        if (threesPositionIsFinal(tBlock[rotation], shift.x, shift.y))
                            shift.x--;

                        break;

                    case 3:
                        deleteThreeFromBoard(rLblock[rotation], shift.x, shift.y);

                        shift.x++;

                        maxX = checkThreeSideFree(rLblock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;

                        if (threesPositionIsFinal(rLblock[rotation], shift.x, shift.y))
                            shift.x--;

                        break;

                    case 4:
                        deleteThreeFromBoard(lLblock[rotation], shift.x, shift.y);

                        shift.x++;

                        maxX = checkThreeSideFree(lLblock[rotation], 1);

                        if (shift.x > maxX)
                            shift.x = maxX;

                        if (threesPositionIsFinal(lLblock[rotation], shift.x, shift.y))
                            shift.x--;

                        break;

                    case 5:
                        deleteSquareFromBoard(shift.x, shift.y);

                        shift.x++;

                        if (shift.x > BOARD_WIDTH - 2)
                            shift.x = BOARD_WIDTH - 2;

                        if (squarePositionIsFinal(shift.x, shift.y))
                            shift.x--;

                        break;

                    case 6:
                        deleteLineFromBoard(line[rotation], shift.x, shift.y);

                        shift.x++;

                        if (rotation == 0 || rotation == 2)
                        {
                            maxX = checkLineSideFree(line[rotation], 1);

                            if (shift.x > maxX)
                                shift.x = maxX;
                        }
                        else if (shift.x < 0)
                            shift.x = 0;
                        else if (shift.x > BOARD_WIDTH - 4)
                            shift.x = BOARD_WIDTH - 4;

                        if (linePositionIsFinal(line[rotation], shift.x, shift.y))
                            shift.x--;

                        break;

                    default:
                        break;
                    }

                    break;
                }
                case SDLK_SPACE:
                {
                    switch (blockType)
                    {
                    case 0:
                        deleteThreeFromBoard(lSquig[rotation], shift.x, shift.y);
                        break;

                    case 1:
                        deleteThreeFromBoard(rSquig[rotation], shift.x, shift.y);
                        break;

                    case 2:
                        deleteThreeFromBoard(tBlock[rotation], shift.x, shift.y);
                        break;

                    case 3:
                        deleteThreeFromBoard(rLblock[rotation], shift.x, shift.y);
                        break;

                    case 4:
                        deleteThreeFromBoard(lLblock[rotation], shift.x, shift.y);
                        break;

                    case 5:
                        deleteSquareFromBoard(shift.x, shift.y);
                        break;

                    case 6:
                        deleteLineFromBoard(line[rotation], shift.x, shift.y);
                        break;

                    default:
                        break;
                    }

                    shift.x = shift.baseX;
                    shift.y = shift.baseY;

                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;

                    break;
                }
                }
            default:
                break;
            }

        SDL_RenderPresent(rend);

        if (SDL_GetTicks() - lastDrop > dropDelay)
        {

            lastDrop = SDL_GetTicks();

            switch (blockType)
            {
            case 0:
                deleteThreeFromBoard(lSquig[rotation], shift.x, shift.y);

                shift.y++;

                if (threesPositionIsFinal(lSquig[rotation], shift.x, shift.y))
                {

                    drawThreeOnBoard(lSquig[rotation], shift.x, shift.y - 1);
                    shift.x = shift.baseX;
                    shift.y = shift.baseY;
                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;
                }
                break;

            case 1:
                deleteThreeFromBoard(rSquig[rotation], shift.x, shift.y);

                shift.y++;

                if (threesPositionIsFinal(rSquig[rotation], shift.x, shift.y))
                {

                    drawThreeOnBoard(rSquig[rotation], shift.x, shift.y - 1);
                    shift.x = shift.baseX;
                    shift.y = shift.baseY;
                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;
                }
                break;

            case 2:
                deleteThreeFromBoard(tBlock[rotation], shift.x, shift.y);

                shift.y++;

                if (threesPositionIsFinal(tBlock[rotation], shift.x, shift.y))
                {

                    drawThreeOnBoard(tBlock[rotation], shift.x, shift.y - 1);
                    shift.x = shift.baseX;
                    shift.y = shift.baseY;
                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;
                }
                break;

            case 3:
                deleteThreeFromBoard(rLblock[rotation], shift.x, shift.y);

                shift.y++;

                if (threesPositionIsFinal(rLblock[rotation], shift.x, shift.y))
                {

                    drawThreeOnBoard(rLblock[rotation], shift.x, shift.y - 1);
                    shift.x = shift.baseX;
                    shift.y = shift.baseY;
                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;
                }
                break;

            case 4:
                deleteThreeFromBoard(lLblock[rotation], shift.x, shift.y);

                shift.y++;

                if (threesPositionIsFinal(lLblock[rotation], shift.x, shift.y))
                {

                    drawThreeOnBoard(lLblock[rotation], shift.x, shift.y - 1);
                    shift.x = shift.baseX;
                    shift.y = shift.baseY;
                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;
                }
                break;

            case 5:
                deleteSquareFromBoard(shift.x, shift.y);

                shift.y++;

                if (squarePositionIsFinal(shift.x, shift.y))
                {

                    drawSqareOnBoard(shift.x, shift.y - 1);
                    shift.x = shift.baseX;
                    shift.y = shift.baseY;
                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;
                }
                break;

            case 6:
                deleteLineFromBoard(line[rotation], shift.x, shift.y);

                shift.y++;

                if (linePositionIsFinal(line[rotation], shift.x, shift.y))
                {

                    drawLineOnBoard(line[rotation], shift.x, shift.y - 1);

                    shift.x = shift.baseX;
                    shift.y = shift.baseY;
                    rotation = 0;
                    blockType = nextBlock;
                    while (nextBlock == blockType)
                        nextBlock = rand() % 7;
                }
                break;

            default:
                break;
            }

            for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
            {
                bool rowFull = true;

                for (int j = 0; j < BOARD_WIDTH; j++)
                {
                    if (board[i][j] == '.')
                    {
                        rowFull = false;
                        break;
                    }
                }
                if (rowFull)
                {
                    for (int a = 0; a < BOARD_WIDTH; a++)
                        board[i][a] = '.';

                    for (int t = i; t >= 0; t--)
                    {
                        for (size_t a = 0; a < BOARD_WIDTH; a++)
                        {
                            if (t - 1 < 0)
                            {
                                board[t][a] = '.';
                            }
                            else
                                board[t][a] = board[t - 1][a];
                        }
                    }
                    i++;
                }
            }
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);

    return 0;
}

void deleteThreeFromBoard(char three[3][3], int shiftX, int shiftY)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (three[i][j] != '.')
                board[i + shiftY][j + shiftX] = '.';
}

void deleteLineFromBoard(char line[4][4], int shiftX, int shiftY)
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

void drawThreeOnBoard(char three[3][3], int shiftX, int shiftY)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (three[i][j] != '.')
                board[i + shiftY][j + shiftX] = three[i][j];
}

void drawLineOnBoard(char line[4][4], int shiftX, int shiftY)
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
            case 'r':
                r = 171, g = 12, b = 36;
                break;

            case 'g':
                r = 43, g = 179, b = 16;
                break;

            case 'p':
                r = 86, g = 8, b = 138;
                break;

            case 'o':
                r = 224, g = 123, b = 7;
                break;

            case 'b':
                r = 6, g = 64, b = 150;
                break;

            case 'y':
                r = 191, g = 177, b = 21;
                break;

            case 'c':
                r = 8, g = 138, b = 118;
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
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
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
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
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
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
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
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
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
                    SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - BLOCK_SIZE * 0.5) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
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
                SDL_Rect tmp = {(WINDOW_WIDTH - BORDER_MARGIN - 0.25 * BLOCK_SIZE) + 1 + (j - 3) * BLOCK_SIZE * 0.5, 1 + (i + 0.5) * BLOCK_SIZE * 0.5 + BORDER_MARGIN + BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
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
            SDL_Rect tmp = {WINDOW_WIDTH - BORDER_MARGIN - 2.5 * BLOCK_SIZE + 2 * BLOCK_SIZE / 2, 1 + BORDER_MARGIN + (i + 0.5) * BLOCK_SIZE / 2, BLOCK_SIZE * 0.5, BLOCK_SIZE * 0.5};
            SDL_RenderFillRect(rend, &tmp);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
            SDL_RenderDrawRect(rend, &tmp);
        }
    }
}

int checkThreeSideFree(char three[3][3], int side)
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

int checkLineSideFree(char line[4][4], int side)
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

bool threesPositionIsFinal(char three[3][3], int shiftX, int shiftY)
{

    bool stop = false;

    for (int i = 0; i < 3 && !stop; i++)
        for (int j = 0; j < 3; j++)
            if (three[i][j] != '.' && board[i + shiftY][j + shiftX] != '.' || i + shiftY > BOARD_HEIGHT)
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
            if (board[i + shiftY][j + shiftX] != '.' || i + shiftY > BOARD_HEIGHT)
            {
                stop = true;
                break;
            }

    return stop;
}

bool linePositionIsFinal(char line[4][4], int shiftX, int shiftY)
{
    bool stop = false;

    for (int i = 0; i < 4 && !stop; i++)
        for (int j = 0; j < 4; j++)
            if (line[i][j] != '.' && board[i + shiftY][j + shiftX] != '.' || i + shiftY > BOARD_HEIGHT)
            {
                stop = true;
                break;
            }

    return stop;
}
