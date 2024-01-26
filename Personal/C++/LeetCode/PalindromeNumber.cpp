#include <iostream>
#include <string>

bool isPalindrome(int x);

int main(int argc, char const *argv[])
{

    std::cout << (isPalindrome(151) ? "This number is a plindrome." : "This number is not a palindrome") << std::endl;

    return 0;
}

bool isPalindrome(int x)
{

    std::string tmp = std::to_string(x);

    for (int i = 0; i < (tmp.length() / 2); i++)
        if (tmp[i] != tmp[tmp.length() - 1 - i])
            return false;

    return true;
}