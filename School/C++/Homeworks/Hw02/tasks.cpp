#include "tasks.h"

void UTF8String::SaveUTF8Bytes(CodePoint cdp)
{
  if (cdp <= 0x7F)
  {
    if (reserved < size + 1)
    {
      reserved = size + 5;
      uint8_t *newData = new uint8_t[reserved];
      for (size_t i = 0; i < size; ++i)
        newData[i] = buffer[i];
      delete[] buffer;
      buffer = newData;
    }
    buffer[size++] = static_cast<uint8_t>(cdp);
  }
  else if (cdp <= 0x7FF)
  {
    if (reserved < size + 2)
    {
      reserved = size + 6;
      uint8_t *newData = new uint8_t[reserved];
      for (size_t i = 0; i < size; ++i)
        newData[i] = buffer[i];
      delete[] buffer;
      buffer = newData;
    }
    buffer[size++] = static_cast<uint8_t>(0xC0 | ((cdp >> 6) & 0x1F));
    buffer[size++] = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
  }
  else if (cdp <= 0xFFFF)
  {
    if (reserved < size + 3)
    {
      reserved = size + 7;
      uint8_t *newData = new uint8_t[reserved];
      for (size_t i = 0; i < size; ++i)
        newData[i] = buffer[i];
      delete[] buffer;
      buffer = newData;
    }
    buffer[size++] = static_cast<uint8_t>(0xE0 | ((cdp >> 12) & 0x0F));
    buffer[size++] = static_cast<uint8_t>(0x80 | ((cdp >> 6) & 0x3F));
    buffer[size++] = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
  }
  else if (cdp <= 0x10FFFF && cdp >= 0x10000)
  {
    if (reserved < size + 4)
    {
      reserved = size + 8;
      uint8_t *newData = new uint8_t[reserved];
      for (size_t i = 0; i < size; ++i)
        newData[i] = buffer[i];
      delete[] buffer;
      buffer = newData;
    }
    buffer[size++] = static_cast<uint8_t>(0xF0 | ((cdp >> 18) & 0x07));
    buffer[size++] = static_cast<uint8_t>(0x80 | ((cdp >> 12) & 0x3F));
    buffer[size++] = static_cast<uint8_t>(0x80 | ((cdp >> 6) & 0x3F));
    buffer[size++] = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
  }
}

void UTF8String::SaveUTF8Bytes(char c)
{
  CodePoint cdp = static_cast<CodePoint>(c);

  if (cdp <= 0x7F)
  {
    if (reserved < size + 1)
    {
      reserved = size + 5;
      uint8_t *newData = new uint8_t[reserved];
      for (size_t i = 0; i < size; ++i)
        newData[i] = buffer[i];
      delete[] buffer;
      buffer = newData;
    }
    buffer[size++] = static_cast<uint8_t>(cdp);
  }
  else if (cdp <= 0x7FF)
  {
    if (reserved < size + 2)
    {
      reserved = size + 6;
      uint8_t *newData = new uint8_t[reserved];
      for (size_t i = 0; i < size; ++i)
        newData[i] = buffer[i];
      delete[] buffer;
      buffer = newData;
    }
    buffer[size++] = static_cast<uint8_t>(0xC0 | ((cdp >> 6) & 0x1F));
    buffer[size++] = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
  }
  else if (cdp <= 0xFFFF)
  {
    if (reserved < size + 3)
    {
      reserved = size + 7;
      uint8_t *newData = new uint8_t[reserved];
      for (size_t i = 0; i < size; ++i)
        newData[i] = buffer[i];
      delete[] buffer;
      buffer = newData;
    }
    buffer[size++] = static_cast<uint8_t>(0xE0 | ((cdp >> 12) & 0x0F));
    buffer[size++] = static_cast<uint8_t>(0x80 | ((cdp >> 6) & 0x3F));
    buffer[size++] = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
  }
  else if (cdp <= 0x10FFFF && cdp >= 0x10000)
  {
    if (reserved < size + 4)
    {
      reserved = size + 8;
      uint8_t *newData = new uint8_t[reserved];
      for (size_t i = 0; i < size; ++i)
        newData[i] = buffer[i];
      delete[] buffer;
      buffer = newData;
    }
    buffer[size++] = static_cast<uint8_t>(0xF0 | ((cdp >> 18) & 0x07));
    buffer[size++] = static_cast<uint8_t>(0x80 | ((cdp >> 12) & 0x3F));
    buffer[size++] = static_cast<uint8_t>(0x80 | ((cdp >> 6) & 0x3F));
    buffer[size++] = static_cast<uint8_t>(0x80 | (cdp & 0x3F));
  }
}

UTF8String::~UTF8String() { delete[] buffer; }

UTF8String::UTF8String(const char *ptr)
{
  for (size_t i = 0; i < strlen(ptr); i++)
    SaveUTF8Bytes(ptr[i]);
}

UTF8String::UTF8String(UTF8String &&str)
{
  size = str.size;
  reserved = str.reserved;
  buffer = str.buffer;
  str.buffer = nullptr;
}

UTF8String::UTF8String(const UTF8String &str)
{
  size = str.size;
  reserved = str.reserved;
  buffer = new uint8_t[reserved];
  std::copy(str.buffer, str.buffer + str.size, buffer);
}

UTF8String::UTF8String(const std::string &str)
{
  for (char c : str)
    SaveUTF8Bytes(c);
}

UTF8String::UTF8String(std::vector<CodePoint> CodePoints)
{
  for (size_t i = 0; i < CodePoints.size(); i++)
    SaveUTF8Bytes(CodePoints[i]);
}

std::optional<uint8_t> UTF8String::operator[](size_t idx) const
{
  if (idx < size)
    return static_cast<uint8_t>(buffer[idx]);

  return std::nullopt;
}

UTF8String &UTF8String::operator=(UTF8String &&str)
{
  if (this != &str)
  {
    if (buffer != nullptr)
      delete[] buffer;

    size = str.size;
    reserved = str.reserved;
    buffer = str.buffer;

    str.size = 0;
    str.reserved = 0;
    str.buffer = nullptr;
  }
  return *this;
}

UTF8String UTF8String::operator+(UTF8String &str)
{
  UTF8String data;
  data.size = size + str.size;
  data.reserved = size + str.size + 2;
  data.buffer = new uint8_t[data.reserved];

  for (size_t i = 0; i < size; i++)
    data.buffer[i] = buffer[i];

  for (size_t i = 0; i < str.size; i++)
    data.buffer[size + i] = str.buffer[i];

  return data;
}

UTF8String &UTF8String::operator+=(UTF8String &str)
{
  if (size + str.size >= reserved)
  {
    reserved = size + str.size + 4;
    uint8_t *newData = new uint8_t[reserved];
    std::copy(buffer, buffer + size, newData); // Copy contents of *this
    delete[] buffer;
    buffer = newData;
  }

  // Append contents of str to the end of buffer
  std::copy(str.buffer, str.buffer + str.size, buffer + size);

  size += str.size;
  return *this;
}

UTF8String::operator std::string() const
{
  std::string result;
  for (size_t i = 0; i < size; ++i)
    result += static_cast<char>(buffer[i]);
  return result;
}

bool UTF8String::operator!=(UTF8String &str) const { return !(*this == str); }

bool UTF8String::operator==(UTF8String &str) const
{
  if (size != str.size)
    return false;

  for (size_t i = 0; i < size; ++i)
    if (buffer[i] != str.buffer[i])
      return false;

  return true;
}

UTF8String &UTF8String::operator=(const UTF8String &str)
{
  if (this == &str)
    return *this;

  if (buffer != nullptr)
    delete[] buffer;

  size = str.size;
  reserved = str.reserved;
  buffer = new uint8_t[reserved];
  for (size_t i = 0; i < size; ++i)
    buffer[i] = str.buffer[i];

  return *this;
}

UTF8String UTF8String::operator+(const UTF8String &str) const
{
  UTF8String data;
  data.size = size + str.size;
  data.reserved = size + str.size + 2;
  data.buffer = new uint8_t[data.reserved];

  for (size_t i = 0; i < size; i++)
    data.buffer[i] = buffer[i];

  for (size_t i = 0; i < str.size; i++)
    data.buffer[size + i] = str.buffer[i];

  return data;
}

std::optional<uint32_t> UTF8String::nth_code_point(size_t idx) const
{
  uint32_t count = 0, trailByteCount = 0;

  for (size_t i = 0; i < size; i++)
  {
    if ((buffer[i] & 0x80) == 0x00)
      trailByteCount = 0, count++;
    else if ((buffer[i] & 0xE0) == 0xC0)
      trailByteCount = 1, count++;
    else if ((buffer[i] & 0xF0) == 0xE0)
      trailByteCount = 2, count++;
    else if ((buffer[i] & 0xF8) == 0xF0)
      trailByteCount = 3, count++;

    if (count - 1 == idx)
    {
      CodePoint res = 0;

      switch (trailByteCount)
      {
      case 0:
        res = buffer[i];
        break;

      case 1:
        res |= (buffer[i++] & 0x1F) << 6;
        res |= (buffer[i++] & 0x3F);
        break;

      case 2:
        res |= (buffer[i++] & 0x0F) << 12;
        res |= (buffer[i++] & 0x3F) << 6;
        res |= (buffer[i++] & 0x3F);
        break;

      case 3:
        res |= (buffer[i++] & 0x07) << 18;
        res |= (buffer[i++] & 0x3F) << 12;
        res |= (buffer[i++] & 0x3F) << 6;
        res |= (buffer[i++] & 0x3F);
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
  if (size + str.size >= reserved)
  {
    reserved = size + str.size + 4;
    uint8_t *newData = new uint8_t[reserved];
    std::copy(buffer, buffer + size, newData);
    delete[] buffer;
    buffer = newData;
  }

  std::copy(str.buffer, str.buffer + str.size, buffer + size);

  size += str.size;
  return *this;
}

void UTF8String::append(CodePoint codePoint) { SaveUTF8Bytes(codePoint); }

uint32_t UTF8String::get_point_count() const
{
  uint32_t count = 0;
  for (size_t i = 0; i < size;)
    if ((buffer[i] & 0xC0) != 0x80)
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
  if (size != str.size)
    return false;

  for (size_t i = 0; i < size; ++i)
    if (buffer[i] != str.buffer[i])
      return false;

  return true;
}
