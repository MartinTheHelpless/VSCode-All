#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Node.h"
/**
 * @class huffCode
 * @brief Represents a Huffman coding implementation for compression and decompression.
 */
class huffCode
{
private:
    int frequencies[256]; /**< Array to store the frequency of each character. */
    int valueMap[256][8]; /**< 2D array to map the Huffman codes for each character. */
    Node *root;           /**< Pointer to the root node of the Huffman tree. */

public:
    /**
     * @brief Default constructor for the huffCode class.
     */
    huffCode();

    /**
     * @brief Creates the Huffman tree based on character frequencies.
     */
    void createTree();

    /**
     * @brief Gets the root node of the Huffman tree.
     * @return Pointer to the root node.
     */
    Node *getRootNode();

    /**
     * @brief Gets the depth of a given node in the Huffman tree.
     * @param node Pointer to the node.
     * @return The depth of the node in the tree.
     */
    int getTreeDepth(Node *node);

    /**
     * @brief Maps the Huffman codes for each character in the tree.
     * @param node Pointer to the current node in the tree.
     * @param dirs String representing the direction to reach the current node.
     */
    void mapTree(Node *node, std::string dirs);

    /**
     * @brief Compresses the input file using Huffman coding.
     * @param input Pointer to the input file stream.
     * @param output Pointer to the output file stream.
     */
    void compress(std::ifstream *input, std::ofstream *output);

    /**
     * @brief Decompresses the input file using Huffman coding.
     * @param input Pointer to the input file stream.
     * @param output Pointer to the output file stream.
     */
    void decompress(std::ifstream *input, std::ofstream *output);
};
