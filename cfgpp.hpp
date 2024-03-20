#pragma once

#ifndef CFGPP_HPP
#define CFGPP_HPP

#include <string>

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

    private:
    };
} // namespace CFGPP

#endif // CFGPP_HPP