#pragma once

#include <core.hpp>

namespace bolt
{
    struct attribute_layout // USED IN model_dynamic_inteface and model_static_inteface
    {
        int32_t size;
        uint32_t type;
        uint32_t normalise;
        int32_t total_size_in_bytes;
        ptrdiff_t offset;
    };
}