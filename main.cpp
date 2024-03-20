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