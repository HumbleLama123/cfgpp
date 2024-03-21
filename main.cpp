#include "cfgpp.hpp"

int main()
{
    CFGPP::manipulator f;

    f.add_str("string", "value");

    f.add_ns("namespace");
    f.add_ns_str("namespace", "a", "value");

    f.write_file("settings.cfg");

    for (size_t i = 0; i < 100000000; i++)
        f.read("string");

    CFGPP_LOG("Reading string \"string\" 100000000 times is done.");

    for (size_t i = 0; i < 100000000; i++)
        f.read("namespace", "string");

    CFGPP_LOG("Reading string \"string\" in namespace \"namespace\" 100000000 "
              "times is done.");

    return 0;
}