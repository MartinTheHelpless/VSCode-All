#include "tasks.h"

UTF8String::UTF8String(const char *ptr)
{
    size = strlen(ptr);
    reserved = size + 1;
    buffer = new uint8_t[reserved];
    std::copy(ptr, ptr + reserved, buffer);
}

UTF8String::UTF8String(const UTF8String &str)
{
    size = str.size;
    reserved = str.reserved;
    buffer = new uint8_t[reserved];
    std::copy(str.buffer, str.buffer + reserved, buffer);
}

UTF8String::UTF8String(UTF8String &&str)
{
    size = str.size;
    reserved = str.reserved;
    buffer = str.buffer;
    str.buffer = nullptr;
}

UTF8String &UTF8String::operator=(const UTF8String &str)
{

    if (buffer != nullptr)
        delete[] buffer;

    size = str.size;
    reserved = str.reserved;
    buffer = new uint8_t[reserved];
    std::copy(str.buffer, str.buffer + reserved, buffer);

    return *this;
}
