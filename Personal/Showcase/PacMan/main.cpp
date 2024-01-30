#include <stdbool.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#ifdef main
#undef main
#endif

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int BOARD_WIDTH = 28; // (28 : 36 tiles original Pac Man Game)
const int BOARD_HEIGHT = 36;

const int WINDOW_WIDTH = BOARD_WIDTH * 20; // 3 : 4
const int WINDOW_HEIGHT = BOARD_HEIGHT * 20;

int main(int argc, char const *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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

    if (TTF_Init() != 0)
    {
        SDL_Log("Font could not be loaded.");
        return 1;
    }

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);

    TTF_Font *font = TTF_OpenFont("src/Aller_Rg.ttf", 30);

    SDL_Color fontColor = {255, 255, 255};

    Uint32 frameStart, frameTime;

    bool quit = false;
    SDL_Event event;

    // ------------------------------------------------------------------------------------------
    // ---------------------------- GAME LOOP ---------------------------------------------------
    // ------------------------------------------------------------------------------------------

    while (!quit)
    {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

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
                case SDLK_a:
                {

                    break;
                }

                case SDLK_d:
                {

                    break;
                }

                case SDLK_q:
                {

                    break;
                }

                case SDLK_e:
                {

                    break;
                }

                case SDLK_s:
                {
                    break;
                }

                case SDLK_SPACE:
                {
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

        SDL_RenderPresent(rend);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
    }

    // ------------------------------------------------------------------------------------------
    // ---------------------------- END OF GAME LOOP --------------------------------------------
    // ------------------------------------------------------------------------------------------

    // std::cout << "Game Over !\nYour score is: " << score << std::endl;

    SDL_Quit();

    return 0;
}
