#include <iostream>
#include <time.h>

void fillArr(int *pole, int length);

void ascInsertSort(int *pole, int n);

void descInsertSort(int *pole, int n);

void generalInsertSort(int *pole, int n, int direction);

void printArr(int *pole, int n);

bool isSortedAsc(int *pole, int n);

bool isSortedDesc(int *pole, int n);

int main(int argc, char const *argv[])
{
    int length = 20000;

    int desc = 1;

    int asc = 0;

    std::cout << "Start" << std::endl;

    int polei[length];

    fillArr(polei, length);

    if (length <= 20)
        printArr(polei, length);

    generalInsertSort(polei, length, asc);

    if (isSortedAsc(polei, length))
    {
        std::cout << "Array is sorted" << std::endl;
    }
    else
    {
        std::cout << "Array is not sorted" << std::endl;
    }

    if (length <= 20)
        printArr(polei, length);

    generalInsertSort(polei, length, desc);

    if (isSortedDesc(polei, length))
    {
        std::cout << "Array is sorted" << std::endl;
    }
    else
    {
        std::cout << "Array is not sorted" << std::endl;
    }

    if (length <= 20)
        printArr(polei, length);

    return 0;
}

void fillArr(int *pole, int length)
{
    srand(time(nullptr));
    for (int i = 0; i < length; i++)
        pole[i] = rand() % (length + 1 - 0) + 0;
}

void ascInsertSort(int *pole, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (pole[j] < pole[j - 1])
            {
                int temp = pole[j];
                pole[j] = pole[j - 1];
                pole[j - 1] = temp;
            }
            else
                break;
        }
    }
}

void descInsertSort(int *pole, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (pole[j] > pole[j - 1])
            {
                int temp = pole[j];
                pole[j] = pole[j - 1];
                pole[j - 1] = temp;
            }
            else
                break;
        }
    }
}

void generalInsertSort(int *pole, int n, int direction)
{
    for (int i = 0; i < n; i++)
        for (int j = i; j > 0; j--)
            if (direction == 0 ? pole[j] < pole[j - 1] : pole[j] > pole[j - 1])
            {
                int temp = pole[j];
                pole[j] = pole[j - 1];
                pole[j - 1] = temp;
            }
            else
                break;
}

void printArr(int *pole, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << pole[i] << " ";
    std::cout << std::endl;
}

bool isSortedAsc(int *pole, int n)
{
    bool sorted = true;
    for (int i = 0; i < n - 1; i++)
    {
        pole[i] <= pole[i + 1] ? sorted : sorted = false;
    }
    return sorted;
}

bool isSortedDesc(int *pole, int n)
{
    bool sorted = true;
    for (int i = 0; i < n - 1; i++)
    {
        pole[i] >= pole[i + 1] ? sorted : sorted = false;
    }
    return sorted;
}
