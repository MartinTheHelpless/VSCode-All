#include <memory>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Maze.h"
#include "defines.h"

#ifdef main
#undef main
#endif

SDL_Window *window = nullptr;
SDL_Renderer *rend = nullptr;
TTF_Font *font;

SDL_Texture *ButtonTexts[5];

bool Init();

void Close();

void DrawPathChoices(uint32_t path, uint32_t maze);

int main(int argc, char const *argv[])
{

    Init();

    int index = 0;

    float mazeScale = 59;

    Maze *testMaze = new Maze(mazeScale);

    testMaze->RandomizeMaze(0, mazeScale);

    Uint32 frameStart, frameTime, mazeChoice = 0, pathMode = 0, lastState = 0;

    bool quit = false, rButtonPressed = false, drawWall = false, finding = false;
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
                if (event.wheel.y > 0 && !finding) // scroll up
                    mazeScale - 2 < 15 ? mazeScale = 15 : mazeScale -= 2, testMaze->ClearMaze(mazeScale), testMaze->RandomizeMaze(mazeChoice, mazeScale);

                else if (event.wheel.y < 0 && !finding) // scroll down
                    mazeScale + 2 > 59 ? mazeScale = 59 : mazeScale += 2, testMaze->ClearMaze(mazeScale), testMaze->RandomizeMaze(mazeChoice, mazeScale);

                break;
            }

            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_LCTRL && !finding)
                    drawWall = !drawWall;
                else if (event.key.keysym.sym == SDLK_r && !finding)
                    testMaze->ClearMaze(mazeScale), testMaze->RandomizeMaze(mazeChoice, mazeScale);
                else if (event.key.keysym.sym == SDLK_SPACE && !finding)
                    testMaze->ResetPath(mazeScale), finding = true;
                else if (event.key.keysym.sym == SDLK_t && !finding)
                    testMaze->ResetPath(mazeScale);

                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.button == SDL_BUTTON_LEFT && !finding)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    for (int i = 0; i < 5; i++) // 5 pathfinding choices
                    {
                        if (i == 2)
                            continue;

                        SDL_Rect tmp = {660, 80 + i * 110, 100, 50};
                        if (mouseX >= tmp.x && mouseX < tmp.x + tmp.w &&
                            mouseY >= tmp.y && mouseY < tmp.y + tmp.h)
                        {
                            if (i > 2)
                                mazeChoice = i % 3, testMaze->RandomizeMaze(mazeChoice, mazeScale);
                            else
                                pathMode = i;

                            break;
                        }
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT && !finding)
                    rButtonPressed = true;
                else if (event.button.button == SDL_BUTTON_MIDDLE && !finding)
                    testMaze->ClearMaze(mazeScale);

                break;
            }

            case SDL_MOUSEBUTTONUP:
            {

                if (event.button.button == SDL_BUTTON_RIGHT && !finding)
                    rButtonPressed = false;
                else if (event.button.button == SDL_BUTTON_MIDDLE && !finding)
                    testMaze->ClearMaze(mazeScale);

                break;
            }

            default:
                break;
            }

            if (rButtonPressed)
            {

                float factor = 600.0f / mazeScale;

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

                y *= 59;

                if (testMaze->GetMazeNode(x + y)->m_Type < 2)
                    testMaze->GetMazeNode(x + y)->m_Type = (drawWall ? 0 : 1);
            }
        }

        if (finding)
            finding = !testMaze->PathFind(pathMode, mazeScale);

        testMaze->DrawMaze(rend, mazeScale);

        DrawPathChoices(pathMode, mazeChoice);

        SDL_RenderPresent(rend);
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
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    font = TTF_OpenFont("src/Aller_Rg.ttf", 30);
    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);
    SDL_SetWindowResizable(window, SDL_FALSE);

    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface *tmp_Surface = TTF_RenderText_Blended(font, "DFS Alg.", white);
    ButtonTexts[0] = SDL_CreateTextureFromSurface(rend, tmp_Surface);

    tmp_Surface = TTF_RenderText_Blended(font, "BFS Alg.", white);
    ButtonTexts[1] = SDL_CreateTextureFromSurface(rend, tmp_Surface);

    tmp_Surface = TTF_RenderText_Blended(font, "-------", white);
    ButtonTexts[2] = SDL_CreateTextureFromSurface(rend, tmp_Surface);

    tmp_Surface = TTF_RenderText_Blended(font, "Prim Maze", white);
    ButtonTexts[3] = SDL_CreateTextureFromSurface(rend, tmp_Surface);

    tmp_Surface = TTF_RenderText_Blended(font, "Kruskal Maze", white);
    ButtonTexts[4] = SDL_CreateTextureFromSurface(rend, tmp_Surface);

    SDL_FreeSurface(tmp_Surface);
    return true;
}

void Close()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);

    for (SDL_Texture *text : ButtonTexts)
        SDL_DestroyTexture(text);

    SDL_Quit();
}

void DrawPathChoices(uint32_t path, uint32_t maze)
{

    for (int i = 0; i < 5; i++) // 5 pathfinding choices
    {
        if (i == path || i == maze + 3)
        {
            SDL_SetRenderDrawColor(rend, 97, 43, 0, 0);
            SDL_Rect tmp = {660, 80 + i * 110, 100, 50};
            SDL_RenderFillRect(rend, &tmp);

            tmp = {670, 90 + i * 110, 80, 30};
            SDL_RenderCopy(rend, ButtonTexts[i], nullptr, &tmp);
        }
        else
        {
            SDL_SetRenderDrawColor(rend, 230, 103, 0, 0);
            SDL_Rect tmp = {660, 80 + i * 110, 100, 50};
            SDL_RenderFillRect(rend, &tmp);

            tmp = {670, 90 + i * 110, 80, 30};
            SDL_RenderCopy(rend, ButtonTexts[i], nullptr, &tmp);
        }
    }
}
