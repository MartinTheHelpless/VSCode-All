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

void quickSort(std::vector<int> *vect)
{
    int size = (*vect).size();

    int tmp[size];

    for (int i = 0; i < size; i++)
        tmp[i] = (*vect)[i];

    quickSort(*tmp, 0, size);

    for (int i = 0; i < size; i++)
        (*vect).pop_back();

    for (int i = 0; i < size; i++)
        (*vect).push_back(tmp[i]);
}

bool isSorted(int &arr, int n)
{
    for (int i = 1; i < n; i++)
        if ((&arr)[i] < (&arr)[i - 1])
            return false;

    return true;
}

bool isSorted(std::vector<int> *vect)
{
    for (int i = 1; i < (*vect).size(); i++)
        if ((*vect)[i] < (*vect)[i - 1])
            return false;

    return true;
}

int main(int argc, char const *argv[])
{

    srand(time(NULL));

    int length = 50;

    std::vector<int> randArr;

    for (int i = 0; i < length; i++)
        randArr.push_back(rand() % 50);

    std::cout << (isSorted(&randArr) ? "Sorted" : "Not Sorted") << std::endl;

    quickSort(&randArr);

    std::cout << (isSorted(&randArr) ? "Sorted" : "Not Sorted") << std::endl;

    return 0;
}
