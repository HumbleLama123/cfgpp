[![C/C++ CI](https://github.com/HumbleLama123/cfgpp/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/HumbleLama123/cfgpp/actions/workflows/c-cpp.yml)
# CFGPP
```cpp
// main.cpp

#include "cfgpp.hpp"

int main()
{
    CFGPP::manipulator f;

    f.add_str("string", "value");

    f.add_ns("namespace");
    f.add_ns_str("namespace", "a", "value");

    f.write_file("settings.cfg");

    CFGPP_LOG("Reading string \"string\" 1000000 times is done.");
    for (size_t i = 0; i < 10000000; i++)
        f.read("string");

    CFGPP_LOG("Reading string \"string\" in namespace \"namespace\" 1000000 "
              "times is done.");
    for (size_t i = 0; i < 1000000; i++)
        f.read("namespace", "string");

    return 0;
}
```
```
clang++ main.cpp cfgpp.cpp -std=c++23 -Wall -Werror
```
# The main goal of the project
The main goal of the project is to write a simple, fast and high-quality configuration file manipulator library for the C++ language, using the new features of C++23.