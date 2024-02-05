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

bool Init();

void Close();

int main(int argc, char const *argv[])
{

    if (!Init())
        return -1;

    font = TTF_OpenFont("src/Aller_Rg.ttf", 30);

    SDL_Surface *tmp = IMG_Load("src/assets/background.png");
    background = SDL_CreateTextureFromSurface(rend, tmp);
    SDL_Rect backgroundRec = {0, 3 * TILE_DIM, WINDOW_WIDTH, WINDOW_HEIGHT - 5 * TILE_DIM};
    SDL_FreeSurface(tmp);

    pacMan = new Player();

    ghosts[0] = new Ghost(0, 13.0f, 11.0f, 1, 0.1f, {25, -4}, {255, 0, 0, 0});    // Blinky
    ghosts[1] = new Ghost(2, 13.0f, 11.0f, 1, 0.1f, {27, 31}, {0, 255, 255, 0});  // Inky
    ghosts[2] = new Ghost(3, 13.0f, 11.0f, 1, 0.1f, {0, 31}, {255, 184, 82, 0});  // Clyde
    ghosts[3] = new Ghost(1, 13.0f, 11.0f, 1, 0.1f, {2, -4}, {255, 184, 255, 0}); // Pinky

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        /* code */
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
