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
    std::string tmp = "";

    char current = p[0];

    int count = 0;

    for (int i = 0; i <= p.length(); i++)
    {
        char r = p[i];
        if (r != current && r == '*' && i > 0 && p[i + 1] == current)
        {
            i++;
            while (p[i] == current)
            {
                count++;
                i++;
            }
            count > 0 ? count-- : count;
            tmp += p[i - 1];
            tmp += count + 48;
            tmp.append("+");
            current = p[i];
            count = 1;
        }
        else if (r != current && r == '*' && i > 0)
        {
            count > 0 ? count-- : count;
            tmp += p[i - 1];
            tmp += count + 48;
            tmp.append("+");
            count = 1;
            i++;
            current = p[i];
        }
        else if (r != current && i > 0)
        {
            tmp += p[i - 1];
            tmp += count + 48;
            current = r;
            count = 1;
        }
        else
            count++;
    }

    int index = 0;

    char lastStar = 0;

    for (int i = 0; i < tmp.size(); i++)
    {
        current = tmp[i];
        i++;
        count = tmp[i] - 48;

        if (current == '.')
        {
            if (i + 1 < tmp.length() && tmp[i + 1] == '+')
            {
                i++;
                int check = 0;
                while (s[index] != tmp[i + 1] && s[index] != 0)
                {
                    check++;
                    index++;
                }
                if (check < count)
                {
                    return false;
                }

                lastStar = current;
            }
            else
            {
                for (int j = 0; j < count; j++)
                {
                    if (index >= s.length() || s[index] == 0)
                        return false;

                    index++;
                }
            }
        }
        else
        {
            if (i + 1 < tmp.length() && tmp[i + 1] == '+')
            {
                i++;
                int check = 0;
                while (s[index] == current)
                {
                    check++;
                    index++;
                }

                if (check < count)
                    return false;
                if (check > 0)
                    lastStar = current;
            }
            else
            {
                for (int j = 0; j < count; j++)
                {
                    if (s[index] == current || lastStar == current)
                        index++;
                    else
                        return false;
                }
                lastStar = 0;
            }
        }
    }

    if (index < s.length())
        return false;

    return true;
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