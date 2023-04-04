#include <texture_gl.hpp>

namespace bolt
{
    uint32_t TextureGL::activeTexture = GL_TEXTURE0;

    TextureGL::TextureGL(texture_config_gl config)
        :width(config.width), height(config.height), type(config.type)
    {
        ;
    }

    [[nodiscard]] ref_ptr<TextureGL> TextureGL::create(texture_config_gl config)
    {
        return create_ref<TextureGL>(config);
    }

    void TextureGL::bind() const
    {
        if(activeTexture < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
        {
            glActiveTexture(activeTexture);
            glBindTexture(type, texture);

            activeTexture++;
        }
    }

    void TextureGL::unbind()
    {
        if(activeTexture > GL_TEXTURE0)
        {
            activeTexture--;

            glActiveTexture(activeTexture);
            glBindTexture(type, texture);
        }
    }
}