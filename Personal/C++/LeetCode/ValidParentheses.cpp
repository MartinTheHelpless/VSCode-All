#include <iostream>
#include <vector>

bool isValid(std::string s);

int main(int argc, char const *argv[])
{

    std::string s = "[{()}]";

    std::cout << (isValid(s) ? "Valid" : "Invalid");
    return 0;
}

bool isValid(std::string s)
{

    std::vector<int> check;

    int normal = 0, square = 0, curly = 0;

    int last = 0;

    for (int i = 0; i < s.length(); i++)
    {

        switch (int(s[i]))
        {
        case 40:
            normal++;
            check.push_back(40);
            last = 40;
            break;

        case 41:
            normal--;
            if (!check.empty() && check[check.size() - 1] == 40)
                check.pop_back();
            else
                return false;

            break;

        case 91:
            square++;
            check.push_back(91);
            last = 91;
            break;

        case 93:
            square--;
            if (!check.empty() && check[check.size() - 1] == 91)
                check.pop_back();
            else
                return false;

            break;

        case 123:
            curly++;
            check.push_back(123);
            last = 123;
            break;

        case 125:
            curly--;
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
}