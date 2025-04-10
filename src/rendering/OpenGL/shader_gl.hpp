#pragma once

#include <core.hpp>
#include <cstdint>
#include <util.hpp>
#include <file_system.hpp>
#include <renderer_exception.hpp>

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
            explicit ShaderGL(shader_config_gl config);

            virtual ~ShaderGL();

            [[nodiscard]] static ref_ptr<ShaderGL> create(shader_config_gl config);

            [[nodiscard]] uint32_t get_shader() const;

        private:
            uint32_t shader;
    };

    class ProgramGL
    {
        public:
            explicit ProgramGL(std::vector<ref_ptr<ShaderGL>> config);

            virtual ~ProgramGL();

            [[nodiscard]] static ref_ptr<ProgramGL> create(std::vector<ref_ptr<ShaderGL>> config);

            [[nodiscard]] uint32_t get_program() const;

            void bind() const;

            void static unbind();

            void destroy() const;

        private:
            uint32_t program;
    };
}
