#include <optional>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using CodePoint = uint32_t;

class UTF8String
{
private:
    size_t size = 0;
    size_t reserved = 0;
    uint8_t *buffer = nullptr;

    void SaveUTF8Bytes(CodePoint cdp);
    void SaveUTF8Bytes(char c);

public:
    ~UTF8String();
    UTF8String() = default;

    UTF8String(const char *ptr);
    UTF8String(UTF8String &&str);
    UTF8String(const UTF8String &str);
    UTF8String(const std::string &str);
    UTF8String(std::vector<CodePoint> CodePoints);

    std::optional<uint8_t> operator[](size_t idx) const;

    operator std::string() const;
    UTF8String operator+(UTF8String &str);
    bool operator==(UTF8String &str) const;
    bool operator!=(UTF8String &str) const;
    UTF8String &operator=(UTF8String &&str);
    UTF8String &operator+=(UTF8String &str);
    bool operator!=(const UTF8String &str) const;
    bool operator==(const UTF8String &str) const;
    UTF8String &operator=(const UTF8String &str);
    UTF8String &operator+=(const UTF8String &str);
    UTF8String operator+(const UTF8String &str) const;

    std::optional<uint32_t> nth_code_point(size_t idx) const;

    void append(CodePoint codePoint);

    uint32_t get_byte_count() const { return size; };
    uint32_t get_point_count() const;
};
