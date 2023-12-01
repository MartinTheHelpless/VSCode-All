#include <iostream>
#include <Windows.h>

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 0.0f;
float fPlayerY = 0.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

int main(int argc, char const *argv[])
{

    int screenSize = nScreenHeight * nScreenWidth;

    // Create a new screen buffer (normal printing is too slow to run a game)
    char *screen = new char[screenSize];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    std::wstring map;

    map += L"################";

    for (int i = 16; i < nMapHeight - 2; i++)
        map += L"#..............#";

    map += L"################";

    while (true)
    {

        for (int i = 0; i < nScreenWidth; i++)
        {
            /* code */
        }

        screen[screenSize - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, screenSize, {0, 0}, &dwBytesWritten);
    }

    return 0;
}
