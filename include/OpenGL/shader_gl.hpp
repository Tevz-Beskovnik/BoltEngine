#pragma once

#include <core.hpp>
#include <util.hpp>
#include <shader_interface.hpp>

namespace bolt
{
    class ShaderGL : public ShaderInterface
    {
        public:
            [[nodiscard]] ShaderGL(const_str shader_location, shader_type type, render_framework framework_type);

            ~ShaderGL();

            void bind() override;

            void unbind() override;

            void destroy() override;

        private:
            void read_shader(const_str shader_location);

            void compile_shader(shader_type type);

            void link_shader();

            std::string shader_string;

            uint32_t shader;

            uint32_t program;
    };
}