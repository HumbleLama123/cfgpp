[![C/C++ CI](https://github.com/HumbleLama123/cfgpp/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/HumbleLama123/cfgpp/actions/workflows/c-cpp.yml)
# CFGPP
```cpp
// main.cpp

#include <iostream>

#include "cfgpp.hpp"

using namespace std;

int main()
{
    CFGPP::manipulator f("settings.cfg");

    if (f.contains("str1"))
        cout << f.read("str1") << endl;

    if (f.contains_ns("ns1") && f.contains("ns1", "str1"))
        cout << f.read("ns1", "str1") << endl;

    return 0;
}
```
```cfg
# settings.cfg

str1 = "value1"

[ns1]
str1 = "value2"
```
```
clang++ main.cpp cfgpp.cpp -std=c++23 -Wall -Werror
```
# The main goal of the project
The main goal of the project is to write a simple, fast and high-quality configuration file manipulator library for the C++ language, using the new features of C++23.