#pragma once

#include <core.hpp>
#include <log.hpp>
#include <exception_interface.hpp>

namespace bolt
{
    class AssertionException : public ExceptionInterface {
        public:
            explicit AssertionException(std::string error, source_location s = source_location::current());

            [[nodiscard]] const char* what() const noexcept override;

        private:
            std::string error;
            std::string file_location;
            std::string out;
    };
}
