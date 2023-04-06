#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    class IndexBufferGL
    {
        public:
            explicit IndexBufferGL(const std::vector<uint32_t>& indices);

            static ref_ptr<IndexBufferGL> create(const std::vector<uint32_t>& indices);

            virtual ~IndexBufferGL();

            void bind() const;

            static void unbind();

            void delete_buffer() const;

        private:
            uint32_t buffer;
    };
}