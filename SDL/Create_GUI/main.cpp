#include "GUIcmp.h"

/*
 A program made enitrely in sdl with GUI components (reusable).
 Includes:
    Password manager (email / nick to login and password)
    Task list for periods of time
    List of desired games (wishlist or task list of games I WANT TO PLAY)
    Calendar (optional)
    List of programs I use (in case of a OS mmigration or new pc to keep track of necessary apps)
    Movie watchlist with possible timestamps (if movie is not finished and wan to continue later)
    Profile / Avatar customisation (just for fun profile cration)
    Notepad to use as a tool to write notes at seminars at school, etc.
    Timetable (optional - would have to be connected to other apps somehow same as calendar)
    Weather report for the week
    ?-?-?-? Nickname randomizer / generator (some fun hobby project for this one - could be anything)
*/

// Unlike a game, no need to refresh the renderer (RendererPresent(rend)) all the time:
//  -refresh only on action (saves a ton of resources)

int main(int argc, char const *argv[])
{

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *win = SDL_CreateWindow("GUI test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720 - 6, SDL_WINDOW_SHOWN);

    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, 0);

    if (sdlTest(win, rend))
        return 1;

    int window = 0;

    /*
    0 - Profile + main dashboard - Widgets (weather, to-do list, birthdays / name days, ...)
    1 - Calendar + Timetable somewhere around here
    2 - Task list with descriptions
    3 - Weather report
    4 - Notepad + file manager for school subjects
    5 - Password manager
    6 - Game list
    7 - Movie list
    8 - Password manager
    */

    int endProgram = 5;

    SDL_RenderPresent(rend);

    while (window != endProgram)
    {

        switch (window)
        {
        case 0:
            /* code */
            break;

        case 1:
            /* code */
            break;

        case 2:
            /* code */
            break;

        case 3:
            /* code */
            break;

        case 4:
            /* code */
            break;

        case 5:
            /* code */
            break;

        default:
            break;
        }
    }

    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    return 0;
}

/*

        bool end = false;
        SDL_Event ev;
        while (!end)
        {
            while (SDL_PollEvent(&ev))
            {
                switch (ev.type)
                {
                case SDL_QUIT:
                    end = true;
                    window = endProgram;
                    break;

                default:
                    break;
                }
            }
        }

*/