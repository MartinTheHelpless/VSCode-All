#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define windowWidth 700
#define windowHeight 450

#define jpgRows 10
#define jpgCols 18

#define topMargin 45

#define moleDelay 500

bool endGame = false;

int cols = 0;
int rows = 0;

int lifeTime = 4000;

void lose(SDL_Renderer *renderer)
{
    SDL_Surface *img = IMG_Load("srcFiles/background.jpg");
    SDL_Texture *back = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    SDL_Rect endScreen = {windowWidth / 2 - 120, windowHeight / 2 - 70, 240, 140};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderCopy(renderer, back, NULL, &endScreen);

    SDL_Rect quit = {windowWidth / 2 - 48, windowHeight / 2 - 45, 100, 40};

    SDL_Rect playAgain = {windowWidth / 2 - 110, windowHeight / 2 + 3, 220, 45};

    SDL_RenderPresent(renderer);

    SDL_Event ev;
    bool wait = true;
    while (wait)
    {
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                wait = false;
                endGame = true;
                break;

            case SDL_MOUSEBUTTONDOWN:

                SDL_Point mouse = {ev.button.x, ev.button.y};

                if (SDL_PointInRect(&mouse, &quit))
                {
                    wait = false;
                    endGame = true;
                    break;
                }
                else if (SDL_PointInRect(&mouse, &playAgain))
                {
                    wait = false;
                    break;
                }

            default:
                break;
            }
        }
    }
}

void staticDraw(SDL_Renderer *renderer, TTF_Font *Font, int score)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 0};

    // constantly same drawing :

    SDL_Rect pointTag = {windowWidth / 2 - 70, 2, 90, 40};
    SDL_Surface *txt = TTF_RenderText_Solid(Font, "Points : ", white);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, txt);
    SDL_FreeSurface(txt);

    SDL_RenderCopy(renderer, text, NULL, &pointTag);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    char scr[9];

    sprintf(scr, "%d", score);
    txt = TTF_RenderText_Solid(Font, scr, white);
    text = SDL_CreateTextureFromSurface(renderer, txt);
    SDL_FreeSurface(txt);

    SDL_Rect topBorder = {0, 42, windowWidth, 3};
    SDL_RenderFillRect(renderer, &topBorder);

    SDL_Rect txtRect = {0, 2, 0, 40};

    if (score < 10)
    {
        txtRect.x = windowWidth / 2 - 10 + 30;
        txtRect.w = 20;
    }
    else if (score < 100)
    {
        txtRect.x = windowWidth / 2 - 17 + 35;
        txtRect.w = 35;
    }
    else
    {
        txtRect.x = windowWidth / 2 - 27 + 50;
        txtRect.w = 55;
    }

    SDL_RenderCopy(renderer, text, NULL, &txtRect);
}

void game(SDL_Renderer *renderer, SDL_Surface *image)
{

    int start = 1;

    int score = 0;
    char scr[9];

    TTF_Font *Font = TTF_OpenFont("srcFiles/Sans.ttf", 23);

    SDL_Color white = {255, 255, 255, 0};

    SDL_Color green = {50, 186, 19, 0};

    bool play = true;

    int random = rand() % 10 + 1;

    int randomX = 0;
    int randomY = 0;
    int sizeX = 80;
    int sizeY = 80;
    char tmr[8];

    staticDraw(renderer, Font, score);
    SDL_RenderPresent(renderer);

    SDL_Delay(moleDelay);

    while (play)
    {
        float count = 4.0;

        count -= 0.1 * score;

        count <= 0.5 ? count = 0.5 : count;

        randomX = rand() % (windowWidth - 99);
        randomY = rand() % (windowHeight - 171) + 72;

        sizeX = rand() % (90 + 1 - 80) + 80;
        sizeY = rand() % (90 + 1 - 75) + 75;

        uint64_t counterStart = SDL_GetPerformanceCounter();

        uint64_t frequency = SDL_GetPerformanceFrequency();

        SDL_Event ev;
        bool quit = false;
        while (!quit)
        {

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

            SDL_RenderClear(renderer);

            // constantly same drawing :

            staticDraw(renderer, Font, score);

            // variable drawing :

            SDL_Rect timer = {randomX + sizeX / 2 - 30, randomY - 20, 60, 20};

            sprintf(tmr, "%.2f", count);
            SDL_Surface *txt = TTF_RenderText_Solid(Font, tmr, green);
            SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, txt);
            SDL_FreeSurface(txt);
            SDL_RenderCopy(renderer, text, NULL, &timer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

            SDL_Rect emote = {randomX, randomY, sizeX, sizeY};
            SDL_RenderFillRect(renderer, &emote);

            SDL_Texture *emt = SDL_CreateTextureFromSurface(renderer, image);

            SDL_Rect origin = {cols * 100 + 15, rows * 77, sizeX, sizeY};

            SDL_RenderCopyEx(renderer, emt, &origin, &emote, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(renderer);

            while (SDL_PollEvent(&ev))
            {
                switch (ev.type)
                {
                case SDL_QUIT:
                    quit = true;
                    play = false;
                    endGame = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (ev.button.x >= randomX && ev.button.x <= randomX + 80 && ev.button.y >= randomY && ev.button.y <= randomY + 80)
                    {

                        for (size_t i = 0; i < 40; i++)
                        {
                            SDL_RenderClear(renderer);
                            staticDraw(renderer, Font, score);

                            SDL_Rect a = {randomX - i, randomY - i, sizeX / 2, sizeY / 2};

                            SDL_Rect originA = {cols * 100 + 15, rows * 77, sizeX / 2, sizeY / 2};
                            SDL_RenderCopyEx(renderer, emt, &originA, &a, i*7, NULL, SDL_FLIP_NONE);

                            SDL_Rect b = {randomX + sizeX / 2 + i, randomY - i, sizeX / 2, sizeY / 2};

                            SDL_Rect originB = {cols * 100 + 15 + sizeX / 2, rows * 77, sizeX / 2, sizeY / 2};
                            SDL_RenderCopyEx(renderer, emt, &originB, &b, i*7, NULL, SDL_FLIP_NONE);

                            SDL_Rect c = {randomX - i, randomY + sizeY / 2 + i, sizeX / 2, sizeY / 2};

                            SDL_Rect originC = {cols * 100 + 15, rows * 77 + sizeY / 2, sizeX / 2, sizeY / 2};
                            SDL_RenderCopyEx(renderer, emt, &originC, &c, i*7, NULL, SDL_FLIP_NONE);

                            SDL_Rect d = {randomX + sizeX / 2 + i, randomY + sizeY / 2 + i, sizeX / 2, sizeY / 2};

                            SDL_Rect originD = {cols * 100 + 15 + sizeX / 2, rows * 77 + sizeY / 2, sizeX / 2, sizeY / 2};
                            SDL_RenderCopyEx(renderer, emt, &originD, &d, i*7, NULL, SDL_FLIP_NONE);

                            SDL_RenderPresent(renderer);
                        }

                        score += 1;
                        cols++;
                        quit = true;
                    }
                    break;

                default:
                    break;
                }
            }

            uint64_t counterEnd = SDL_GetPerformanceCounter();

            uint64_t elapsedTime = counterEnd - counterStart;

            counterStart = counterEnd;

            float a = elapsedTime;
            float b = frequency;
            float dTime = a / b;

            count -= dTime;

            if (count <= 0)
            {
                SDL_RenderClear(renderer);

                staticDraw(renderer, Font, score);

                count = 0;

                SDL_Rect origin = {cols * 100 + 15, rows * 77, sizeX, sizeY};

                SDL_RenderCopyEx(renderer, emt, &origin, &emote, 0, NULL, SDL_FLIP_NONE);

                sprintf(tmr, "%.2f", count);
                txt = TTF_RenderText_Solid(Font, tmr, green);
                text = SDL_CreateTextureFromSurface(renderer, txt);
                SDL_FreeSurface(txt);
                SDL_RenderCopy(renderer, text, NULL, &timer);
                SDL_RenderPresent(renderer);

                play = false;
                quit = true;
                lose(renderer);
                break;
            }
        }

        if (cols >= jpgCols)
        {
            cols = 0;
            rows++;
        }

        if (rows >= jpgRows)
        {
            rows = 0;
            cols = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Whack-a-Twitch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 450, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1)
    {
        printf("Font init failed.\n");
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *image = IMG_Load("srcFiles/emojipedia.jpg");

    while (!endGame)
    {
        game(renderer, image);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
