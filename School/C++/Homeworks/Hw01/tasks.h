#pragma once
#include <iostream>
#include <utility>
#include <stdio.h>
#include <vector>

namespace math
{
    int fibonacci(int n);
}

namespace strutils
{
    std::string camel_to_snake(std::string input);

    bool parse_uint(std::string input, int &result);

    bool validate_utf8(std::vector<size_t> input, size_t &result);
}