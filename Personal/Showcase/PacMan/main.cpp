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

#ifdef main
#undef main
#endif

class SDLClear
{
public:
    void operator()(SDL_Window *window) const
    {
        SDL_DestroyWindow(window);
    }

    void operator()(SDL_Renderer *renderer) const
    {
        SDL_DestroyRenderer(renderer);
    }
};

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int GAME_WIDTH = 28; // (28 : 36 tiles original Pac Man Game)
const int GAME_HEIGHT = 36;

const int TILE_DIM = 20;
const int ENTITY_DIM = 30;

const int WINDOW_WIDTH = GAME_WIDTH * TILE_DIM; // 3 : 4
const int WINDOW_HEIGHT = GAME_HEIGHT * TILE_DIM;

void DrawGrid(SDL_Renderer *rend);

void DrawDots(SDL_Renderer *rend, char map[31][29]);

void DrawGhost(SDL_Renderer *rend, Ghost *ghost);

int main(int argc, char const *argv[])
{
    // --------------------------------------------------------------------------------------------
    // -------------------------------------- MAP DEFINITION START --------------------------------
    // --------------------------------------------------------------------------------------------

    // std::string map = ".............................oooooooooooo..oooooooooooo..o....o.....o..o.....o....o..x....o.....o..o.....o....x..o....o.....o..o.....o....o..oooooooooooooooooooooooooo..o....o..o........o..o....o..o....o..o........o..o....o..oooooo..oooo..oooo..oooooo.......o.....e..e.....o............o.....e..e.....o............o..eeeeeeeeee..o............o..e...gg...e..o............o..e.eeeeee.e..o......eeeeeeoeee.eeeeee.eeeoeeeeee......o..e.eeeeee.e..o............o..e........e..o............o..eeeeeeeeee..o............o..e........e..o............o..e........e..o.......oooooooooooo..oooooooooooo..o....o.....o..o.....o....o..o....o.....o..o.....o....o..xoo..ooooooo..ooooooo..oox....o..o..o........o..o..o......o..o..o........o..o..o....oooooo..oooo..oooo..oooooo..o..........o..o..........o..o..........o..o..........o..oooooooooooooooooooooooooo.............................";
    /*std::wstring map;
    map += L"............................";
    map += L".oooooooooooo..oooooooooooo.";
    map += L".o....o.....o..o.....o....o.";
    map += L".x....o.....o..o.....o....x.";
    map += L".o....o.....o..o.....o....o.";
    map += L".oooooooooooooooooooooooooo.";
    map += L".o....o..o........o..o....o.";
    map += L".o....o..o........o..o....o.";
    map += L".oooooo..oooo..oooo..oooooo.";
    map += L"......o.....e..e.....o......";
    map += L"......o.....e..e.....o......";
    map += L"......o..eeeeeeeeee..o......";
    map += L"......o..e...gg...e..o......";
    map += L"......o..e.eeeeee.e..o......";
    map += L"eeeeeeoeee.eeeeee.eeeoeeeeee";
    map += L"......o..e.eeeeee.e..o......";
    map += L"......o..e........e..o......";
    map += L"......o..eeeeeeeeee..o......";
    map += L"......o..e........e..o......";
    map += L"......o..e........e..o......";
    map += L".oooooooooooo..oooooooooooo.";
    map += L".o....o.....o..o.....o....o.";
    map += L".o....o.....o..o.....o....o.";
    map += L".xoo..ooooooo..ooooooo..oox.";
    map += L"...o..o..o........o..o..o...";
    map += L"...o..o..o........o..o..o...";
    map += L".oooooo..oooo..oooo..oooooo.";
    map += L".o..........o..o..........o.";
    map += L".o..........o..o..........o.";
    map += L".oooooooooooooooooooooooooo.";
    map += L"............................";*/

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

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    std::unique_ptr<SDL_Window, SDLClear> window(SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN));

    if (!window)
    {
        SDL_Log("Unable to initialize SDL Window\n");
        return 1;
    }

    std::unique_ptr<SDL_Renderer, SDLClear> rend(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));

    if (!rend)
    {
        SDL_Log("Unable to initialize SDL Renderer \n");
        SDL_DestroyWindow(window.get());
        return 1;
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Font could not be loaded.");
        return 1;
    }

    SDL_SetRenderDrawBlendMode(rend.get(), SDL_BLENDMODE_NONE);

    TTF_Font *font = TTF_OpenFont("src/Aller_Rg.ttf", 30);

    Uint32 frameStart, frameTime;

    SDL_Surface *tmp = IMG_Load("src/assets/background.png");
    SDL_Texture *background = SDL_CreateTextureFromSurface(rend.get(), tmp);
    SDL_FreeSurface(tmp);
    SDL_Rect backgroundRec = {0, 3 * TILE_DIM, WINDOW_WIDTH, WINDOW_HEIGHT - 5 * TILE_DIM};

    int timers[] = {7, 20, 7, 20, 5, 20, 5}; // Int array for measuring scatter and chase phases
    float elapsed = timers[0];

    float frightTime = 6000; // Time that ghosts stay frightened for after change of state in ms

    float compTime = 0;

    int index = 1;
    bool phase = false; // true = scatter phase

    bool quit = false;
    SDL_Event event;

    Player *pacMan = new Player();

    Ghost *ghosts[4] = {new Ghost(0, 13.0f, 11.0f, 1, 0.1f, {25, -4}, {255, 0, 0, 0}),     // Blinky
                        new Ghost(2, 13.0f, 11.0f, 1, 0.1f, {27, 31}, {0, 255, 255, 0}),   // Inky
                        new Ghost(3, 13.0f, 11.0f, 1, 0.1f, {0, 31}, {255, 184, 82, 0}),   // Clyde
                        new Ghost(1, 13.0f, 11.0f, 1, 0.1f, {2, -4}, {255, 184, 255, 0})}; // Pinky

    // ------------------------------------------------------------------------------------------
    // ---------------------------- GAME LOOP ---------------------------------------------------
    // ------------------------------------------------------------------------------------------

    int temp = 1;

    while (!quit)
    {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend.get(), 0, 0, 0, 255);
        SDL_RenderClear(rend.get());

        SDL_RenderCopy(rend.get(), background, nullptr, &backgroundRec);

        // DrawGrid(rend.get());

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

                default:
                    break;
                }

                break;

            default:
                break;
            }
        }

        if (pacMan->Update(map) == 1)
        {
            for (Ghost *ghost : ghosts)
            {
                ghost->SetState(2);
                ghost->SetSpeed(0.05f);
            }
            elapsed += 6000;
        }

        for (Ghost *ghost : ghosts)
            ghost->Update(map, pacMan->GetX(), pacMan->GetY(), pacMan->GetDirection(), ghosts[0]->GetX(), ghosts[0]->GetY());

        DrawDots(rend.get(), map);

        SDL_Rect player = {-5 + pacMan->GetX() * TILE_DIM, -5 + 3 * TILE_DIM + pacMan->GetY() * TILE_DIM, ENTITY_DIM, ENTITY_DIM};
        SDL_SetRenderDrawColor(rend.get(), 255, 255, 0, 255);
        SDL_RenderFillRect(rend.get(), &player);

        for (Ghost *ghost : ghosts)
            DrawGhost(rend.get(), ghost);

        for (Ghost *ghost : ghosts)
        {
            SDL_Rect blink = {10 + ghost->GetChaseTile().first * TILE_DIM, 10 + 3 * TILE_DIM + ghost->GetChaseTile().second * TILE_DIM, 20, 20};
            SDL_SetRenderDrawColor(rend.get(), ghost->GetColor().r, ghost->GetColor().g, ghost->GetColor().b, ghost->GetColor().a);
            SDL_RenderFillRect(rend.get(), &blink);
        }

        SDL_SetRenderDrawColor(rend.get(), 0, 0, 0, 0);

        SDL_RenderPresent(rend.get());

        // std::cout << "[X, Y] = [" << pacMan->GetX() << ", " << pacMan->GetY() << "]" << std::endl;

        if (((float)SDL_GetTicks() / 1000.0f) > elapsed && index < 7)
        {

            std::cout << ((float)SDL_GetTicks() / 1000.0f) << std::endl;

            std::cout << (phase ? "Scatter" : "Chase") << std::endl;

            elapsed = SDL_GetTicks() * 1000.0f + timers[index++];

            for (Ghost *ghost : ghosts)
                ghost->SetState((phase ? 0 : 1));
            phase = !phase;
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
    }

    // ------------------------------------------------------------------------------------------
    // ---------------------------- END OF GAME LOOP --------------------------------------------
    // ------------------------------------------------------------------------------------------

    std::cout << "Game Over !\nYour score is: " << pacMan->GetScore() << std::endl;

    SDL_DestroyTexture(background);
    SDL_Quit();

    return 0;
}

void DrawGrid(SDL_Renderer *rend)
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

void DrawDots(SDL_Renderer *rend, char map[31][29])
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

void DrawGhost(SDL_Renderer *rend, Ghost *ghost)
{
    SDL_Rect blink = {-5 + ghost->GetX() * TILE_DIM, -5 + 3 * TILE_DIM + ghost->GetY() * TILE_DIM, ENTITY_DIM, ENTITY_DIM};
    SDL_SetRenderDrawColor(rend, ghost->GetColor().r, ghost->GetColor().g, ghost->GetColor().b, ghost->GetColor().a);
    SDL_RenderFillRect(rend, &blink);
}
