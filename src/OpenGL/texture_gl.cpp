#include <texture_gl.hpp>

namespace bolt
{
    uint32_t TextureGL::activeTexture = GL_TEXTURE0;

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