#pragma once

#include <primitives.hpp>
#include <util.hpp>
#include <core.hpp>

namespace bolt
{
    enum texture_type_gl {
        TEXTURE_2D = GL_TEXTURE_2D
    };

    struct texture_config_gl
    {
        texture_type_gl type;
        const_str texture_location;
        uint64_t width;
        uint64_t height;
    };

    class TextureGL
    {
        public:
            explicit TextureGL(texture_config_gl config);

            [[nodiscard]] static ref_ptr<TextureGL> create(texture_config_gl config);

            void bind() const;

            void unbind();

        private:
            static uint32_t activeTexture;

            texture_type_gl type;

            uint32_t texture;

            uint64_t width, height;
    };
}