#include <iostream>
#include <ranges>
#include <vector>
#include <functional>
#include <algorithm>
#include <ranges>
#include <chrono>
#include <numeric>

int CountOddNumbersInRange1(std::vector<int> &vec, const std::function<int(int)> &func)
{
    return std::ranges::count_if(vec, func);
}

int CountOddNumbersInRange2(std::vector<int> &vec, const std::function<int(int)> &func)
{
    return std::transform_reduce(vec.begin(), vec.end(), 0, std::plus<>(),
                                 [&func](int num)
                                 { return func(num); });
}

int CountOddNumbersInRange3(std::vector<int> &vec, const std::function<int(int)> &func)
{
    int a = 0;
    for (int t : vec)
        if (t % 2 == 0)
            a++;
    return a;
}

int CountOddNumbersInRange4(std::vector<int> &vec, const std::function<int(int)> &func)
{
    int a = 0;
    for (int t : vec)
        (t % 2 == 0 ? a++ : a);

    return a;
}

int CountOddNumbersInRange5(std::vector<int> &vec, const std::function<int(int)> &func)
{
    return std::accumulate(vec.begin(), vec.end(), 0,
                           [&](int count, int num)
                           { return count + (func(num) ? 1 : 0); });
}

template <typename Func>

void MeasureAverageFunctionRuntime(std::vector<int> &vec, Func func, const std::function<int(int)> &lambda)
{
    auto start_time = std::chrono::steady_clock::now();

    for (int i = 0; i < 1000000; i++)
        func(vec, lambda);

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

    std::cout << "Execution time per one function call: " << duration.count() / 1000000 << " nanoseconds" << std::endl;
}

int main(int argc, char const *argv[])
{

    std::vector<int> vec = {12, 4, 5, 6, 9, 7, 12, 654, 61, 6, 16, 464, 68,
                            6, 4, 624, 64, 165, 4, 97, 9, 9, 11, 65, 13, 21};

    auto lambda = [](int value)
    { return value % 2 == 0; };

    MeasureAverageFunctionRuntime(vec, CountOddNumbersInRange1, lambda);
    MeasureAverageFunctionRuntime(vec, CountOddNumbersInRange2, lambda);
    MeasureAverageFunctionRuntime(vec, CountOddNumbersInRange3, lambda);
    MeasureAverageFunctionRuntime(vec, CountOddNumbersInRange4, lambda);
    MeasureAverageFunctionRuntime(vec, CountOddNumbersInRange5, lambda);

    return 0;
}
