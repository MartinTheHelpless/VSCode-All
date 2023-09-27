#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int N = 5;

void printVector(std::vector<double> vect);

void forwardElimination(vector<vector<double>> &matrix);

int main()
{
    std::vector<std::vector<double>> matrix = {
        {1, 2, -3, 4, 5},
        {2, 1, 0, 3, 0},
        {0, 2, 1, 2, -1},
        {3, -1, 0, 5, 2},
        {2, 1, 2, 3, -4}};

    forwardElimination(matrix);

    for (int i = 0; i < matrix.size(); i++)
    {
        printVector(matrix[i]);
    }

    return 0;
}

void printVector(std::vector<double> vect)
{
    for (int i = 0; i < vect.size(); i++)
    {
        std::cout << std::fixed;
        std::cout << std::setprecision(2);
        std::cout << vect[i] << (vect[i + 1] < 0 ? "  " : "   ");
        std::cout << (vect[i + 1] > 9 || vect[i + 1] < -9 ? "" : " ");
    }
    std::cout << std::endl;
}

void forwardElimination(vector<vector<double>> &matrix)
{
    for (int k = 0; k < N - 1; k++)
    {
        for (int i = k + 1; i < N; i++)
        {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j < N; j++)
            {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }
}