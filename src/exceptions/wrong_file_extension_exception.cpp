//
// Created by Tevz on 19/05/2023.
//

#include <wrong_file_extension_exception.hpp>

namespace bolt
{
    WrongFileExtensionException::WrongFileExtensionException(std::string error, source_location s)
        : error(error), file_location(std::string{"["} + s.function_name() + "#" + std::to_string(s.line()) + "]"), out(error + " " + file_location),
          LogException(error + " " + std::string{"["} + s.function_name() + "#" + std::to_string(s.line()) + "]")
    {
        ;
    }

    [[nodiscard]] const char* WrongFileExtensionException::what() const noexcept
    {
        return out.c_str();
    }
}
