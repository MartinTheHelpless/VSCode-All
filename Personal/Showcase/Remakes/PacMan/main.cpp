#include <memory>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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
        "......o..e....g...e..o......",
        "......o..e....e...e..o......",
        "eeeeeeoeee....e...eeeoeeeeee",
        "......o..e....e...e..o......",
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

int DrawDots();

void DrawPlayer();

void DrawGhosts();

void DrawGhostChaseTargets();

void CheckCollisions(bool &quit);

int main(int argc, char const *argv[])
{

    if (!Init())
        return 1;

    font = TTF_OpenFont("src/Aller_Rg.ttf", 30);

    SDL_Color fontColor = {255, 255, 255, 0};

    SDL_Surface *tmp = IMG_Load("src/assets/Background.png");
    background = SDL_CreateTextureFromSurface(rend, tmp);
    SDL_Rect backgroundRec = {0, 3 * TILE_DIM, WINDOW_WIDTH, WINDOW_HEIGHT - 5 * TILE_DIM};
    SDL_FreeSurface(tmp);

    pacMan = new Player();

    // (id, x, y, direction, speed, x and y scatter target, color) color will be removed with sprite addition

    ghosts[0] = new Ghost(0, 14.0f, 14.0f, 0, 2, {25, -4}, {255, 0, 0, 0});    // Blinky
    ghosts[1] = new Ghost(2, 14.0f, 14.0f, 0, 2, {27, 31}, {0, 255, 255, 0});  // Inky
    ghosts[2] = new Ghost(3, 14.0f, 14.0f, 0, 2, {0, 31}, {255, 184, 82, 0});  // Clyde
    ghosts[3] = new Ghost(1, 14.0f, 14.0f, 0, 2, {2, -4}, {255, 184, 255, 0}); // Pinky

    Uint32 frameStart, frameTime;

    bool blink = false, pink = false, ink = false, cly = false;

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {

        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, background, nullptr, &backgroundRec);

        // DrawGrid();

        if (DrawDots() <= 0)
            quit = true;

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

                case SDLK_1:
                {
                    blink = !blink;
                    break;
                }

                case SDLK_2:
                {
                    ink = !ink;
                    break;
                }

                case SDLK_3:
                {
                    pink = !pink;
                    break;
                }

                case SDLK_4:
                {
                    cly = !cly;
                    break;
                }

                case SDLK_SPACE:
                {
                    /*for (Ghost *ghost : ghosts)
                        ghost->SetState(1);*/

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
            for (Ghost *ghost : ghosts)
                if ((int(ghost->GetX()) > 17 || int(ghost->GetX()) < 10 || int(ghost->GetY()) > 16 || int(ghost->GetY()) < 12) && ghost->GetState() != 3)
                    ghost->SetState(2);

        Uint32 ticks = SDL_GetTicks();

        for (Ghost *ghost : ghosts)
            ghost->Update(map, pacMan->GetX(), pacMan->GetY(), pacMan->GetDirection(), ghosts[0]->GetX(), ghosts[0]->GetY(), ticks);

        CheckCollisions(quit);

        DrawGhosts();
        // DrawGhostChaseTargets();
        DrawPlayer();

        /*
        std::cout << pacMan->GetX() << " | " << pacMan->GetY() << std::endl;
        std::cout << ghosts[0]->GetX() << " | " << ghosts[0]->GetY() << std::endl;
        std::cout << "State: " << ghosts[0]->GetState() << " | Direction: " << ghosts[0]->GetDirection() << std::endl;
        std::cout << SDL_GetTicks() / 1000.0f << std::endl;
        */

        blink ? std::cout << "X: " << ghosts[0]->GetX() << " | Y: " << ghosts[0]->GetY() << std::endl : std::cout << "";
        ink ? std::cout << "X: " << ghosts[1]->GetX() << " | Y: " << ghosts[1]->GetY() << std::endl : std::cout << "";
        pink ? std::cout << "X: " << ghosts[2]->GetX() << " | Y: " << ghosts[2]->GetY() << std::endl : std::cout << "";
        cly ? std::cout << "X: " << ghosts[3]->GetX() << " | Y: " << ghosts[3]->GetY() << std::endl : std::cout << "";

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

int DrawDots()
{

    int dotCount = 0;

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    for (int i = 0; i < 31; i++)
        for (int j = 0; j < 28; j++)
            if (map[i][j] == 'o')
            {
                dotCount++;
                SDL_Rect rect = {j * TILE_DIM + TILE_DIM / 2 - 2, 3 * TILE_DIM + i * TILE_DIM + TILE_DIM / 2 - 2, 4, 4};
                SDL_RenderFillRect(rend, &rect);
            }
            else if (map[i][j] == 'x')
            {
                dotCount++;
                SDL_Rect rect = {j * TILE_DIM + TILE_DIM / 2 - 6, 3 * TILE_DIM + i * TILE_DIM + TILE_DIM / 2 - 4, 12, 12};
                SDL_RenderFillRect(rend, &rect);
            }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);

    return dotCount;
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

void DrawGhostChaseTargets()
{
    for (Ghost *ghost : ghosts)
    {
        SDL_Rect tmp = {int(ghost->GetChaseTile().first * TILE_DIM), 3 * TILE_DIM + int(ghost->GetChaseTile().second * TILE_DIM), ENTITY_DIM / 2, ENTITY_DIM / 2};
        SDL_SetRenderDrawColor(rend, ghost->GetColor().r, ghost->GetColor().g, ghost->GetColor().b, ghost->GetColor().a);
        SDL_RenderFillRect(rend, &tmp);
    }
}

void CheckCollisions(bool &quit)
{

    for (int i = 0; i < 4; i++)
    {

        float x = ghosts[i]->GetX() - pacMan->GetX();
        float y = ghosts[i]->GetY() - pacMan->GetY();

        if (sqrt(x * x + y * y) <= 1.0f && ghosts[i]->GetState() == 2)
            ghosts[i]->SetState(3);
        else if (sqrt(x * x + y * y) <= 1.0f && (ghosts[i]->GetState() == 1 || ghosts[i]->GetState() == 0))
            quit = true;
    }
}
