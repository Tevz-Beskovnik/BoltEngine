#include <buffer_gl.hpp>

namespace bolt
{
    BufferGL::BufferGL(const std::vector<float>& buffer)
    {
        BOLT_MSG_DEBUG("creating VBO")

        glGenBuffers(1, &this->buffer);
        bind();
        glBufferData(GL_ARRAY_BUFFER, buffer.size()*sizeof(float), buffer.data(), GL_STATIC_DRAW);
        unbind();
        BOLT_MSG_DEBUG("created VBO")
    }

    ref_ptr<BufferGL> BufferGL::create(const std::vector<float>& buffer)
    {
        return create_ref<BufferGL>(buffer);
    }

    BufferGL::~BufferGL()
    {
        delete_buffer();
    }

    void BufferGL::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }

    void BufferGL::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    inline void BufferGL::delete_buffer() const
    {
        BOLT_MSG_DEBUG("Deleting VBO")
        glDeleteBuffers(1, &buffer);
    }
}