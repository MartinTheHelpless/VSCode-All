#include <stdbool.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <vector>
#include <stdlib.h>
#include "src/include/Ghost.h"
#include "src/include/Player.h"
#include "src/include/defines.h" // File with all the consts, defines, etc.

#ifdef main
#undef main
#endif

SDL_Window *window = nullptr;
SDL_Renderer *rend = nullptr;

SDL_Texture *background;
TTF_Font *font;

Ghost *ghosts[4];
Player *pacMan;

// --------------------------------------------------------------------------------------------
// -------------------------------------- MAP DEFINITION START --------------------------------
// --------------------------------------------------------------------------------------------

char map[31][29] =
    {
        "............................",
        ".oooooooooooo..oooooooooooo.",
        ".o....o.....o..o.....o....o.",
        ".x....o.....o..o.....o....x.",
        ".o....o.....o..o.....o....o.",
        ".oooooooooooooooooooooooooo.",
        ".o....o..o........o..o....o.",
        ".o....o..o........o..o....o.",
        ".oooooo..oooo..oooo..oooooo.",
        "......o.....e..e.....o......",
        "......o.....e..e.....o......",
        "......o..eeeeeeeeee..o......",
        "......o..e........e..o......",
        "......o..e...ee...e..o......",
        "eeeeeeoeee.eeeeee.eeeoeeeeee",
        "......o..e........e..o......",
        "......o..e........e..o......",
        "......o..eeeeeeeeee..o......",
        "......o..e........e..o......",
        "......o..e........e..o......",
        ".oooooooooooo..oooooooooooo.",
        ".o....o.....o..o.....o....o.",
        ".o....o.....o..o.....o....o.",
        ".xoo..oooooooeeooooooo..oox.",
        "...o..o..o........o..o..o...",
        "...o..o..o........o..o..o...",
        ".oooooo..oooo..oooo..oooooo.",
        ".o..........o..o..........o.",
        ".o..........o..o..........o.",
        ".oooooooooooooooooooooooooo.",
        "............................",
};

// --------------------------------------------------------------------------------------------
// --------------------------------------- MAP DEFINITION END ---------------------------------
// --------------------------------------------------------------------------------------------

bool Init();

void Close();

void DrawGrid();

void DrawDots();

void DrawPlayer();

void DrawGhosts();

int main(int argc, char const *argv[])
{

    if (!Init())
        return -1;

    font = TTF_OpenFont("src/Aller_Rg.ttf", 30);

    SDL_Color fontColor = {255, 255, 255, 0};

    SDL_Surface *tmp = IMG_Load("src/assets/Background.png");
    background = SDL_CreateTextureFromSurface(rend, tmp);
    SDL_Rect backgroundRec = {0, 3 * TILE_DIM, WINDOW_WIDTH, WINDOW_HEIGHT - 5 * TILE_DIM};
    SDL_FreeSurface(tmp);

    pacMan = new Player();

    // (id, x, y, direction, speed, x and y scatter target, color) color will be removed with sprite addition

    ghosts[0] = new Ghost(0, 13.0f, 11.0f, 1, 0.1f, {25, -4}, {255, 0, 0, 0});    // Blinky
    ghosts[1] = new Ghost(2, 13.0f, 11.0f, 1, 0.1f, {27, 31}, {0, 255, 255, 0});  // Inky
    ghosts[2] = new Ghost(3, 13.0f, 11.0f, 1, 0.1f, {0, 31}, {255, 184, 82, 0});  // Clyde
    ghosts[3] = new Ghost(1, 13.0f, 11.0f, 1, 0.1f, {2, -4}, {255, 184, 255, 0}); // Pinky

    Uint32 frameStart, frameTime;

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {

        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, background, nullptr, &backgroundRec);

        // DrawGrid();
        DrawDots();

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

                case SDLK_w:
                {
                    pacMan->SetMoveDir(0);
                    break;
                }
                case SDLK_a:
                {
                    pacMan->SetMoveDir(1);
                    break;
                }

                case SDLK_s:
                {
                    pacMan->SetMoveDir(2);
                    break;
                }

                case SDLK_d:
                {
                    pacMan->SetMoveDir(3);
                    break;
                }

                case SDLK_SPACE:
                {
                    for (Ghost *ghost : ghosts)
                        ghost->SetState(1);

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

        pacMan->Update(map);

        for (Ghost *ghost : ghosts)
            ghost->Update(map, pacMan->GetX(), pacMan->GetY(), pacMan->GetDirection(), ghosts[0]->GetX(), ghosts[0]->GetY());

        DrawGhosts();
        DrawPlayer();

        // std::cout << pacMan->GetX() << " " << pacMan->GetY() << std::endl;

        SDL_RenderPresent(rend);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
    }

    Close();

    return 0;
}

bool Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Player Movement", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window)
    {
        SDL_Log("Unable to initialize SDL Window\n");
        return false;
    }

    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!rend)
    {
        SDL_Log("Unable to initialize SDL Renderer \n");
        SDL_DestroyWindow(window);
        return false;
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Font could not be loaded.");
        return 1;
    }

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);

    return true;
}

void Close()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void DrawGrid()
{

    SDL_SetRenderDrawColor(rend, 10, 115, 12, 0);

    for (int i = 0; i <= GAME_WIDTH; i++)
        for (int j = 0; j <= GAME_HEIGHT; j++)
        {
            SDL_Rect rect = {0, 0, i * TILE_DIM, j * TILE_DIM};
            SDL_RenderDrawRect(rend, &rect);
        }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
}

void DrawDots()
{

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    for (int i = 0; i < 31; i++)
        for (int j = 0; j < 28; j++)
            if (map[i][j] == 'o')
            {
                SDL_Rect rect = {j * TILE_DIM + TILE_DIM / 2 - 2, 3 * TILE_DIM + i * TILE_DIM + TILE_DIM / 2 - 2, 4, 4};
                SDL_RenderFillRect(rend, &rect);
            }
            else if (map[i][j] == 'x')
            {
                SDL_Rect rect = {j * TILE_DIM + TILE_DIM / 2 - 6, 3 * TILE_DIM + i * TILE_DIM + TILE_DIM / 2 - 4, 12, 12};
                SDL_RenderFillRect(rend, &rect);
            }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
}

void DrawPlayer()
{
    SDL_Rect tmp = {-5 + int(pacMan->GetX() * TILE_DIM), -5 + 3 * TILE_DIM + int(pacMan->GetY() * TILE_DIM), ENTITY_DIM, ENTITY_DIM};
    SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
    SDL_RenderFillRect(rend, &tmp);
}

void DrawGhosts()
{
    for (Ghost *ghost : ghosts)
    {
        SDL_Rect tmp = {-5 + int(ghost->GetX() * TILE_DIM), -5 + 3 * TILE_DIM + int(ghost->GetY() * TILE_DIM), ENTITY_DIM, ENTITY_DIM};
        SDL_SetRenderDrawColor(rend, ghost->GetColor().r, ghost->GetColor().g, ghost->GetColor().b, ghost->GetColor().a);
        SDL_RenderFillRect(rend, &tmp);
    }
}
