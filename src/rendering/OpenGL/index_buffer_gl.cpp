#include <index_buffer_gl.hpp>

namespace bolt
{
    IndexBufferGL::IndexBufferGL(const std::vector<uint32_t>& indices)
    {
        BOLT_LOG_INFO("Generating index buffer")

        glGenBuffers(1, &buffer);
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
        unbind();

        BOLT_LOG_INFO("Generated index buffer")
    }

    ref_ptr<IndexBufferGL> IndexBufferGL::create(const std::vector<uint32_t>& indices)
    {
        return create_ref<IndexBufferGL>(indices);
    }

    IndexBufferGL::~IndexBufferGL()
    {
        delete_buffer();
    }

    void IndexBufferGL::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    }

    void IndexBufferGL::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBufferGL::delete_buffer() const
    {
        BOLT_LOG_INFO("Deleting Index buffer")
        glDeleteBuffers(1, &buffer);
    }
}