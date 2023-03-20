#pragma once

#include <util.hpp>
#include <core.hpp>

namespace bolt
{
    #ifndef ASSERT_FILE_EXISTS
    #define ASSERT_FILE_EXISTS(path) (does_file_exist(path) ? true : throw std::runtime_error("File does not exist"))
    #endif

    bool does_file_exist(const_str file);
}
