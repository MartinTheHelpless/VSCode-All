#include <iostream>
#include <fstream>

void createHeader(char *header);

int result(int input);

int main(int argc, char const *argv[])
{

    char header[256];

    createHeader(header);

    std::cout << result(256) << std::endl;

    return 0;
}

void createHeader(char *header)
{
    header[0] = 'e';
}

int result(int input)
{

    if (input != 1)
        return input + result(input / 2);
    else
        return input;
}
