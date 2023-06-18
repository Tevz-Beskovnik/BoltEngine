#pragma once

#include <core.hpp>
#include <util.hpp>
#include <log_exception.hpp>

namespace bolt
{
    class TextureException : public LogException
    {
        public:
            explicit TextureException(std::string error, source_location s = source_location::current());

            [[nodiscard]] const char* what() const noexcept override;

        private:
            std::string error;
            std::string file_location;
            std::string out;
    };
}