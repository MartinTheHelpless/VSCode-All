#include <vector>
#include <iostream>
#include <filesystem>
#include "raylib.h"

#define TILE_SIZE 16

#define MAP_WIDTH 24

#define MAP_HEIGHT 12

int main(void)
{
    int multiplier = 3;

    const int screenWidth = 24 * TILE_SIZE * multiplier * 1.5;
    const int screenHeight = 12 * TILE_SIZE * multiplier * 1.5;

    std::vector<Texture2D> textures;

    InitWindow(screenWidth, screenHeight, "Process");
    for (const auto &entry : std::filesystem::directory_iterator("src/tiles/chopped"))
    {
        const std::string filePath = entry.path().string();

        if (IsFileExtension(filePath.c_str(), ".png"))
        {
            Image tmp = LoadImage(filePath.c_str());
            ImageResize(&tmp, tmp.width * multiplier, tmp.height * multiplier);
            Texture2D texture = LoadTextureFromImage(tmp);
            textures.push_back(texture);
            UnloadImage(tmp);
        }
    }

    std::vector<std::pair<int, Vector2>> rects;

    int textNum = 0;

    SetTargetFPS(60);

    Vector2 mouse = {0, 0};

    int rotation = 0;

    std::vector<int> rotations;

    Rectangle rect = {};

    while (!WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
    {
        mouse = GetMousePosition();
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float tmp = GetMouseWheelMove();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int x = 1 + mouse.x - ((int)(mouse.x) % (TILE_SIZE * multiplier));
            int y = 1 + mouse.y - ((int)(mouse.y) % (TILE_SIZE * multiplier));

            Rectangle tmp = {y, x, textures[textNum].width, textures[textNum].height};
            rects.push_back({textNum, {(float)x, (float)y}});
            rotations.push_back(rotation);
        }

        if (tmp != 0)
        {
            textNum += tmp;
            textNum < 0 ? textNum = (textures.size() - 2) : textNum;
            textNum >= textures.size() ? textNum = 0 : textNum;
            rotation = 0;
        }

        int keyPressed = GetKeyPressed();

        if (keyPressed == KEY_Y && rects.size() > 0)
            rects.pop_back();
        else if (keyPressed == KEY_R)
        {
            rotation += 90;
            rotation >= 360 ? rotation = 0 : rotation;
        }

        for (int i = 0; i < rects.size(); i++)
            DrawTextureEx(textures[rects[i].first], rects[i].second, rotations[i], 1, WHITE);

        int x = 1 + mouse.x - ((int)(mouse.x) % (TILE_SIZE * multiplier));
        int y = 1 + mouse.y - ((int)(mouse.y) % (TILE_SIZE * multiplier));

        DrawTextureEx(textures[textNum], {(float)x, (float)y}, rotation, 1, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
