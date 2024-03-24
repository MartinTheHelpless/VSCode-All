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

        ByteIterator(const uint8_t *pointer, size_t size)
            : m_Size(size), m_Ptr(pointer) {}

        ~ByteIterator() = default;

        ByteIterator begin() const { return ByteIterator(m_Ptr, m_Size); }
        ByteIterator end() const
        {
            ByteIterator tmp = ByteIterator(m_Ptr, m_Size);
            tmp.m_Index = m_Size;
            return tmp;
        }

        bool operator==(const ByteIterator it) const { return (it.m_Ptr == m_Ptr && it.m_Index == m_Index && it.m_Size == m_Size); }

        bool operator!=(const ByteIterator it) const { return !(*this == it); }

        uint8_t operator*() const { return *(m_Ptr + m_Index); }

        ByteIterator operator++()
        {
            m_Index++;
            return *this;
        }

        ByteIterator operator+(int32_t i) const
        {
            ByteIterator tmp = ByteIterator(m_Ptr, m_Size);
            tmp.m_Index = m_Index + i;
            return tmp;
        }

        ByteIterator operator-(int32_t i) const
        {
            ByteIterator tmp = ByteIterator(m_Ptr, m_Size);
            tmp.m_Index = m_Index - i;
            return tmp;
        }

        ByteIterator operator--()
        {
            m_Index--;
            return *this;
        }

        ByteIterator operator++(int)
        {
            ByteIterator tmp = *this;
            m_Index++;
            return tmp;
        }

        ByteIterator operator--(int)
        {
            ByteIterator tmp = *this;
            m_Index--;
            return tmp;
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
        size_t m_Size;
        size_t m_Index = 0;
        const uint8_t *m_Ptr;

        uint32_t IsLeadingByte(uint8_t byte) const
        {
            if ((byte & 0x80) == 0x00)
                return 1;
            else if ((byte & 0xE0) == 0xC0)
                return 2;
            else if ((byte & 0xF0) == 0xE0)
                return 3;
            else if ((byte & 0xF8) == 0xF0)
                return 4;

            return 0;
        }

        void IncrementToNextCdp(uint32_t k)
        {
            for (size_t i = 0; i < k; i++)
                do
                    m_Index++;
                while (m_Index < m_Size && IsLeadingByte(*(m_Ptr + m_Index)) == 0);
        }
        void DecrementToPrevCdp(uint32_t k)
        {
            for (size_t i = 0; i < k; i++)
                do
                    m_Index--;
                while (m_Index > 0 && IsLeadingByte(*(m_Ptr + m_Index)) == 0);
        }

    public:
        CdpIterator(const UTF8String &str) : m_Size(str.m_Size), m_Ptr(&str.m_Buffer[0]) {}

        CdpIterator(const uint8_t *pointer, size_t size)
            : m_Size(size), m_Ptr(pointer) {}

        ~CdpIterator() = default;

        CdpIterator begin() const { return CdpIterator(m_Ptr, m_Size); }
        CdpIterator end() const
        {
            CdpIterator tmp = CdpIterator(m_Ptr, m_Size);
            tmp.m_Index = m_Size;
            return tmp;
        }

        bool operator==(const CdpIterator it) const { return (it.m_Ptr == m_Ptr && it.m_Index == m_Index && it.m_Size == m_Size); }

        bool operator!=(const CdpIterator it) const { return !(*this == it); }

        uint32_t operator*() const
        {

            CodePoint res = 0;

            switch (IsLeadingByte(*(m_Ptr + m_Index)))
            {
            case 1:
                res = *(m_Ptr + m_Index);
                break;

            case 2:
                res |= (*(m_Ptr + m_Index) & 0x1F) << 6;
                res |= (*(m_Ptr + m_Index + 1) & 0x3F);
                break;

            case 3:
                res |= (*(m_Ptr + m_Index) & 0x0F) << 12;
                res |= (*(m_Ptr + m_Index + 1) & 0x3F) << 6;
                res |= (*(m_Ptr + m_Index + 2) & 0x3F);
                break;

            case 4:
                res |= (*(m_Ptr + m_Index) & 0x07) << 18;
                res |= (*(m_Ptr + m_Index + 1) & 0x3F) << 12;
                res |= (*(m_Ptr + m_Index + 2) & 0x3F) << 6;
                res |= (*(m_Ptr + m_Index + 3) & 0x3F);
                break;

            default:
                break;
            }
            return res;
        }

        CdpIterator operator+(int32_t i) const
        {
            CdpIterator tmp = CdpIterator(m_Ptr, m_Size);
            tmp.IncrementToNextCdp(i);
            return tmp;
        }

        CdpIterator operator-(int32_t i) const
        {
            CdpIterator tmp = CdpIterator(m_Ptr, m_Size);
            tmp.DecrementToPrevCdp(i);
            return tmp;
        }

        CdpIterator operator++()
        {
            IncrementToNextCdp(1);
            return *this;
        }

        CdpIterator operator--()
        {
            DecrementToPrevCdp(1);
            return *this;
        }

        CdpIterator operator++(int)
        {
            CdpIterator tmp = *this;
            IncrementToNextCdp(1);
            return tmp;
        }

        CdpIterator operator--(int)
        {
            CdpIterator tmp = *this;
            DecrementToPrevCdp(1);
            return tmp;
        }

        CdpIterator operator+=(uint32_t i)
        {
            IncrementToNextCdp(i);
            return *this;
        }

        CdpIterator operator-=(int16_t i)
        {
            DecrementToPrevCdp(i);
            return *this;
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

struct BigData
{
    explicit BigData(int value) : value(value) {}

    BigData(const BigData &) = delete;
    BigData &operator=(const BigData &) = delete;

    int value;
};

class Tree
{
private:
    BigData &m_Data;

public:
    Tree(BigData &value) : m_Data(value) {}
    ~Tree() {}

    BigData get_value() { return; }

    bool has_parent();
    bool is_same_tree_as(Tree *tree);

    void swap_children();
    void replace_value();

    Tree *set_left_child(std::unique_ptr<Tree, std::default_delete<Tree>> child);
    Tree *set_right_child(std::unique_ptr<Tree, std::default_delete<Tree>> child);
    Tree *get_left_child();
    Tree *get_parent();
    Tree *get_right_child();
    Tree *take_child(Tree child);
    Tree *take_left_child();
    Tree *take_right_child();
    Tree *get_root();
};