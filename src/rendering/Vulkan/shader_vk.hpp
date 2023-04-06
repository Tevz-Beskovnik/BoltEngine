#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    class ShaderVK
    {
    public:
        [[nodiscard]] ShaderVK(const_str shader_location, uint32_t type);

        ~ShaderVK();

        [[nodiscard]] static ref_ptr<ShaderVK> create(const_str shader_location, uint32_t type);

        void bind();

        void unbind();

        void destroy();
    };
}