#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

bool isMatch(std::string s, std::string p);

int main(int argc, char const *argv[])
{
    std::string s = "aaaaa";
    std::string p = "c*d*f*g*h*j*j*k*l*p*o*u*aaa.a";

    std::cout << (isMatch(s, p) ? "Match found. String is correct." : "Match not found.") << std::endl;

    return 0;
}

bool isMatch(std::string s, std::string p)
{

    std::vector<std::string> c;

    std::string tmp = "";

    for (int i = 0;; i++)
    {
        if (p[i] == '*')
        {
            tmp += p[i];

            if (tmp.length() > 2)
            {
                std::string star;
                star += tmp[tmp.length() - 2];
                star += tmp[tmp.length() - 1];
                tmp = tmp.substr(0, tmp.length() - 2);

                c.push_back(tmp);
                c.push_back(star);
            }
            else
                c.push_back(tmp);
            tmp = "";
        }
        else if (p[i] == '\0')
        {
            if (tmp != "")
                c.push_back(tmp);
            break;
        }
        else
            tmp += p[i];
    }

    int delim = 0;

    bool match = true;

    for (int i = 0; match && delim < c.size();)
    {
        if (c[delim].length() == 2 && c[delim][1] == '*' && c[delim][0] != '.')
        {
            while (s[i] == c[delim][0])
                i++;
            delim++;
        }

        if (strstr(c[delim].c_str(), "*") == nullptr && strstr(c[delim].c_str(), ".") == nullptr)
        {
            int tmp = 0;
            for (int j = 0; j < c[delim].length(); j++)
            {
                if (s[i] != c[delim][tmp])
                {
                    match = false;
                    break;
                }
                else
                {
                    tmp++;
                    i++;
                }
            }
            delim++;
        }
    }

    return match;
}