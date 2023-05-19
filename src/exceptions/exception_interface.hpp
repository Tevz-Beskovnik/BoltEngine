#pragma once

#include <core.hpp>

namespace bolt
{
class ExceptionInterface : public std::exception
    {
        public:
            [[nodiscard]] virtual const char* what() const noexcept = 0;
    };
}