#include "vertex_gl.hpp"

namespace bolt
{
    VertexGL::VertexGL(std::vector<float>& buffer)
        :buffer(0)
    {
        float* positionsPointer = buffer.data();

        glGenBuffers(1, &this->buffer);
        this->bind();
        glBufferData(GL_ARRAY_BUFFER, static_cast<long>(buffer.size()), positionsPointer, GL_STATIC_DRAW);
        unbind();
    }

    VertexGL::~VertexGL()
    {
        glDeleteBuffers(1, &buffer);
    }

    [[nodiscard]] single_ptr<VertexGL> VertexGL::create(std::vector<float>& buffer)
    {
        return create_single<VertexGL>(buffer);
    }

    [[nodiscard]] uint32_t VertexGL::get_buffer() const
    {
        return buffer;
    }

    void VertexGL::set_data(long offset, std::vector<float>& new_buffer) const
    {
        this->bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, static_cast<long>(buffer.size()), buffer.data());
        unbind();
    }

    void VertexGL::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }

    void VertexGL::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexGL::delete_buffer()
    {
        glDeleteBuffers(1, &buffer);
    }
}