#include "srcFiles/Components.h"

int main(int argc, char *argv[])
{
    // SDL init

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        // SDL initialization failed, print error message
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    // window init

    SDL_Window *window = SDL_CreateWindow("Breakout !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 460, 640, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        // Window creation failed, print error message
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1)
    {
        printf("Font init failed.\n");
    }

    // Get icon for the window and set it as window icon:

    SDL_Surface *icon = IMG_Load("srcFiles/icon.png");
    if (icon == NULL)
    {
        printf("Icon load error.\n");
    }

    SDL_SetWindowIcon(window, icon);

    // Renderer creation

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        // Renderer creation failed, print error message
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }

    // Open or create file to store scores

    FILE *scrFile = fopen("srcFiles/scores.txt", "at+");

    FILE *level = fopen("srcFiles/level.txt", "rt");

    // Load Backgrounds

    SDL_Surface *image = IMG_Load("srcFiles/menuBack.jpg");
    SDL_Texture *menuBackground = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    image = IMG_Load("srcFiles/HoF.jpg");
    SDL_Texture *HoFBackground = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    image = IMG_Load("srcFiles/gameBackgroundB.jpg");
    SDL_Texture *gameBackground = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    image = IMG_Load("srcFiles/SettBackground.jpg");
    SDL_Texture *settBackground = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    drawMenu(renderer, menuBackground);

    // Program loop

    while (true)
    {
        if (drawDef == 0)
        {
            drawMenu(renderer, menuBackground);
        }
        else if (drawDef == 1)
        {
            settings(renderer, settBackground);
        }
        else if (drawDef == 2)
        {
            hallOfFame(renderer, HoFBackground, scrFile);
        }
        else if (drawDef == 3)
        {
            gameItself(renderer, gameBackground, scrFile, rand() % 10 + 1, level);
        }
        else if (drawDef == 4)
        {
            break;
        }
    }

    fclose(scrFile);
    fclose(level);

    // SDL_Quit(); to close window and all SDl components before the program ends
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
