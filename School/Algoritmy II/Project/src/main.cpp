// main.cpp

#include "huffCode.cpp"

/**
 * @brief Main function for the Huffman coding application.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit status.
 */
int main(int argc, char const *argv[])
{
    // Check for correct number of command-line arguments
    if (false && argc != 4) // Note: This condition will always evaluate to false, check if it's intentional
    {
        std::cout << "Check your arguments please.\nExample args: computil c input.txt output.huff" << std::endl;
        return 1;
    }

    char mode = 'c'; // argv[1][0]; // Extract the mode from command-line arguments

    std::string inFile = "input.txt";   // argv[2];  // Input file path
    std::string outFile = "output.txt"; // argv[3]; // Output file path

    std::ifstream input;
    std::ofstream output;

    switch (mode)
    {
    case 'd':
    {
        huffCode *test = new huffCode(); // Create an instance of huffCode for decompression

        // Open input and output files
        input.open(inFile, std::ios::in);
        output.open(outFile, std::ios::out);

        // Perform decompression
        test->decompress(&input, &output);

        std::cout << "Successful decompression." << std::endl;

        break;
    }
    case 'c':
    {
        // Open input and output files for compression
        output.open(outFile, std::ios::out | std::ios::binary);
        input.open(inFile, std::ios::in);

        huffCode *test = new huffCode(); // Create an instance of huffCode for compression

        // Perform compression
        test->compress(&input, &output);

        std::cout << "Successful compression." << std::endl;

        break;
    }

    default:
        std::cout << "Incorrect mode selected. Please choose either \"d\" or \"c\"" << std::endl;
        return 1;
        break;
    }

    // Close input and output files
    input.close();
    output.close();

    return 0;
}
