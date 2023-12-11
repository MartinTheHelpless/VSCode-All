#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main()
{
    std::unordered_map<char, int> charMap = {
        {'a', 3},
        {'b', 1},
        {'c', 5},
        {'d', 2}
        // Add more characters and their corresponding values if needed
    };

    // Create a vector of pairs to store characters and their integer values
    std::vector<std::pair<char, int>> charVector(charMap.begin(), charMap.end());

    // Sort the vector based on integer values in descending order
    std::sort(charVector.begin(), charVector.end(),
              [](const auto &a, const auto &b)
              {
                  return a.second > b.second;
              });

    // Create the final string by appending characters in the sorted order
    std::string result;
    for (const auto &pair : charVector)
    {
        result += pair.first;
    }

    std::cout << "Resulting string: " << result << std::endl;

    return 0;
}