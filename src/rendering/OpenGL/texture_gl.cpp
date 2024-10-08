#include <texture_gl.hpp>

namespace bolt
{
    TextureGL::TextureGL(texture_config_gl config)
        :width(0), height(0), type(config.type), binding(0), name(std::move(config.name))
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

        if(texture_buffer)
        {
            BOLT_LOG_INFO("Binding texture buffer to active binding and generating mipmaps")

            std::filesystem::path tex_file = config.texture_location;
            if(tex_file.extension() == ".jpg")
                glTexImage2D(config.type, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
            else if(tex_file.extension() == ".png")
                glTexImage2D(config.type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_buffer);
            else
                throw TextureException("Unsuported file extension on texture", config.texture_location);

            glGenerateMipmap(config.type);
        }
        else
            throw TextureException("Failed to load image: ", config.texture_location);

        BOLT_LOG_INFO("Freeing loaded image from stb")

        stbi_image_free(texture_buffer);
    }

    TextureGL::TextureGL(premade_texture_config_gl config)
        :texture(config.texture), type(config.type), width(config.width), height(config.height), name(std::move(config.name))
    {
        ;
    }

    TextureGL::~TextureGL()
    {
        glDeleteTextures(1, &texture);
    }

    [[nodiscard]] ref_ptr<TextureGL> TextureGL::create(texture_config_gl config)
    {
        return create_ref<TextureGL>(config);
    }

    [[nodiscard]] ref_ptr<TextureGL> TextureGL::create(premade_texture_config_gl config)
    {
        return create_ref<TextureGL>(config);
    }

    void TextureGL::bind()
    {
        if(CommonTextureGL::activeTexture < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
        {
            binding = (int32_t)CommonTextureGL::activeTexture;

            glActiveTexture(CommonTextureGL::activeTexture);
            glBindTexture(type, texture);

            CommonTextureGL::activeTexture++;
        }
    }

    void TextureGL::bind_uniform(uint32_t program) const
    {
        std::string uniform_name = "uTexture" + std::string(name);
        BOLT_LOG_INFO("Binding on uniform location: ")
        BOLT_LOG_INFO(uniform_name)

        int32_t uTexture = glGetUniformLocation(program, uniform_name.c_str());

        glUniform1i(uTexture, binding-GL_TEXTURE0);
    }

    void TextureGL::unbind()
    {
        if(CommonTextureGL::activeTexture > GL_TEXTURE0)
        {
            CommonTextureGL::activeTexture--;
        }

        glBindTexture(type, 0);
    }
}