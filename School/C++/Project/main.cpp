#include <memory>
#include <iostream>
#include <SDL2/SDL.h>
#include "Maze.h"
#include "defines.h"

#ifdef main
#undef main
#endif

SDL_Window *window = nullptr;
SDL_Renderer *rend = nullptr;

bool Init();

void Close();

void DrawPathChoices(uint32_t choice);

int main(int argc, char const *argv[])
{

    Init();

    Maze *testMaze = new Maze();

    Uint32 frameStart, frameTime, pathMode = 0, lastState = 0;
    float scale = 60;

    bool quit = false, rButtonPressed = false, drawWall = true;
    SDL_Event event;

    while (!quit)
    {

        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 20, 20, 20, 255);
        SDL_RenderClear(rend);

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
            {
                quit = true;
                break;
            }

            case SDL_MOUSEWHEEL:
            {
                if (event.wheel.y > 0) // scroll up
                    scale - 1 < 15 ? scale = 15 : scale--;
                else if (event.wheel.y < 0) // scroll down
                    scale + 1 > 60 ? scale = 60 : scale++;
                break;
            }

            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_LCTRL)
                    drawWall = !drawWall;
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    for (int i = 0; i < 5; i++) // 5 pathfinding choices
                    {
                        SDL_Rect tmp = {660, 80 + i * 110, 100, 50};
                        if (mouseX >= tmp.x && mouseX < tmp.x + tmp.w &&
                            mouseY >= tmp.y && mouseY < tmp.y + tmp.h)
                        {
                            pathMode = i;
                            break;
                        }
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    rButtonPressed = true;
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                    testMaze->ClearMaze();

                break;
            }

            case SDL_MOUSEBUTTONUP:
            {

                if (event.button.button == SDL_BUTTON_RIGHT)
                    rButtonPressed = false;
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                    testMaze->ClearMaze();

                break;
            }

            default:
                break;
            }

            if (rButtonPressed)
            {

                float factor = 600.0f / scale;

                uint32_t x, y;

                if (event.button.x > 619)
                    x = 599 / factor;
                else if (event.button.x <= 21)
                    x = 1 / factor;
                else
                    x = (event.button.x - 20) / factor;

                if (event.button.y > 619)
                    y = 599 / factor;
                else if (event.button.y <= 21)
                    y = 1 / factor;
                else
                    y = (event.button.y - 20) / factor;

                y *= 60;

                testMaze->GetMazeNode(x + y)->m_Type = (drawWall ? 0 : 1);
            }
        }

        testMaze->DrawMaze(rend, scale);

        DrawPathChoices(pathMode);

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

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);
    SDL_SetWindowResizable(window, SDL_FALSE);

    return true;
}

void Close()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void DrawPathChoices(uint32_t choice)
{

    for (int i = 0; i < 5; i++) // 5 pathfinding choices
    {
        SDL_SetRenderDrawColor(rend, 30 + i * 30, i * 50, 10 + i * 10, 0);
        SDL_Rect tmp = {660, 80 + i * 110, 100, 50};
        SDL_RenderFillRect(rend, &tmp);
    }
}
