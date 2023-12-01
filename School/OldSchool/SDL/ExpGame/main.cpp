#include <iostream>
#include <vector>

#include "fcs.cpp"

#define WIN_HEIGHT 685
#define WIN_WIDTH 980
static int avatarPick = 0;

class player
{
    int avatar = 0; // Avatar 0 to 4 as there is 5 characters to choose from.
};

int mainMenu(SDL_Window *window, SDL_Renderer *rend, TTF_Font *basic, TTF_Font *titleF);

int game(SDL_Window *window, SDL_Renderer *rend, TTF_Font *basic, TTF_Font *title);

int settings(SDL_Window *window, SDL_Renderer *rend, TTF_Font *basic, TTF_Font *title);

int hof(SDL_Window *window, SDL_Renderer *rend, TTF_Font *basic, TTF_Font *title);

int main(int argc, char const *argv[])
{

    int avatarPick = 0;

    int change = 0;

    /*-----------------------SDL Preparation-----------------------------*/

    SDL_Init(SDL_INIT_EVERYTHING && SDL_INIT_TIMER);

    SDL_Window *window = SDL_CreateWindow("Random Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT - 6, SDL_WINDOW_SHOWN);

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED & SDL_RENDERER_PRESENTVSYNC);

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        return 1;
    }

    TTF_Font *basic = TTF_OpenFont("Other/TTFonts/JuicySteak.ttf", 50);

    TTF_Font *title = TTF_OpenFont("Other/TTFonts/JuicySteak.ttf", 80);

    TTF_SetFontOutline(title, 5);

    if (basic == NULL || title == NULL)
    {
        std::cout << "Font could not be loaded." << std::endl;
        return 1;
    }

    if (window == NULL)
    {
        std::cout << "Window could not be rendered." << std::endl;
        return 1;
    }

    if (rend == NULL)
    {
        std::cout << "renderer could not be initiated." << std::endl;
        return 1;
    }

    /*-----------------------SDL Preparation-----------------------------*/

    SDL_RenderClear(rend);

    for (int i = 0; i < 1; i)
    {
        switch (change)
        {
        case 0:
            // desired function (Main Menu here)
            change = mainMenu(window, rend, basic, title);

            break;

        case 1:
            // desired function (Game)
            change = game(window, rend, basic, title);

            break;

        case 2:
            // desired function (Settings)
            change = settings(window, rend, basic, title);

            break;

        case 3:
            // desired function (Hall of Fame)
            change = hof(window, rend, basic, title);

            break;

        case 4:
            // desired function (exit case here)
            i++;
            break;

        default:
            break;
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    TTF_CloseFont(basic);
    TTF_CloseFont(title);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

int mainMenu(SDL_Window *window, SDL_Renderer *rend, TTF_Font *basic, TTF_Font *titleF)
{

    const char *menuOptions[4] = {"Play Game", "Settings", "Hall of Fame", "Quit Game"};

    SDL_Texture *background;
    txtLoad(rend, &background, "Other/Images/Background.png");

    SDL_Color orangeMenu = {227, 129, 0, 0};

    SDL_Color redMenu = {227, 34, 0, 0};

    SDL_Rect title = {270, 90, 450, 120};

    SDL_Rect rectGame = {380, 227, 240, 70};
    SDL_Rect rectSett = {380, 307, 240, 70};
    SDL_Rect rectHoF = {380, 387, 240, 70};
    SDL_Rect rectQuit = {380, 467, 240, 70};

    int highlight = 1;

    SDL_Event ev;
    while (1)
    {

        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                SDL_DestroyTexture(background);
                return 4;
                break;
            }
            else if (ev.type == SDL_KEYDOWN)
            {
                if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w)
                {
                    highlight--;
                    highlight < 1 ? highlight = 4 : highlight;
                }
                else if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s)
                {
                    highlight++;
                    highlight > 4 ? highlight = 1 : highlight;
                }
                else if (ev.key.keysym.sym == SDLK_RETURN)
                {
                    SDL_DestroyTexture(background);
                    return highlight;
                }
            }
            else if (ev.type == SDL_MOUSEMOTION)
            {
                int posX;
                int posY;

                SDL_GetMouseState(&posX, &posY);

                const SDL_Point mouse = {posX, posY};

                if (SDL_PointInRect(&mouse, &rectGame))
                {
                    highlight = 1;
                }
                else if (SDL_PointInRect(&mouse, &rectSett))
                {
                    highlight = 2;
                }
                else if (SDL_PointInRect(&mouse, &rectHoF))
                {
                    highlight = 3;
                }
                else if (SDL_PointInRect(&mouse, &rectQuit))
                {
                    highlight = 4;
                }
            }
            else if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                int posX;
                int posY;

                SDL_GetMouseState(&posX, &posY);

                const SDL_Point mouse = {posX, posY};

                if (SDL_PointInRect(&mouse, &rectGame))
                {
                    highlight = 1;
                    SDL_DestroyTexture(background);
                    return highlight;
                }
                else if (SDL_PointInRect(&mouse, &rectSett))
                {
                    highlight = 2;
                    SDL_DestroyTexture(background);
                    return highlight;
                }
                else if (SDL_PointInRect(&mouse, &rectHoF))
                {
                    highlight = 3;
                    SDL_DestroyTexture(background);
                    return highlight;
                }
                else if (SDL_PointInRect(&mouse, &rectQuit))
                {
                    highlight = 4;
                    SDL_DestroyTexture(background);
                    return highlight;
                }
            }

            SDL_RenderCopy(rend, background, NULL, NULL);

            SDL_Texture *titl;
            textLoad(rend, &titl, &titleF, {36, 87, 0, 0}, "The Forest Run");
            SDL_RenderCopy(rend, titl, NULL, &title);
            SDL_DestroyTexture(titl);

            for (int i = 0; i < 4; i++)
            {

                SDL_Rect multiRect = {380, 227 + i * 80, 240, 70};
                SDL_Texture *temp;
                textLoad(rend, &temp, &basic, highlight == i + 1 ? redMenu : orangeMenu, menuOptions[i]);

                SDL_RenderCopy(rend, temp, NULL, &multiRect);
                SDL_DestroyTexture(temp);
            }

            SDL_RenderPresent(rend);
        }
    }
    return 0;
}

int game(SDL_Window *window, SDL_Renderer *rend, TTF_Font *basic, TTF_Font *title)
{
    SDL_RenderClear(rend);

    SDL_Surface *uni;

    int lowestHeight = 535;

    SDL_Rect ground = {0, 535, WIN_WIDTH, 285};

    SDL_Rect menuRect = {43, 605, 120, 55};

    SDL_Color white = {255, 255, 255, 0};

    SDL_Color red = {227, 34, 0, 0};

    SDL_Rect res;

    int spriteX = 300;
    int spriteY = lowestHeight;

    SDL_Rect sRect = {spriteX, spriteY, 96, 115};

    int spriteSpeed = 60;

    SDL_Texture *sIdle[4];
    SDL_Texture *sRunL[4];
    SDL_Texture *sRunR[4];

    SDL_Texture *background;
    txtLoad(rend, &background, "Other/Images/backgroundGame.png");

    switch (avatarPick)
    {
    case 0:
        txtLoad(rend, &sIdle[0], "Other/Sprites/DuckSDL/idle_0.png");
        txtLoad(rend, &sIdle[1], "Other/Sprites/DuckSDL/idle_1.png");
        txtLoad(rend, &sIdle[2], "Other/Sprites/DuckSDL/idle_2.png");
        txtLoad(rend, &sIdle[3], "Other/Sprites/DuckSDL/idle_3.png");
        txtLoad(rend, &sRunR[0], "Other/Sprites/DuckSDL/run_0.png");
        txtLoad(rend, &sRunR[1], "Other/Sprites/DuckSDL/run_1.png");
        txtLoad(rend, &sRunR[2], "Other/Sprites/DuckSDL/run_2.png");
        txtLoad(rend, &sRunR[3], "Other/Sprites/DuckSDL/run_3.png");
        txtLoad(rend, &sRunL[0], "Other/Sprites/DuckSDL/rn_0.png");
        txtLoad(rend, &sRunL[1], "Other/Sprites/DuckSDL/rn_1.png");
        txtLoad(rend, &sRunL[2], "Other/Sprites/DuckSDL/rn_2.png");
        txtLoad(rend, &sRunL[3], "Other/Sprites/DuckSDL/rn_3.png");
        break;

    case 1:
        txtLoad(rend, &sIdle[0], "Other/Sprites/PirateSDL/idle_0.png");
        txtLoad(rend, &sIdle[1], "Other/Sprites/PirateSDL/idle_1.png");
        txtLoad(rend, &sIdle[2], "Other/Sprites/PirateSDL/idle_2.png");
        txtLoad(rend, &sIdle[3], "Other/Sprites/PirateSDL/idle_3.png");
        txtLoad(rend, &sRunR[0], "Other/Sprites/PirateSDL/run_0.png");
        txtLoad(rend, &sRunR[1], "Other/Sprites/PirateSDL/run_1.png");
        txtLoad(rend, &sRunR[2], "Other/Sprites/PirateSDL/run_2.png");
        txtLoad(rend, &sRunR[3], "Other/Sprites/PirateSDL/run_3.png");
        txtLoad(rend, &sRunL[0], "Other/Sprites/PirateSDL/rn_0.png");
        txtLoad(rend, &sRunL[1], "Other/Sprites/PirateSDL/rn_1.png");
        txtLoad(rend, &sRunL[2], "Other/Sprites/PirateSDL/rn_2.png");
        txtLoad(rend, &sRunL[3], "Other/Sprites/PirateSDL/rn_3.png");
        break;

    case 2:
        txtLoad(rend, &sIdle[0], "Other/Sprites/ShamanSDL/idle_0.png");
        txtLoad(rend, &sIdle[1], "Other/Sprites/ShamanSDL/idle_1.png");
        txtLoad(rend, &sIdle[2], "Other/Sprites/ShamanSDL/idle_2.png");
        txtLoad(rend, &sIdle[3], "Other/Sprites/ShamanSDL/idle_3.png");
        txtLoad(rend, &sRunR[0], "Other/Sprites/ShamanSDL/run_0.png");
        txtLoad(rend, &sRunR[1], "Other/Sprites/ShamanSDL/run_1.png");
        txtLoad(rend, &sRunR[2], "Other/Sprites/ShamanSDL/run_2.png");
        txtLoad(rend, &sRunR[3], "Other/Sprites/ShamanSDL/run_3.png");
        txtLoad(rend, &sRunL[0], "Other/Sprites/ShamanSDL/rn_0.png");
        txtLoad(rend, &sRunL[1], "Other/Sprites/ShamanSDL/rn_1.png");
        txtLoad(rend, &sRunL[2], "Other/Sprites/ShamanSDL/rn_2.png");
        txtLoad(rend, &sRunL[3], "Other/Sprites/ShamanSDL/rn_3.png");
        break;

    case 3:
        txtLoad(rend, &sIdle[0], "Other/Sprites/SkeletSDL/idle_0.png");
        txtLoad(rend, &sIdle[1], "Other/Sprites/SkeletSDL/idle_1.png");
        txtLoad(rend, &sIdle[2], "Other/Sprites/SkeletSDL/idle_2.png");
        txtLoad(rend, &sIdle[3], "Other/Sprites/SkeletSDL/idle_3.png");
        txtLoad(rend, &sRunR[0], "Other/Sprites/SkeletSDL/run_0.png");
        txtLoad(rend, &sRunR[1], "Other/Sprites/SkeletSDL/run_1.png");
        txtLoad(rend, &sRunR[2], "Other/Sprites/SkeletSDL/run_2.png");
        txtLoad(rend, &sRunR[3], "Other/Sprites/SkeletSDL/run_3.png");
        txtLoad(rend, &sRunL[0], "Other/Sprites/SkeletSDL/rn_0.png");
        txtLoad(rend, &sRunL[1], "Other/Sprites/SkeletSDL/rn_1.png");
        txtLoad(rend, &sRunL[2], "Other/Sprites/SkeletSDL/rn_2.png");
        txtLoad(rend, &sRunL[3], "Other/Sprites/SkeletSDL/rn_3.png");
        break;

    case 4:
        txtLoad(rend, &sIdle[0], "Other/Sprites/ZombieSDL/idle_0.png");
        txtLoad(rend, &sIdle[1], "Other/Sprites/ZombieSDL/idle_1.png");
        txtLoad(rend, &sIdle[2], "Other/Sprites/ZombieSDL/idle_2.png");
        txtLoad(rend, &sIdle[3], "Other/Sprites/ZombieSDL/idle_3.png");
        txtLoad(rend, &sRunR[0], "Other/Sprites/ZombieSDL/run_0.png");
        txtLoad(rend, &sRunR[1], "Other/Sprites/ZombieSDL/run_1.png");
        txtLoad(rend, &sRunR[2], "Other/Sprites/ZombieSDL/run_2.png");
        txtLoad(rend, &sRunR[3], "Other/Sprites/ZombieSDL/run_3.png");
        txtLoad(rend, &sRunL[0], "Other/Sprites/ZombieSDL/rn_0.png");
        txtLoad(rend, &sRunL[1], "Other/Sprites/ZombieSDL/rn_1.png");
        txtLoad(rend, &sRunL[2], "Other/Sprites/ZombieSDL/rn_2.png");
        txtLoad(rend, &sRunL[3], "Other/Sprites/ZombieSDL/rn_3.png");
        break;
    }

    SDL_Texture *slashR;
    txtLoad(rend, &slashR, "Other/Sprites/slashR.png");

    SDL_Texture *slashL;
    txtLoad(rend, &slashL, "Other/Sprites/slashL.png");

    bool menuCheck = false;
    int sMove = 0;
    int jump = -31;
    int maxJump = -25;
    int animPhase = 0;
    int idlePhase = 0;
    int speed = 0;
    int counter = 0;
    int attack = 0;

    long atTimer = SDL_GetPerformanceCounter();
    long freq = SDL_GetPerformanceFrequency();

    long delta = atTimer;

    SDL_Event ev;
    while (true)
    {

        freq = SDL_GetPerformanceFrequency();

        SDL_RenderClear(rend);

        while (SDL_PollEvent(&ev))
        {

            int posX, posY;

            SDL_GetMouseState(&posX, &posY);

            SDL_Point mouse = {posX, posY};

            switch (ev.type)
            {
            case SDL_QUIT:
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(sIdle[0]);
                SDL_DestroyTexture(sIdle[1]);
                SDL_DestroyTexture(sIdle[2]);
                SDL_DestroyTexture(sIdle[3]);
                SDL_DestroyTexture(sRunL[0]);
                SDL_DestroyTexture(sRunL[1]);
                SDL_DestroyTexture(sRunL[2]);
                SDL_DestroyTexture(sRunL[3]);
                SDL_DestroyTexture(sRunR[0]);
                SDL_DestroyTexture(sRunR[1]);
                SDL_DestroyTexture(sRunR[2]);
                SDL_DestroyTexture(sRunR[3]);
                SDL_DestroyTexture(slashR);
                SDL_DestroyTexture(slashL);

                return 4;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (SDL_PointInRect(&mouse, &menuRect))
                {
                    SDL_DestroyTexture(background);
                    SDL_DestroyTexture(sIdle[0]);
                    SDL_DestroyTexture(sIdle[1]);
                    SDL_DestroyTexture(sIdle[2]);
                    SDL_DestroyTexture(sIdle[3]);
                    SDL_DestroyTexture(sRunL[0]);
                    SDL_DestroyTexture(sRunL[1]);
                    SDL_DestroyTexture(sRunL[2]);
                    SDL_DestroyTexture(sRunL[3]);
                    SDL_DestroyTexture(sRunR[0]);
                    SDL_DestroyTexture(sRunR[1]);
                    SDL_DestroyTexture(sRunR[2]);
                    SDL_DestroyTexture(sRunR[3]);

                    return 0;
                }
                break;

            case SDL_MOUSEMOTION:
                SDL_PointInRect(&mouse, &menuRect) ? menuCheck = true : menuCheck = false;
                break;

            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym)
                {
                case SDLK_a:
                    sMove = 2;
                    break;

                case SDLK_d:
                    sMove = 1;
                    break;

                case SDLK_SPACE:

                    jump <= maxJump ? jump = maxJump + 1 : jump;
                    break;

                case SDLK_LCTRL:

                    switch (sMove)
                    {
                    case 0:
                        attack = 1;
                        break;

                    case 1:
                        attack = 1;
                        break;

                    case 2:
                        attack = 2;
                        break;
                    }

                    break;
                }

                atTimer = SDL_GetPerformanceCounter();

                break;

            case SDL_KEYUP:

                switch (ev.key.keysym.sym)
                {
                case SDLK_a:
                    sMove == 2 ? sMove = 0 : sMove;
                    break;

                case SDLK_d:
                    sMove == 1 ? sMove = 0 : sMove;
                    break;
                }
                break;
            }
        }

        SDL_RenderCopy(rend, background, NULL, NULL);

        //---------------------Movement, jump and attack----------------------------------

        long timer = SDL_GetPerformanceCounter();

        /*
        BUG !!
        -------------Attack - suspended atm ------------------------

        if (attack != 0 && (timer - atTimer) * 1000 / freq <= 150)
        {
            SDL_Rect attRect = {sRect.x + (attack == 1 ? +40 : -90), sRect.y + 50, 130, 65};
            SDL_RenderCopy(rend, attack == 1 ? slashR : slashL, NULL, &attRect);
        }
        else
            attack = 0;*/

        if ((timer - delta) * 1000 / freq >= spriteSpeed * 2 && sMove == 0)
        {
            delta = SDL_GetPerformanceCounter();
            animPhase = 0;
            SDL_RenderCopy(rend, sIdle[idlePhase], NULL, &sRect);
            idlePhase++;
            idlePhase >= 4 ? idlePhase = 0 : idlePhase;
        }
        else if ((timer - delta) * 1000 / freq >= spriteSpeed && sMove == 1)
        {
            delta = SDL_GetPerformanceCounter();
            idlePhase = 0;
            SDL_RenderCopy(rend, sIdle[idlePhase], NULL, &sRect);
            animPhase++;
            animPhase >= 4 ? animPhase = 0 : animPhase;
        }
        else if ((timer - delta) * 1000 / freq >= spriteSpeed && sMove == 2)
        {
            delta = SDL_GetPerformanceCounter();
            idlePhase = 0;
            SDL_RenderCopy(rend, sIdle[idlePhase], NULL, &sRect);
            animPhase++;
            animPhase >= 4 ? animPhase = 0 : animPhase;
        }
        else if (sMove == 0)
        {
            if (speed >= 5 && jump > maxJump && counter >= 3)
            {
                counter = 0;
                sRect.y += jump;
                jump++;
                speed = 0;
            }
            else if (speed >= 5)
            {
                speed = 0;
                counter++;
            }
            else
                speed++;

            SDL_RenderCopy(rend, sIdle[idlePhase], NULL, &sRect);
        }
        else if (sMove == 1)
        {
            if (speed >= 5 && jump > maxJump && counter >= 3)
            {
                counter = 0;
                sRect.y += jump;
                jump++;
                speed = 0;
                sRect.x++;
            }
            else if (speed >= 5)
            {
                speed = 0;
                counter++;
                sRect.x++;
            }
            else
                speed++;

            sRect.x >= 836 ? sRect.x = 836 : sRect.x;

            SDL_RenderCopy(rend, sRunR[animPhase], NULL, &sRect);
        }
        else if (sMove == 2)
        {
            if (speed >= 5 && jump > maxJump && counter >= 3)
            {
                counter = 0;
                sRect.y += jump;
                jump++;
                speed = 0;
                sRect.x--;
            }
            else if (speed >= 5)
            {
                speed = 0;
                counter++;
                sRect.x--;
            }
            else
                speed++;

            sRect.x <= 60 ? sRect.x = 60 : sRect.x;

            SDL_RenderCopy(rend, sRunL[animPhase], NULL, &sRect);
        }

        if (SDL_IntersectRect(&sRect, &ground, &res))
        {
            sRect.y = lowestHeight - 121;
            jump = maxJump;
        }

        SDL_Texture *menu;
        textLoad(rend, &menu, &basic, menuCheck ? red : white, "Menu");
        SDL_RenderCopy(rend, menu, NULL, &menuRect);
        SDL_DestroyTexture(menu);

        SDL_RenderPresent(rend);
    }

    return 0;
}

int settings(SDL_Window *window, SDL_Renderer *rend, TTF_Font *basic, TTF_Font *title)
{

    SDL_RenderClear(rend);

    std::string idleSprites[5] = {
        "Other/Sprites/DuckSDL/no_anim_0.png",
        "Other/Sprites/PirateSDL/no_anim_0.png",
        "Other/Sprites/ShamanSDL/no_anim_0.png",
        "Other/Sprites/SkeletSDL/no_anim_0.png",
        "Other/Sprites/ZombieSDL/no_anim_0.png"};

    SDL_Texture *background;
    txtLoad(rend, &background, "Other/Images/Background.png");
    SDL_RenderCopy(rend, background, NULL, NULL);

    SDL_Rect rcts = {290, 90, 400, 120};

    SDL_Rect rectQuit = {43, 605, 120, 55};

    SDL_Rect spriteRect = {425, 250, 120, 150};

    SDL_Rect arrL = {320, 255, 105, 180};

    SDL_Rect arrR = {565, 255, 105, 180};

    int color = 0;

    SDL_Color white = {255, 255, 255, 0};

    SDL_Color red = {227, 34, 0, 0};

    SDL_Event ev;
    while (1)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                SDL_DestroyTexture(background);
                return 4;
                break;
            }
            else if (ev.type == SDL_KEYDOWN)
            {
                if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d)
                {
                    avatarPick++;
                    avatarPick > 4 ? avatarPick = 0 : avatarPick;
                }
                else if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a)
                {
                    avatarPick--;
                    avatarPick < 0 ? avatarPick = 4 : avatarPick;
                }
                else if (ev.key.keysym.sym == SDLK_RETURN)
                {
                    return 0;
                }
            }
            else if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                int posX;
                int posY;

                SDL_GetMouseState(&posX, &posY);

                const SDL_Point mouse = {posX, posY};

                if (SDL_PointInRect(&mouse, &rectQuit))
                    return 0;
                else if (SDL_PointInRect(&mouse, &arrR))
                {
                    avatarPick++;
                    avatarPick > 4 ? avatarPick = 0 : avatarPick;
                }
                else if (SDL_PointInRect(&mouse, &arrL))
                {
                    avatarPick--;
                    avatarPick < 0 ? avatarPick = 4 : avatarPick;
                }
            }
            else if (ev.type == SDL_MOUSEMOTION)
            {
                int posX;
                int posY;

                SDL_GetMouseState(&posX, &posY);

                const SDL_Point mouse = {posX, posY};

                if (SDL_PointInRect(&mouse, &rectQuit))
                    color = 1;
                else
                    color = 0;
            }

            SDL_RenderCopy(rend, background, NULL, NULL);

            SDL_Texture *temp;
            txtLoad(rend, &temp, idleSprites[avatarPick]);
            SDL_RenderCopy(rend, temp, NULL, &spriteRect);
            SDL_DestroyTexture(temp);

            SDL_Texture *arrow;
            textLoad(rend, &arrow, &basic, white, ">>");
            SDL_RenderCopy(rend, arrow, NULL, &arrR);
            SDL_DestroyTexture(arrow);

            textLoad(rend, &arrow, &basic, white, "<<");
            SDL_RenderCopy(rend, arrow, NULL, &arrL);
            SDL_DestroyTexture(arrow);

            textLoad(rend, &temp, &basic, {36, 87, 0, 0}, "Settings");
            SDL_RenderCopy(rend, temp, NULL, &rcts);
            SDL_DestroyTexture(temp);

            textLoad(rend, &temp, &basic, color == 0 ? white : red, "Menu");
            SDL_RenderCopy(rend, temp, NULL, &rectQuit);
            SDL_DestroyTexture(temp);

            SDL_RenderPresent(rend);
        }
    }

    return 0;
}

int hof(SDL_Window *window, SDL_Renderer *rend, TTF_Font *basic, TTF_Font *title)
{

    SDL_RenderClear(rend);

    FILE *scores = fopen("Other/scores.txt", "at+");
    if (scores == NULL)
    {
        std::cout << "Could not open the file." << std::endl;
        return 0;
    }

    SDL_Texture *temp;

    SDL_Texture *background;
    txtLoad(rend, &background, "Other/Images/backgroundGame.png");

    SDL_RenderCopy(rend, background, NULL, NULL);
    int count = 0;

    char c;

    for (c = getc(scores); c != EOF; c = getc(scores))
    {
        if (c == '\n')
            count++;
    }

    c != '\n' ? count++ : count;

    rewind(scores);

    std::vector<std::string> lines;

    char line[256];

    int i = 0;

    while (fgets(line, sizeof(line), scores))
    {
        lines.push_back(line);
    }

    // Optional -- Add names or nicks to the scores (csv file, divide string with ","
    // and save int format : "nickname,score"  )

    SDL_Rect rcts = {290, 90, 400, 120};

    SDL_Rect rectQuit = {43, 605, 120, 55};

    int color = 0;

    SDL_Color white = {255, 255, 255, 0};

    SDL_Color red = {227, 34, 0, 0};

    SDL_Event ev;
    while (1)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                SDL_DestroyTexture(background);
                return 4;
                break;
            }
            else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN)
            {
                return 0;
            }
            else if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                int posX;
                int posY;

                SDL_GetMouseState(&posX, &posY);

                const SDL_Point mouse = {posX, posY};

                if (SDL_PointInRect(&mouse, &rectQuit))
                    return 0;
            }
            else if (ev.type == SDL_MOUSEMOTION)
            {
                int posX;
                int posY;

                SDL_GetMouseState(&posX, &posY);

                const SDL_Point mouse = {posX, posY};

                if (SDL_PointInRect(&mouse, &rectQuit))
                    color = 1;
                else
                    color = 0;
            }

            SDL_RenderCopy(rend, background, NULL, NULL);

            for (int i = 0; i < lines.size(); i++)
            {

                if (i == 5)
                    break;

                SDL_Rect rcts = {400, 227 + 65 * i, 220, 65};
                SDL_Rect dot = {370, 225 + 65 * i, 20, 70};
                SDL_Rect position = {340, 227 + 65 * i, 30, 65};

                int a = atoi(lines[i].c_str());

                std::string scre = std::to_string(a);

                std::string strng = std::to_string(i + 1);

                std::string ins = std::to_string(a);

                SDL_Color black = {0, 0, 0, 0};

                textLoad(rend, &temp, &basic, black, strng);
                SDL_RenderCopy(rend, temp, NULL, &position);
                SDL_DestroyTexture(temp);

                textLoad(rend, &temp, &basic, black, ".");
                SDL_RenderCopy(rend, temp, NULL, &dot);
                SDL_DestroyTexture(temp);

                textLoad(rend, &temp, &basic, black, scre);
                SDL_RenderCopy(rend, temp, NULL, &rcts);
                SDL_DestroyTexture(temp);
            }

            textLoad(rend, &temp, &title, {36, 87, 0, 0}, "Hall of Fame");
            SDL_RenderCopy(rend, temp, NULL, &rcts);
            SDL_DestroyTexture(temp);

            textLoad(rend, &temp, &basic, color == 0 ? white : red, "Menu");
            SDL_RenderCopy(rend, temp, NULL, &rectQuit);
            SDL_DestroyTexture(temp);

            SDL_RenderPresent(rend);
        }
    }

    fclose(scores);

    return 0;
}
