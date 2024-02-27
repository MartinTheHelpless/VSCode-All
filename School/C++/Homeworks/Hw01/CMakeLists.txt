cmake_minimum_required(VERSION 3.8)
project(tasks01)

set(CMAKE_CXX_STANDARD 17)

option(DISABLE_ASAN "Do not use Address sanitizer" ON)

if (NOT DISABLE_ASAN)
    if (NOT WIN32)
        add_compile_options(-fsanitize=address)
    endif()
endif()

# Use main.cpp to call and debug your functions
add_executable(tasks main.cpp tasks.cpp)

# Use the `tests` executable to run unit tests
add_executable(tests tests.cpp tasks.cpp)
