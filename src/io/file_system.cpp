#include <file_system.hpp>

namespace bolt
{
    bool doesFileExist(const_str file)
    {
        std::fstream file_open(file);

        return file_open.is_open();
    }
}