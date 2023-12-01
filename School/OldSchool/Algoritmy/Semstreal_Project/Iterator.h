#pragma once
#include <stack>
#include "Graph.h"

class Iterator
{
private:
    Graph *baseGraph;

public:
    Iterator(Graph *baseGraph);

    void reset();

    void next();

    bool isEnd();

    void currentKey();
};