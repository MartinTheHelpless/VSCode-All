#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <time.h>
#include <chrono>

void rotateMatrix90(int mat[3][3])
{
    int rotatedMat[3][3];

    // Calculate the rotated matrix
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            rotatedMat[j][2 - i] = mat[i][j];
}

void displayMatrix(int mat[3][3])
{
    // Display the matrix
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int matrix[3][3] = {{0, 0, 0},
                        {1, 1, 1},
                        {0, 0, 0}};

    std::cout << "Original Matrix:\n";
    displayMatrix(matrix);

    // Rotate the matrix by 90 degrees clockwise using an auxiliary matrix
    rotateMatrix90(matrix);

    std::cout << "\nRotated Matrix (90 degrees clockwise):\n";
    displayMatrix(matrix);

    return 0;
}
