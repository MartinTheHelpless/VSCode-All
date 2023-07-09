#include "components.c"

void endGame(SDL_Renderer *renderer);

void winGame(SDL_Renderer *renderer);

void settings(SDL_Renderer *renderer, SDL_Texture *background);

void drawMenu(SDL_Renderer *renderer, SDL_Texture *background);

void hallOfFame(SDL_Renderer *renderer, SDL_Texture *background, FILE *scrFile);

void gameItself(SDL_Renderer *renderer, SDL_Texture *background, FILE *scrFile, int rNum, FILE *level);