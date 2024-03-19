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

    private:
    };
} // namespace CFGPP

#endif // CFGPP_HPP