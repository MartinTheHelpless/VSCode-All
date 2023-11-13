#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <random>

void insertSort(int &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = (&arr)[i];
        int position = i;

        for (int j = i + 1; j < n; j++)
            if (min > (&arr)[j])
            {
                min = (&arr)[j];
                position = j;
            }

        (&arr)[position] = (&arr)[i];
        (&arr)[i] = min;
    }
}

int partition(int &arr, int low, int high)
{
    int pivot = (&arr)[high];
    int i = (low - 1);

    for (int j = low; j <= high; j++)
        if ((&arr)[j] < pivot)
        {
            i++;
            std::swap((&arr)[i], (&arr)[j]);
        }

    std::swap((&arr)[i + 1], (&arr)[high]);
    return (i + 1);
}

void quickSort(int &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
/*
int main(int argc, char const *argv[])
{

    srand(time(NULL));

    int length = 50;

    int randArr[length];

    for (int i = 0; i < length; i++)
        randArr[i] = rand() % 50;

    quickSort(*randArr, 0, length);

    for (int i = 0; i < length; i++)
        std::cout << i + 1 << " - " << randArr[i] << std::endl;

    return 0;
}
*/