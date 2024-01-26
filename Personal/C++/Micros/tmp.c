#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printRectangle(char *arr[], int cols, int rows);

void printArray(char *arr[], int start, int x, int width);

int main(int argc, char const *argv[])
{

    int h;
    scanf("%d", &h);

    char *arr = (char *)malloc(sizeof(char) * h * h);

    for (int i = 0; i < h * h; i++)
        arr[i] = '.';

    for (int i = 0; i < h * h; i++)
    {
        if (i % h == 0)
            printf("\n");
        printf("%c%s", arr[i], " ");
    }

    // printArray(&arr, 0, h * h, h);

    printf("%c%s", arr[0], " ");

    printf("%c%s", arr[1], " ");

    printf("%c%s", arr[2], " ");

    printf("%c%s", arr[3], " ");

    printf("%c%s", arr[4], " ");

    printf("\n");
    printf("%c%s", arr[5], " ");

    return 0;
}

void printRectangle(char *arr[], int cols, int rows)
{

    for (int i = 0; i < rows * cols; i++)
    {
        if (i % cols == 0 && i != 0)
            printf("\n");
        printf("%c%s", (*arr)[i], " ");
    }
}

void printArray(char *arr[], int start, int x, int width)
{

    if (x >= 0 && start < x)
    {
        start % width == 0 ? printf("\n") : printf("");
        printf("%c%s", (*arr)[start], " ");
        printArray(arr, start + 1, x, width);
    }
}
