#include "Graph.h"

int main(int argc, char const *argv[])
{
    std::vector<std::vector<std::vector<int>>> matrices = {{{0, 2, 0, 6, 0},
                                                            {2, 0, 3, 8, 5},
                                                            {0, 3, 0, 0, 7},
                                                            {6, 8, 0, 0, 9},
                                                            {0, 5, 7, 9, 0}},

                                                           {{0, 9, 75, 0, 0},
                                                            {9, 0, 95, 19, 42},
                                                            {75, 95, 0, 51, 66},
                                                            {0, 19, 51, 0, 31},
                                                            {0, 42, 66, 31, 0}},

                                                           {{0, 19, 5, 0, 0},
                                                            {19, 0, 5, 9, 2},
                                                            {5, 5, 0, 1, 6},
                                                            {0, 9, 1, 0, 1},
                                                            {0, 2, 6, 1, 0}},

                                                           {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                                            {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                                            {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                                            {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                                            {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                                            {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                                            {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                                            {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                                            {0, 0, 2, 0, 0, 0, 6, 7, 0}}};

    for (int i = 0; i < matrices.size() * 2; i++)
    {
        i == matrices.size() ? std::cout << "-----------------------------------\n\n" : std::cout << "";

        Graph *test = new Graph(&matrices[i % matrices.size()]);

        test->dijkstra(&matrices[i % matrices.size()], (i >= matrices.size() ? 4 : 0));

        test->clearGraph();
    }

    return 0;
}
