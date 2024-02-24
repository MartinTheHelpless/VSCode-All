#pragma once
#include <iostream>
#include <utility>
#include <stdio.h>
#include <vector>
#include <limits>

namespace math
{
    int fibonacci(int n);
}

namespace strutils
{
    std::string camel_to_snake(std::string input);

    bool parse_uint(std::string input, uint32_t &result);

    bool validate_utf8(std::vector<uint8_t> &input, size_t &result);
}