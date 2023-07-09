#include <iostream>
#include <vector>
#include "Matrix.cpp"

bool vTrue(std::vector<int> a, int x);

bool isUni(int *x, int n);

int main(int argc, char const *argv[])
{

    std::vector<int> a;

    int n = 10;

    int array[n] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    isUni(array, n) == true ? printf("Yes\n") : printf("Nope\n");

    /*int n = 12;

    for (size_t i = 1; i < n + 1; i++)
        a.push_back(i);

    vTrue(a, 13) ? printf("True\n") : printf("False\n");

    Matrix x(2, 2);

    x.init();
    x.print();

    Matrix y(2, 2);

    y.init();
    y.print();

    Matrix c(2, 2);

    MMMulti(x, y, c);

    c.print();*/

    return 0;
}

bool vTrue(std::vector<int> a, int x)
{

    for (size_t i = 0; i < a.size(); i++)
    {
        if (x == a[i])
        {
            return true;
        }
    }
    return false;
}

bool isUni(int *x, int n)
{
    for (int j = 0; j < n - 1; j++)
    {
        for (int i = j + 1; i < n; i++)
        {
            if (x[j] == x[i] && i != j)
                return false;
        }
    }
    return true;
}
