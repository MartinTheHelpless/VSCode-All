class Node
{
private:
    int value;
    std::string crs;
    Node *lChild;
    Node *rChild;

public:
    Node(int value, std::string crs, Node *lChild, Node *rChild)
    {
        this->value = value;
        this->crs = crs;
        this->lChild = lChild;
        this->rChild = rChild;
    }

    Node(int value, std::string crs)
    {
        this->value = value;
        this->crs = crs;
        this->lChild = nullptr;
        this->rChild = nullptr;
    }

    void setLChild(Node *child)
    {
        this->lChild = child;
    }

    void setRChild(Node *child)
    {
        this->rChild = child;
    }

    int getValue()
    {
        return this->value;
    }

    std::string getCrs()
    {
        return this->crs;
    }

    Node *getLChild()
    {
        return this->lChild;
    }

    Node *getRChild()
    {
        return this->rChild;
    }
};