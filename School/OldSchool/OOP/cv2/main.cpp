#include <string>
#include <iostream>
#include <cmath>
#include <vector>

#include "User.cpp"
#include "keyValue.cpp"
#include "Car.cpp"

int main(int argc, char const *argv[])
{
    User *me = new User("Martin", 21, 190);

    Car *dream = new Car("Ford", "Mustang", "Black", 1969, 141);

    keyValue *myKey = new keyValue(0, 2.85);

    std::cout << me->toString() << std::endl;

    std::cout << dream->toString() << std::endl;

    return 0;
}
