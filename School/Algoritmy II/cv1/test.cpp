#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<double>> A_1 = {
    {1, 2, -3, 4, 5},
    {2, 1, 0, 3, 0},
    {0, 2, 1, 2, -1},
    {3, -1, 0, 5, 2},
    {2, 1, 2, 3, -4}};

vector<double> B_1 = {4, 9, 5, 3, 2};

vector<double> variables;

void printMatrix(vector<vector<double>> matrix_a, vector<double> matrix_b)
{
    for (int i = 0; i < matrix_a.size(); i++)
    {
        for (int j = 0; j < matrix_a[i].size(); j++)
        {
            cout << matrix_a[i][j] << '\t';
        }
        cout << "|" << matrix_b[i] << endl;
    }
    cout << endl;
    cout << endl;
}

void printOutput(vector<double> output)
{
    for (int i = 0; i < output.size(); i++)
    {
        cout << "x" << i + 1 << ": " << output[i] << endl;
    }
}

int main()
{

    cout << setprecision(4);
    for (int i = 0; i < A_1[0].size(); i++)
    {
        variables.push_back(1);
    }

    if (A_1.size() < A_1[0].size())
    {
        cout << "Can't calculate Matrix." << endl;
        return -1;
    }

    printMatrix(A_1, B_1);

    // Rows
    for (int i = 0; i < A_1[0].size(); i++)
    {
        // Next rows
        for (int j = i; j < A_1.size(); j++)
        {
            for (int k = j + 1; k < A_1.size(); k++)
            {
                if (A_1[k][i] != 0 && A_1[j][i] != 0)
                {
                    double divider = A_1[j][i] / A_1[k][i];
                    for (int l = 0; l < A_1[j].size(); l++)
                    {
                        A_1[k][l] -= A_1[j][l] / divider;
                    }
                    B_1[k] -= B_1[j] / divider;
                }
            }
        }
    }

    printMatrix(A_1, B_1);

    for (int i = A_1.size() - 1; i >= 0; i--)
    {
        double row = 0;
        double unknown_var = 0;
        for (int j = 0; j < A_1[i].size(); j++)
        {
            if (i == j)
            {
                unknown_var = A_1[i][j];
            }
            else
            {
                row += A_1[i][j] * variables[j];
            }
        }
        if (unknown_var == 0)
        {
            cout << "Can't resolve Matrix." << endl;
            return -1;
        }
        variables[i] = (B_1[i] - row) / unknown_var;
    }

    printOutput(variables);
    return 0;
}
