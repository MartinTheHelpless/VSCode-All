#pragma once
#include <iostream>
#include <utility>
#include <stdio.h>

namespace math
{
    int fibonacci(int n);
}

namespace strutils
{
    std::string camel_to_snake(std::string input);

    bool parse_uint(std::string input, int &result);

    size_t validate_utf8(size_t &input, int &result);
}