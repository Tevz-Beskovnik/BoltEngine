#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <line.hpp>
#include <util.hpp>

namespace bolt
{
    #define SETUP_PRIMITIVES std::vector<uint32_t> buffers; \
                             std::vector<uint32_t> shaders; \
                             std::vector<uint32_t> draw_type; \
                             std::vector<uint32_t> count;   \
                             int32_t buffer_size;

    #define DRAW_PRIMITIVES draw_primitives(buffers, shaders, draw_type, count);

    void draw_primitives(const std::vector<uint32_t>& buffers, const std::vector<uint32_t>& shaders, const std::vector<uint32_t>& draw_types, const std::vector<uint32_t>& count);
}