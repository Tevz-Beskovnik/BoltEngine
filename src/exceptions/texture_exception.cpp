#include <texture_exception.hpp>

namespace bolt
{
    TextureException::TextureException(std::string error, source_location s)
        : error(error), file_location(std::string{"["} + s.function_name() + "#" + std::to_string(s.line()) + "]"), out(error + " " + file_location),
          LogException(error + " " + std::string{"["} + s.function_name() + "#" + std::to_string(s.line()) + "]")
    {
        ;
    }

    [[nodiscard]] const char* TextureException::what() const noexcept
    {
        return out.c_str();
    }
}