#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int drawDef = 0;

#define gameWidth 400
#define gameHeight 590
#define platHeight 20
#define LRMargine 30
#define topMargine 50

const int columns = 7;
const int rows = 5;

typedef struct
{
    int posX;
    int posY;
    int velX;
    int velY;
    int diameter;
    char hexColor[8];
} Ball;

typedef struct
{
    int posX;
    int posY;
    int width;
    int height;
    char hexColor[8];
} Platform;

#define windowWidth 460
#define windowHeight 640

// RGB values:
// Paddle:
int rP = 255;
int gP = 255;
int bP = 255;

// Ball:
int rB = 0;
int gB = 255;
int bB = 0;

// Difficulty:
int rD = 48;
int gD = 148;
int bD = 62;
int diff = 2;

void endGame(SDL_Renderer *renderer)
{
    SDL_Surface *endMenu = IMG_Load("srcFiles/endGame.jpg");
    SDL_Texture *endGame = SDL_CreateTextureFromSurface(renderer, endMenu);
    SDL_FreeSurface(endMenu);

    SDL_Rect endScreen = {windowWidth / 2 - 140, windowHeight / 2 - 160, 280, 330};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderCopy(renderer, endGame, NULL, &endScreen);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    SDL_Rect frameA = {115, 275, 230, 50};
    SDL_RenderDrawRect(renderer, &frameA);

    SDL_Rect frameB = {164, 341, 130, 50};
    SDL_RenderDrawRect(renderer, &frameB);

    SDL_Rect frameC = {177, 408, 110, 50};
    SDL_RenderDrawRect(renderer, &frameC);

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
                drawDef = 4;
                wait = !wait;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (ev.button.x >= 115 && ev.button.x <= 345 && ev.button.y >= 275 && ev.button.y <= 325)
                {
                    drawDef = 3;
                    wait = !wait;
                }
                else if (ev.button.x >= 164 && ev.button.x <= 294 && ev.button.y >= 341 && ev.button.y <= 391)
                {
                    drawDef = 0;
                    wait = !wait;
                }
                else if (ev.button.x >= 177 && ev.button.x <= 287 && ev.button.y >= 408 && ev.button.y <= 458)
                {
                    drawDef = 4;
                    wait = !wait;
                }

                break;

            default:
                break;
            }
        }
    }
}

void winGame(SDL_Renderer *renderer)
{
    // Get win game PopUp:

    SDL_Surface *endMenu = IMG_Load("srcFiles/winGame.jpg");
    SDL_Texture *endGame = SDL_CreateTextureFromSurface(renderer, endMenu);
    SDL_FreeSurface(endMenu);

    // Use a rectangle to display the texture:

    SDL_Rect endScreen = {windowWidth / 2 - 140, windowHeight / 2 - 160, 280, 330};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderCopy(renderer, endGame, NULL, &endScreen);

    // Set white draw color for frames around text:

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    SDL_Rect frameA = {115, 275, 230, 50};
    SDL_RenderDrawRect(renderer, &frameA);

    SDL_Rect frameB = {164, 341, 130, 50};
    SDL_RenderDrawRect(renderer, &frameB);

    SDL_Rect frameC = {177, 408, 110, 50};
    SDL_RenderDrawRect(renderer, &frameC);

    // Show / render everything on screen

    SDL_RenderPresent(renderer);

    // Wait for events:

    SDL_Event ev;
    bool wait = true;
    while (wait)
    {
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                drawDef = 4;
                wait = !wait;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (ev.button.x >= 115 && ev.button.x <= 345 && ev.button.y >= 275 && ev.button.y <= 325)
                {
                    drawDef = 3;
                    wait = !wait;
                }
                else if (ev.button.x >= 164 && ev.button.x <= 294 && ev.button.y >= 341 && ev.button.y <= 391)
                {
                    drawDef = 0;
                    wait = !wait;
                }
                else if (ev.button.x >= 177 && ev.button.x <= 287 && ev.button.y >= 408 && ev.button.y <= 458)
                {
                    drawDef = 4;
                    wait = !wait;
                }

                break;

            default:
                break;
            }
        }
    }
}

void settings(SDL_Renderer *renderer, SDL_Texture *background)
{

    /* Color settings for ball and platform render (color filled rectangles)
    These are the only things that change in this window because all other stuff is on background*/
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    SDL_Rect pickedPaddle;

    pickedPaddle.x = 343;
    pickedPaddle.y = 71;
    pickedPaddle.w = 24;
    pickedPaddle.h = 24;

    SDL_SetRenderDrawColor(renderer, rP, gP, bP, 0);
    SDL_RenderFillRect(renderer, &pickedPaddle);

    SDL_Rect pickedBall = {344, 267, 24, 24};
    SDL_SetRenderDrawColor(renderer, rB, gB, bB, 0);
    SDL_RenderFillRect(renderer, &pickedBall);

    SDL_Rect pickedDiff = {159, 268, 24, 24};
    SDL_SetRenderDrawColor(renderer, rD, gD, bD, 0);
    SDL_RenderFillRect(renderer, &pickedDiff);

    // render everything

    SDL_RenderPresent(renderer);

    // Wait for event

    bool quit = false;
    SDL_Event ev;
    while (!quit)
    {
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                drawDef = 4;
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Back Button
                if (ev.button.x >= 15 && ev.button.x <= 165 && ev.button.y >= 560 && ev.button.y <= 630)
                {
                    drawDef = 0;
                    quit = true;
                }
                // White Paddle Option
                else if (ev.button.x >= 304 && ev.button.x <= 330 && ev.button.y >= 108 && ev.button.y <= 134)
                {
                    rP = 255;
                    gP = 255;
                    bP = 255;
                    quit = !quit;
                    drawDef = 1;
                }
                // Green Paddle Option
                else if (ev.button.x >= 342 && ev.button.x <= 368 && ev.button.y >= 108 && ev.button.y <= 134)
                {
                    rP = 48;
                    gP = 148;
                    bP = 62;
                    quit = !quit;
                    drawDef = 1;
                }
                // D Blue Paddle Option
                else if (ev.button.x >= 380 && ev.button.x <= 406 && ev.button.y >= 108 && ev.button.y <= 134)
                {
                    rP = 34;
                    gP = 53;
                    bP = 125;
                    quit = !quit;
                    drawDef = 1;
                }
                // Red Paddle Option
                else if (ev.button.x >= 304 && ev.button.x <= 330 && ev.button.y >= 146 && ev.button.y <= 172)
                {
                    rP = 112;
                    gP = 34;
                    bP = 34;
                    quit = !quit;
                    drawDef = 1;
                }
                // Purple Paddle Option
                else if (ev.button.x >= 342 && ev.button.x <= 368 && ev.button.y >= 146 && ev.button.y <= 172)
                {
                    rP = 82;
                    gP = 36;
                    bP = 145;
                    quit = !quit;
                    drawDef = 1;
                }
                // Blue Paddle Option
                else if (ev.button.x >= 380 && ev.button.x <= 406 && ev.button.y >= 146 && ev.button.y <= 172)
                {
                    rP = 74;
                    gP = 138;
                    bP = 157;
                    quit = !quit;
                    drawDef = 1;
                }
                // White Ball Option
                else if (ev.button.x >= 305 && ev.button.x <= 331 && ev.button.y >= 304 && ev.button.y <= 330)
                {
                    rB = 255;
                    gB = 255;
                    bB = 255;
                    quit = !quit;
                    drawDef = 1;
                }
                // Green Ball Option
                else if (ev.button.x >= 343 && ev.button.x <= 369 && ev.button.y >= 304 && ev.button.y <= 330)
                {
                    rB = 0;
                    gB = 255;
                    bB = 0;
                    quit = !quit;
                    drawDef = 1;
                }
                // D Blue Ball Option
                else if (ev.button.x >= 381 && ev.button.x <= 407 && ev.button.y >= 304 && ev.button.y <= 330)
                {
                    rB = 25;
                    gB = 74;
                    bB = 255;
                    quit = !quit;
                    drawDef = 1;
                }
                // Red Ball Option
                else if (ev.button.x >= 305 && ev.button.x <= 331 && ev.button.y >= 342 && ev.button.y <= 368)
                {
                    rB = 255;
                    gB = 44;
                    bB = 44;
                    quit = !quit;
                    drawDef = 1;
                }
                // Purple Ball Option
                else if (ev.button.x >= 343 && ev.button.x <= 369 && ev.button.y >= 342 && ev.button.y <= 368)
                {
                    rB = 143;
                    gB = 61;
                    bB = 255;
                    quit = !quit;
                    drawDef = 1;
                }
                // Blue Ball Option
                else if (ev.button.x >= 381 && ev.button.x <= 407 && ev.button.y >= 342 && ev.button.y <= 368)
                {
                    rB = 17;
                    gB = 202;
                    bB = 255;
                    quit = !quit;
                    drawDef = 1;
                }
                // Easy Green Diff Option
                else if (ev.button.x >= 158 && ev.button.x <= 184 && ev.button.y >= 318 && ev.button.y <= 344)
                {
                    rD = 48;
                    gD = 148;
                    bD = 62;
                    quit = !quit;
                    drawDef = 1;
                    diff = 2;
                }
                // Medium D Blue Diff Option
                else if (ev.button.x >= 158 && ev.button.x <= 184 && ev.button.y >= 366 && ev.button.y <= 392)
                {
                    rD = 34;
                    gD = 53;
                    bD = 125;
                    quit = !quit;
                    drawDef = 1;
                    diff = 3;
                }
                // Hard Red Diff Option
                else if (ev.button.x >= 158 && ev.button.x <= 184 && ev.button.y >= 414 && ev.button.y <= 440)
                {
                    rD = 112;
                    gD = 34;
                    bD = 34;
                    quit = !quit;
                    drawDef = 1;
                    diff = 5;
                }

                break;

            default:
                break;
            }
        }
    }
}

void drawMenu(SDL_Renderer *renderer, SDL_Texture *background)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    // render background :

    SDL_RenderPresent(renderer);

    // listen for events and clicks on buttons:

    SDL_Event ev;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                drawDef = 4;
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ((ev.button.x >= 150 && ev.button.x <= 307) && (ev.button.y >= 220 && ev.button.y <= 285))
                {
                    drawDef = 3; // The Game
                    quit = true;
                }
                else if ((ev.button.x >= 120 && ev.button.x <= 330) && (ev.button.y >= 315 && ev.button.y <= 375))
                {
                    drawDef = 1; // Settings
                    quit = true;
                }
                else if ((ev.button.x >= 55 && ev.button.x <= 400) && (ev.button.y >= 400 && ev.button.y <= 460))
                {
                    drawDef = 2; // Hall of Fame
                    quit = true;
                }
                else if ((ev.button.x >= 150 && ev.button.x <= 307) && (ev.button.y >= 490 && ev.button.y <= 550))
                {
                    drawDef = 4; // Quit
                    quit = true;
                }

            default:
                break;
            }
        }
    }
}

void hallOfFame(SDL_Renderer *renderer, SDL_Texture *background, FILE *scrFile)
{

    // Get amount of lines in a file

    int lines = 0;
    int am = 0;

    rewind(scrFile);

    while (!feof(scrFile))
    {
        am = fgetc(scrFile);
        if (am == '\n')
        {
            lines++;
        }
    }

    // Allocate space for as many ints as there is lines in the file

    int *scores = (int *)malloc(sizeof(int) * lines);

    rewind(scrFile);

    for (size_t i = 0; i < lines; i++)
    {
        char num[7];
        fgets(num, sizeof(num), scrFile);
        scores[i] = atoi(num);
    }

    // File management and hall of fame display

    int firstPlace = 0;
    int secondPlace = 0;
    int thirdPlace = 0;

    for (size_t i = 0; i < lines; i++)
    {
        if (scores[i] > firstPlace)
            firstPlace = scores[i];

        if (scores[i] > secondPlace && scores[i] < firstPlace)
            secondPlace = scores[i];

        if (scores[i] > thirdPlace && scores[i] < secondPlace)
            thirdPlace = scores[i];
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    TTF_Font *Font = TTF_OpenFont("srcFiles/Sans.ttf", 29);

    char intToTxt[10];
    SDL_Color white = {255, 255, 255, 0};

    sprintf(intToTxt, "%d", firstPlace);
    SDL_Surface *txt = TTF_RenderText_Solid(Font, intToTxt, white);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, txt);
    SDL_FreeSurface(txt);

    int width;

    if (firstPlace < 10)
        width = 40;
    else if (firstPlace < 100)
        width = 60;
    else if (firstPlace < 1000)
        width = 80;
    else
        width = 100;

    SDL_Rect first = {240, 180, width, 50};
    SDL_RenderCopy(renderer, text, NULL, &first);

    sprintf(intToTxt, "%d", secondPlace);
    txt = TTF_RenderText_Solid(Font, intToTxt, white);
    text = SDL_CreateTextureFromSurface(renderer, txt);
    SDL_FreeSurface(txt);

    if (secondPlace < 10)
        width = 40;
    else if (secondPlace < 100)
        width = 60;
    else if (secondPlace < 1000)
        width = 80;
    else
        width = 100;

    SDL_Rect second = {240, 284, width, 50};
    SDL_RenderCopy(renderer, text, NULL, &second);

    sprintf(intToTxt, "%d", thirdPlace);
    txt = TTF_RenderText_Solid(Font, intToTxt, white);
    text = SDL_CreateTextureFromSurface(renderer, txt);
    SDL_FreeSurface(txt);

    if (thirdPlace < 10)
        width = 40;
    else if (thirdPlace < 100)
        width = 60;
    else if (thirdPlace < 1000)
        width = 80;
    else
        width = 100;

    SDL_Rect third = {240, 388, width, 50};
    SDL_RenderCopy(renderer, text, NULL, &third);

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
    SDL_Rect back = {180, 506, 100, 50};
    SDL_RenderDrawRect(renderer, &back);

    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event ev;
    while (!quit)
    {
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                drawDef = 4;
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (ev.button.x >= 180 && ev.button.x <= 280 && ev.button.y >= 506 && ev.button.y <= 556)
                {
                    drawDef = 0;
                    quit = true;
                }

                break;

            default:
                break;
            }
        }
    }
}

void gameItself(SDL_Renderer *renderer, SDL_Texture *background, FILE *scrFile, int rNum, FILE *level)
{

    // Some game-important data init and font load

    int lives = 3;
    int lastLives = 3;

    int framesSinceLastColl = 0;
    int score = 0;
    TTF_Font *Font = TTF_OpenFont("srcFiles/Sans.ttf", 20);

    // Platform struct init

    Platform plat;
    plat.height = 10;
    plat.width = 80;
    plat.posX = (windowWidth - plat.width) / 2;
    plat.posY = windowHeight - plat.height - 10;

    // Ball struct init

    Ball ball;
    ball.diameter = 12;
    ball.posX = (windowWidth - ball.diameter) / 2;
    ball.posY = windowHeight - 25 - plat.height;

    /* set values for:

    h = horizontal platform speed
    bV = ball vertical speed
    bH = ball horizontal speed

    */
    int h = 0;
    int bH;

    if (rNum % 2 == 0)
        bH = -diff;
    else
        bH = diff;

    int bV = -diff;

    bool play = true;
    SDL_Event ev;

    // array of Tiles (each tile has a number 0 or 1 in the array)
    // 1 - draw wile and check for collision
    // 0 - do not draw and check for collision

    int arrSize = rows * columns;
    int *tileArr = (int *)malloc(sizeof(int) * arrSize);

    // init array to all 1 to draw all tiles in beginning

    for (size_t i = 0; i < rows; i++)
    {
        char line[9];
        fgets(line, sizeof(line), level);
        for (size_t o = 0; o < columns; o++)
        {
            if (line[o] == 'x')
            {
                tileArr[columns * i + o] = 1;
            }
            else
                tileArr[columns * i + o] = 0;
        }
    }

    rewind(level);

    // Game loop

    while (play)
    {

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        char scr[10];

        SDL_Color white = {255, 255, 255};

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_Rect border = {30, 50, 400, 600};
        SDL_RenderDrawRect(renderer, &border);

        SDL_Rect thickA = {29, 49, 402, 591};
        SDL_RenderDrawRect(renderer, &thickA);

        SDL_Rect thickB = {28, 48, 404, 592};
        SDL_RenderDrawRect(renderer, &thickB);

        SDL_Rect thickC = {27, 47, 406, 593};
        SDL_RenderDrawRect(renderer, &thickC);

        SDL_Rect thickD = {26, 46, 408, 594};
        SDL_RenderDrawRect(renderer, &thickD);

        // Draw ball

        SDL_Rect brect = {ball.posX, ball.posY, ball.diameter, ball.diameter};
        SDL_SetRenderDrawColor(renderer, rB, gB, bB, 0);
        SDL_RenderFillRect(renderer, &brect);

        // Draw paddle

        SDL_Rect paddle = {plat.posX, windowHeight - 25, plat.width, plat.height};
        SDL_SetRenderDrawColor(renderer, rP, gP, bP, 0);
        SDL_RenderFillRect(renderer, &paddle);

        // Draw lives

        for (size_t i = 0; i < lives; i++)
        {
            SDL_SetRenderDrawColor(renderer, 176, 19, 19, 0);
            SDL_Rect live = {440, 200 + i * 35, 15, 25};
            SDL_RenderFillRect(renderer, &live);
        }

        // Draw tiles

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t o = 0; o < columns; o++)
            {

                if (tileArr[columns * i + o] != 1)
                {
                    continue;
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 10 + (5 * (i + 2) * (o + 1)), 0, 255 - (2 * (i + 3) * (o + 3)), 0);
                    SDL_Rect tile = {55 + o * 50, 90 + i * 27, 45, 23};
                    SDL_RenderFillRect(renderer, &tile);
                }
            }
        }

        sprintf(scr, "%d", score);
        SDL_Surface *txt = TTF_RenderText_Solid(Font, scr, white);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, txt);
        SDL_FreeSurface(txt);

        SDL_Rect txtRect = {132, 3, 0, 40};

        if (score < 10)
            txtRect.w = 20;
        else if (score < 100)
            txtRect.w = 35;
        else
            txtRect.w = 55;

        SDL_RenderCopy(renderer, text, NULL, &txtRect);

        SDL_RenderPresent(renderer);

        if (lives < lastLives)
        {
            lastLives--;
            SDL_Delay(1000);
        }

        // Even listening:

        while (SDL_PollEvent(&ev) != 0)
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                play = !play;
                drawDef = 4;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (ev.button.x >= 255 && ev.button.x <= 445 && ev.button.y >= 0 && ev.button.y <= 50)
                {
                    drawDef = 0;
                    play = !play;
                }
                break;

            case SDL_KEYDOWN:
                if (ev.key.keysym.sym == SDLK_a)
                {
                    h = -(diff - diff / 2);
                }
                else if (ev.key.keysym.sym == SDLK_d)
                {
                    h = (diff - diff / 2);
                }

            default:
                break;
            }
        }

        // next part is all collision checking:

        // Keep plat in boundries:

        if (plat.posX <= 30)
        {
            h = 0;
            plat.posX = 31;
        }
        else if (plat.posX >= 350)
        {
            h = 0;
            plat.posX = 349;
        }

        // Keep ball in boundries:

        if (ball.posX <= 34)
        {
            bH = -bH;
        }
        else if (ball.posX >= 422)
        {
            bH = -bH;
        }

        // Check if ball is not under paddle / game over

        if (ball.posY <= 50)
        {
            bV = diff;
        }
        else if (ball.posY + ball.diameter >= 640 && lives == 1)
        {
            bH = 0;
            bV = -diff;
            h = 0;
            endGame(renderer);
            break;
        }
        else if (ball.posY + ball.diameter >= 640)
        {

            bV = -diff;
            ball.posX = windowWidth / 2 - ball.diameter / 2;
            ball.posY = windowHeight - 35 - plat.height;
            plat.posX = windowWidth / 2 - plat.width / 2;
            lives--;
        }

        // Collision check ball with paddle:

        if ((ball.posY + ball.diameter) >= plat.posY && (ball.posY + ball.diameter - diff - 1) <= plat.posY)
        {
            if (ball.posX + ball.diameter >= plat.posX && ball.posX + ball.diameter / 2 <= plat.posX + plat.width / 4)
            {
                bH = -4;
                bV = -diff;
                score += 18 * diff;
            }
            else if (ball.posX + ball.diameter / 2 > plat.posX + plat.width / 4 && ball.posX + ball.diameter / 2 < plat.posX + plat.width / 2)
            {
                bH = -2;
                bV = -diff;
                score += 18 * diff;
            }
            else if (ball.posX + ball.diameter / 2 == plat.posX + plat.width / 2)
            {
                bH = 0;
                bV = -diff;
                score += 18 * diff;
            }
            else if (ball.posX + ball.diameter / 2 > plat.posX + plat.width / 2 && ball.posX + ball.diameter / 2 <= plat.posX + plat.width / 4 * 3)
            {
                bH = 2;
                bV = -diff;
                score += 18 * diff;
            }
            else if (ball.posX + ball.diameter / 2 > plat.posX + plat.width / 4 * 3 && ball.posX + ball.diameter / 2 <= plat.posX + plat.width)
            {
                bH = 4;
                bV = -diff;
                score += 18 * diff;
            }
        }

        /*
        if ((ball.posX + ball.diameter) >= plat.posX && ball.posX <= plat.posX + plat.width)
            {
                bV = -diff;
                score += diff * 6;
            }
        */

        // Now this all is tile collision: from here ----------------------

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t o = 0; o < columns; o++)
            {
                SDL_Rect tile = {65 + o * 56, 90 + i * 30, 50, 23};

                if (tileArr[columns * i + o] == 0)
                {
                    continue;
                }
                else if (bV > 0 && bH > 0)
                {
                    // Down Right
                    SDL_Point pt = {ball.posX + ball.diameter, ball.posY + ball.diameter};

                    if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (ball.posX + ball.diameter) - (65 + o * 56) > (ball.posY + ball.diameter) - (90 + i * 30))
                    {

                        score += 18 * diff;
                        bV = -diff;
                        framesSinceLastColl = 0;
                        tileArr[columns * i + o] = 0;

                        break;
                    }
                    else if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (ball.posX + ball.diameter) - (65 + o * 56) < (ball.posY + ball.diameter) - (90 + i * 30))
                    {
                        bH = -bH;
                        score += 18 * diff;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                    else if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (ball.posX + ball.diameter) - (65 + o * 56) == (ball.posY + ball.diameter) - (90 + i * 30))
                    {
                        bV = -diff;
                        score += 18 * diff;
                        bH = -bH;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                }
                else if (bV > 0 && bH < 0)
                {
                    // Down Left
                    SDL_Point pt = {ball.posX, ball.posY + ball.diameter};

                    if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (115 + o * 56) - ball.posX > (ball.posY + ball.diameter) - (90 + i * 30))
                    {
                        bV = -diff;
                        score += 18 * diff;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                    else if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (115 + o * 56) - ball.posX < (ball.posY + ball.diameter) - (90 + i * 30))
                    {
                        bH = -bH;
                        score += 18 * diff;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                    else if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (115 + o * 56) - ball.posX == (ball.posY + ball.diameter) - (90 + i * 30))
                    {
                        bV = -diff;
                        score += 18 * diff;
                        bH = -bH;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                }
                else if (bV < 0 && bH > 0)
                {
                    // Up Right
                    SDL_Point pt = {ball.posX + ball.diameter, ball.posY};

                    if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (ball.posX + ball.diameter) - (65 + o * 56) > (113 + i * 30) - ball.posY)
                    {
                        bV = diff;
                        score += 18 * diff;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                    else if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (ball.posX + ball.diameter) - (65 + o * 56) < (113 + i * 30) - ball.posY)
                    {
                        bH = -bH;
                        score += 18 * diff;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                    else if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (ball.posX + ball.diameter) - (65 + o * 56) == (113 + i * 30) - ball.posY)
                    {
                        bV = diff;
                        score += 18 * diff;
                        bH = -bH;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                }
                else if (bV < 0 && bH < 0)
                {
                    // Up Left
                    SDL_Point pt = {ball.posX, ball.posY};

                    if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (115 + o * 56) - ball.posX > (113 + i * 30) - ball.posY)
                    {
                        bV = diff;
                        score += 18 * diff;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                    else if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (115 + o * 56) - ball.posX < (113 + i * 30) - ball.posY)
                    {
                        bH = -bH;
                        score += 18 * diff;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                    else if (framesSinceLastColl >= 4 && SDL_PointInRect(&pt, &tile) && (115 + o * 56) - ball.posX == (113 + i * 30) - ball.posY)
                    {
                        bV = diff;
                        score += 18 * diff;
                        bH = -bH;
                        tileArr[columns * i + o] = 0;
                        framesSinceLastColl = 0;
                        break;
                    }
                }
                else if (bV < 0 && bH == 0)
                {
                    // Down Right
                    SDL_Point pta = {ball.posX, ball.posY + ball.diameter};

                    SDL_Point ptb = {ball.posX + ball.diameter, ball.posY + ball.diameter};

                    if (framesSinceLastColl >= 4 && (SDL_PointInRect(&pta, &tile) || SDL_PointInRect(&ptb, &tile)))
                    {

                        score += 18 * diff;
                        bV = diff;
                        framesSinceLastColl = 0;
                        tileArr[columns * i + o] = 0;

                        break;
                    }
                }
            }
        }

        // to here ---------------------------------------------------------

        // Now check if all tiles are gone or not:

        bool gameIsWon = true;

        for (size_t i = 0; i < arrSize; i++)
        {
            tileArr[i] == 1 ? gameIsWon = false : gameIsWon;
        }

        // if they are, game is won:

        if (bH == 0 && h == 0)
            SDL_RenderPresent(renderer);

        if (gameIsWon == true)
        {
            winGame(renderer);
            char finScore[9];
            sprintf(finScore, "%d", score);
            strncat(finScore, "\n", 2);
            fputs(finScore, scrFile);
            break;
        }

        ball.posX += bH;
        ball.posY += bV;
        plat.posX += h;
        framesSinceLastColl++;
    }

    // free the malloced array of tiles:

    free(tileArr);
}
