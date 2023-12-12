#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <bitset>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

struct Node
{
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}

    ~Node()
    {
        delete left;
        delete right;
    }
};

Node *buildHuffmanTree(unordered_map<char, unsigned> *freqMap, string *returned);
void compressAndWriteToFile(ifstream *inFile, ofstream *outFile, Node *root, string *frequencies);

string readCompressedData(ifstream &inFile)
{
    vector<int> compressedIntegers;

    int readBuffer;
    while (inFile.read(reinterpret_cast<char *>(&readBuffer), sizeof(readBuffer)))
    {
        compressedIntegers.push_back(readBuffer);
    }

    // Convert the integers back to a string of 1's and 0's
    string readCompressedData;
    for (int i : compressedIntegers)
    {
        for (int j = CHAR_BIT - 1; j >= 0; --j)
        {
            char bit = ((i >> j) & 1) + '0';
            readCompressedData += bit;
        }
    }

    return readCompressedData;
}

streampos getFileSize(const string &fileName)
{
    ifstream inFile(fileName, ios::in);
    if (!inFile.is_open())
    {
        cerr << "Error opening file for reading." << endl;
        return -1; // Return -1 to indicate an error
    }

    // Seek to the end of the file
    inFile.seekg(0, ios::end);

    // Get the file size
    streampos fileSize = inFile.tellg();

    // Close the file
    inFile.close();

    if (fileSize == -1)
    {
        cerr << "Error getting file size." << endl;
        return -1; // Return -1 to indicate an error
    }

    return fileSize;
}

int main()
{

    int argc = 4;
    const char *argv[4] = {"nazec", "C", "input.txt", "output.txt"};

    // Check if the correct number of arguments is provided
    if (argc != 4)
    {
        // cerr << "Incorrect number of arguments.\nEnter in the format: 'name of the program' 'C or D' 'input_file' 'output_file'." << endl;
        // return 1;
    }

    // Check if the second argument is 'C' for compression or 'D' for decompression
    if (argv[1][0] == 'C')
    {
        // Compression
        ifstream source(argv[2]);

        source >> noskipws;

        if (!source.is_open())
        {
            cerr << "Error opening " << argv[2] << " file for reading." << endl;
            return 1;
        }

        stringstream buffer;
        buffer << source.rdbuf(); // Read the entire file into the stringstream

        // Close the file

        // Extract the content of the stringstream into a string
        string data = buffer.str();

        int size = data.length();

        string fileName = argv[3];

        source.seekg(0, ios::beg);

        // Compression
        unordered_map<char, unsigned> freqMap;
        for (char ch : data)
        {
            freqMap[ch]++;
        }

        string treeResult = "";

        Node *root = buildHuffmanTree(&freqMap, &treeResult);

        /*
        unordered_map<char, string> codes;
        getHuffmanCodes(root, "", codes);
        */

        ofstream outFile(fileName, ios::out);

        outFile << size;

        std::cout << treeResult << std::endl;

        outFile << treeResult;

        outFile.put('\0');

        compressAndWriteToFile(&source, &outFile, root, &treeResult);

        outFile.close();

        // Free memory
        delete root;
        streampos in = getFileSize(argv[2]);

        if (in != -1)
        {
            cout << "File Size of input file: " << in << " bytes" << endl;
        }
        streampos out = getFileSize(argv[3]);

        if (out != -1)
        {
            cout << "File Size of output file: " << out << " bytes" << endl;
        }
        double compressionRatio = static_cast<double>(out) / static_cast<double>(in);
        cout << "Compression ratio: " << compressionRatio << endl;
    }
    else if (argv[1][0] == 'D')
    {

        // Decompression
        ifstream inFile(argv[2], ios::binary);

        inFile >> noskipws;

        int originalSize;

        inFile >> originalSize;

        /*ifstream inFile;
        inFile.open("output.txt", ios::in);*/

        if (!inFile.is_open())
        {
            cerr << "Error opening file for reading." << endl;
            return 1;
        }

        string treeString = "";

        char c;

        inFile >> c;

        while (c != 0)
        {
            treeString += c;
            inFile >> c;
        }

        treeString += '|';

        Node *nodes[treeString.length()];

        int index = treeString.length() - 1;

        Node *connectable = new Node((char)treeString[index--], 0);

        while (index >= 0)
        {

            Node *temp = new Node((char)treeString[index], 0);

            index--;

            Node *tmp = new Node('$', 0);

            tmp->right = connectable;
            tmp->left = temp;

            connectable = tmp;
        }

        Node *root = connectable;

        string decompressedData;
        Node *currentNode = root;

        ofstream outFile(argv[3], ios::out);

        outFile << noskipws;

        char byte;

        string tmp = "";

        int check = originalSize;

        while (check > 0)
        {

            inFile >> byte;

            for (int j = 0; j < 8; j++)
            {
                // Get bit from string

                int bit = (byte >> (7 - j)) & 1;

                if (bit == 1)
                    tmp += "1";
                else if (bit == 0)
                {
                    tmp += "0";
                    check--;
                }
            }
        }

        tmp += '\0';

        cout << tmp << endl;

        for (int i = 0; tmp[i] != 0 && originalSize > 0; i++)
        {
            if (tmp[i] == '1')
                currentNode = currentNode->right;
            else if (tmp[i] == '0')
            {
                currentNode = currentNode->left;
                if (currentNode != nullptr)
                {
                    outFile.put(currentNode->data);
                    originalSize--;
                }
                currentNode = root;
            }
        }

        // Close the output file
        outFile.close();

        std::cout << "Successful decompression" << std::endl;

        // Free memory for the decompression tree
        delete root;
    }
    else
    {
        cerr << "Invalid operation. Use 'C' for compression or 'D' for decompression.";
        return 1;
    }

    return 0;
}

Node *buildHuffmanTree(unordered_map<char, unsigned> *freqMap, string *returned)
{

    std::vector<std::pair<char, int>> charVector((*freqMap).begin(), (*freqMap).end());

    // Sort the vector based on integer values in descending order
    std::sort(charVector.begin(), charVector.end(),
              [](const auto &a, const auto &b)
              {
                  return a.second > b.second;
              });

    std::string result;
    for (const auto &pair : charVector)
    {
        result += pair.first;
    }

    (*returned) = result;

    result += '|';

    Node *nodes[result.length()];

    int index = result.length() - 1;

    Node *connectable = new Node(result[index], (*freqMap)[(char)(result[index])]);

    index--;

    while (index >= 0)
    {

        Node *temp = new Node((char)result[index], (*freqMap)[(char)(result[index])]);

        index--;

        Node *tmp = new Node('$', 0);

        tmp->right = connectable;
        tmp->left = temp;

        connectable = tmp;
    }

    return connectable;
}

void compressAndWriteToFile(ifstream *inFile, ofstream *outFile, Node *root, string *frequencies)
{
    char buffer = 0;
    int bitsInBuffer = 0;
    int offset = 7;

    unsigned char c;

    string tmp = "";

    while ((*inFile) >> c)
    {
        for (int i = 0; (*frequencies)[i] != c; i++)
            tmp += "1";

        tmp += "0";
    }

    tmp += '\0';

    cout << tmp << endl;

    for (int i = 0; tmp[i] != 0; i++)
    {
        if (tmp[i] == '1')
        {
            buffer |= (1 << offset);
            bitsInBuffer++;
            offset--;
        }
        else if (tmp[i] == '0')
        {
            buffer &= ~(1 << offset); // Clear the bit at the specified offset
            bitsInBuffer++;
            offset--;
        }

        if (bitsInBuffer == CHAR_BIT)
        {
            (*outFile).put(buffer);
            bitsInBuffer = 0;
            offset = 7;
        }
    }

    if (bitsInBuffer > 0)
    {
        while (offset > 0)
        {
            buffer &= ~(1 << offset);
            offset--;
        }

        (*outFile).put(buffer);
    }

    (*outFile).close();
}
