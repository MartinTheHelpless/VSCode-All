#include <iostream>
#include <vector>
#include <time.h>
#include "Sorts.cpp"

void printArray(int &arr, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << i + 1 << " - " << (&arr)[i] << std::endl;
}

void printVector(std::vector<int> *vect)
{
    for (int i = 0; i < (*vect).size(); i++)
        std::cout << i + 1 << " - " << (*vect)[i] << std::endl;
}

void fillArrWithRands(int &arr, int n, int min, int max)
{
    srand(time(NULL));

    for (int i = 0; i < n; i++)
        (&arr)[i] = min + rand() % (max - min);
}

void fillVectorWithRands(std::vector<int> *vect, int n, int min, int max)
{

    srand(time(NULL));

    if ((*vect).size() != 0)
        for (int i = 0; i < (*vect).size(); i++)
            (*vect).pop_back();

    for (int i = 0; i < n; i++)
        (*vect).push_back(min + rand() % (max - min));
}

void sortVector(std::vector<int> *vect)
{
    int size = (*vect).size();

    int tmp[size];

    for (int i = 0; i < size; i++)
        tmp[i] = (*vect)[i];

    quickSort(*tmp, 0, size - 1);

    for (int i = 0; i < size; i++)
        (*vect).pop_back();

    for (size_t i = 0; i < size; i++)
        (*vect).push_back(tmp[i]);
}

int main(int argc, char const *argv[])
{

    time_t start = time(NULL);

    std::vector<int> vect;

    fillVectorWithRands(&vect, 10000, 0, 10000);

    sortVector(&vect);

    printVector(&vect);

    time_t end = time(NULL);

    std::cout << "Program time: " << end - start << std::endl;

    return 0;
}
