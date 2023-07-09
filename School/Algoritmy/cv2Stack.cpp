#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <stack>
#include <vector>

void parCheck();

bool checkParity(std::string text);

int gcd(int m, int n);

void bubbleSort();

int gcdIt(int m, int n);

int main(int argc, char const *argv[])
{
    /*
    std::string text = "((())((())))";

    std::cout << "text is: " << (checkParity(text) ? "OK" : "Crappy") << std::endl;
    */

    int x = 11;
    int y = 121;

    std::cout << gcdIt(x, y) << " -- " << gcd(x, y) << std::endl;

    return 0;
}

void parCheck()
{

    while (true)
    {
        std::string line;

        std::cin >> line;

        bool wrong = false;

        int open = 0;
        int closed = 0;

        int i = 0;

        char c = line[i];

        while (c != 0)
        {
            c == '(' ? open++ : open;
            c == ')' ? closed++ : closed;

            if (closed > open)
            {
                wrong = true;
                break;
            }

            i++;
            c = line[i];
        }

        if (open > closed)
        {
            std::cout << "Chybí vám uzavírací závorka/y. " << std::endl;
        }
        else if (open < closed)
        {
            std::cout << "Chybí vám otevírací závorka/y. " << std::endl;
        }
        else if (wrong)
        {
            std::cout << "Závorky jsou ve špatném pořadí. " << std::endl;
        }
        else
            std::cout << "Závorky jsou správně." << std::endl;
    }
}

bool checkParity(std::string text)
{
    std::stack<char> s;

    for (int i = 0; i < text.length(); i++)
    {

        if (text[i] == '(')
        {
            s.push(text[i]);
        }
        else if (text[i] == ')')
        {
            if (!s.empty())
            {
                s.pop();
            }
            else
                return false;
        }
    }

    if (s.empty())
    {
        return true;
    }

    return false;
}

int gcd(int m, int n)
{
    if (n == 0)
        return m;

    return gcd(n, m % n);
}

int gcdIt(int m, int n)
{
    while (n > 0)
    {
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}

void bubbleSort() {}
