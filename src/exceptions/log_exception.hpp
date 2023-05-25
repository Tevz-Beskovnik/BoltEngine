#pragma once

#include <core.hpp>
#include <log.hpp>

namespace bolt
{
    class LogException : public std::exception {
        public:
            LogException() = delete;

            explicit LogException(std::string message);

            [[nodiscard]] virtual const char* what() const noexcept = 0;
    };
}
