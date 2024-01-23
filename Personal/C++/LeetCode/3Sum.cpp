#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> threeSum(std::vector<int> &nums);

int main(int argc, char const *argv[])
{
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};

    std::vector<std::vector<int>> res = threeSum(nums);

    for (const auto &v : res)
    {
        for (int num : v)
            std::cout << num << " ";
        std::cout << std::endl;
    }

    return 0;
}

std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
{
    std::vector<std::vector<int>> res;

    std::sort(nums.begin(), nums.end());

    int n = nums.size();

    for (int i = 0; i < n - 2; ++i)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int target = -nums[i];
        int left = i + 1;
        int right = n - 1;

        while (left < right)
        {
            int sum = nums[left] + nums[right];

            if (sum < target)
                ++left;
            else if (sum > target)
                --right;
            else
            {
                res.push_back({nums[i], nums[left], nums[right]});

                while (left < right && nums[left] == nums[left + 1])
                    ++left;
                while (left < right && nums[right] == nums[right - 1])
                    --right;

                ++left;
                --right;
            }
        }
    }

    return res;
}
