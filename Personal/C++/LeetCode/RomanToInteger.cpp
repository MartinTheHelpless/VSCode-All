#include <iostream>
#include <unordered_map>

int romanToInt(std::string s);

int main(int argc, char const *argv[])
{

    std::cout << romanToInt("MCMXCIV") << std::endl;
    return 0;
}
int romanToInt(std::string s)
{

    std::unordered_map<char, int> map = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

    int res = 0;

    for (int i = 0; i < s.length(); i++)
        if (i + 1 < s.length() && map[s[i]] < map[s[i + 1]])
            res -= map[s[i]];
        else
            res += map[s[i]];

    return res;
}