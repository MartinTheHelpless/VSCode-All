#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void printVector(std::vector<double> vect);

void forwardElimination(vector<vector<double>> &matrix);

int main()
{
    std::vector<std::vector<double>> matrix = {
        {1, 2, -3, 4, 5, 4},
        {2, 1, 0, 3, 0, 9},
        {0, 2, 1, 2, -1, 5},
        {3, -1, 0, 5, 2, 3},
        {2, 1, 2, 3, -4, 2}};
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
        std::cout << (vect[i + 1] > 9 || vect[i + 1] < -9 ? "" : " ");
        std::cout << vect[i] << (vect[i + 1] < 0 ? "  " : "   ") << (i + 1 == vect.size() - 1 ? (vect[i + 1] > 0 ? "| " : " | ") : "");
    }
    std::cout << std::endl;
}

void forwardElimination(vector<vector<double>> &matrix)
{
    for (int k = 0; k < matrix.size() - 1; k++)
    {
        for (int i = k + 1; i < matrix.size(); i++)
        {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j < matrix.size() + 1; j++)
            {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }
}