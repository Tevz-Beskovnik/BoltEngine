//
// Created by Tevz on 18/05/2023.
//

#include <bolt_renderer_exception.hpp>

namespace bolt
{
    RendererException::RendererException(std::string error, source_location s)
        : error(error), file_location(std::string{"["} + s.function_name() + "#" + std::to_string(s.line()) + "]"), out(error + " " + file_location)
    {
        ;
    }

    [[nodiscard]] const char* RendererException::what() const noexcept
    {
        return out.c_str();
    }
}