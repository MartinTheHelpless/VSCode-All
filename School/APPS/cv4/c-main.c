#include <stdio.h>

int my_strchr(char *str, char to_find, int *count);
char string1[] = "Ahoj svete! EeEe";
char to_find = 'e';
int count;
char help;
char hel;

char string[] = "Ahoj svete";
char buff[255];
int size = 5;
void my_strcpy(char *to, char *from, long max);

int main(int argc, char const *argv[])
{
    int first = my_strchr(string1, to_find, &count);

    // int first = my_strchr(string, to_find, &count);

    my_strcpy(buff, string, size);

    printf("Copied string: %s\n", buff);

    printf("First position: %d\n", first);

    return 0;
}