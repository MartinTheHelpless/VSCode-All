#include <iostream>
#include <vector>

bool isValid(std::string s);

int main(int argc, char const *argv[])
{

    std::string s = "{[()]}";

    std::cout << (isValid(s) ? "Valid" : "Invalid");
    return 0;
}

bool isValid(std::string s)
{

    std::vector<int> check;

    for (int i = 0; i < s.length(); i++)
    {

        switch (int(s[i]))
        {
        case 40:
            check.push_back(40);
            break;

        case 41:
            if (!check.empty() && check[check.size() - 1] == 40)
                check.pop_back();
            else
                return false;

            break;

        case 91:
            check.push_back(91);
            break;

        case 93:
            if (!check.empty() && check[check.size() - 1] == 91)
                check.pop_back();
            else
                return false;

            break;

        case 123:
            check.push_back(123);
            break;

        case 125:
            if (!check.empty() && check[check.size() - 1] == 123)
                check.pop_back();
            else
                return false;

            break;

        default:
            break;
        }
    }

    if (check.size() == 0)
        return true;
    else
        return false;
}