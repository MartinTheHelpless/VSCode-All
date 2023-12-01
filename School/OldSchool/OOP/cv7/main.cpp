#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "Player.cpp"

int WIN_HEIGHT;
int WIN_WIDTH;

void textLoad(SDL_Renderer *rend, SDL_Texture **temp, TTF_Font **font, SDL_Color color, std::string text);

int menu(SDL_Window *window, SDL_Renderer *rend);

int game(SDL_Window *window, SDL_Renderer *rend, Player *p);

int settings(SDL_Window *window, SDL_Renderer *rend, Player *p);

int upgrades(SDL_Window *window, SDL_Renderer *rend, Player *p);

int main(int argc, char const *argv[])
{

    Player *p = new Player("Player 1");
    p->setBasePos(200, 200);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Random Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN && SDL_WINDOW_FULLSCREEN);

    SDL_GetWindowSize(window, &WIN_WIDTH, &WIN_HEIGHT);

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED & SDL_RENDERER_PRESENTVSYNC);

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        return 1;
    }

    int draw = 0;

    while (draw != 4)
    {
        switch (draw)
        {
        case 0: // Main menu
            draw = menu(window, rend);
            break;

        case 1: // Game
            draw = game(window, rend, p);
            break;

        case 2: // Main menu
            draw = settings(window, rend, p);
            break;

        case 3: // Main menu
            draw = upgrades(window, rend, p);
            break;

        default:
            draw = 0;
            break;
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void textLoad(SDL_Renderer *rend, SDL_Texture **temp, TTF_Font **font, SDL_Color color, std::string text)
{

    SDL_Surface *surf = TTF_RenderText_Solid(*font, text.c_str(), color);

    *temp = SDL_CreateTextureFromSurface(rend, surf);

    SDL_FreeSurface(surf);
}

int menu(SDL_Window *window, SDL_Renderer *rend)
{

    SDL_Color black = {0, 0, 0, 0};

    SDL_Color white = {255, 255, 255, 0};

    SDL_Color orange = {217, 112, 0, 0};

    TTF_Font *basic = TTF_OpenFont("Other/TTFonts/JuicySteak.ttf", 50);

    TTF_Font *title = TTF_OpenFont("Other/TTFonts/JuicySteak.ttf", 80);

    int menuOptions = 4;

    SDL_Rect settRect[menuOptions];

    SDL_Color mainColor[menuOptions] = {white, white, white, white};

    for (int i = 0; i < menuOptions; i++)
        settRect[i] = {WIN_WIDTH / 2 - 140, WIN_HEIGHT / 3 + i * 130, 280, 110};

    SDL_Rect titleR = {WIN_WIDTH / 2 - 275, WIN_HEIGHT / 3 - 220, 550, 200};

    SDL_Texture *uni;

    SDL_Event ev;
    while (1)
    {

        textLoad(rend, &uni, &title, white, "Main Menu");
        SDL_RenderCopy(rend, uni, NULL, &titleR);
        SDL_DestroyTexture(uni);
        for (int i = 0; i < menuOptions; i++)
        {
            textLoad(rend, &uni, &basic, mainColor[i], i == 0 ? "Play Game" : i == 1 ? "upgrades"
                                                                          : i == 2   ? "Settings"
                                                                                     : "Quit Game");
            SDL_RenderCopy(rend, uni, NULL, &settRect[i]);
            SDL_DestroyTexture(uni);
        }

        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                TTF_CloseFont(basic);
                TTF_CloseFont(title);
                return 4;
                break;

            case SDL_MOUSEBUTTONDOWN:

                SDL_Point mouse;

                SDL_GetMouseState(&mouse.x, &mouse.y);

                if (SDL_PointInRect(&mouse, &settRect[0]))
                {
                    TTF_CloseFont(basic);
                    TTF_CloseFont(title);
                    return 1;
                }
                else if (SDL_PointInRect(&mouse, &settRect[1]))
                {
                    TTF_CloseFont(basic);
                    TTF_CloseFont(title);
                    return 2;
                }
                else if (SDL_PointInRect(&mouse, &settRect[2]))
                {
                    TTF_CloseFont(basic);
                    TTF_CloseFont(title);
                    return 3;
                }
                else if (SDL_PointInRect(&mouse, &settRect[3]))
                {
                    TTF_CloseFont(basic);
                    TTF_CloseFont(title);
                    return 4;
                }
                break;

            case SDL_MOUSEMOTION:

                SDL_GetMouseState(&mouse.x, &mouse.y);

                if (SDL_PointInRect(&mouse, &settRect[0]))
                    mainColor[0] = orange;
                else
                    mainColor[0] = white;

                if (SDL_PointInRect(&mouse, &settRect[1]))
                    mainColor[1] = orange;
                else
                    mainColor[1] = white;

                if (SDL_PointInRect(&mouse, &settRect[2]))
                    mainColor[2] = orange;
                else
                    mainColor[2] = white;

                if (SDL_PointInRect(&mouse, &settRect[3]))
                    mainColor[3] = orange;
                else
                    mainColor[3] = white;

                break;

            default:
                break;
            }
        }

        SDL_RenderPresent(rend);
    }
    return 0;
}

int game(SDL_Window *window, SDL_Renderer *rend, Player *p)
{

    SDL_Event ev;
    while (true)
    {
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                return 4;
                break;

            default:
                break;
            }
        }
    }

    return 0;
}

int settings(SDL_Window *window, SDL_Renderer *rend, Player *p)
{
    return 0;
}

int upgrades(SDL_Window *window, SDL_Renderer *rend, Player *p)
{
    return 0;
}
