/*
class ByteIterator
{
private:
    size_t m_Size;
    size_t m_Index = 0;
    const uint8_t *m_Ptr;
    std::vector<uint8_t> m_Bytes;

public:
    ByteIterator(const std::vector<uint8_t> bytes)
        : m_Size(bytes.size()), m_Bytes(bytes) { m_Ptr = &m_Bytes[0]; }

    ~ByteIterator() = default;

    bool operator!=(ByteIterator byte)
    {
        if (m_Index != byte.m_Index)
            return false;
        return true;
    }

    const ByteIterator begin() { return *this; }
    const ByteIterator end()
    {
        m_Index = m_Size - 1;
        return *this;
    }

    uint8_t operator*() { return *(m_Ptr + m_Index); }

    ByteIterator *operator++()
    {
        m_Index++;
        return this;
    }

    ByteIterator *operator--()
    {
        m_Index--;
        return this;
    }

    ByteIterator *operator++(int)
    {
        ByteIterator *tmp = this;
        m_Index++;
        return tmp;
    }

    ByteIterator *operator--(int)
    {
        ByteIterator *tmp = this;
        m_Index--;
        return tmp;
    }

    ByteIterator *operator+=(uint32_t i)
    {
        m_Index += i;
        return this;
    }

    ByteIterator *operator-=(int16_t i)
    {
        m_Index -= i;
        return this;
    }

    ByteIterator *operator+(int16_t i)
    {
        ByteIterator *tmp = new ByteIterator(m_Bytes);
        tmp->m_Index = m_Index + i;
        return tmp;
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
    CdpIterator(const std::vector<uint32_t> cdps, uint32_t pointCount)
        : m_Size(pointCount), m_Points(cdps) { m_Ptr = &m_Points[0]; }

    ~CdpIterator() = default;

    bool operator!=(CdpIterator cdp)
    {
        if (m_Index != cdp.m_Index)
            return false;
        return true;
    }

    const CdpIterator begin() { return *this; }
    const CdpIterator end()
    {
        m_Index = m_Size - 1;
        return *this;
    }

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
        CdpIterator *tmp = this;
        m_Index++;
        return tmp;
    }

    CdpIterator *operator--(int)
    {
        CdpIterator *tmp = this;
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

class ByteIterWrapper
{
private:
    std::vector<uint8_t> m_Bytes;

public:
    ByteIterWrapper(const UTF8String str) : m_Bytes(str.m_Buffer) {}
    ~ByteIterWrapper() {}

    ByteIterator begin() { return ByteIterator(m_Bytes).begin(); }
    ByteIterator end() { return ByteIterator(m_Bytes).end(); }
};

class CdpIterWrapper
{
private:
    uint32_t m_Size;
    std::vector<uint32_t> m_Points;

public:
    CdpIterWrapper(const UTF8String str)
    {
        m_Size = str.get_point_count();

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
    }
    ~CdpIterWrapper() = default;

    CdpIterator begin() { return CdpIterator(m_Points, m_Size).begin(); }
    CdpIterator end() { return CdpIterator(m_Points, m_Size).end(); }
};

ByteIterWrapper bytes() const { return ByteIterWrapper(*this); }

CdpIterWrapper codepoints() const { return CdpIterWrapper(*this); }
*/

/*



*/