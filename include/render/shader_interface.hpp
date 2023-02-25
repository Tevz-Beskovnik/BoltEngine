#pragma once

namespace bolt
{
    enum shader_type {
        VERTEX_SHADER = 0x8B31,
        FRAGMENT_SHADER = 0x8B30
    };

    class ShaderInterface
    {
        public:
            virtual void setup_vertex_attributes() { ; };

            virtual void add_variable() { ; };

            virtual void bind() { ; };

            virtual void unbind() { ; };

            virtual void destroy() { ; };
    };
}