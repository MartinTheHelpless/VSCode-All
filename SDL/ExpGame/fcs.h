#include "fcs.cpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

void txtLoad(SDL_Renderer *rend, SDL_Texture **txt, std::string img);

void textLoad(SDL_Renderer *rend, SDL_Texture **temp, TTF_Font **font, SDL_Color color, std::string text);