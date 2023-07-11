#pragma once

#include <util.hpp>
#include <model_interface.hpp>
#include <buffer_gl.hpp>
#include <index_buffer_gl.hpp>
#include <util.hpp>
#include <structs.hpp>

namespace bolt
{
    struct vertex_config
    {
        ref_ptr<IndexBufferGL> index_buffer;
        const std::vector<float>& verticies;
        const std::vector<attribute_layout>& layouts;
    };

    class VertexGL
    {
        public:
            explicit VertexGL(vertex_config config);

            ~VertexGL();

            [[nodiscard]] static ref_ptr<VertexGL> create(vertex_config config);

            [[nodiscard]] bool has_index() const;

            void bind() const;

            static void unbind();

            void delete_vertex_array() const;

        private:
            ref_ptr<IndexBufferGL> index_buffer;
            ref_ptr<BufferGL> buffer;
            uint32_t vertex_array_object;
            uint32_t vertex_buffer_index;
    };
}