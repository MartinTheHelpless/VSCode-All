#include <raylib.h>

#define PLAYER_JUMP 50

#define MENU_TEXTURE_OFFSET 0

enum menu
{
    play,
    settings,
    quit,

    GAME_TEXTURE_OFFSET
};

enum game
{
    menu,
    pause,
    help,
    cont, // continue
    floor0,
    floor1,

    OPTIONS_TEXTURE_OFFSET
};

#define DrawTextureEx(texture, rectangle, scale, rotation) DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, {(float)rectangle.x, (float)rectangle.y, (float)texture.width / (1 / scale), (float)texture.height / (1 / scale)}, {0, 0}, rotation, WHITE);

#define GameTexture(x) textures[GAME_TEXTURE_OFFSET + x]
#define MenuTexture(x) textures[MENU_TEXTURE_OFFSET + x]

#define positionRect(x) rectangles[x]
