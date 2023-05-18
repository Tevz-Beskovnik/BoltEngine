#pragma once

#include <core.hpp>

namespace bolt
{
    class ExceptionInterface
    {
        public:
            [[nodiscard]] virtual std::string get_error() const = 0;
    };
}