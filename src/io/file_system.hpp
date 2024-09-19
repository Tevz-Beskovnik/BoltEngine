#pragma once

#include <util.hpp>
#include <core.hpp>

namespace bolt
{
    #ifndef ASSERT_FILE_EXISTS
    #define ASSERT_FILE_EXISTS(path, err) if(!does_file_exist(path)) \
    {                                                                \
        BOLT_LOG_INFO(std::string{err} + path)                       \
        throw std::runtime_error(std::string{err} + path);           \
    }
    #endif

    bool does_file_exist(const_str file);
}
