#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <util.hpp>

namespace bolt
{
    class VertexGL
    {
        public:
            explicit VertexGL(const std::vector<float>& buffer);

            ~VertexGL();

            [[nodiscard]] static single_ptr<VertexGL> create(const std::vector<float>& buffer);

            [[nodiscard]] uint32_t get_buffer() const;

            void set_data(long offset, std::vector<float>& new_buffer) const;

            void bind() const;

            static void unbind();

            void delete_buffer();

        private:
            uint32_t buffer;
    };
}