#include <iostream>
#include <string>

bool isMatch(const std::string &s, const std::string &p);

int main(int argc, char const *argv[])
{
    std::string s = "abcdede";
    std::string p = "ab.*de";

    std::cout << (isMatch(s, p) ? "Match found. String is correct." : "Match not found.") << std::endl;

    return 0;
}

bool isMatch(const std::string &s, const std::string &p)
{
    int sIndex = 0, pIndex = 0;

    while (pIndex < p.length())
    {
        char patternChar = p[pIndex];

        if (pIndex + 1 < p.length() && p[pIndex + 1] == '*')
        {
            pIndex += 2;

            while (sIndex < s.length() && (s[sIndex] == patternChar || patternChar == '.'))
            {
                if (isMatch(s.substr(sIndex), p.substr(pIndex)))
                {
                    return true;
                }

                sIndex++;
            }
        }
        else
        {
            if (sIndex < s.length() && (s[sIndex] == patternChar || patternChar == '.'))
            {
                sIndex++;
                pIndex++;
            }
            else
            {
                return false;
            }
        }
    }

    return sIndex == s.length() && pIndex == p.length();
}

/*int delim = 0;

    bool match = true;
    int i = 0;
    bool repeat = false;

    while (match && delim < c.size() && i < s.length() + 1)
    {

        if (c[delim].length() == 2 && c[delim][1] == '*' || c[delim][0] == '*')
            if (c[delim][0] == '.')
            {
                if (delim + 1 < c.size() && c[delim + 1][0] != '.')
                {
                    delim++;
                    while (s[i] != c[delim][0] && s[i] != 0)
                    {
                        i++;
                        repeat = true;
                    }
                    if (s[i] == 0)
                    {
                        match = false;
                        break;
                    }
                }
                else if (delim + 1 < c.size() && c[delim + 1][0] != '.')
                {
                    i = s.length();
                    break;
                }
                else
                    delim++;
            }
            else
            {
                while (s[i] == c[delim][0] && s[i] != 0)
                {
                    i++;
                    repeat = true;
                }

                if (delim + 1 < c.size() && c[delim + 1][0] == c[delim][0])
                    for (int j = 0; c[delim + 1][j] == c[delim][0]; j++)
                        i--;

                delim++;
            }
        else
        {
            for (char t : c[delim])
            {
                if (repeat && t == s[i - 1])
                {
                    i++;
                }
                else if (t == '.' && i < s.length() && s[i] != 0)
                    i++;
                else if (t != 0 && t != s[i])
                {
                    match = false;
                    break;
                }
                else
                    i++;
                repeat = false;
            }
            delim++;
        }
    }

    if ((i < s.length() || (i < s.length() && c[delim - 1][0] != '.' && c[delim - 1].length() != 2)) && c[delim - 1] != ".*")
        match = false;

    return match;*/