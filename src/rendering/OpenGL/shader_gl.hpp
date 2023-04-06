#pragma once

#include <core.hpp>
#include <util.hpp>
#include <file_system.hpp>

namespace bolt
{
    struct shader_config_gl
    {
        const_str shader_location;
        uint32_t type;
    };

    class ShaderGL
    {
        public:
            ShaderGL(std::vector<shader_config_gl> config);

            virtual ~ShaderGL();

            [[nodiscard]] static ref_ptr<ShaderGL> create(std::vector<shader_config_gl> config);

            [[nodiscard]] uint32_t get_program() const;

            void bind() const;

            void static unbind();

            void destroy() const;

        private:
            void read_shader(const_str shader_location);

            void compile_shader(uint32_t type);

            std::string shader_string;

            std::vector<uint32_t> delete_queue;

            uint32_t program;
    };
}