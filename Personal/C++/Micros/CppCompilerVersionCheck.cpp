#include <iostream>

int main(int argc, char const *argv[])
{
    if (__cplusplus == 202002L)
        std::cout << "C++20" << std::endl;
    else if (__cplusplus == 201703L)
        std::cout << "C++17" << std::endl;
    else if (__cplusplus == 201402L)
        std::cout << "C++14" << std::endl;
    else if (__cplusplus == 201103)
        std::cout << "C++11" << std::endl;
    else if (__cplusplus == 199711L)
        std::cout << "C++98" << std::endl;
    else
        std::cout << "Pre-standard C++" << std::endl;
    return 0;
}
