#include <iostream>
#include "Tree.cpp"

bool binarySearchIter(int *pole, int length, int s);

bool binaryRet(int *arr, int l, int r, int value);

bool isSorted(int *pole, int length);

void arrFill(int *pole, int length);

void arrPrint(int *pole, int length);

int main(int argc, char const *argv[])
{
    int n = 10;

    int pole[n];

    srand(time(nullptr));

    arrFill(pole, n);

    arrPrint(pole, n);

    int x = rand() % 11;

    std::cout << "Value " << x << (binaryRet(pole, 0, n, x) ? " found.\n" : " not found.\n");

    Tree *tree;

    tree->insertValue(10);
    tree->insertValue(5);
    tree->insertValue(15);
    tree->insertValue(13);
    tree->insertValue(8);
    tree->insertValue(4);
    tree->insertValue(1);
    tree->insertValue(21);

    return 0;
}

bool binarySearchIter(int *pole, int length, int s)
{
    int l = 0;
    int r = length - 1;

    while (l <= length)
    {
        int m = (l + r) / 2;

        if (pole[m] == s)
            return true;
        if (pole[m] > s)
            r = m - 1;
        if (pole[m] < s)
            l = m + 1;
    }
    return false;
}

bool binaryRet(int *arr, int l, int r, int value)
{
    if (l > r)
        return false;

    int m = l + (r - l) / 2;

    if (value == arr[m])
        return true;
    if (value < arr[m])
        return binaryRet(arr, l, m - 1, value);
    if (value > arr[m])
        return binaryRet(arr, m + 1, r, value);
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
