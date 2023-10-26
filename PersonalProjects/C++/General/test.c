#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printRectangle(char *arr[], int cols, int rows);

int main(int argc, char const *argv[])
{

    int cols = 0;
    int rows = 0;
    scanf("%d", &rows);
    scanf("%d", &cols);

    char *arr = (char *)malloc(sizeof(char) * (cols * rows));

    for (int i = 0; i < cols * rows; i++)
        arr[i] = '.';

    int x = 0;
    int y = 0;

    char key = 'k';

    while (key != 'x')
    {

        scanf("%c", &key);

        switch (key)
        {
        case 'o':
            arr[x + y * cols] = 'o';
            break;

        case '>':
            if (x == cols - 1)
                x = 0;
            else
                x++;
            break;

        case '<':
            if (x == 0)
                x += cols - 1;
            else
                x--;
            break;

        case 'v':
            if (y == rows - 1)
                y = 0;
            else
                y++;
            break;

        case '^':
            if (y == 0)
                y = rows - 1;
            else
                y--;
            break;

        default:
            break;
        }
    }

    printRectangle(&arr, cols, rows);

    return 0;
}

void printRectangle(char *arr[], int cols, int rows)
{

    for (int i = 0; i < rows * cols; i++)
    {
        if (i % cols == 0)
            printf("\n");
        printf("%c", (*arr)[i]);
    }
}
