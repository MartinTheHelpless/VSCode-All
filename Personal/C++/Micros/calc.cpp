#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

int main()
{

    double result = 0;

    while (true)
    {
        std::cout << "\nType a operation you would like to perform: " << std::endl;

        char operation;

        std::cin >> operation;

        if (operation != '/' && operation != '+' && operation != '-' && operation != '*' && operation != '^')
        {
            std::cout << "Please check the operation you chose." << std::endl;
        }
        else
        {

            char *ifRes;
            double a = 0;
            double b = 0;

            std::cout << "Choose two numbers to perform the operation with: " << std::endl;

            std::cin >> *(ifRes);

            if (std::strstr(ifRes, "res") != NULL)
                a = result;
            else
                a = atoi(ifRes);

            std::cin >> *(ifRes);

            if (std::strstr(ifRes, "res") != NULL)
                b = result;
            else
                b = atoi(ifRes);

            std::cout << "A is: " << a << std::endl;

            std::cout << "B is: " << b << std::endl;

            std::cout << "Result: " << a << " " << operation << " " << b << " = ";

            switch (operation)
            {

            case '+':
                result = a + b;
                std::cout << result << std::endl;
                break;

            case '-':
                result = a - b;
                std::cout << result << std::endl;
                break;

            case '*':
                result = a * b;
                std::cout << result << std::endl;
                break;

            case '/':

                if (b != 0)
                {
                    result = a / b;
                    std::cout << result << std::endl;
                }
                else
                    std::cout << "Division by zero exeption." << std::endl;
                break;

            case '^':
                result = pow(a, b);
                std::cout << result << std::endl;
                break;

            default:
                break;
            }

            std::cout << "Perform another operation ? y/n" << std::endl;

            std::cin >> operation;

            if (operation == 'n')
                break;
            else if (operation != 'y')
                std::cout << "You have not entered a valid character. The program will continue." << std::endl;

            std::cout << "If you would like to use result in next calculation,\ninstead of a number type \"res\" while choosing a number to operate with" << std::endl;
        }
    }

    std::cout << "Goodbye !" << std::endl;

    return 0;
}
