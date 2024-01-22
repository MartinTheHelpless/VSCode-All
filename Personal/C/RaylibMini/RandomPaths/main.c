#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>

const int screenWidth = 800;
const int screenHeight = 600;

#define NUMBER_OF_RUNS 5
#define NUMBER_OF_STEPS 10000

typedef struct Point
{
    int x;
    int y;
} Point;

Point *random_walk(size_t number_of_steps)
{

    srand(time(NULL));

    Point *pts = (Point *)malloc(sizeof(Point) * number_of_steps);

    pts[0] = (Point){0, 0};

    for (int i = 1; i < number_of_steps; i++)
    {
        Point p = pts[i - 1];
        int r = rand() % 4;
        switch (r)
        {
        case 0:
            p.x += 1;
            break;

        case 1:
            p.x -= 1;
            break;

        case 2:
            p.y += 1;
            break;

        case 3:
            p.y -= 1;
            break;

        default:
            break;
        }

        pts[i] = p;
    }

    return pts;
}

void DrawPath(Point *pts, int number_of_steps, int step_size, Color color)
{

    for (size_t i = 0; i < number_of_steps - 1; i++)
    {
        Point a, b;
        a = pts[i];
        b = pts[i + 1];

        DrawLine(screenWidth / 2 + step_size * a.x, screenWidth / 2 + step_size * a.y, screenWidth / 2 + step_size * b.x, (int)(screenWidth / 2 + step_size * b.y), color);
    }
}

int main(int argc, char const *argv[])
{

    Color colors[NUMBER_OF_RUNS] = {RED, BLUE, GREEN, YELLOW, ORANGE};

    Point **p_pts = (Point **)malloc(sizeof(Point *) * NUMBER_OF_RUNS);

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        p_pts[i] = random_walk(NUMBER_OF_STEPS);
    }

    Point tmp[5][NUMBER_OF_STEPS];

    InitWindow(screenWidth, screenHeight, "Raylib Linked Library");

    SetTargetFPS(1);

    int step_size = 5;

    srand(time(NULL));

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        tmp[i][0] = (Point){0, 0};

        for (int j = 1; j < NUMBER_OF_STEPS; j++)
        {
            Point p = tmp[i][j - 1];
            int r = rand() % 4;
            switch (r)
            {
            case 0:
                p.x += 1;
                break;

            case 1:
                p.x -= 1;
                break;

            case 2:
                p.y += 1;
                break;

            case 3:
                p.y -= 1;
                break;

            default:
                break;
            }

            tmp[i][j] = p;
        }
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color){51, 51, 51, 255});

        for (int i = 0; i < NUMBER_OF_RUNS; i++)
        {
            // Draw each path in a separate color
            for (int j = 0; j < NUMBER_OF_STEPS - 1; j++)
            {
                Point a = tmp[i][j];
                Point b = tmp[i][j + 1];
                DrawLine(screenWidth / 2 + step_size * a.x, screenHeight / 2 + step_size * b.y, screenWidth / 2 + step_size * b.x, screenHeight / 2 + step_size * a.y, colors[i]);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
        free(p_pts[i]);

    free(p_pts);

    return 0;
}
