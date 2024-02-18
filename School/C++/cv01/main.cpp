#include "tasks.h"
#include <iostream>

int main(int argc, char const *argv[])
{

    int res;

    std::cout << math::fibonacci(4) << std::endl;

    if (strutils::parse_uint("65158", res))
        std::cout << res << std::endl;

    std::cout << strutils::camel_to_snake("helloWorld") << std::endl;

    return 0;
}
