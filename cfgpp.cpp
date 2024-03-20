#include <filesystem>
#include <fstream>
#include <vector>

#include "cfgpp.hpp"

inline struct cfg_file_data {
    struct content {
        std::vector<std::string> strs;
        std::vector<std::pair<std::string, std::vector<std::string>>> ns;
    } content;
} cfg_file_data;

inline std::string str_trim_whitespaces(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(),
                             [](const char& c) { return std::isspace(c); }),
              str.end());

    return str;
}

inline bool line_is_ns(std::string line)
{
    line = str_trim_whitespaces(line);

    return true ? line[0] == '[' && line.back() == ']' && line.size() > 2 &&
                      std::count(line.begin(), line.end(), '[') == 1 &&
                      std::count(line.begin(), line.end(), ']') == 1
                : false;
}

inline bool line_is_str(std::string line)
{
    line = str_trim_whitespaces(line);

    return line[0] != '=' && std::count(line.begin(), line.end(), '=') == 1 &&
           std::count(line.begin(), line.end(), '"') == 2 &&
           line.find_first_of('=') < line.find_first_of('"');
}

inline std::string get_str_value(const std::string& str)
{
    return str.substr(str.find_first_of('"') + 1,
                      str.find_last_of('"') - str.find_first_of('"') - 1);
}

inline std::string get_str_name(const std::string& str)
{
    return str.substr(0, str.find_first_of('='));
}

inline std::string get_ns_name(const std::string& ns)
{
    return ns.substr(1, ns.size() - 2);
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

        bool ns = false;

        size_t current_ns = -1;

        while (std::getline(f, line)) {
            if (line_is_ns(line)) {
                if (!ns)
                    ns = true;

                current_ns++;

                cfg_file_data.content.ns.push_back(
                    std::make_pair<std::string, std::vector<std::string>>(
                        get_ns_name(line), std::vector<std::string>()));

                continue;
            }

            if (line_is_str(line) && !ns)
                cfg_file_data.content.strs.push_back(line);
            else if (ns) {
                if (line_is_str(line))
                    cfg_file_data.content.ns[current_ns].second.push_back(line);
            }
        }
    } else {
        // Error
    }
}

void CFGPP::manipulator::close()
{
    cfg_file_data.content.strs.clear();
    cfg_file_data.content.ns.clear();
}

bool CFGPP::manipulator::contains(const std::string& str_name)
{
    for (const auto& i : cfg_file_data.content.strs) {
        if (get_str_name(i) == str_name)
            return true;
    }

    return false;
}

bool CFGPP::manipulator::contains(const std::string& ns_name,
                                  const std::string& str_name)
{
    for (const auto& i : cfg_file_data.content.ns) {
        if (i.first == ns_name) {
            for (const auto& n : i.second) {
                if (get_str_name(n) == str_name)
                    return true;
            }
        }
    }

    return false;
}

bool CFGPP::manipulator::contains_ns(const std::string& ns_name)
{
    for (const auto& i : cfg_file_data.content.ns) {
        if (i.first == ns_name)
            return true;
    }

    return false;
}

std::string CFGPP::manipulator::read(const std::string& str_name)
{
    std::string out;

    for (const auto& i : cfg_file_data.content.strs) {
        if (get_str_name(i) == str_name)
            out = get_str_value(i);
    }

    return out;
}

std::string CFGPP::manipulator::read(const std::string& ns_name,
                                     const std::string& str_name)
{
    std::vector<std::string> out_ns;

    std::string out_str;

    for (const auto& i : cfg_file_data.content.ns) {
        if (i.first == ns_name)
            out_ns = i.second;
    }

    for (const auto& i : out_ns) {
        if (get_str_name(i) == str_name)
            out_str = get_str_value(i);
    }

    return out_str;
}
