#include <iostream>
#include <cmath>

void bSort(int *pole, int length);

void sSort(int *pole, int length);

bool isSorted(int *pole, int length);

void arrFill(int *pole, int length);

void arrPrint(int *pole, int length);

void printMissing(int *pole, int length, int min, int max);

int main(int argc, char const *argv[])
{

    int n = 200000;

    int pole[n];

    arrFill(pole, n);

    // arrPrint(pole, n);

    sSort(pole, n);

    // arrPrint(pole, n);

    time_t start = time(nullptr);

    sSort(pole, n);

    time_t end = time(nullptr);

    std::cout << "Time: " << end - start << "\n\n";

    // arrPrint(pole, n);

    // printMissing(pole, n, 14, 20);

    return 0;
}

void bSort(int *pole, int length)
{

    for (int i = 0; !isSorted(pole, length); i++)
    {
        i >= length - 1 ? i = 0 : i;

        if (pole[i] > pole[i + 1])
        {
            int temp = pole[i];
            pole[i] = pole[i + 1];
            pole[i + 1] = temp;
        }
    }
}

void sSort(int *pole, int length)
{

    for (int i = 0; i < length; i++)
    {
        int q = i;
        for (int j = i + 1; j < length; j++)
            pole[q] < pole[j] ? q = j : q;

        int tmp = pole[q];
        pole[q] = pole[i];
        pole[i] = q;
    }
}

void printMissing(int *pole, int length, int min, int max)
{
    int poleIn[max - min + 1];

    for (int i = 0; i < length; i++)
        if (min <= pole[i] && max >= pole[i])
            poleIn[pole[i] - min] = pole[i];

    for (int i = 0; i < max - min + 1; i++)
        if (poleIn[i] != i + min)
            printf("Missing: %d\n", i + min);
}

bool isSorted(int *pole, int length)
{
    bool sorted = true;

    for (int i = 0; i < length - 1; i++)
        pole[i] <= pole[i + 1] ? sorted : sorted = false;

    return sorted;
}

void arrFill(int *pole, int length)
{
    for (size_t i = 0; i < length; i++)
        pole[i] = length - i - 1;
}

void arrPrint(int *pole, int length)
{
    for (int i = 0; i < length; i++)
    {
        std::cout << "Array value on position " << i << " is " << pole[i] << std::endl;
    }

    std::cout << "\n";
}
