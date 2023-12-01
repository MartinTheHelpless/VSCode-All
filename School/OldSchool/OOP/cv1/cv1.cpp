#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>

int main(int argc, char const *argv[])
{
    int temperature[10] = {-4, 8, 1, -10, -5, 7, -6, -2, 3, 4};

    int actTemp = 0;

    for (size_t i = 0; i < 10; i++)
    {

        std::cout << "Temperature is: " << actTemp << " + " << temperature[i] << " = " << actTemp + temperature[i] << std::endl;

        actTemp += temperature[i];

        if (actTemp <= -10)
        {
            std::cout << "Core froze !!\nBOOOM!!" << std::endl;
            break;
        }
        else if (actTemp >= 10)
        {
            std::cout << "Core oveheated !!\nBOOOM!!" << std::endl;
            break;
        }
    }

    return 0;
}
