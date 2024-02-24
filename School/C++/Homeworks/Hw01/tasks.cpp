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

    bool validate_utf8(std::vector<uint8_t> &input, size_t &result)
    {

        auto calculate_bytes_to_check = [](const uint8_t &byte, size_t &bytes_to_check) -> bool
        {
            if (byte <= 0x7F)
                bytes_to_check = 1;
            else if (byte >= 0xC2 && byte <= 0xDF)
                bytes_to_check = 2;
            else if (byte >= 0xE0 && byte <= 0xEF)
                bytes_to_check = 3;
            else if (byte >= 0xF0 && byte <= 0xF4)
                bytes_to_check = 4;
            else
                return false;

            return true;
        };

        if (input.size() == 0)
        {
            result = 0;
            return true;
        }

        size_t validSequences = 0;

        for (uint16_t i = 0; i < input.size();)
        {
            uint8_t byte = input[i];
            size_t bytes_to_check = 0;

            if (!calculate_bytes_to_check(byte, bytes_to_check))
            {
                i++;
                continue;
            }

            if (i + bytes_to_check > input.size())
                break;

            bool valid_sequence = true;
            for (size_t j = 1; j < bytes_to_check; ++j)
                if ((input[i + j] & 0xC0) != 0x80)
                {
                    valid_sequence = false;
                    break;
                }

            if (valid_sequence)
                validSequences++;

            i += bytes_to_check;
        }

        if (validSequences > 1)
        {
            result = validSequences;
            return true;
        }
        else
            return false;
    }
}
