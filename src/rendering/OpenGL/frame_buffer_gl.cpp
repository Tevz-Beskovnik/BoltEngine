#include <frame_buffer_gl.hpp>

namespace bolt
{
    FrameBufferGL::FrameBufferGL(frame_buffer_conf config)
        :viewport_width(config.width), viewport_height(config.height), new_viewport(false),
        viewport_x(0), viewport_y(0), texture_width(config.width), texture_height(config.height),
        background(config.background)
    {
        glGenFramebuffers(1, &FBO);

        bind();

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            BOLT_ERROR(RendererException("Failed to create framebuffer object"))

        // TODO replace this with the texture class
        glGenTextures(1, &fbo_texture);
        glBindTexture(GL_TEXTURE_2D, fbo_texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, config.width, config.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);

        // Set the list of draw buffers.
        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
        glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
    }

    FrameBufferGL::~FrameBufferGL()
    {
        delete_frame_buffer();
    }

    ref_ptr<FrameBufferGL> FrameBufferGL::create(frame_buffer_conf config)
    {
        return create_ref<FrameBufferGL>(config);
    }

    void FrameBufferGL::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        if (new_viewport)
        {
            glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
            new_viewport = false;
        }

        glClearColor(background.r_dec, background.g_dec, background.b_dec, background.a_dec);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void FrameBufferGL::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBufferGL::set_viewport(int32_t x, int32_t y, int32_t width, int32_t height)
    {
        viewport_x = x;
        viewport_y = y;
        viewport_width = width;
        viewport_height = height;
        new_viewport = true;
    }

    [[nodiscard]] ref_ptr<CommonTextureGL> FrameBufferGL::get_texture()
    {
        premade_texture_config_gl config {
            .type = TEXTURE_2D,
            .texture = fbo_texture,
            .width = texture_width,
            .height = texture_height
        };

        return TextureGL::create(config);
    }

    void FrameBufferGL::delete_frame_buffer() const
    {
        BOLT_LOG_INFO("Deleting frame buffer")
        glDeleteFramebuffers(1, &FBO);
    }
}