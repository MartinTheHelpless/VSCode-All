#include <iostream>
#include <cmath>

int myAtoi(std::string s);

int main(int argc, char const *argv[])
{

    std::cout << myAtoi("4193 with words") << std::endl;

    return 0;
}

int myAtoi(std::string s)
{

    int res = 0;

    bool whiteSpace = true;

    bool positive = true;

    int tmp = 0, letter = 0, start = 0;

    for (int i = 0; i < s.length(); i++)
        if (whiteSpace && s[i] != ' ')
        {
            whiteSpace = false;
            start = tmp;
            tmp = 1;
        }
        else if (!whiteSpace && s[i] == ' ')
            break;
        else if (!(s[i] <= 57 && s[i] >= 48) && !whiteSpace)
        {
            tmp++;
            letter++;
        }
        else
            tmp++;

    for (int i = start; i < tmp + start; i++)
    {
        if (s[i] == '-')
            positive = false;
        else if (s[i] == '+')
            positive = true;
        else if (!(s[i] >= 48 && s[i] <= 57))
            letter--;
        else
        {
            if (pow(10, tmp + start - letter - i - 1) >= INT_MAX)
            {
                res = INT_MAX;
                break;
            }
            else
                res += (s[i] - 48) * pow(10, tmp + start - letter - i - 1);
        }
    }

    if (!positive)
        if (res == INT_MAX)
            return -2147483648;
        else
            return -res;

    return res;
}