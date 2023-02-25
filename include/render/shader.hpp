#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <util.hpp>

namespace bolt
{
    class Shader
    {
        public:
            [[nodiscard]] explicit Shader(const_str shader_location);

            // TODO: move this comment to vertex.hpp when it's in the works
            /// User implemented function that setustup shader eg.: Vertex buffer layout, uniform binds, ect..
            void setup();

            void bind();

            void unbind();
    };
}