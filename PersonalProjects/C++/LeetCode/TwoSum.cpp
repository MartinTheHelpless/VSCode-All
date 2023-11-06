#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> test1 = {2, 7, 11, 15};
std::vector<int> test2 = {3, 2, 4};
std::vector<int> test3 = {3, 3};

std::vector<int> twoSum(std::vector<int> &nums, int target);

int main(int argc, char const *argv[])
{

    int target = 9;

    std::cout << "[" << twoSum(test1, target)[0] << ", " << twoSum(test1, target)[1] << "]" << std::endl;

    return 0;
}

std::vector<int> twoSum(std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> numMap;
    int n = nums.size();

    // Build the hash table
    for (int i = 0; i < n; i++)
        numMap[nums[i]] = i;

    // Find the complement
    for (int i = 0; i < n; i++)
    {
        int complement = target - nums[i];
        if (numMap.count(complement) && numMap[complement] != i)
        {
            return {i, numMap[complement]};
        }
    }

    return {}; // No solution found
}
