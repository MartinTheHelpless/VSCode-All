#include <iostream>
#include <vector>

void gaussianElimination(std::vector<std::vector<double>> matrix, std::vector<double> right);

void printVector(std::vector<double> vect);

int main(int argc, char const *argv[])
{
        std::vector<std::vector<double>> input = {
            {1, 2, -3, 4, 5},
            {2, 1, 0, 3, 0},
            {0, 2, 1, 2, -1},
            {3, -1, 0, 5, 2},
            {2, 1, 2, 3, -4}};
        std::vector<double> right = {4, 9, 5, 3, 2};

        gaussianElimination(input, right);

        return 0;
}

void gaussianElimination(std::vector<std::vector<double>> mat, std::vector<double> right)
{

        for (int i = 0; i < mat.size(); i++)
        {
                for (int j = i; j < mat[i].size(); j++)
                {
                        if (mat[j][0] != 0 && mat[j][0] != 0 && int(mat[j][0]) % int(mat[j][0]) == 0)
                        {
                                for (int a = 0; a <= int(mat[j][0]) / int(mat[j][0]); a++)
                                {
                                        std::cout << "trough" << std::endl;
                                        if (mat[j][0] > mat[i][0])
                                        {
                                                for (int k = 0; k < mat[j].size(); k++)
                                                        mat[j][k] -= mat[i][k];
                                                right[j] -= right[i];
                                        }
                                        else if (mat[j][0] < mat[i][0])
                                        {
                                                for (int k = 0; k < mat[j].size(); k++)
                                                        mat[j][k] += mat[i][k];
                                                right[j] += right[i];
                                        }
                                }
                        }
                }
        }

        for (int i = 0; i < mat.size(); i++)
        {
                printVector(mat[i]);
        }
}

void printVector(std::vector<double> vect)
{
        for (int i = 0; i < vect.size(); i++)
        {
                std::cout << vect[i] << (vect[i + 1] < 0 ? "  " : "   ");
                std::cout << (vect[i + 1] > 9 || vect[i + 1] < -9 ? "" : " ");
        }
        std::cout << std::endl;
}