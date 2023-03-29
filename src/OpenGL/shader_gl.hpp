#pragma once

#include <core.hpp>
#include <util.hpp>
#include <file_system.hpp>

namespace bolt
{
    class ShaderGL
    {
        public:
            ShaderGL();

            ~ShaderGL();

            [[nodiscard]] static ref_ptr<ShaderGL> create();

            void add_shader(const_str shader_location, shader_type type);

            [[nodiscard]] uint32_t get_program() const;

            void bind() const;

            void static unbind();

            void destroy() const;

        private:
            void read_shader(const_str shader_location);

            void compile_shader(shader_type type);

            void link_shader() const;

            std::string shader_string;

            uint32_t shader;

            uint32_t program;
    };
}