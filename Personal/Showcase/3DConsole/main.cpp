#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <Windows.h>
#include <cmath>
#include <stdio.h>

int nScreenWidth = 170;
int nScreenHeight = 40;

int nMapHeight = 32;
int nMapWidth = 32;

float fPlayerX = 1.0f;        // Starting position X
float fPlayerY = 1.0f;        // Starting position Y
float fPlayerA = 0.0f;        // Player Start Rotation
float fFOV = 3.14159f / 2.0f; // Field of View
float fDepth = 16.0f;         // max render distance
float fSpeed = 5.0f;          // Walk speed
float fRotSpeed = 0.5f;       // Player rotation speed

int main()
{

    int screenSize = nScreenHeight * nScreenWidth;

    // Create a new screen buffer (normal printing is too slow to run a game)
    char *screen = new char[nScreenWidth * nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    std::wstring map;

    /*
                Maze
    map += L"#............###";
    map += L"#..............#";
    map += L"####.#########.#";
    map += L"#....#.......#.#";
    map += L"####.#.#####.#.#";
    map += L"#....#.##..#...#";
    map += L"######.#..##.###";
    map += L"#......#.......#";
    map += L"####.###.#.###.#";
    map += L"#.....####.#.#.#";
    map += L"#.###........#.#";
    map += L"#.#.#.####.##..#";
    map += L"#.#.#......#...#";
    map += L"#.#.###.####.###";
    map += L"#..........#...#";
    map += L"##############!#";
    */

    //          Normal Map
    map += L"#..............................#";
    map += L"###..........##########.########";
    map += L"#.#.########.#.#####..#.#......#";
    map += L"#.#........#.#.................#";
    map += L"#.########.#.###########.#######";
    map += L"#..........#...........#.......#";
    map += L"#####.######.#########.#########";
    map += L"#.###........#..#..............#";
    map += L"#......####.....#####.########.#";
    map += L"#..###########..#.##..#.##...#.#";
    map += L"#.............#.#.##..#....###.#";
    map += L"#..##########.#.#.#..#####.....#";
    map += L"#.............#.#.........##...#";
    map += L"#..############....#####..##.###";
    map += L"#...............#......##.##...#";
    map += L"##############################!#";

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();

    while (true)
    {

        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
            fPlayerA -= (fSpeed * fRotSpeed) * fElapsedTime;

        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
            fPlayerA += (fSpeed * fRotSpeed) * fElapsedTime;

        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
            fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
            fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;

            if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
            {
                fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;
                fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;
            }
        }

        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;
            fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;

            if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
            {
                fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
                fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;
            }
        }

        if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '!')
            break;

        for (int x = 0; x < nScreenWidth; x++)
        {
            float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

            float fStepSize = 0.1f;
            float fDistanceToWall = 0.0f;

            bool bHitWall = false;
            bool bBoundary = false;

            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);

            while (!bHitWall && fDistanceToWall < fDepth)
            {
                fDistanceToWall += fStepSize;
                int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
                {
                    bHitWall = true;
                    fDistanceToWall = fDepth;
                }
                else
                {
                    if (map.c_str()[nTestX * nMapWidth + nTestY] == '#')
                    {
                        bHitWall = true;

                        std::vector<std::pair<float, float>> p; // Distance , Dot

                        for (int tx = 0; tx < 2; tx++)
                        {
                            for (int ty = 0; ty < 2; ty++)
                            {
                                float vy = (float)nTestY + ty - fPlayerY;
                                float vx = (float)nTestX + tx - fPlayerX;
                                float d = sqrt(vx * vx + vy * vy);
                                float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                                p.push_back(std::pair<float, float>(d, dot));
                            }
                        }

                        sort(p.begin(), p.end(), [](const std::pair<float, float> &left, const std::pair<float, float> &right)
                             { return left.first < right.first; });

                        float fBound = 0.01;
                        if (acos(p.at(0).second) < fBound)
                            bBoundary = true;

                        if (acos(p.at(1).second) < fBound)
                            bBoundary = true;

                        if (acos(p.at(2).second) < fBound)
                            bBoundary = true;
                    }
                }
            }

            int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;

            short nShade = ' ';
            if (fDistanceToWall <= fDepth / 4.0f)
                nShade = 178; // Very close
            else if (fDistanceToWall < fDepth / 3.0f)
                nShade = 177;
            else if (fDistanceToWall < fDepth / 2.0f)
                nShade = 176;
            else if (fDistanceToWall < fDepth)
                nShade = 173;
            else
                nShade = ' '; // Too far away

            if (bBoundary)
                nShade = ' '; // Black it out

            for (int y = 0; y < nScreenHeight; y++)
            {
                if (y <= nCeiling)
                    screen[y * nScreenWidth + x] = ' ';
                else if (y > nCeiling && y <= nFloor)
                    screen[y * nScreenWidth + x] = nShade;
                else
                {
                    float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
                    if (b < 0.25)
                        nShade = '#';
                    else if (b < 0.5)
                        nShade = 'x';
                    else if (b < 0.75)
                        nShade = '.';
                    else if (b < 0.9)
                        nShade = '-';
                    else
                        nShade = ' ';
                    screen[y * nScreenWidth + x] = nShade;
                }
            }
        }

        swprintf_s(((wchar_t *)(screen)), 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);

        /*
        for (int nx = 0; nx < nMapWidth; nx++)
            for (int ny = 0; ny < nMapWidth; ny++)
            {
                screen[(ny + 1) * nScreenWidth + nx] = map[ny * nMapWidth + nx];
            }
        screen[((int)fPlayerX + 1) * nScreenWidth + (int)fPlayerY] = 'P';
        */

        // Display Frame
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
    }

    return 0;
}
