#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <string>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

int sdlTest(SDL_Window *win, SDL_Renderer *rend)
{

    if (win == NULL || rend == NULL)
    {
        std::cout << "SDL initialization error.\n";
        return 1;
    }

    return 0;
}