#include <iostream>

int main()
{
    unsigned char bits[] = {0, 1, 0, 1, 1, 1, 0, 0};
    int decimalValue = 0;

    for (int i = 0; i < 8; ++i)
    {
        decimalValue = (decimalValue << 1) | bits[i];
    }

    char character = static_cast<char>(decimalValue);
    std::cout << "Character: " << character << std::endl;

    int treeDepth = 0;

    return 0;
}
