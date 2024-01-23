#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2);

int main(int argc, char const *argv[])
{

    std::vector<int> a = {1, 2};
    std::vector<int> b = {3};

    double x = findMedianSortedArrays(a, b);

    std::cout << (double)x << std::endl;

    return 0;
}

double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2)
{

    std::vector<int> tmp;

    while (nums1.size() > 0)
    {
        tmp.push_back(nums1[nums1.size() - 1]);
        nums1.pop_back();
    }

    while (nums2.size() > 0)
    {
        tmp.push_back(nums2[nums2.size() - 1]);
        nums2.pop_back();
    }

    std::sort(tmp.begin(), tmp.end());

    if (tmp.size() % 2 == 0)
        return (tmp[(tmp.size() / 2.0f)] + tmp[(tmp.size() / 2.0f) - 1]) / 2.0f;
    else
        return tmp[tmp.size() / 2];
}