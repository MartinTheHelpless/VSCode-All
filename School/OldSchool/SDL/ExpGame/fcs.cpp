#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

void txtLoad(SDL_Renderer *rend, SDL_Texture **temp, std::string img)
{

    SDL_Surface *surf = IMG_Load(img.c_str());

    *temp = SDL_CreateTextureFromSurface(rend, surf);

    SDL_FreeSurface(surf);
}

void textLoad(SDL_Renderer *rend, SDL_Texture **temp, TTF_Font **font, SDL_Color color, std::string text)
{

    SDL_Surface *surf = TTF_RenderText_Solid(*font, text.c_str(), color);

    *temp = SDL_CreateTextureFromSurface(rend, surf);

    SDL_FreeSurface(surf);
}
