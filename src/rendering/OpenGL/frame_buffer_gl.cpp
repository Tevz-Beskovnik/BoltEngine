#include <frame_buffer_gl.hpp>

namespace bolt
{
    FrameBufferGL::FrameBufferGL(frame_buffer_conf config)
    {
        glGenFramebuffers(1, &FBO);

        bind();

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            BOLT_ERROR("Failed to create framebuffer object")

        // TODO replace this with the texture class
        glGenTextures(1, &fbo_texture);
        glBindTexture(GL_TEXTURE_2D, fbo_texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);

    }

    FrameBufferGL::~FrameBufferGL()
    {
        delete_frame_buffer();
    }

    ref_ptr<FrameBufferGL> FrameBufferGL::create(frame_buffer_conf config)
    {
        return create_ref<FrameBufferGL>(config);
    }

    void FrameBufferGL::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    }

    void FrameBufferGL::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBufferGL::delete_frame_buffer() const
    {
        BOLT_LOG_INFO("Deleting frame buffer")
        glDeleteFramebuffers(1, &FBO);
    }
}