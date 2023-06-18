#pragma once

#include <texture_exception.hpp>
#include <primitives.hpp>
#include <util.hpp>
#include <core.hpp>

namespace bolt
{
    enum texture_format {
        PNG,
        JPG
    };

    enum texture_type_gl {
        TEXTURE_2D = GL_TEXTURE_2D
    };

    struct texture_config_gl
    {
        texture_type_gl type;
        texture_format format;
        const_str texture_location;
    };

    class TextureGL
    {
        public:
            explicit TextureGL(texture_config_gl config);

            ~TextureGL();

            [[nodiscard]] static ref_ptr<TextureGL> create(texture_config_gl config);

            void bind();

            void bind_uniform(uint32_t program) const;

            void unbind();

        private:
            static uint32_t activeTexture;

            int32_t binding;

            uint8_t* texture_buffer;

            texture_type_gl type;

            uint32_t texture;

            int32_t BPP; // bytes per pixel

            int32_t width, height;
    };
}