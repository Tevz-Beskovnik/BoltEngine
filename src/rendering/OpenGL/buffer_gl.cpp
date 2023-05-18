#include <buffer_gl.hpp>

namespace bolt
{
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
        BOLT_LOG_INFO("Deleting VBO")
        glDeleteBuffers(1, &buffer);
    }
}