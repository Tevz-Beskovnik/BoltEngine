#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <util.hpp>

#define setup_primitives std::vector<uint32_t> buffers{}; \
                             std::vector<uint32_t> vertex_arrays{}; \
                             std::vector<uint32_t> shaders{}; \
                             std::vector<uint32_t> draw_type{}; \
                             std::vector<uint32_t> count{};   \
                             int32_t buffer_size;

#define draw_primitives draw_primitives_f(vertex_arrays, shaders, draw_type, count);

namespace bolt
{
    void draw_primitives_f(const std::vector<uint32_t>& vertex_arrays, const std::vector<uint32_t>& shaders, const std::vector<uint32_t>& draw_types, const std::vector<uint32_t>& count);
}