#include "tasks.h"
#include <iostream>

std::string camel_to_snake(std::string input)
{

    std::string result = "";

    for (int i = 0; i < input.length(); i++)
    {
        if (isupper(input[i]) && i != 0)
            result += '_', result += tolower(input[i]);
        else if (isupper(input[i]) && i == 0)
            result += tolower(input[i]);
        else
            result += input[i];
    }

    return result;
}

int main(int argc, char const *argv[])
{
    std::string tmp = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

    std::cout << camel_to_snake(tmp) << std::endl;

    return 0;
}
