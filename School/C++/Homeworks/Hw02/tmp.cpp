std::optional<CodePoint> UTF8String::nth_code_point(size_t n) const
{
    size_t i = 0;
    size_t count = 0;
    while (i < size)
    {
        if ((bytes[i] & 0x80) == 0)
        {
            if (count == n)
            {
                return static_cast<CodePoint>(bytes[i]);
            }
            i++;
        }
        else if ((bytes[i] & 0xE0) == 0xC0)
        {
            if (count == n)
            {
                return static_cast<CodePoint>((bytes[i] & 0x1F) << 6 | (bytes[i + 1] & 0x3F));
            }
            i += 2;
        }
        else if ((bytes[i] & 0xF0) == 0xE0)
        {
            if (count == n)
            {
                return static_cast<CodePoint>((bytes[i] & 0x0F) << 12 | (bytes[i + 1] & 0x3F) << 6 | (bytes[i + 2] & 0x3F));
            }
            i += 3;
        }
        else if ((bytes[i] & 0xF8) == 0xF0)
        {
            if (count == n)
            {
                return static_cast<CodePoint>((bytes[i] & 0x07) << 18 | (bytes[i + 1] & 0x3F) << 12 | (bytes[i + 2] & 0x3F) << 6 | (bytes[i + 3] & 0x3F));
            }
            i += 4;
        }
        count++;
    }
    return std::nullopt;
}