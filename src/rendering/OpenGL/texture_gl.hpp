#pragma once

#include <texture_exception.hpp>
#include <common_texture.hpp>
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
    };

    struct premade_texture_config_gl
    {
        texture_type_gl type;
        uint32_t texture;
        int32_t width, height;
    };

    class TextureGL : public CommonTextureGL
    {
        public:
            explicit TextureGL(texture_config_gl config);

            explicit TextureGL(premade_texture_config_gl config);

            ~TextureGL();

            [[nodiscard]] static ref_ptr<TextureGL> create(texture_config_gl config);

            [[nodiscard]] static ref_ptr<TextureGL> create(premade_texture_config_gl config);

            void bind() override;

            void bind_uniform(uint32_t program) const override;

            void unbind() override;

        private:
            int32_t binding;

            uint8_t* texture_buffer;

            texture_type_gl type;

            uint32_t texture;

            int32_t BPP; // bytes per pixel

            int32_t width, height;
    };
}