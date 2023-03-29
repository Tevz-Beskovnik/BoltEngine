#pragma once

#include <primitives.hpp>
#include <util.hpp>
#include <core.hpp>

namespace bolt
{
    enum texture_type {
        TEXTURE_2D = GL_TEXTURE_2D
    };

    class TextureGL
    {
        public:
            TextureGL(texture_type type);

            [[nodiscard]] static ref_ptr<TextureGL> create(texture_type type);

            void bind() const;

            void unbind();

        private:
            static uint32_t activeTexture;

            texture_type type;

            uint32_t texture;

            uint64_t width, height;
    };
}