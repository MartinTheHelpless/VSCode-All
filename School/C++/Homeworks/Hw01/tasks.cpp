#include "tasks.h"

// TODO: implement functions from assignment.md

namespace math
{

    int fibonacci(int n)
    {
        int curr = 0;
        int next = 1;

        for (int i = 0; i < n; i++)
            curr = std::exchange(next, curr + next);

        return curr;
    }
}

namespace strutils
{

    std::string camel_to_snake(std::string input)
    {

        std::string result = "";

        for (int i = 0; i < input.length(); i++)
        {
            if (isupper(input[i]) && i != 0)
                result += '_', result += tolower(input[i]);
            else if (isupper(input[i]) && i == 0)
                result += tolower(input[i]);
            else
                result += input[i];
        }

        return result;
    }

    bool parse_uint(std::string input, uint32_t &result)
    {
        if (input.empty())
            return false;

        uint32_t tmpRes = 0;

        const uint32_t max_uint32 = std::numeric_limits<uint32_t>::max();

        for (char c : input)
        {
            if (!std::isdigit(c))
                return false;

            uint32_t digit = c - '0';

            if (tmpRes > max_uint32 / 10 || (tmpRes == max_uint32 / 10 && digit > max_uint32 % 10))
                return false;

            tmpRes = tmpRes * 10 + digit;
        }

        result = tmpRes;

        return true;
    }

    bool validate_utf8(std::vector<uint8_t> input, size_t &result)
    {
        return true;
    }
}
