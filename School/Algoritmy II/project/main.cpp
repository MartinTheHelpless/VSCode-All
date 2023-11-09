#include "huffCode.cpp"

int main(int argc, char const *argv[])
{

    if (false && argc != 4)
    {
        std::cout << "Check your arguments please.\nExample args: computil c input.txt output.huff" << std::endl;
        return 1;
    }

    char mode = 'c'; // argv[1][0];

    std::string inFile = "example.txt"; // argv[2];

    std::string outFile = "compressed.huff"; // argv[3];

    switch (mode)
    {
    case 'd':
    {
        break;
    }
    case 'c':
    {
        std::ifstream input;
        std::ofstream output;
        output.open(outFile, std::ios::out | std::ios::binary);
        input.open(inFile, std::ios::in);

        huffCode *test = new huffCode(&input);

        Node *root = test->getRootNode();

        test->createOutput(&input, &output);

        input.close();
        output.close();

        input.open(outFile, std::ios::in);
        output.open("decompressed.txt", std::ios::out);

        test->decompress(&input, &output);

        input.close();
        output.close();
        break;
    }

    default:
        std::cout << "Incorrect mode seleced. Please choose either \"d\" or \"c\"" << std::endl;
        return 1;
        break;
    }

    std::cout << "Succesful execution." << std::endl;

    return 0;
}
