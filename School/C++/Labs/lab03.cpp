#include <iostream>
#include <functional>
#include <cstring>
#include <regex>

struct S
{
    size_t x = 0;

    S(const char *s);
    S(const std::string &str);
};

S::S(const char *s) : x(strlen(s)) {}

S::S(const std::string &str) : x(str.size()) {}

int main(int argc, char const *argv[])
{

    S s{"string"};
    std::cout << s.x << std::endl;

    std::regex re{R"([a-zA-Z]{2,4}\d{3})"};
    std::cmatch m;

    if (std::regex_match("cd123", m, re))
        std::cout << "Found" << std::endl;
    else
        std::cout << "Not Found" << std::endl;

    return 0;
}
