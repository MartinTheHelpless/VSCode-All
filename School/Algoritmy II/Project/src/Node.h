/**
 * @class Node
 * @brief Represents a node in a binary tree.
 */
class Node
{
private:
    int value;       /**< The value of the node. */
    std::string crs; /**< The character string associated with the node. */
    Node *lChild;    /**< Pointer to the left child node. */
    Node *rChild;    /**< Pointer to the right child node. */

public:
    /**
     * @brief Parameterized constructor for creating a node with left and right child nodes.
     * @param value The value of the node.
     * @param crs The character string associated with the node.
     * @param lChild Pointer to the left child node.
     * @param rChild Pointer to the right child node.
     */
    Node(int value, std::string crs, Node *lChild, Node *rChild)
    {
        this->value = value;
        this->crs = crs;
        this->lChild = lChild;
        this->rChild = rChild;
    }

    /**
     * @brief Parameterized constructor for creating a node without child nodes.
     * @param value The value of the node.
     * @param crs The character string associated with the node.
     */
    Node(int value, std::string crs)
    {
        this->value = value;
        this->crs = crs;
        this->lChild = nullptr;
        this->rChild = nullptr;
    }

    /**
     * @brief Set the left child of the node.
     * @param child Pointer to the left child node.
     */
    void setLChild(Node *child)
    {
        this->lChild = child;
    }

    /**
     * @brief Set the right child of the node.
     * @param child Pointer to the right child node.
     */
    void setRChild(Node *child)
    {
        this->rChild = child;
    }

    /**
     * @brief Get the value of the node.
     * @return The value of the node.
     */
    int getValue()
    {
        return this->value;
    }

    /**
     * @brief Get the character string associated with the node.
     * @return The character string of the node.
     */
    std::string getCrs()
    {
        return this->crs;
    }

    /**
     * @brief Get the left child node.
     * @return Pointer to the left child node.
     */
    Node *getLChild()
    {
        return this->lChild;
    }

    /**
     * @brief Get the right child node.
     * @return Pointer to the right child node.
     */
    Node *getRChild()
    {
        return this->rChild;
    }
};
