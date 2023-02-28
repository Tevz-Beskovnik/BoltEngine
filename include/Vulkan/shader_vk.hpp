#pragma once

#include <core.hpp>
#include <util.hpp>
#include <shader_interface.hpp>

namespace bolt
{
    class ShaderVK : public ShaderInterface
    {
    public:
        [[nodiscard]] ShaderVK(const_str shader_location, shader_type type);

        ~ShaderVK();

        [[nodiscard]] static ref_ptr<ShaderVK> create(const_str shader_location, shader_type type);

        void bind() override;

        void unbind() override;

        void destroy() override;
    };
}