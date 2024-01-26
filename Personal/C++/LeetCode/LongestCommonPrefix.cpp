#include <iostream>
#include <vector>

std::string longestCommonPrefix(std::vector<std::string> &strs);

int main(int argc, char const *argv[])
{

    std::vector<std::string> tmp = {"flower", "flow", "flight"};

    std::cout << longestCommonPrefix(tmp) << std::endl;

    return 0;
}

std::string longestCommonPrefix(std::vector<std::string> &strs)
{

    std::string pref = "";

    bool prefEnd = false;

    for (int i = 0; i < strs[0].length(); i++)
    {
        for (int j = 1; j < strs.size(); j++)
        {
            if (strs[j][i] == 0 || i >= strs[j].length())
            {
                prefEnd = true;
                break;
            }
            else if (strs[0][i] != strs[j][i])
            {
                prefEnd = true;
                break;
            }
        }
        if (!prefEnd)
            pref += strs[0][i];
    }

    return pref;
}