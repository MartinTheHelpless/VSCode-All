#include <iostream>
#include <vector>
#include <algorithm>

int longestStrChain(std::vector<std::string> &words);

int main(int argc, char const *argv[])
{

    std::vector<std::string> test = {"a", "ab", "ac", "bd", "abc", "abd", "abdd"};

    std::cout << longestStrChain(test) << std::endl;

    return 0;
}

int longestStrChain(std::vector<std::string> &words)
{

    std::vector<std::pair<std::string, std::pair<int, int>>> mapa;

    if (words.size() == 0)
        return 0;
    else if (words.size() == 1)
        return 1;

    sort(words.begin(), words.end(), true);

    int longest = 0;

    for (int i = 0; i < words.size(); i++)
    {

        int longestCurrent = 1;
        std::string word = words[i];

        for (int j = i + 1; j < words.size(); j++)
        {
            if (words[j].length() == word.length() + 1)
            {
                int changes = 0;
                for (int o = 0; o < word.length() && changes <= 1; o++)
                {
                    std::string tmp = words[j];
                    if (word[o] != words[j][o + changes])
                    {
                        changes++;
                        o--;
                        continue;
                    }
                }

                if (changes == 1 || changes == 0)
                {
                    if (words[j + 1].length() == words[j].length())
                        mapa.push_back({word, {j + 1, longestCurrent}});

                    word = words[j], longestCurrent++;
                }
            }
        }

        if (longest < longestCurrent)
            longest = longestCurrent;

        if (longest + i + 1 >= words.size())
            break;
    }

    for (int i = 0; i < mapa.size(); i++)
    {

        int longestCurrent = mapa[i].second.second;
        std::string word = mapa[i].first;

        for (int j = mapa[i].second.first; j < words.size(); j++)
        {
            if (words[j].length() == word.length() + 1)
            {
                int changes = 0;
                for (int o = 0; o < word.length() && changes <= 1; o++)
                {
                    std::string tmp = words[j];
                    if (word[o] != words[j][o + changes])
                    {
                        changes++;
                        o--;
                        continue;
                    }
                }

                if (changes == 1 || changes == 0)
                {
                    if (words[j + 1].length() == words[j].length())
                        mapa.push_back({word, {j + 1, longestCurrent}});

                    word = words[j], longestCurrent++;
                }
            }
        }

        if (longest < longestCurrent)
            longest = longestCurrent;

        if (longest + i + 1 >= words.size())
            break;
    }

    return longest;
}