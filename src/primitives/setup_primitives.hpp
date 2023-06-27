#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <util.hpp>

#define setup_primitives std::vector<uint32_t> buffers{}; \
                             std::vector<uint32_t> vertex_arrays{}; \
                             std::vector<uint32_t> shaders{}; \
                             std::vector<uint32_t> draw_type{}; \
                             std::vector<int32_t> count{};    \
                             std::vector<uint32_t> textures{}; \
                             int32_t buffer_size;         \
                             std::pair<uint32_t, uint32_t> _shader_tex_pair;

#define draw_primitives draw_primitives_f(vertex_arrays, shaders, draw_type, count, textures);

namespace bolt
{
    void draw_primitives_f(const std::vector<uint32_t>& vertex_arrays, const std::vector<uint32_t>& shaders, const std::vector<uint32_t>& draw_types, const std::vector<int32_t>& count, const std::vector<uint32_t>& textures);
}