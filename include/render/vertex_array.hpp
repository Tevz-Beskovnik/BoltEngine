#pragma once

#include <core.hpp>
#include <util.hpp>
#include <vertex_array_interface.hpp>

namespace bolt
{
    class VertexArray
    {
        public:
            [[nodiscard]] VertexArray();

            [[nodiscard]] static ref_ptr<VertexArray> create();

            void bind();

            void unbind();

        private:
            ref_ptr<VertexArrayInterface> vertex_array_interface;
    };
}