#include <iostream>
#include <string>
#include <cmath>

int reverse(int x);

int main(int argc, char const *argv[])
{

    std::cout << reverse(1534236469) << std::endl;

    return 0;
}

int reverse(int x)
{

    std::string text = std::to_string(x);

    bool positive = true;

    int res = 0;

    int fix = 0;
    int last = 0;

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == '-')
        {
            fix++;
            positive = false;
        }
        else if (text[i] > 46 && text[i] < 58)
        {
            if ((text[i] - 48) * pow(10, i - fix) + res > INT32_MAX)
            {
                res = 0;
                break;
            }
            else
            {
                res += (text[i] - 48) * pow(10, i - fix);
            }
        }
        else
        {
            fix++;
            continue;
        }
    }

    if (!positive)
    {
        return -res;
    }

    return res;
}