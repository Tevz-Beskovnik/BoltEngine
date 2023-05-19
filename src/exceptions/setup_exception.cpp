//
// Created by Tevz on 19/05/2023.
//

#include <setup_exception.hpp>

namespace bolt
{
    SetupException::SetupException(std::string error, source_location s)
        : error(error), file_location(std::string{"["} + s.function_name() + "#" + std::to_string(s.line()) + "]"), out(error + " " + file_location)
    {
        BOLT_LOG_ERROR(out)
    }

    [[nodiscard]] const char* SetupException::what() const noexcept
    {
        return out.c_str();
    }
}
