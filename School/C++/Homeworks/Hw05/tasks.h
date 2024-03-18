#pragma once

#include <memory>
#include <cstdint>

/// UTF-8 string (reuse your previous implementation and modify it)

using CodePoint = uint32_t;
class UTF8String;

/// Binary tree
// Big data that we cannot afford to copy
struct BigData {
    explicit BigData(int value): value(value) {}

    BigData(const BigData&) = delete;
    BigData& operator=(const BigData&) = delete;

    int value;
};

class Tree;
