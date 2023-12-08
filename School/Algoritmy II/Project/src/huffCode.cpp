// huffCode.cpp

#include "huffCode.h"

/**
 * @brief Default constructor for the huffCode class.
 */
huffCode::huffCode()
{
    // No initialization needed in this constructor
}

/**
 * @brief Create the Huffman tree based on character frequencies.
 *
 * This function constructs the Huffman tree using the frequencies of characters in the input data.
 * It builds the tree bottom-up, starting from individual nodes for each character and combining them
 * until a single root node is formed.
 */
void huffCode::createTree()
{
    int maxCount = 0;
    int nodeCount = 0;
    int totalCount = 0;

    // Calculate total frequency and find the maximum frequency
    for (int i = 0; i < 256; i++)
    {
        totalCount += this->frequencies[i];
        if (maxCount < this->frequencies[i])
            maxCount = this->frequencies[i];
        if (this->frequencies[i] > 0)
            nodeCount++;
    }

    Node *nodeBook[nodeCount];

    int position = 0;

    // Create nodes for each character with a frequency greater than 0
    for (int i = 1; i < maxCount + 1; i++)
        for (int j = 0; j < 256; j++)
            if (this->frequencies[j] == i)
                nodeBook[position++] = new Node(this->frequencies[j], std::string() + char(j));

    Node *tmp = nullptr;

    // Combine nodes to create the Huffman tree
    for (int i = 1; i < totalCount + 1; i++)
        for (int j = 0; j < nodeCount; j++)
            if (nodeBook[j]->getValue() == i)
                if (tmp == nullptr)
                    tmp = nodeBook[j];
                else
                {
                    int sumVal = nodeBook[j]->getValue() + tmp->getValue();

                    Node *tmpNode;

                    if (tmp->getLChild() == nullptr && tmp->getRChild() == nullptr)
                        tmpNode = new Node(sumVal, tmp->getCrs() + nodeBook[j]->getCrs(), tmp, nodeBook[j]);
                    else
                        tmpNode = new Node(sumVal, nodeBook[j]->getCrs() + tmp->getCrs(), nodeBook[j], tmp);

                    nodeBook[j] = tmpNode;
                    tmp = nullptr;
                }

    int tmpVal = 0;

    // Find the root of the Huffman tree
    for (int i = 0; i < nodeCount; i++)

        if (tmpVal < nodeBook[i]->getValue())
        {
            tmpVal = nodeBook[i]->getValue();
            tmp = nodeBook[i];
        }

    this->root = tmp;
}

/**
 * @brief Get the root node of the Huffman tree.
 * @return Pointer to the root node.
 */
Node *huffCode::getRootNode()
{
    return this->root;
}

/**
 * @brief Get the depth of a node in the Huffman tree.
 * @param node Pointer to the node.
 * @return Depth of the node in the tree.
 */
int huffCode::getTreeDepth(Node *node)
{
    if (node->getLChild() == nullptr && node->getRChild() == nullptr)
        return 1;
    else
    {
        // Recursively calculate the depth of the left and right children
        int l = getTreeDepth(node->getLChild());

        int r = getTreeDepth(node->getRChild());

        // Return the maximum depth among the left and right subtrees
        if (r > l)
            return 1 + r;
        else
            return 1 + l;
    }
}

/**
 * @brief Map the Huffman tree and store binary representation in valueMap.
 * @param node Pointer to the current node.
 * @param dirs String representing the binary directions.
 *
 * This function traverses the Huffman tree and maps the binary representation of each leaf node
 * to its corresponding character in the valueMap array.
 */
void huffCode::mapTree(Node *node, std::string dirs)
{

    if (node->getLChild() == nullptr && node->getRChild() == nullptr)
    {
        // Map the binary representation of the leaf node to its character
        int pos = int(node->getCrs()[0]);

        for (int i = 0; i < 8; i++)
            this->valueMap[pos][i] = (dirs[i] == '0' || dirs[i] == '1' ? dirs[i] - '0' : 6);
    }
    else
    {
        // Recursively map the left and right subtrees
        if (node->getLChild() != nullptr)
            mapTree(node->getLChild(), dirs + "0");
        if (node->getRChild() != nullptr)
            mapTree(node->getRChild(), dirs + "1");
    }
}

/**
 * @brief Compress the input file using Huffman coding.
 * @param input Pointer to the input file stream.
 * @param output Pointer to the output file stream.
 *
 * This function compresses the input file using Huffman coding and writes the compressed data to the output stream.
 */
void huffCode::compress(std::ifstream *input, std::ofstream *output)
{

    char c;
    (*input) >> std::noskipws;

    for (int i = 0; i < 256; i++)
        this->frequencies[i] = 0;

    // Calculate character frequencies
    while ((*input) >> c)
        this->frequencies[int(c)]++;

    (*input).clear();
    (*input).seekg(0, std::ios::beg);

    createTree();

    mapTree(this->root, "");

    // Compressed data insertion:

    int bytes = 1;

    // Write the Huffman tree structure to the output stream
    for (int i = 0; i < this->root->getCrs().length(); i++)
    {
        (*output).put(this->root->getCrs()[i]);
        (*output).put(char(this->frequencies[int(this->root->getCrs()[i])]));
        bytes++;
    }

    (*output).put(char(0));

    unsigned char currentByte = 0;
    int bitOffset = 7;

    // Compress the actual data using the Huffman tree
    while ((*input) >> c)
    {
        for (int i = 0; i < 8; i++)
        {
            if (this->valueMap[int(c)][i] == 0 || this->valueMap[int(c)][i] == 1)
            {
                if (this->valueMap[int(c)][i] == 1)
                    currentByte |= (1 << bitOffset);

                bitOffset--;
                if (bitOffset < 0)
                {
                    bytes++;
                    (*output).put(currentByte);
                    currentByte = 0;
                    bitOffset = 7;
                }
            }
            else
                break;
        }
    }

    if (bitOffset != 7)
    {
        (*output).put(currentByte);
        bytes++;
    }

    int inBytes = 0;

    // Calculate original and compressed file sizes for compression ratio
    for (int i = 0; i < 256; i++)
        inBytes += this->frequencies[i];

    std::cout << std::setprecision(3);
    std::cout << "Original file size: " << inBytes * 8 << "b\nCompressed file size: " << bytes * 8 << "b.\nCompression ratio: " << double(bytes) / double(inBytes) * 100 << "%." << std::endl;
}

/**
 * @brief Decompress the input file using Huffman coding.
 * @param input Pointer to the input file stream.
 * @param output Pointer to the output file stream.
 *
 * This function decompresses the input file using Huffman coding and writes the decompressed data to the output stream.
 */
void huffCode::decompress(std::ifstream *input, std::ofstream *output)
{

    (*input) >> std::noskipws;

    for (int i = 0; i < 256; i++)
        this->frequencies[i] = 0;

    char check;

    (*input) >> check;

    int origLength = 0;

    // Read the Huffman tree structure from the input stream
    while (check != 0)
    {
        int tmp = int(check);
        (*input) >> check;
        this->frequencies[tmp] = int(check);
        origLength += int(check);
        (*input) >> check;
    }

    createTree();

    std::string decomp = "";

    // Read the compressed data from the input stream
    for (int i = 0; (*input) >> check; i++)
        decomp.append(std::string(sizeof(char), check));

    Node *navNode = this->root;

    // Decompress the data using the Huffman tree
    for (int i = 0; origLength != 0; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // Get bit from string

            bool bit = (decomp[i] >> (7 - j)) & 1;

            // Move in the tree according to the bit

            if (bit)
                navNode = navNode->getRChild();
            else
                navNode = navNode->getLChild();

            // Check if the node is a leaf node

            if (navNode->getLChild() == nullptr && navNode->getRChild() == nullptr)
            {
                (*output).put(navNode->getCrs()[0]);
                navNode = this->root;
                origLength--;
                if (origLength == 0)
                    break;
            }
        }
    }
}
