#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
    std::vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    int counts[arr.size()];

    for (int i = 0; i < arr.size(); i++)
        counts[i] = 0;

    for (int i = 0; i < arr.size() - 1; i++)
        for (int a = i + 1; a < arr.size(); a++)
            if (arr[i] > arr[a])
                counts[i]++;
            else
                counts[a]++;

    int finalArr[arr.size()];

    for (int i = 0; i < arr.size(); i++)
        finalArr[counts[i]] = arr[i];

    for (int i = 0; i < arr.size(); i++)
        std::cout << i + 1 << ". " << finalArr[i] << std::endl;

    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < arr.size(); i++)
    {
        if (min > arr[i])
            min = arr[i];
        if (max < arr[i])
            max = arr[i];
    }

    std::cout << min << " ---------------------------------------- " << max << std::endl;

    int tmpArr[max + 1];

    for (int i = 0; i < max + 1; i++)
        tmpArr[i] = 0;

    for (int i = 0; i < arr.size(); i++)
        tmpArr[arr[i]]++;

    for (int i = 1; i < max + 1; i++)
        tmpArr[i] += tmpArr[i - 1];

    int another[max + 1];

    for (int i = 0; i < max + 1; i++)
        std::cout << i << ". " << tmpArr[i] << std::endl;

    std::cout << min << " ---------------------------------------- " << max << std::endl;

    for (int i = 0; i < arr.size(); i++)
    {
        another[tmpArr[arr[i]]--] = arr[i];
    }

    for (int i = min; i < max; i++)
        std::cout << i + 1 << ". " << another[i] << std::endl;

    return 0;
}
