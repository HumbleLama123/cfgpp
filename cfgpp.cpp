#include <filesystem>
#include <fstream>
#include <vector>

#include "cfgpp.hpp"

inline struct cfg_file_data {
    struct content {
        std::vector<std::string> ns, strs;
    } content;
} cfg_file_data;

inline std::string str_trim_whitespaces(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(),
                             [](const char& c) { return std::isspace(c); }),
              str.end());

    return str;
}

inline bool line_is_str(std::string line)
{
    line = str_trim_whitespaces(line);

    return line[0] != '=' && std::count(line.begin(), line.end(), '=') == 1 &&
           std::count(line.begin(), line.end(), '"') == 2 &&
           line.find_first_of('=') < line.find_first_of('"');
}

CFGPP::manipulator::manipulator()
{
}

CFGPP::manipulator::manipulator(const std::string& cfg_file_path)
{
    open(cfg_file_path);
}

void CFGPP::manipulator::open(const std::string& cfg_file_path)
{
    if (std::filesystem::exists(cfg_file_path)) {
        std::ifstream f(cfg_file_path);

        std::string line;

        while (std::getline(f, line)) {
        }
    } else {
        // Error
    }
}