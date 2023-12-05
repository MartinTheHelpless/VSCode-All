#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{

    FILE *file = fopen("lines.txt", "r");

    int total = 0;

    char c;

    int i = 0;

    char num[3];
    c = fgetc(file);
    while (c != EOF)
    {
        if (isdigit(c) && i == 0)
        {
            num[0] = c;
            i++;
        }
        else if (isdigit(c) && i >= 1)
        {
            num[1] = c;
            num[2] = '\0';
            i = 2;
        }
        else if (c == '\n')
        {
            if (i == 2)
            {
                total += std::stoi(num);
            }
            else if (i == 1)
            {
                num[1] = num[0];
                // num[0] = ' ';
                num[2] = '\0';
                total += std::stoi(num);
            }
            std::cout << total << std::endl;
            i = 0;
        }
        c = fgetc(file);
    }

    std::cout << total << std::endl;

    return 0;
}
