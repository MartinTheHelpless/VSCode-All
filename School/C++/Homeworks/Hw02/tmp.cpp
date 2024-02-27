#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>

// Function to convert a const char* string to UTF-8 and store it in a vector
void string_to_utf8(const char *str, std::vector<uint8_t> &utf8)
{
    // Clear the vector to ensure it's empty before storing new values
    utf8.clear();

    // Iterate over each character in the input string
    for (size_t i = 0; str[i] != '\0'; ++i)
    {
        uint8_t byte = static_cast<uint8_t>(str[i]); // Convert char to uint8_t (ASCII)

        // Add the byte to the vector
        utf8.push_back(byte);
    }
}

void utf8_to_string(const std::vector<uint8_t> &utf8)
{
    // Initialize a string to store the converted result
    std::string result;

    // Iterate over each byte in the UTF-8 vector
    for (uint8_t byte : utf8)
    {
        // Append the byte to the result string
        result += static_cast<char>(byte);
    }

    // Output the result string to the console
    std::cout << "UTF-8 converted back to string: " << result << std::endl;
}

int main()
{
    // Define a vector to store the UTF-8 representation
    std::vector<uint8_t> utf8;

    // Test with different const char* strings
    const char *word1 = "dsadasda";       // ASCII characters only
    const char *word2 = "ÄÖÜß";           // Chinese characters (UTF-8)
    const char *word3 = "こんにちは世界"; // Japanese characters (UTF-8)

    // Convert each const char* string to UTF-8 and store the result in the vector
    string_to_utf8(word2, utf8);
    // Display the UTF-8 representation
    std::cout << "UTF-8 representation of '" << word2 << "': ";
    for (auto byte : utf8)
    {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    std::cout << word2 << std::endl;

    // Repeat the process for other strings (word2 and word3)

    return 0;
}
