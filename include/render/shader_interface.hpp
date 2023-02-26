#pragma once

namespace bolt
{
    enum shader_type
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

    class ShaderInterface
    {
        public:
            virtual void bind() { ; };

            virtual void unbind() { ; };

            virtual void destroy() { ; };
    };
}