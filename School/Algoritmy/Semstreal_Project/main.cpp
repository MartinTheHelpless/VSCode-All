#include "Graph.cpp"
#include "Iterator.cpp"

int main(int argc, char const *argv[])
{

    FILE *f = fopen("graph.txt", "wt+");

    Graph *g = new Graph();

    g->loadGraph(f);

    fclose(f);

    return 0;
}
