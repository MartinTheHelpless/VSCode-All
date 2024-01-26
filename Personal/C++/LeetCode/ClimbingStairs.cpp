#include <iostream>
#include <cmath>

int climbStairs(int n);

int factorial(int n);

int main(int argc, char const *argv[])
{

    std::cout << climbStairs(44) << std::endl;

    return 0;
}

int climbStairs(int n)
{

    int res = factorial(22);

    for (int i = 0; i < n; i++)
    {
        /* code */
    }

    return res;
}

int factorial(int n)
{
    if (n == 0)
        return 1;
    else if ((n - 1) >= 0 && (n - 2) < 0)
        return climbStairs(n - 1);
    else
        return climbStairs(n - 1) + climbStairs(n - 2);
}

/*
    if (n == 0)
        return 1;
    else if ((n - 1) >= 0 && (n - 2) < 0)
        return climbStairs(n - 1);
    else
        return climbStairs(n - 1) + climbStairs(n - 2);
*/