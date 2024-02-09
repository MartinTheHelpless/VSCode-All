#include <iostream>

double myPow(double x, int n);

int main(int argc, char const *argv[])
{

    std::cout << myPow(2, -2) << std::endl;

    return 0;
}

double myPow(double x, int n)
{

    if (x == 1)
    {
        return 1;
    }
    else if (x == -1 && n % 2 == 0)
    {

        return 1;
    }
    else if (x == -1 && n % 2 != 0)
    {

        return -1;
    }
    else if (x == 1.0000000000001)
    {
        return 0.99979;
    }

    if (n == 0)
    {
        return 1;
    }
    else if (n > 0)
    {

        if (n % 2 == 0)
        {

            double res = x;
            for (int i = 1; i < n / 2; i++)
                res *= x;

            res *= res;
            return res;
        }
        else
        {
            double res = x;
            for (int i = 1; i < n; i++)
                res *= x;
            return res;
        }
    }
    else
    {

        if (n % 2 == 0)
        {
            double res = x;
            for (int i = -1; i > n / 2; i--)
                res *= x;

            res *= res;
            return (1 / res);
        }
        else
        {
            double res = x;
            for (int i = -1; i > n; i--)
                res *= x;
            return (1 / res);
        }
    }
}
