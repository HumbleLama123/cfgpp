#include <iostream>

#include "../../cfgpp.hpp"

using namespace std;

int main()
{
    CFGPP::manipulator f("settings.cfg");

    int i = 0;

    while (cout << "- Create new string[1]\n"
                << "- Create new namespace[2]\n"
                << "- Create new string in existing namespace[3]\n"
                << "- Overwrite file[4]\n"
                << ">> ") {
        std::string str_name, str_value, ns_name;

        cin >> i;

        switch (i) {
        case 1:
            cout << "Enter new string name: ";
            cin >> str_name;
            cout << "Enter new string value: ";
            cin >> str_value;

            f.add_str(str_name, str_value);

            break;
        case 2:
            cout << "Enter new namespace name: ";
            cin >> ns_name;

            f.add_ns(ns_name);

            break;
        case 3:
            cout << "Enter existing namespace name: ";
            cin >> ns_name;
            cout << "Enter new string name: ";
            cin >> str_name;
            cout << "Enter new string value: ";
            cin >> str_value;

            f.add_ns_str(ns_name, str_name, str_value);

            break;
        case 4:
            f.write_file(f.get_file_path());
            break;
        }
    }
}