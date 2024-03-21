#include <algorithm>
#include <filesystem>
#include <fstream>

#include "cfgpp.hpp"

inline std::string into_str_format(const std::string& str_name,
                                   const std::string& str_value)
{
    return str_name + " = \"" + str_value + '"';
}

inline std::string into_namespace_format(const std::string& namespace_name)
{
    return '[' + namespace_name + ']';
}

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

inline std::string get_str_name(std::string str)
{
    str = str_trim_whitespaces(str);

    return str.substr(0, str.find_first_of('='));
}

inline std::string get_ns_name(std::string ns)
{
    ns = str_trim_whitespaces(ns);

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
        const_cast<std::string&>(this->cfg_file_path) = cfg_file_path;

        std::ifstream f(cfg_file_path);

        std::string line;

        bool ns = false;

        size_t current_ns = -1;

        while (std::getline(f, line)) {
            if (line_is_ns(line)) {
                if (!ns)
                    ns = true;

                current_ns++;

                content.ns.push_back(
                    std::make_pair(get_ns_name(line), CFGPP_STRS_CONTENT()));

                continue;
            }

            if (line_is_str(line) && !ns)
                content.strs.push_back(
                    std::make_pair(get_str_name(line), get_str_value(line)));
            else if (ns) {
                if (line_is_str(line))
                    content.ns[current_ns].second.push_back(std::make_pair(
                        get_str_name(line), get_str_value(line)));
            }
        }
    } else {
        CFGPP_LOG("[CFGPP][ERROR]: The specified file could not be found.");

        exit(EXIT_FAILURE);
    }
}

void CFGPP::manipulator::close()
{
    content.strs.clear();
    content.ns.clear();
}

bool CFGPP::manipulator::contains(const std::string& str_name)
{
    for (const auto& i : content.strs) {
        if (i.first == str_name)
            return true;
    }

    return false;
}

bool CFGPP::manipulator::contains(const std::string& ns_name,
                                  const std::string& str_name)
{
    for (const auto& i : content.ns) {
        if (i.first == ns_name) {
            for (const auto& n : i.second) {
                if (n.first == str_name)
                    return true;
            }
        }
    }

    return false;
}

bool CFGPP::manipulator::contains_ns(const std::string& ns_name)
{
    for (const auto& i : content.ns) {
        if (i.first == ns_name)
            return true;
    }

    return false;
}

std::string CFGPP::manipulator::read(const std::string& str_name)
{
    std::string out;

    for (const auto& i : content.strs) {
        if (i.first == str_name)
            out = i.second;
    }

    return out;
}

std::string CFGPP::manipulator::read(const std::string& ns_name,
                                     const std::string& str_name)
{
    CFGPP_STRS_CONTENT out_ns;

    std::string out_str;

    for (const auto& i : content.ns) {
        if (i.first == ns_name)
            out_ns = i.second;
    }

    for (const auto& i : out_ns) {
        if (i.first == str_name)
            out_str = i.second;
    }

    return out_str;
}

void CFGPP::manipulator::add_str(const std::string& str_name,
                                 const std::string& value)
{
    content.strs.push_back(std::make_pair(str_name, value));
}

void CFGPP::manipulator::add_ns(const std::string& ns_name)
{
    content.ns.push_back(std::make_pair(ns_name, CFGPP_STRS_CONTENT()));
}

void CFGPP::manipulator::add_ns_str(const std::string& ns_name,
                                    const std::string& str_name,
                                    const std::string& value)
{
    size_t current_ns_id = 0;

    for (size_t i = 0; i < content.ns.size(); i++) {
        if (content.ns[i].first == ns_name)
            current_ns_id = i;
    }

    content.ns[current_ns_id].second.push_back(std::make_pair(str_name, value));
}

void CFGPP::manipulator::write_file(const std::string& cfg_file_path)
{
    if (std::filesystem::exists(cfg_file_path)) {
        const_cast<std::string&>(this->cfg_file_path) = cfg_file_path;

        std::ofstream f(cfg_file_path);

        for (const auto& i : content.strs)
            f << into_str_format(i.first, i.second) + '\n';

        for (const auto& i : content.ns) {
            f << '\n' + into_namespace_format(i.first) + '\n';

            for (const auto& n : i.second)
                f << into_str_format(n.first, n.second) + '\n';
        }
    } else {
        CFGPP_LOG("[CFGPP][ERROR]: The specified file could not be found.");

        exit(EXIT_FAILURE);
    }
}

CFGPP_STRS_CONTENT& CFGPP::manipulator::get_str_vec()
{
    return content.strs;
}

CFGPP_NS_CONTENT& CFGPP::manipulator::get_ns_vec()
{
    return content.ns;
}

std::string CFGPP::manipulator::get_file_path()
{
    return cfg_file_path;
}