#include <log_exception.hpp>

namespace bolt
{
    LogException::LogException(std::string message)
    {
        BOLT_LOG_ERROR(message);
    }
}