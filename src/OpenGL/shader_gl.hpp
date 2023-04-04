#pragma once

#include <core.hpp>
#include <util.hpp>
#include <file_system.hpp>

namespace bolt
{
    struct shader_config_gl
    {
        const_str shader_location;
        shader_type type;
    };

    class ShaderGL
    {
        public:
            ShaderGL();

            ~ShaderGL();

            [[nodiscard]] static ref_ptr<ShaderGL> create();

            void add_shader(shader_config_gl config);

            [[nodiscard]] uint32_t get_program() const;

            void bind() const;

            void static unbind();

            void destroy() const;

            void link_shader() const;

        private:
            void read_shader(const_str shader_location);

            void compile_shader(shader_type type);

            std::string shader_string;

            std::vector<uint32_t> delete_queue;

            uint32_t program;
    };
}