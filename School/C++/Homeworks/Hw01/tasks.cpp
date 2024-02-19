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
            if (isupper(input[i]))
                result += '_', result += tolower(input[i]);
            else
                result += input[i];
        }

        return result;
    }

    bool parse_uint(std::string input, int &result)
    {

        int position = 1;

        for (int i = input.length() - 1; i >= 0; i--)
        {
            if (int(input[i]) > 57 || input[i] < 48)
                return false;

            result += (int(input[i]) - 48) * position;
            position *= 10;
        }

        return true;
    }

    bool validate_utf8(std::vector<uint8_t> input, size_t &result)
    {
        return false;
    }
}
