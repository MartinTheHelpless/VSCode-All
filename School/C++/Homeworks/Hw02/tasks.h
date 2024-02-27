#pragma once

#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>
#include <cstring>

using CodePoint = uint32_t;

class UTF8String
{
    size_t size = 0;
    size_t reserved = 0;
    uint8_t *buffer = nullptr;

public:
    ~UTF8String();
    UTF8String() = default;

    UTF8String(const char *ptr);
    UTF8String(const UTF8String &str);
    UTF8String(UTF8String &&str);

    UTF8String &operator=(const UTF8String &str);
    UTF8String &operator=(UTF8String &&str);
    UTF8String &operator+=(const UTF8String &str);

    operator bool();

    uint32_t get_byte_count() { return size; };
    uint32_t get_point_count() { return size; };
    uint8_t &operator[](const size_t idx) { return buffer[idx]; };

    friend std::ostream &operator<<(std::ostream &os, const UTF8String &str);
};
