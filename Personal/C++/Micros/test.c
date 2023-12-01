// C program for splitting a string
// using strtok()
#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "Geeks-for-Geeks";
    char str2[] = "Geeks for Geeks";

    char *token = strtok(str, "-");

    while (token != NULL)
    {
        printf(" % s\n", token);
        token = strtok(NULL, "-");
    }

    return 0;
}