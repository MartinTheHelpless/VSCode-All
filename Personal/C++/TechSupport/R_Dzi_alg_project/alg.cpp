#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <bitset>
#include <vector>
#include <climits>
using namespace std;

struct Node
{
    char data;
    unsigned int freq;
    Node *left, *right;

    Node(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}

    ~Node()
    {
        delete left;
        delete right;
    }
};

Node *buildHuffmanTree(const unordered_map<char, unsigned> &freqMap);
void getHuffmanCodes(Node *root, const string &currentCode, unordered_map<char, string> &codes);
void writeTreeToFile(ofstream &outFile, Node *root);
void readTreeFromFile(ifstream &inFile, Node *&root);
string compress(const string &data, const unordered_map<char, string> &codes);
void compressAndWriteToFile(const string &data, const unordered_map<char, string> &codes, const string &fileName, Node *root);
string decompress(const string &compressedData, Node *root);

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
    ifstream inFile(fileName, ios::binary);
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

int main(int argc, char *argv[])
{
    // Check if the correct number of arguments is provided
    if (argc != 4)
    {
        cerr << "Incorrect number of arguments.\nEnter in the format: 'name of the program' 'C or D' 'input_file' 'output_file'." << endl;
        return 1;
    }

    // Check if the second argument is 'C' for compression or 'D' for decompression
    if (argv[1][0] == 'C')
    {
        // Compression
        ifstream source(argv[2]);
        if (!source.is_open())
        {
            cerr << "Error opening " << argv[2] << " file for reading." << endl;
            return 1;
        }

        stringstream buffer;
        buffer << source.rdbuf(); // Read the entire file into the stringstream

        // Close the file
        source.close();

        // Extract the content of the stringstream into a string
        string data = buffer.str();
        string fileName = argv[3];

        // Compression
        unordered_map<char, unsigned> freqMap;
        for (char ch : data)
        {
            freqMap[ch]++;
        }

        Node *root = buildHuffmanTree(freqMap);

        unordered_map<char, string> codes;
        getHuffmanCodes(root, "", codes);

        compressAndWriteToFile(data, codes, fileName, root);

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
        ;
    }
    else if (argv[1][0] == 'D')
    {
        // Decompression
        ifstream inFile;
        inFile.open("output.txt", ios::in);
        if (!inFile.is_open())
        {
            cerr << "Error opening new file for reading." << endl;
            return 1;
        }

        // Read the size of the original data
        size_t originalSize;
        inFile.read(reinterpret_cast<char *>(&originalSize), sizeof(originalSize));

        // Read the Huffman tree from the file
        Node *decompressionRoot = nullptr;
        readTreeFromFile(inFile, decompressionRoot);

        // Read the compressed data from the file
        string compressedData = readCompressedData(inFile);
        inFile.close();

        // Decompress the data
        string decompressedData = decompress(compressedData, decompressionRoot);

        // Output the decompressed data
        string outputFileName = argv[3];
        ofstream outputFile(outputFileName);
        if (!outputFile.is_open())
        {
            cerr << "Error opening " << outputFileName << " for writing." << endl;
            return 1;
        }

        outputFile << decompressedData;

        // Close the output file
        outputFile.close();

        // Free memory for the decompression tree
        delete decompressionRoot;
    }
    else
    {
        cerr << "Invalid operation. Use 'C' for compression or 'D' for decompression.";
        return 1;
    }

    return 0;
}

Node *buildHuffmanTree(const unordered_map<char, unsigned> &freqMap)
{
    // Construct an array of Node pointers for each character
    Node *nodes[256]; // Assuming ASCII characters

    for (int i = 0; i < 256; ++i)
    {
        nodes[i] = nullptr;
    }

    // Create nodes for characters with non-zero frequency
    for (const auto &pair : freqMap)
    {
        nodes[static_cast<unsigned char>(pair.first)] = new Node(pair.first, pair.second);
    }

    // Build the Huffman tree
    while (true)
    {
        // Find the two nodes with the smallest frequencies
        int firstMin = -1, secondMin = -1;
        for (int i = 0; i < 256; ++i)
        {
            if (nodes[i] != nullptr)
            {
                if (firstMin == -1 || nodes[i]->freq < nodes[firstMin]->freq)
                {
                    secondMin = firstMin;
                    firstMin = i;
                }
                else if (secondMin == -1 || nodes[i]->freq < nodes[secondMin]->freq)
                {
                    secondMin = i;
                }
            }
        }

        // If there's only one node left, it's the root of the Huffman tree
        if (secondMin == -1)
        {
            return nodes[firstMin];
        }

        // Create a new internal node with the sum of frequencies
        Node *merged = new Node('$', nodes[firstMin]->freq + nodes[secondMin]->freq);
        merged->left = nodes[firstMin];
        merged->right = nodes[secondMin];

        // Set the merged node as the firstMin position, and remove the secondMin node
        nodes[firstMin] = merged;
        nodes[secondMin] = nullptr;
    }
}

void getHuffmanCodes(Node *root, const string &currentCode, unordered_map<char, string> &codes)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data != '$')
    {
        codes[root->data] = currentCode;
    }

    getHuffmanCodes(root->left, currentCode + "0", codes);
    getHuffmanCodes(root->right, currentCode + "1", codes);
}

void writeTreeToFile(ofstream &outFile, Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data == '$')
    {
        outFile << 'I'; // Internal node
        writeTreeToFile(outFile, root->left);
        writeTreeToFile(outFile, root->right);
    }
    else
    {
        outFile << 'L' << root->data; // Leaf node
    }
}

void readTreeFromFile(ifstream &inFile, Node *&root)
{
    char nodeType;
    inFile.get(nodeType);

    if (nodeType == 'I')
    {
        root = new Node('$', 0);
        readTreeFromFile(inFile, root->left);
        readTreeFromFile(inFile, root->right);
    }
    else if (nodeType == 'L')
    {
        root = new Node('$', 0);
        inFile.get(root->data);
    }
}

string compress(const string &data, const unordered_map<char, string> &codes)
{
    string compressedData;
    for (char ch : data)
    {
        compressedData += codes.at(ch);
    }
    cout << compressedData << endl;
    return compressedData;
}

void compressAndWriteToFile(const string &data, const unordered_map<char, string> &codes, const string &fileName, Node *root)
{
    ofstream outFile(fileName, ios::binary);

    // Write the size of the original data (for decompression)
    size_t originalSize = data.size();
    outFile.write(reinterpret_cast<char *>(&originalSize), sizeof(originalSize));

    // Write the Huffman tree information to the file
    writeTreeToFile(outFile, root);

    // Compress the data
    string compressedData = compress(data, codes);

    // Convert the string of 1's and 0's to integers
    vector<int> compressedIntegers;
    for (char bit : compressedData)
    {
        compressedIntegers.push_back(bit - '0');
    }

    // Write the compressed data to the file
    int buffer = 0;
    int bitsInBuffer = 0;
    int offset = 31;

    for (int bit : compressedIntegers)
    {
        buffer |= (bit << offset);
        bitsInBuffer++;
        offset--;

        if (offset == 0)
        {
            outFile.put(buffer);
            bitsInBuffer = 0;
            offset = 31;
        }
    }

    // Write any remaining bits in the buffer
    if (bitsInBuffer > 0)
    {
        buffer <<= (CHAR_BIT - bitsInBuffer);
        outFile.write(reinterpret_cast<char *>(&buffer), sizeof(buffer));
    }

    outFile.close();
}

string decompress(const string &compressedData, Node *root)
{
    string decompressedData;
    Node *current = root;

    for (char bit : compressedData)
    {
        if (bit == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        if (current->data != '$')
        {
            decompressedData += current->data;
            current = root;
        }
    }

    return decompressedData;
}
