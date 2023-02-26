#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <shader_interface.hpp>
#include <file_system.hpp>
#include <util.hpp>

namespace bolt
{
    class Shader
    {
        public:
            [[nodiscard]] explicit Shader(const_str shader_location, shader_type type, render_framework framework_type);

            [[nodiscard]] static ref_ptr<Shader> create(const_str shader_location, shader_type type, render_framework framework_type);

            // TODO: move this comment to vertex.hpp when it's in the works
            /// User implemented function that setustup shader eg.: Vertex buffer layout, uniform binds, ect..
            void bind();

            void unbind();

            void destroy();

        private:
            ref_ptr<ShaderInterface> shader_interface;
    };
}