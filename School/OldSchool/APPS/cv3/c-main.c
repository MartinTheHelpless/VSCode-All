#include <stdio.h>
#include <math.h>
#include <stdint.h>

char pal[] = "aaabaa";

int data[] = {-1, 2, 4, 6, 8, 10, 12, 14, 16, 18};

int length = 10;

int res;

int fib = 2;

int resF = 0;

int pt = 0;

void min();

void fibonacci();

void palindrom();

int main(int argc, char const *argv[])
{

    min();

    for (int i = 0; i < length; i++)
    {
        printf("Arrax[%d] = %d\n", i, data[i]);
    }
    printf("\n");

    fibonacci();

    printf("Fibonacci n. %d --- %d\n", fib, resF);

    palindrom();

    printf("The chosen word is %s\n", pt == 0 ? "a palindrome." : "not a palindrome."); //

    return 0;
}