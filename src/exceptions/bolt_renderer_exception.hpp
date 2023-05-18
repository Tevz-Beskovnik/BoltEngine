#pragma once

#include <core.hpp>
#include <exception_interface.hpp>

namespace bolt
{
    class BoltRendererException : public ExceptionInterface
    {
        public:
            BoltRendererException(std::string error, std::string file_location);

            [[nodiscard]] std::string get_error() const override;

        private:
            std::string error;
            std::string file_location;
    };
}
