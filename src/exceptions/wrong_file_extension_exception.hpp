#pragma once

#include <core.hpp>
#include <exception_interface.hpp>

namespace bolt
{
    class WrongFileExtensionException : public ExceptionInterface {
        public:
            WrongFileExtensionException(std::string error, source_location s = source_location::current());

            [[nodiscard]] const char* what() const noexcept override;

        private:
            std::string error;
            std::string file_location;
            std::string out;
    };
}
