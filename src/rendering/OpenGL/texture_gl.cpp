#include <texture_gl.hpp>

namespace bolt
{
    uint32_t TextureGL::activeTexture = GL_TEXTURE0;

    TextureGL::TextureGL(texture_config_gl config)
        :width(0), height(0), type(config.type), binding(0)
    {
        stbi_set_flip_vertically_on_load(true);
        texture_buffer = stbi_load(config.texture_location, &width, &height, &BPP, 0);

        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        if(texture_buffer)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            throw TextureException("Failed to load image: " + std::string{config.texture_location});
        }

        stbi_image_free(texture_buffer);
    }

    TextureGL::~TextureGL()
    {
        glDeleteTextures(1, &texture);
    }

    [[nodiscard]] ref_ptr<TextureGL> TextureGL::create(texture_config_gl config)
    {
        return create_ref<TextureGL>(config);
    }

    void TextureGL::bind()
    {
        if(activeTexture < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
        {
            BOLT_LOG_INFO("Bound texture: ")
            BOLT_LOG_INFO(std::to_string(activeTexture).c_str())

            binding = (int32_t)activeTexture;

            glActiveTexture(activeTexture);
            glBindTexture(GL_TEXTURE_2D, texture);

            activeTexture++;
        }
    }

    void TextureGL::bind_uniform(uint32_t program) const
    {
        int32_t uTexture = glGetUniformLocation(program, "uTexture");

        glUniform1i(uTexture, binding-GL_TEXTURE0);
    }

    void TextureGL::unbind()
    {
        if(activeTexture > GL_TEXTURE0)
        {
            activeTexture--;

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}