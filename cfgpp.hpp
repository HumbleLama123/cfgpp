#pragma once

#ifndef CFGPP_HPP
#define CFGPP_HPP

#include <string>
#include <vector>

#define CFGPP_STRS_CONTENT std::vector<std::pair<std::string, std::string>>
#define CFGPP_NS_CONTENT std::vector<std::pair<std::string, CFGPP_STRS_CONTENT>>
#define CFGPP_LOG(x) printf("%s\n", x);

namespace CFGPP {
    class manipulator {
    public:
        manipulator();

        manipulator(const std::string& cfg_file_path);

        void open(const std::string& cfg_file_path);

        void close();

        bool contains(const std::string& str_name);

        bool contains(const std::string& ns_name, const std::string& str_name);

        bool contains_ns(const std::string& ns_name);

        std::string read(const std::string& str_name);

        std::string read(const std::string& ns_name,
                         const std::string& str_name);

        void add_str(const std::string& str_name, const std::string& value);

        void add_ns(const std::string& ns_name);

        void add_ns_str(const std::string& ns_name, const std::string& str_name,
                        const std::string& str_value);

        void write_file(const std::string& cfg_file_path);

        CFGPP_STRS_CONTENT& get_str_vec();

        CFGPP_NS_CONTENT& get_ns_vec();

        std::string get_file_path();

    private:
        struct content {
            CFGPP_STRS_CONTENT strs;
            CFGPP_NS_CONTENT ns;
        } content;

        const std::string cfg_file_path;
    };
} // namespace CFGPP

#endif // CFGPP_HPP