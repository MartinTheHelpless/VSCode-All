#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    while (true)
    {
        cout << "Set a size of the triangle: " << endl;

        int width = 0;

        cin >> width;

        width % 2 == 0 ? width++ : width;

        width < 0 ? width = width * (-1) : width;

        width += 2;

        for (size_t i = 0; i < width / 2; i++)
        {
            for (size_t o = 0; o < width; o++)
                o >= width / 2 - i &&o <= width / 2 + i ? cout << "x" : cout << " ";
            cout << endl;
        }
    }

    return 0;
}
