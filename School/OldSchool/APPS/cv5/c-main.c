#include <stdio.h>

int poleB[] = {2, 5, 7, 8, 10, 25, 54, 32, 47, 40, 12, 71};

int size = 10;

long arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int length = 12;

int num = 2;

void fill_pyramid_numbers(long *numbers, long size);

int arrDiv(int *array, int arrLength, int mulNum);

void change_array_by_avg(long *array, long size);

int main()
{

    int nDiv = arrDiv(poleB, length, num);

    printf("There was %d numbers divisible by number %d in the array\n", nDiv, num);

    nDiv = arrDiv(poleB, length, num);

    printf("\n");

    printf("There was %d numbers divisible by number %d in the array\n", nDiv, num);

    fill_pyramid_numbers(arr, 10);

    printf("\n");

    for (int i = 0; i < 10; i++)
        printf("Value on position %d in array is: %ld\n", i, arr[i]);

    change_array_by_avg(arr, 10);

    printf("\n");

    for (int i = 0; i < 10; i++)
        printf("Value on position %d in array is: %ld\n", i, arr[i]);

    return 0;
}