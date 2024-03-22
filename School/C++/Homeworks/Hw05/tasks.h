#include <optional>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>

using CodePoint = uint32_t;

class UTF8String
{
private:
    size_t m_Size = 0;
    std::vector<uint8_t> m_Buffer;

    void SaveUTF8Bytes(CodePoint cdp);
    void SaveUTF8Bytes(char c);

public:
    class ByteIterator
    {
    private:
        size_t m_Size;
        size_t m_Index = 0;
        const uint8_t *m_Ptr;

    public:
        ByteIterator(const std::vector<uint8_t> &bytes)
            : m_Size(bytes.size()), m_Ptr(&bytes[0]) {}

        ByteIterator(const uint8_t *pointer, uint32_t size)
            : m_Size(size), m_Ptr(pointer) {}

        ~ByteIterator() = default;

        const uint8_t *begin() { return m_Ptr; }
        const uint8_t *end() { return m_Ptr + m_Size; }

        uint8_t operator*() { return *(m_Ptr + m_Index); }

        ByteIterator operator++()
        {
            m_Index++;
            return *this;
        }

        ByteIterator operator--()
        {
            m_Index--;
            return *this;
        }

        ByteIterator operator++(int)
        {
            ByteIterator *tmp = new ByteIterator(m_Ptr, m_Size);
            m_Index++;
            return *tmp;
        }

        ByteIterator operator--(int)
        {
            ByteIterator *tmp = new ByteIterator(m_Ptr, m_Size);
            m_Index--;
            return *tmp;
        }

        ByteIterator operator+=(uint32_t i)
        {
            m_Index += i;
            return *this;
        }

        ByteIterator operator-=(int16_t i)
        {
            m_Index -= i;
            return *this;
        }
    };

    class CdpIterator
    {
    private:
        size_t m_Index = 0;
        size_t m_Size;
        const uint32_t *m_Ptr;
        std::vector<uint32_t> m_Points;

    public:
        CdpIterator(const UTF8String &str) : m_Size(str.get_point_count())
        {

            for (size_t j = 0; j < m_Size; j++)
            {

                uint32_t count = 0, trailByteCount = 0;

                for (size_t i = 0; i < str.m_Size; i++)
                {
                    if ((str.m_Buffer[i] & 0x80) == 0x00)
                        trailByteCount = 0, count++;
                    else if ((str.m_Buffer[i] & 0xE0) == 0xC0)
                        trailByteCount = 1, count++;
                    else if ((str.m_Buffer[i] & 0xF0) == 0xE0)
                        trailByteCount = 2, count++;
                    else if ((str.m_Buffer[i] & 0xF8) == 0xF0)
                        trailByteCount = 3, count++;

                    if (count - 1 == j)
                    {
                        CodePoint res = 0;

                        switch (trailByteCount)
                        {
                        case 0:
                            res = str.m_Buffer[i];
                            break;

                        case 1:
                            res |= (str.m_Buffer[i++] & 0x1F) << 6;
                            res |= (str.m_Buffer[i] & 0x3F);
                            break;

                        case 2:
                            res |= (str.m_Buffer[i++] & 0x0F) << 12;
                            res |= (str.m_Buffer[i++] & 0x3F) << 6;
                            res |= (str.m_Buffer[i] & 0x3F);
                            break;

                        case 3:
                            res |= (str.m_Buffer[i++] & 0x07) << 18;
                            res |= (str.m_Buffer[i++] & 0x3F) << 12;
                            res |= (str.m_Buffer[i++] & 0x3F) << 6;
                            res |= (str.m_Buffer[i] & 0x3F);
                            break;

                        default:
                            break;
                        }
                        m_Points.push_back(res);
                        j++;
                    }
                    else
                        i += trailByteCount;
                }
            }

            m_Ptr = &m_Points[0];
        }

        CdpIterator(const std::vector<uint32_t> &points, uint32_t size) : m_Size(size), m_Points(points) {}

        ~CdpIterator() = default;

        const uint32_t *begin() { return m_Ptr; }
        const uint32_t *end() { return m_Ptr + m_Size; }

        uint32_t operator*() { return *(m_Ptr + m_Index); }

        CdpIterator *operator++()
        {
            m_Index++;
            return this;
        }

        CdpIterator *operator--()
        {
            m_Index--;
            return this;
        }

        CdpIterator *operator++(int)
        {
            CdpIterator *tmp = new CdpIterator(m_Points, m_Size);
            m_Index++;
            return tmp;
        }

        CdpIterator *operator--(int)
        {
            CdpIterator *tmp = new CdpIterator(m_Points, m_Size);
            m_Index--;
            return tmp;
        }

        CdpIterator *operator+=(uint32_t i)
        {
            m_Index += i;
            return this;
        }

        CdpIterator *operator-=(int16_t i)
        {
            m_Index -= i;
            return this;
        }
    };

    ByteIterator bytes() const { return ByteIterator(m_Buffer); }

    CdpIterator codepoints() const { return CdpIterator(*this); }

    ~UTF8String();
    UTF8String() = default;

    UTF8String(const char *ptr);
    UTF8String(UTF8String &&str);
    UTF8String(const UTF8String &str);
    UTF8String(const std::string &str);
    UTF8String(std::vector<uint8_t> uint8Points);
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

    uint32_t get_byte_count() const { return m_Size; };
    uint32_t get_point_count() const;
};