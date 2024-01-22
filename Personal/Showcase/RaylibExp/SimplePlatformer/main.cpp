#include "raylib.h"
#include <filesystem>

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 600;

    const char *path = "src/tiles/";

    InitWindow(screenWidth, screenHeight, "Process");

    Texture2D run[6];

    int i = 0;
    int multiplier = 1;

    for (const auto &entry : std::filesystem::directory_iterator((std::string)path + "Character/run"))
    {
        const std::string filePath = entry.path().string();

        if (IsFileExtension(filePath.c_str(), ".png"))
        {
            Image tmp = LoadImage(filePath.c_str());
            ImageResize(&tmp, tmp.width * multiplier, tmp.height * multiplier);
            run[i] = LoadTextureFromImage(tmp);
            UnloadImage(tmp);
        }
        i++;
    }
    i = 0;

    /*Texture2D idle = LoadTextureFromImage(LoadImage("src/tiles/Character/Punk_idle.png"));
    Texture2D attack = LoadTextureFromImage(LoadImage("src/tiles/Character/Punk_attack1.png"));
    Texture2D death = LoadTextureFromImage(LoadImage("src/tiles/Character/Punk_death.png"));
    Texture2D jump = LoadTextureFromImage(LoadImage("src/tiles/Character/Punk_jump.png"));*/

    SetTargetFPS(60);

    Vector2 mouse = {0, 0};

    Rectangle player = {screenWidth / 2, screenHeight / 2, 120, 240};

    while (!WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
    {
        mouse = GetMousePosition();
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_D))
        {
            i++;
            i >= 6 ? i = 0 : i;
        }

        DrawTexture(run[i], player.x, player.y, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
