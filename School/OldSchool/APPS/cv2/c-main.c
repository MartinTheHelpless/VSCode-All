#include <stdio.h>
#include <math.h>
#include <stdint.h>

long longs[] = {45, 56, 150, 51, 256, 87, 91, 85, 88, 20};

int max;

void change();

int main(int argc, char const *argv[])
{
    change();
    for (int i = 0; i < 10; i++)
    {
        printf("long[%d] = %li\n", i, longs[i]);
    }

    return 0;
}