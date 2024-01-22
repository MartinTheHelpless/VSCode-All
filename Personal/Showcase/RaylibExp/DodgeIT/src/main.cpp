#include <filesystem>
#include <raylib.h>
#include <iostream>
#include <cstring>
#include <vector>

#include "includes/defines.h"

struct Player
{
    Rectangle rect;
    int hp;
    int speed;
    float moveDelay;
    int power;
    Player() : hp(10), speed(3), moveDelay(200), power(0), rect({75, 75, 40, 40})
    {
    }
};

const float WINDOW_WIDTH = 1080;
const float WINDOW_HEIGHT = 720;

const bool VSYNC = true;

void PlayGame(std::vector<Texture2D> &textures, Rectangle rectangles[], Player &player);

void DrawMainMenu(std::vector<Texture2D> &textures, Rectangle rectangles[]);

void DrawSettings(std::vector<Texture2D> &textures);

int main(int argc, char const *argv[])
{
    std::vector<Texture2D> textures;

    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dodge it!");

    std::string path = "../assets/sprites/";

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        std::filesystem::path filePath = entry.path();

        if (filePath.extension() == ".png")
        {
            Image tmp = LoadImage(filePath.generic_string().c_str());
            Texture2D texture = LoadTextureFromImage(tmp);
            UnloadImage(tmp);

            textures.push_back(texture);

            std::cout << filePath << " - Loaded" << std::endl;
        }
    }

    int appState = 0;

    if (VSYNC)
        SetTargetFPS(60);

    SetWindowIcon(LoadImage("../assets/misc/icon.png"));

    bool closeWindow = false;

    Player player;

    while (!WindowShouldClose() && !closeWindow)
    {
        BeginDrawing();
        ClearBackground({51, 51, 51, 255});

        float scWidth = GetScreenWidth();
        float scHeight = GetScreenHeight();

        switch (appState)
        {
        case 0:
        {
            Rectangle rectangles[] = {{scWidth / 2.0f - (float)MenuTexture(play).width / 2.0f, scHeight / 3.0f, (float)MenuTexture(play).width, (float)MenuTexture(play).height},
                                      {scWidth / 2.0f - (float)MenuTexture(settings).width / 2.0f, scHeight / 2.0f, (float)MenuTexture(settings).width, (float)MenuTexture(settings).height},
                                      {scWidth / 2.0f - (float)MenuTexture(quit).width / 2.0f, scHeight / 3.0f * 2.0f, (float)MenuTexture(quit).width, (float)MenuTexture(quit).height}};

            DrawMainMenu(textures, rectangles);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vector2 mouse = {(float)GetMouseX(), (float)GetMouseY()};

                if (CheckCollisionPointRec(mouse, rectangles[play]))
                    appState = 1;
                else if (CheckCollisionPointRec(mouse, rectangles[settings]))
                    appState = 2;
                else if (CheckCollisionPointRec(mouse, rectangles[quit]))
                    closeWindow = true;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                Vector2 mouse = {(float)GetMouseX(), (float)GetMouseY()};
            }

            break;
        }
        case 1:
        {
            Rectangle rectangles[] = {{scWidth - (GameTexture(menu).width / 2.0f * 1.2f) * 3.0f, GetScreenHeight() / 50.0f, (float)GameTexture(menu).height / 2.0f, (float)GameTexture(menu).height / 2.0f},
                                      {scWidth - (GameTexture(pause).width / 2.0f * 1.2f) * 2.0f, GetScreenHeight() / 50.0f, (float)GameTexture(pause).height / 2.0f, (float)GameTexture(pause).height / 2.0f},
                                      {scWidth - (GameTexture(help).width / 2.0f * 1.2f) * 1.0f, GetScreenHeight() / 50.0f, (float)GameTexture(help).height / 2.0f, (float)GameTexture(help).height / 2.0f}};

            PlayGame(textures, rectangles, player);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vector2 mouse = {(float)GetMouseX(), (float)GetMouseY()};

                if (CheckCollisionPointRec(mouse, rectangles[menu]))
                    appState = 0;
                else if (CheckCollisionPointRec(mouse, rectangles[pause]))
                {
                    Rectangle contin = {scWidth / 2.0f + (float)GameTexture(cont).width * 0.5f, scHeight / 2.0f - (float)GameTexture(cont).height / 2.0f, (float)GameTexture(cont).width, (float)GameTexture(cont).height};
                    Rectangle mainMenu = {scWidth / 2.0f - (float)GameTexture(menu).width * 1.5f, scHeight / 2.0f - (float)GameTexture(menu).height / 2.0f, (float)GameTexture(menu).width, (float)GameTexture(menu).height};

                    bool showPauseMenu = true;

                    while (showPauseMenu)
                    {
                        BeginDrawing();
                        ClearBackground(GRAY);
                        DrawTextureEx(GameTexture(cont), contin, 1.0f, 0.0f);
                        DrawTextureEx(GameTexture(menu), mainMenu, 1.0f, 0.0f);
                        DrawRectangle(scWidth / 8.0f, scHeight / 8.0f, 3.0f * scWidth / 4.0f, 3.0f * scHeight / 4.0f, CLITERAL(Color){255, 255, 255, 0});

                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        {
                            Vector2 mouse = {(float)GetMouseX(), (float)GetMouseY()};

                            if (CheckCollisionPointRec(mouse, contin))
                                showPauseMenu = false;
                            else if (CheckCollisionPointRec(mouse, mainMenu))
                                appState = 0, showPauseMenu = false;
                        }

                        if (WindowShouldClose())
                        {
                            showPauseMenu = false;
                            closeWindow = true;
                        }
                        EndDrawing();
                    }
                }
                else if (CheckCollisionPointRec(mouse, rectangles[help]))
                    appState = 1;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                Vector2 mouse = {(float)GetMouseX(), (float)GetMouseY()};
            }

            if (IsKeyPressed(KEY_W))
            {
                player.rect.y -= PLAYER_JUMP * player.speed;
                if (player.rect.y <= 75)
                    player.rect.y = 75;
                else
                    player.rect.y;
            }
            else if (IsKeyPressed(KEY_S))
            {
                player.rect.y += PLAYER_JUMP * player.speed;
                player.rect.y >= WINDOW_HEIGHT - 95 ? player.rect.y = WINDOW_HEIGHT - 95 : player.rect.y;
            }
            else if (IsKeyPressed(KEY_A))
            {
                player.rect.x -= PLAYER_JUMP * player.speed;
                player.rect.x <= 75 ? player.rect.x = 75 : player.rect.x;
            }
            else if (IsKeyPressed(KEY_D))
            {
                player.rect.x += PLAYER_JUMP * player.speed;
                player.rect.x >= WINDOW_WIDTH - 105 ? player.rect.x = WINDOW_WIDTH - 105 : player.rect.x;
            }
            break;
        }

        default:
            break;
        }

        EndDrawing();
    }

    CloseWindow();

    for (Texture2D text : textures)
        UnloadTexture(text);

    return 0;
}

void PlayGame(std::vector<Texture2D> &textures, Rectangle rectangles[], Player &player)
{

    DrawTextureEx(GameTexture(menu), positionRect(menu), 0.5f, 0.0f);
    DrawTextureEx(GameTexture(pause), positionRect(pause), 0.5f, 0.0f);
    DrawTextureEx(GameTexture(help), positionRect(help), 0.5f, 0.0f);

    for (int i = 0; i < (WINDOW_HEIGHT - 140) / PLAYER_JUMP; i++)
        for (int j = 0; j < (WINDOW_WIDTH - 140) / PLAYER_JUMP; j++)
        {
            Rectangle tmp = {70.0f + PLAYER_JUMP * j, 70.0f + PLAYER_JUMP * i, (float)GameTexture(floor0).width, (float)GameTexture(floor0).height};
            if ((i * j + i % 2 + j % 3 * 4 + i) % 13 == 0)
            {
                DrawTextureEx(GameTexture(floor1), tmp, 0.416666666f, 0.0f);
            }
            else
            {
                DrawTextureEx(GameTexture(floor0), tmp, 0.3125f, 0.0f);
            }
        }

    DrawRectangle(player.rect.x, player.rect.y, player.rect.width, player.rect.height, RED);
}

void DrawMainMenu(std::vector<Texture2D> &textures, Rectangle rectangles[])
{
    DrawTextureEx(MenuTexture(play), positionRect(play), 1.0f, 0.0f);
    DrawTextureEx(MenuTexture(settings), positionRect(settings), 1.0f, 0.0f);
    DrawTextureEx(MenuTexture(quit), positionRect(quit), 1.0f, 0.0f);
}

void DrawSettings(std::vector<Texture2D> &textures)
{
}

void DrawGameGrid()
{
}