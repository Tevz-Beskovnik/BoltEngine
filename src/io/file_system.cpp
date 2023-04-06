#include <file_system.hpp>

namespace bolt
{
    bool does_file_exist(const_str file)
    {
        std::fstream file_open(file);

        bool is_open = file_open.is_open();

        file_open.close();

        return is_open;
    }
}