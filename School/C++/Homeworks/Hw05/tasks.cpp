#include "tasks.h"

void UTF8String::SaveUTF8Bytes(CodePoint cdp)
{
    if (cdp <= 0x7F)
    {
        m_Buffer.push_back(static_cast<uint8_t>(cdp));
    }
    else if (cdp <= 0x7FF)
    {
        uint8_t tmpStorage = static_cast<uint8_t>(0xC0 | ((cdp >> 6) & 0x1F));
        tmpStorage = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
    }
    else if (cdp <= 0xFFFF)
    {
        uint8_t tmpStorage = static_cast<uint8_t>(0xE0 | ((cdp >> 12) & 0x0F));
        tmpStorage = static_cast<uint8_t>(0x80 | ((cdp >> 6) & 0x3F));
        tmpStorage = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
        m_Buffer.push_back(tmpStorage);
    }
    else if (cdp <= 0x10FFFF && cdp >= 0x10000)
    {
        uint8_t tmpStorage = static_cast<uint8_t>(0xF0 | ((cdp >> 18) & 0x07));
        tmpStorage = static_cast<uint8_t>(0x80 | ((cdp >> 12) & 0x3F));
        tmpStorage = static_cast<uint8_t>(0x80 | ((cdp >> 6) & 0x3F));
        tmpStorage = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
        m_Buffer.push_back(tmpStorage);
    }
}

void UTF8String::SaveUTF8Bytes(char c)
{
    CodePoint cdp = static_cast<CodePoint>(c);

    if (cdp <= 0x7F)
    {
        uint8_t tmpStorage = static_cast<uint8_t>(cdp);
        m_Buffer.push_back(tmpStorage);
    }
    else if (cdp <= 0x7FF)
    {
        uint8_t tmpStorage = static_cast<uint8_t>(0xC0 | ((cdp >> 6) & 0x1F));
        tmpStorage = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
        m_Buffer.push_back(tmpStorage);
    }
    else if (cdp <= 0xFFFF)
    {
        uint8_t tmpStorage = static_cast<uint8_t>(0xE0 | ((cdp >> 12) & 0x0F));
        tmpStorage = static_cast<uint8_t>(0x80 | ((cdp >> 6) & 0x3F));
        tmpStorage = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
        m_Buffer.push_back(tmpStorage);
    }
    else if (cdp <= 0x10FFFF && cdp >= 0x10000)
    {
        uint8_t tmpStorage = static_cast<uint8_t>(0xF0 | ((cdp >> 18) & 0x07));
        tmpStorage = static_cast<uint8_t>(0x80 | ((cdp >> 12) & 0x3F));
        tmpStorage = static_cast<uint8_t>(0x80 | ((cdp >> 6) & 0x3F));
        tmpStorage = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
        m_Buffer.push_back(tmpStorage);
    }
}

UTF8String::~UTF8String() { delete[] this; }

UTF8String::UTF8String(const char *ptr)
{
    for (size_t i = 0; i < strlen(ptr); i++)
        SaveUTF8Bytes(ptr[i]);
}

UTF8String::UTF8String(UTF8String &&str)
{
    m_Buffer = str.m_Buffer;
    str.m_Buffer.clear();
}

UTF8String::UTF8String(const UTF8String &str)
{
    m_Buffer = str.m_Buffer;
}

UTF8String::UTF8String(const std::string &str)
{
    for (char c : str)
        SaveUTF8Bytes(c);
}

UTF8String::UTF8String(std::vector<uint8_t> bytePoints)
{

    for (uint8_t points : bytePoints)
        m_Buffer.push_back(points);
}

UTF8String::UTF8String(std::vector<CodePoint> CodePoints)
{
    for (size_t i = 0; i < CodePoints.size(); i++)
        SaveUTF8Bytes(CodePoints[i]);
}

std::optional<uint8_t> UTF8String::operator[](size_t idx) const
{
    if (idx < m_Buffer.size())
        return static_cast<uint8_t>(m_Buffer[idx]);

    return std::nullopt;
}

UTF8String &UTF8String::operator=(UTF8String &&str)
{
    if (this != &str)
    {
        if (m_Buffer.size() > 0)
            m_Buffer.clear();

        m_Buffer = str.m_Buffer;

        str.m_Buffer.clear();
    }
    return *this;
}

UTF8String UTF8String::operator+(UTF8String &str)
{
    UTF8String data;

    for (uint8_t point : m_Buffer)
        data.m_Buffer.push_back(point);

    for (uint8_t point : str.m_Buffer)
        data.m_Buffer.push_back(point);

    return data;
}

UTF8String &UTF8String::operator+=(UTF8String &str)
{
    for (uint8_t point : str.m_Buffer)
        m_Buffer.push_back(point);

    return *this;
}

UTF8String::operator std::string() const
{
    std::string result;
    for (size_t i = 0; i < m_Buffer.size(); ++i)
        result += static_cast<char>(m_Buffer[i]);
    return result;
}

bool UTF8String::operator!=(UTF8String &str) const { return !(*this == str); }

bool UTF8String::operator==(UTF8String &str) const
{
    if (m_Buffer.size() != str.m_Buffer.size())
        return false;

    for (size_t i = 0; i < m_Buffer.size(); ++i)
        if (m_Buffer[i] != str.m_Buffer[i])
            return false;

    return true;
}

UTF8String &UTF8String::operator=(const UTF8String &str)
{
    if (this == &str)
        return *this;

    if (m_Buffer.size() > 0)
        m_Buffer.clear();

    for (size_t i = 0; i < str.m_Buffer.size(); ++i)
        m_Buffer.push_back(str.m_Buffer[i]);

    return *this;
}

UTF8String UTF8String::operator+(const UTF8String &str) const
{
    UTF8String data;

    for (uint8_t point : m_Buffer)
        data.m_Buffer.push_back(point);

    for (uint8_t point : str.m_Buffer)
        data.m_Buffer.push_back(point);

    return data;
}

std::optional<uint32_t> UTF8String::nth_code_point(size_t idx) const
{
    uint32_t count = 0, trailByteCount = 0;

    for (size_t i = 0; i < m_Buffer.size(); i++)
    {
        if ((m_Buffer[i] & 0x80) == 0x00)
            trailByteCount = 0, count++;
        else if ((m_Buffer[i] & 0xE0) == 0xC0)
            trailByteCount = 1, count++;
        else if ((m_Buffer[i] & 0xF0) == 0xE0)
            trailByteCount = 2, count++;
        else if ((m_Buffer[i] & 0xF8) == 0xF0)
            trailByteCount = 3, count++;

        if (count - 1 == idx)
        {
            CodePoint res = 0;

            switch (trailByteCount)
            {
            case 0:
                res = m_Buffer[i];
                break;

            case 1:
                res |= (m_Buffer[i++] & 0x1F) << 6;
                res |= (m_Buffer[i++] & 0x3F);
                break;

            case 2:
                res |= (m_Buffer[i++] & 0x0F) << 12;
                res |= (m_Buffer[i++] & 0x3F) << 6;
                res |= (m_Buffer[i++] & 0x3F);
                break;

            case 3:
                res |= (m_Buffer[i++] & 0x07) << 18;
                res |= (m_Buffer[i++] & 0x3F) << 12;
                res |= (m_Buffer[i++] & 0x3F) << 6;
                res |= (m_Buffer[i++] & 0x3F);
                break;

            default:
                break;
            }
            return res;
        }
        i += trailByteCount;
    }

    return std::nullopt;
}

UTF8String &UTF8String::operator+=(const UTF8String &str)
{

    for (uint8_t point : str.m_Buffer)
        m_Buffer.push_back(point);

    return *this;
}

void UTF8String::append(CodePoint codePoint) { SaveUTF8Bytes(codePoint); }

uint32_t UTF8String::get_point_count() const
{
    uint32_t count = 0;
    for (size_t i = 0; i < m_Buffer.size();)
        if ((m_Buffer[i] & 0xC0) != 0x80)
            i++, count++;
        else
            i++;
    return count;
}

bool UTF8String::operator!=(const UTF8String &str) const
{
    return !(*this == str);
}

bool UTF8String::operator==(const UTF8String &str) const
{
    if (m_Buffer.size() != str.m_Buffer.size())
        return false;

    for (size_t i = 0; i < m_Buffer.size(); ++i)
        if (m_Buffer[i] != str.m_Buffer[i])
            return false;

    return true;
}
