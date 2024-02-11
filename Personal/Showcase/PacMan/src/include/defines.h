#pragma once
#include <SDL2/SDL.h>

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int GAME_WIDTH = 28; // (28 : 36 tiles original Pac Man Game)
const int GAME_HEIGHT = 36;

const int TILE_DIM = 20;
const int ENTITY_DIM = 30;

const int WINDOW_WIDTH = GAME_WIDTH * TILE_DIM; // 3 : 4
const int WINDOW_HEIGHT = GAME_HEIGHT * TILE_DIM;

#define FLOAT_MAX 3.40282e+038

// --------------------------------------------------------------------------------------------
// ------------------- Smart pointer helper class (for deleting the objects) ------------------
// --------------------------------------------------------------------------------------------

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