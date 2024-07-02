#include <vertex_gl.hpp>

namespace bolt {
    VertexGL::VertexGL(vertex_config config)
        :vertex_buffer_index(0), index_buffer(config.index_buffer)
    {
        BOLT_LOG_INFO("Creating VAO")

        glGenVertexArrays(1, &vertex_array_object);

        glBindVertexArray(vertex_array_object);

        if(index_buffer != nullptr)
            index_buffer->bind();

        buffer = BufferGL::create(config.verticies);

        buffer->bind();

        BOLT_LOG_INFO("Bound VAO and buffer")

        for(const auto& layout : config.layouts)
        {
            glVertexAttribPointer(
                vertex_buffer_index,
                layout.size,
                layout.type,
                layout.normalise,
                layout.total_size_in_bytes,
                (void *) layout.offset
            );

            glEnableVertexAttribArray(vertex_buffer_index);

            BOLT_LOG_INFO("Binding index: " + std::to_string(vertex_buffer_index))

            vertex_buffer_index++;
        }

        BufferGL::unbind();

        glBindVertexArray(0);

        BOLT_LOG_INFO("Created VAO")
    }

    VertexGL::~VertexGL()
    {
        delete_vertex_array();
    }

    [[nodiscard]] ref_ptr<VertexGL> VertexGL::create(vertex_config config)
    {
        return create_ref<VertexGL>(config);
    }

    [[nodiscard]] bool VertexGL::has_index() const
    {
        return index_buffer != nullptr;
    }

    void VertexGL::bind() const
    {
        glBindVertexArray(vertex_array_object);
    }

    void VertexGL::unbind()
    {
        glBindVertexArray(0);
    }

    void VertexGL::delete_vertex_array() const
    {
        BOLT_LOG_INFO("Deleting VAO")
        glDeleteVertexArrays(1, &vertex_array_object);
    }
};