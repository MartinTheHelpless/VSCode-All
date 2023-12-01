#include <iostream>

class Matrix
{
public:
    int rows;
    int cols;

    int **data;

    Matrix(int rows, int cols)
    {
        this->data = new int *[rows];

        for (int i = 0; i < rows; i++)
        {
            this->data[i] = new int[cols];

            for (size_t j = 0; j < cols; j++)
                this->data[i][j] = 0;
        }

        this->cols = cols;
        this->rows = rows;
    }

    void init()
    {

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i][j] = i + j;
            }
        }
    }

    void print()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

void MMMulti(Matrix a, Matrix b, Matrix c)
{

    if (a.rows == b.cols)
    {
        for (int i = 0; i < c.rows; i++)
        {
            for (int j = 0; j < c.cols; j++)
            {
                for (int k = 0; k < a.cols; k++)
                    c.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
}