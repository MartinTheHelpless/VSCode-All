#include "huffCode.cpp"

int main(int argc, char const *argv[])
{

    if (false && argc != 4)
    {
        std::cout << "Check your arguments please.\nExample args: computil c input.txt output.huff" << std::endl;
        return 1;
    }

    char mode = argv[1][0];

    std::string inFile = argv[2];

    std::string outFile = argv[3];

    std::ifstream input;
    std::ofstream output;

    switch (mode)
    {
    case 'd':
    {
        huffCode *test = new huffCode();

        input.open(inFile, std::ios::in);
        output.open(outFile, std::ios::out);

        test->decompress(&input, &output);

        std::cout << "Succesful decompression." << std::endl;

        break;
    }
    case 'c':
    {
        output.open(outFile, std::ios::out | std::ios::binary);
        input.open(inFile, std::ios::in);

        huffCode *test = new huffCode();

        test->compress(&input, &output);

        std::cout << "Succesful compression." << std::endl;

        break;
    }

    default:
        std::cout << "Incorrect mode seleced. Please choose either \"d\" or \"c\"" << std::endl;
        return 1;
        break;
    }

    input.close();
    output.close();

    return 0;
}
