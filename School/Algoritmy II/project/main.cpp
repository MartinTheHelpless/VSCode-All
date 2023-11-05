#include "huffCode.cpp"

int main(int argc, char const *argv[])
{

    if (false && argc != 4)
    {
        std::cout << "Check your arguments please.\nExample args: computil c input.txt output.huff" << std::endl;
        return 1;
    }

    char mode = 'c'; //(*argv)[1];

    std::string inFile = "example.txt"; // argv[2];

    std::string outFile = "output.huff"; // argv[3];

    switch (mode)
    {
    case 'd':
    {
        break;
    }
    case 'c':
    {
        std::ifstream input;
        input.open(inFile, std::ios::in);

        huffCode *test = new huffCode(&input);

        Node *root = test->getRootNode();

        input.close();
        break;
    }

    default:
        std::cout << "Incorrect mode seleced. Please choose either \"d\" or \"c\"" << std::endl;
        return 1;
        break;
    }

    return 0;
}
