#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <util.hpp>

namespace bolt
{
    class VertexGL
    {
        public:
            VertexGL();

            ~VertexGL();

            [[nodiscard]] static single_ptr<VertexGL> create();

            [[nodiscard]] uint32_t get_buffer() const;

            void bind() const;

            static void unbind() const;

        private:
    };
}