#include <animated_texture_gl.hpp>

namespace bolt
{
    AnimatedTextureGL::AnimatedTextureGL(animated_texture_config_gl config)
        :type(config.type), binding(0), animation(config.animation), previous_time(0), current_frame(0), prev_animation(
        nullptr), new_animation(false)
    {
        BOLT_LOG_INFO("Generating textures")

        frame_duration = config.animation->get_duration()/config.animation->get_frames()->size();

        textures = new uint32_t[animation->get_frames()->size()];
        glGenTextures(animation->get_frames()->size(), textures);

        BOLT_LOG_INFO("Setting up animated texture")

        for(uint16_t i = 0; i < animation->get_frames()->size(); i++)
        {
            setup_texture(textures[i], (*animation->get_frames())[i]);
        }

        BOLT_LOG_INFO("Setting up animated texture")
    }

    AnimatedTextureGL::~AnimatedTextureGL()
    {
        glDeleteTextures(animation->get_frames()->size(), textures);
        delete textures;
    }

    [[nodiscard]] ref_ptr<AnimatedTextureGL> AnimatedTextureGL::create(animated_texture_config_gl config)
    {
        return create_ref<AnimatedTextureGL>(config);
    }

    void AnimatedTextureGL::bind()
    {
        if (new_animation)
        {
            set_animation_internal();
            new_animation = false;
        }

        if (previous_time == 0)
        {
            previous_time = glfwGetTime();
            bind_current_frame();
        }
        else
        {
            double current_time = glfwGetTime();
            use_lock.lock();
            if(current_time-previous_time >= frame_duration)
            {
                previous_time = glfwGetTime();
                if(current_frame == animation->get_frames()->size()-1)
                    current_frame = 0;
                else
                    current_frame++;
            }
            use_lock.unlock();

            bind_current_frame();
        }
    }

    void AnimatedTextureGL::bind_uniform(uint32_t program) const
    {
        std::string uniform_name = "uTexture" + std::string(animation->get_name());
        BOLT_LOG_INFO("Binding on uniform location: ")
        BOLT_LOG_INFO(uniform_name)

        int32_t uTexture = glGetUniformLocation(program, uniform_name.c_str());

        glUniform1i(uTexture, binding-GL_TEXTURE0);
    }

    void AnimatedTextureGL::unbind()
    {
        if(CommonTextureGL::activeTexture > GL_TEXTURE0)
        {
            CommonTextureGL::activeTexture--;
        }

        glBindTexture(type, 0);
        BOLT_LOG_INFO("Unlocking for unbind")
    }

    void AnimatedTextureGL::setup_texture(uint32_t tex_id, uint8_t* tex_buffer)
    {
        BOLT_LOG_INFO("Binding tex")
        glBindTexture(type, tex_id);

        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if(tex_buffer)
        {
            BOLT_LOG_INFO("binding tex buffer to texture")
            if(animation->get_file_extension() == ".jpg")
                glTexImage2D(type, 0, GL_RGBA, animation->get_width(), animation->get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, tex_buffer);
            else if(animation->get_file_extension() == ".png")
                glTexImage2D(type, 0, GL_RGBA, animation->get_width(), animation->get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_buffer);
            else
                throw TextureException("Unsuported file extension on texture", animation->get_name());

            glGenerateMipmap(type);
        }
        else
            throw TextureException("Failed to load image: ", animation->get_name());

        BOLT_LOG_INFO("Finished setting up tex");
    }

    void AnimatedTextureGL::bind_current_frame()
    {
        if(CommonTextureGL::activeTexture < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
        {
            binding = (int32_t) CommonTextureGL::activeTexture;

            glActiveTexture(CommonTextureGL::activeTexture);
            glBindTexture(type, textures[current_frame]);

            CommonTextureGL::activeTexture++;
        }
    }

    // TODO: Mutexes needed in here shared memory between render and logic thread!
    void AnimatedTextureGL::set_animation(ref_ptr<bolt::Animation> new_animation)
    {
        use_lock.lock();
        BOLT_LOG_INFO("Locked texture")

        this->prev_animation = this->animation;
        this->animation = new_animation;
        this->new_animation = true;

        use_lock.unlock();
        BOLT_LOG_INFO("Finished animating texture")
    }

    void AnimatedTextureGL::set_animation_internal()
    {
        BOLT_LOG_INFO("Setting new animation")
        current_frame = 0;
        previous_time = 0.0f;

        BOLT_LOG_INFO("Cleaning textures")
        glDeleteTextures(prev_animation->get_frames()->size(), textures);
        delete textures;

        BOLT_LOG_INFO("Generating textures")

        frame_duration = animation->get_duration()/animation->get_frames()->size();

        textures = new uint32_t[animation->get_frames()->size()];
        glGenTextures(animation->get_frames()->size(), textures);

        BOLT_LOG_INFO("Setting up animated textures")

        for(uint16_t i = 0; i < animation->get_frames()->size(); i++)
        {
            BOLT_LOG_INFO("Setting up tex")
            setup_texture(textures[i], (*animation->get_frames())[i]);
        }
    }
}
