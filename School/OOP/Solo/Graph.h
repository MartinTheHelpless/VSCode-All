#pragma once
#include <vector>
#include <iostream>

class Graph
{
private:
    class Vertex
    {
    private:
        int ID;
        int value;
        std::vector<Vertex *> neighbours;

    public:
        Vertex(int id, int value);

        void addNeighbour(Vertex *neighbour);

        int getID();

        int getValue();
    };

    std::vector<Vertex *> nodes;

public:
    Graph();
    ~Graph();
};