#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main(int argc, char const *argv[])
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

    for (int num : vec)
        std::cout << num << std::endl;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);

    std::cout << "----------------------" << std::endl;

    for (int num : vec)
        std::cout
            << num << std::endl;

    return 0;
}
