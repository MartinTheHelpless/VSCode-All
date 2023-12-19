#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#ifdef main
#undef main
#endif

const int WINDOW_DIM = 720;

const int BOARD_DIM = 8;

struct piece
{
    char type;
    int boardX;
    int boardY;
};

void drawBoard(SDL_Renderer *rend);

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to init SDL Video.");
        return 1;
    }

    SDL_Window *window;

    SDL_Renderer *rend;

    if (SDL_CreateWindowAndRenderer(WINDOW_DIM, WINDOW_DIM, SDL_WINDOW_SHOWN, &window, &rend) != 0)
    {
        SDL_Log("Could not initiate window and renderer");
        return 1;
    }

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderClear(rend);

        drawBoard(rend);

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
            }

        SDL_RenderPresent(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void drawBoard(SDL_Renderer *rend)
{

    int xy = WINDOW_DIM / BOARD_DIM;

    for (int i = 0; i < BOARD_DIM; i++)
        for (int j = 0; j < BOARD_DIM; j++)
        {
            SDL_Rect rect = {j * xy, i * xy, xy, xy};
            (i + j) % 2 == 0 ? SDL_SetRenderDrawColor(rend, 220, 220, 220, 0) : SDL_SetRenderDrawColor(rend, 87, 125, 49, 0);
            SDL_RenderFillRect(rend, &rect);
        }
}