#include <iostream>

void power(int *y);

void powe2(int y);

int main(int argc, char const *argv[])
{

    int variable = 4;

    std::cout << variable << std::endl;

    powe2(variable);

    std::cout << variable << std::endl;

    power(&variable);

    std::cout << variable << std::endl;

    return 0;
}

void powe2(int y)
{
    y = 8;
}

void power(int *y)
{
    (*y) = 8;
}
