#include <SDL2/SDL.h>

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

const int GAME_WIDTH = 28; // (28 : 36 tiles original Pac Man Game)
const int GAME_HEIGHT = 36;

const int TILE_DIM = 20;
const int ENTITY_DIM = 30;

const int WINDOW_WIDTH = GAME_WIDTH * TILE_DIM; // 3 : 4
const int WINDOW_HEIGHT = GAME_HEIGHT * TILE_DIM;

// --------------------------------------------------------------------------------------------
// -------------------------------------- MAP DEFINITION START --------------------------------
// --------------------------------------------------------------------------------------------

// std::string map = ".............................oooooooooooo..oooooooooooo..o....o.....o..o.....o....o..x....o.....o..o.....o....x..o....o.....o..o.....o....o..oooooooooooooooooooooooooo..o....o..o........o..o....o..o....o..o........o..o....o..oooooo..oooo..oooo..oooooo.......o.....e..e.....o............o.....e..e.....o............o..eeeeeeeeee..o............o..e...gg...e..o............o..e.eeeeee.e..o......eeeeeeoeee.eeeeee.eeeoeeeeee......o..e.eeeeee.e..o............o..e........e..o............o..eeeeeeeeee..o............o..e........e..o............o..e........e..o.......oooooooooooo..oooooooooooo..o....o.....o..o.....o....o..o....o.....o..o.....o....o..xoo..ooooooo..ooooooo..oox....o..o..o........o..o..o......o..o..o........o..o..o....oooooo..oooo..oooo..oooooo..o..........o..o..........o..o..........o..o..........o..oooooooooooooooooooooooooo.............................";
/*std::wstring map;
map += L"............................";
map += L".oooooooooooo..oooooooooooo.";
map += L".o....o.....o..o.....o....o.";
map += L".x....o.....o..o.....o....x.";
map += L".o....o.....o..o.....o....o.";
map += L".oooooooooooooooooooooooooo.";
map += L".o....o..o........o..o....o.";
map += L".o....o..o........o..o....o.";
map += L".oooooo..oooo..oooo..oooooo.";
map += L"......o.....e..e.....o......";
map += L"......o.....e..e.....o......";
map += L"......o..eeeeeeeeee..o......";
map += L"......o..e...gg...e..o......";
map += L"......o..e.eeeeee.e..o......";
map += L"eeeeeeoeee.eeeeee.eeeoeeeeee";
map += L"......o..e.eeeeee.e..o......";
map += L"......o..e........e..o......";
map += L"......o..eeeeeeeeee..o......";
map += L"......o..e........e..o......";
map += L"......o..e........e..o......";
map += L".oooooooooooo..oooooooooooo.";
map += L".o....o.....o..o.....o....o.";
map += L".o....o.....o..o.....o....o.";
map += L".xoo..ooooooo..ooooooo..oox.";
map += L"...o..o..o........o..o..o...";
map += L"...o..o..o........o..o..o...";
map += L".oooooo..oooo..oooo..oooooo.";
map += L".o..........o..o..........o.";
map += L".o..........o..o..........o.";
map += L".oooooooooooooooooooooooooo.";
map += L"............................";*/

char map[31][29] =
    {
        "............................",
        ".oooooooooooo..oooooooooooo.",
        ".o....o.....o..o.....o....o.",
        ".x....o.....o..o.....o....x.",
        ".o....o.....o..o.....o....o.",
        ".oooooooooooooooooooooooooo.",
        ".o....o..o........o..o....o.",
        ".o....o..o........o..o....o.",
        ".oooooo..oooo..oooo..oooooo.",
        "......o.....e..e.....o......",
        "......o.....e..e.....o......",
        "......o..eeeeeeeeee..o......",
        "......o..e........e..o......",
        "......o..e...ee...e..o......",
        "eeeeeeoeee.eeeeee.eeeoeeeeee",
        "......o..e........e..o......",
        "......o..e........e..o......",
        "......o..eeeeeeeeee..o......",
        "......o..e........e..o......",
        "......o..e........e..o......",
        ".oooooooooooo..oooooooooooo.",
        ".o....o.....o..o.....o....o.",
        ".o....o.....o..o.....o....o.",
        ".xoo..oooooooeeooooooo..oox.",
        "...o..o..o........o..o..o...",
        "...o..o..o........o..o..o...",
        ".oooooo..oooo..oooo..oooooo.",
        ".o..........o..o..........o.",
        ".o..........o..o..........o.",
        ".oooooooooooooooooooooooooo.",
        "............................",
};

// --------------------------------------------------------------------------------------------
// --------------------------------------- MAP DEFINITION END ---------------------------------
// --------------------------------------------------------------------------------------------
// ------------------- Smart pointer helper class (for deleting the objects) ------------------
// --------------------------------------------------------------------------------------------

class SDLClear
{
public:
    void operator()(SDL_Window *window) const
    {
        SDL_DestroyWindow(window);
    }

    void operator()(SDL_Renderer *renderer) const
    {
        SDL_DestroyRenderer(renderer);
    }
};