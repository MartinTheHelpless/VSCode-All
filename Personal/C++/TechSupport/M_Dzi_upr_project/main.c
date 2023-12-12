#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#ifdef main
#undef main
#endif

struct shot
{
    SDL_Rect rect;
    int index;
};

struct Player
{
    SDL_Rect rect;
    int health;
};

struct Enemy
{
    SDL_Rect rect;
    int health;
    int damage;
};

struct Boss
{
    SDL_Rect rect;
    int helath;
    int direction;
};

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int BOT_MARGIN = WINDOW_HEIGHT / 50;
const int TOP_MARGIN = BOT_MARGIN;
const int SIDE_MARGIN = 7;

const int PLAYER_HEIGHT = 50;
const int PLAYER_WIDTH = 50;

const int BOSS_WIDTH = 73;
const int BOSS_HEIGHT = 33;

const int ENEMY_SIZE = 40;

const int SHOT_HEIGHT = 12;
const int SHOT_WIDTH = 3;

const int PLAYER_SPEED = 3;
const int SHOT_SPEED = 5;
const int BOSS_SPEED = 3;

const int SHOT_DELAY = 200;

const int ENEMY_COUNT_X = WINDOW_WIDTH / ENEMY_SIZE / 3 * 2 - 1;

int main(int argc, char const *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window)
    {
        SDL_Log("Unable to create SDL window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!rend)
    {
        SDL_Log("Unable to create SDL renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Uint32 frameStart, frameTime, lastShot, enemyShot;

    int shotCount = 0;
    int enemyShotCount = 0;

    struct Player *p1 = malloc(sizeof(struct Player));
    struct Enemy *enemies = (struct Enemy *)malloc(sizeof(struct Enemy) * ENEMY_COUNT_X * 5);
    struct shot *shots = (struct shot *)malloc(shotCount * sizeof(struct shot));
    struct shot *enemyShots = (struct shot *)malloc(shotCount * sizeof(struct shot));
    struct Boss boss;

    boss.rect.y = TOP_MARGIN + 0.3 * BOSS_HEIGHT;
    boss.rect.x = WINDOW_WIDTH / 2 - BOSS_WIDTH / 2;
    boss.rect.w = BOSS_WIDTH;
    boss.rect.h = BOSS_HEIGHT;
    boss.helath = 8;
    boss.direction = 1;

    p1->rect.x = WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2;
    p1->rect.y = WINDOW_HEIGHT - BOT_MARGIN - PLAYER_HEIGHT;
    p1->rect.w = PLAYER_WIDTH;
    p1->rect.h = PLAYER_HEIGHT;
    p1->health = 6;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < ENEMY_COUNT_X; j++)
        {
            enemies[(i * ENEMY_COUNT_X) + j].rect.x = (WINDOW_WIDTH / 40) + ENEMY_SIZE / 4 * 3 + j * ENEMY_SIZE + (WINDOW_WIDTH / 31) * j;
            enemies[(i * ENEMY_COUNT_X) + j].rect.y = TOP_MARGIN + ENEMY_SIZE * (1.5 + i) + (WINDOW_WIDTH / 45) * i;
            enemies[(i * ENEMY_COUNT_X) + j].rect.w = ENEMY_SIZE;
            enemies[(i * ENEMY_COUNT_X) + j].rect.h = ENEMY_SIZE;

            if (i == 0)
                enemies[(i * ENEMY_COUNT_X) + j].health = 4, enemies[(i * ENEMY_COUNT_X) + j].damage = 0, enemies[(i * ENEMY_COUNT_X) + j];
            else if (i < 3)
                enemies[(i * ENEMY_COUNT_X) + j].health = 2, enemies[(i * ENEMY_COUNT_X) + j].damage = 2, enemies[(i * ENEMY_COUNT_X) + j];
            else
                enemies[(i * ENEMY_COUNT_X) + j].health = 1, enemies[(i * ENEMY_COUNT_X) + j].damage = 4, enemies[(i * ENEMY_COUNT_X) + j];
        }
    }

    bool moveR = false;
    bool moveL = false;
    bool shoot = false;

    SDL_Surface *imageSurface = IMG_Load("src/imgs/ship.png");
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("src/imgs/BackEnemy.png");
    SDL_Texture *backEnemy = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("src/imgs/MidEnemy.png");
    SDL_Texture *midEnemy = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("src/imgs/FrontEnemy.png");
    SDL_Texture *frontEnemy = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    imageSurface = IMG_Load("src/imgs/Boss.png");
    SDL_Texture *bossImg = SDL_CreateTextureFromSurface(rend, imageSurface);
    SDL_FreeSurface(imageSurface);

    enemyShot = 0;

    SDL_Event event;
    int quit = 0;
    while (!quit)
    {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderClear(rend);

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;

            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_a:

                    moveL = false;
                    moveR = true;
                    break;

                case SDLK_d:
                    moveL = true;
                    moveR = false;
                    break;

                case SDLK_w:
                    if (lastShot + SHOT_DELAY <= SDL_GetTicks() && !shoot)
                    {
                        lastShot = SDL_GetTicks();
                        struct shot *tmp = realloc(shots, (shotCount + 1) * sizeof(struct shot));
                        if (tmp != NULL)
                        {
                            shots = tmp;
                            shots[shotCount].rect.x = p1->rect.x + PLAYER_WIDTH / 2 - 2;
                            shots[shotCount].rect.y = p1->rect.y - SHOT_HEIGHT;
                            shots[shotCount].rect.w = SHOT_WIDTH;
                            shots[shotCount].rect.h = SHOT_HEIGHT;
                            shotCount++;
                            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
                            SDL_RenderFillRect(rend, &(shots[shotCount - 1].rect));
                        }
                        shoot = true;
                    }
                    break;

                default:
                    break;
                }
                break;

            case SDL_KEYUP:

                switch (event.key.keysym.sym)
                {
                case SDLK_a:

                    moveR = false;
                    break;

                case SDLK_d:
                    moveL = false;
                    break;

                case SDLK_w:
                    shoot = false;

                default:
                    break;
                }
                break;

            default:
                break;
            }

        if (moveR)
            p1->rect.x -= PLAYER_SPEED, p1->rect.x - SIDE_MARGIN < 0 ? p1->rect.x += PLAYER_SPEED : p1->rect.x;
        else if (moveL)
            p1->rect.x += PLAYER_SPEED, p1->rect.x + PLAYER_WIDTH + SIDE_MARGIN > WINDOW_WIDTH ? p1->rect.x -= PLAYER_SPEED : p1->rect.x;

        int finalShots = shotCount;

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        for (int i = 0; i < shotCount; i++)
        {
            bool hit = false;

            if (SDL_HasIntersection(&boss.rect, &shots[i].rect))
                hit = true, boss.helath--;

            for (int j = 0; j < ENEMY_COUNT_X * 5 && !hit; j++)
                if (SDL_HasIntersection(&enemies[j].rect, &shots[i].rect) && enemies[j].health > 0)
                    hit = true, enemies[j].health--;

            shots[i].rect.y -= SHOT_SPEED;
            if (shots[i].rect.y + SHOT_HEIGHT <= 0 || hit)
                finalShots--;
            else
                SDL_RenderFillRect(rend, &(shots[i].rect));
        }

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < ENEMY_COUNT_X; j++)
                if (enemies[i * ENEMY_COUNT_X + j].health > 0)
                    if (i == 0)
                        SDL_RenderCopy(rend, backEnemy, NULL, &enemies[(i * ENEMY_COUNT_X) + j].rect);
                    else if (i < 3)
                        SDL_RenderCopy(rend, midEnemy, NULL, &enemies[(i * ENEMY_COUNT_X) + j].rect);
                    else
                        SDL_RenderCopy(rend, frontEnemy, NULL, &enemies[(i * ENEMY_COUNT_X) + j].rect);
        }

        if (boss.rect.x < WINDOW_WIDTH && boss.rect.x + BOSS_WIDTH > 0)
            boss.rect.x += BOSS_SPEED * boss.direction, SDL_RenderCopy(rend, bossImg, NULL, &boss.rect);
        else
        {
            int tmp = rand() % 140;
            if (tmp == 136 || tmp == 135)
            {
                if (tmp % 2 == 0)
                    boss.rect.x = 1 - BOSS_WIDTH, boss.direction = 1;
                else
                    boss.rect.x = WINDOW_WIDTH - 1, boss.direction = -1;
            }
        }

        memmove(shots, shots + (shotCount - finalShots), shotCount * sizeof(struct shot));
        struct shot *tmp = realloc(shots, shotCount * sizeof(struct shot));
        shots = tmp;

        shotCount = finalShots;

        if (enemyShot + 500 <= SDL_GetTicks())
        {

            enemyShot = SDL_GetTicks();

            int first[ENEMY_COUNT_X];
            for (int i = 0; i < ENEMY_COUNT_X; i++)
                first[i] = 0;

            for (int i = ENEMY_COUNT_X; i < 5 * ENEMY_COUNT_X; i++)
            {
                if (enemies[i].health > 0)
                    first[i % ENEMY_COUNT_X] = i;
            }

            for (int i = 0; i < ENEMY_COUNT_X; i++)
            {
                int random = rand() % ENEMY_COUNT_X;
                if (first[random] != 0)
                {
                    tmp = realloc(enemyShots, (enemyShotCount + 1) * sizeof(struct shot));
                    if (tmp != NULL)
                    {
                        enemyShots = tmp;
                        enemyShots[enemyShotCount].rect.x = enemies[first[random]].rect.x + ENEMY_SIZE / 2;
                        enemyShots[enemyShotCount].rect.y = enemies[first[random]].rect.y + ENEMY_SIZE;
                        enemyShots[enemyShotCount].rect.w = SHOT_WIDTH;
                        enemyShots[enemyShotCount].rect.h = SHOT_HEIGHT;
                        enemyShotCount++;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        finalShots = enemyShotCount;

        for (int i = 0; i < enemyShotCount; i++)
        {
            bool hit = false;

            if (SDL_HasIntersection(&p1->rect, &enemyShots[i].rect))
                hit = true, p1->health -= 3;

            enemyShots[i].rect.y += SHOT_SPEED;
            if (enemyShots[i].rect.y + SHOT_HEIGHT > WINDOW_HEIGHT || hit)
                finalShots--;
            else
                SDL_RenderFillRect(rend, &(enemyShots[i].rect));
        }

        memmove(enemyShots, enemyShots + (enemyShotCount - finalShots), enemyShotCount * sizeof(struct shot));
        tmp = realloc(enemyShots, enemyShotCount * sizeof(struct shot));
        enemyShots = tmp;

        enemyShotCount = finalShots;

        SDL_RenderCopy(rend, imageTexture, NULL, &(p1->rect));
        SDL_RenderPresent(rend);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
        if (boss.helath < 1 || p1->health < 1)
            quit = 1;
    }

    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    free(p1);
    free(shots);

    return 0;
}
