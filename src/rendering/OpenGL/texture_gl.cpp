#include <texture_gl.hpp>

namespace bolt
{
    uint32_t TextureGL::activeTexture = GL_TEXTURE0;

    TextureGL::TextureGL(texture_config_gl config)
        :width(0), height(0), type(config.type), binding(0)
    {
        stbi_set_flip_vertically_on_load(true);
        texture_buffer = stbi_load(config.texture_location, &width, &height, &BPP, 0);

        BOLT_LOG_INFO("Reading texture file")

        glGenTextures(1, &texture);

        glBindTexture(config.type, texture);

        glTexParameteri(config.type, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(config.type, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(config.type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(config.type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if(texture_buffer)
        {
            BOLT_LOG_INFO("Binding texture buffer to active binding and generating mipmaps")

            std::filesystem::path tex_file = config.texture_location;
            if(tex_file.extension() == ".jpg")
                glTexImage2D(config.type, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
            else if(tex_file.extension() == ".png")
                glTexImage2D(config.type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_buffer);
            else
                throw TextureException("Unsuported file extension on texture");

            glGenerateMipmap(config.type);
        }
        else
        {
            throw TextureException("Failed to load image: " + std::string{config.texture_location});
        }

        BOLT_LOG_INFO("Freeing loaded image from stb")

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
            binding = (int32_t)activeTexture;

            glActiveTexture(activeTexture);
            glBindTexture(type, texture);

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

            glBindTexture(type, 0);
        }
    }
}