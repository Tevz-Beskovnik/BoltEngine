#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    class BufferGL
    {
        public:
            explicit BufferGL(const std::vector<float>& buffer);

            static ref_ptr<BufferGL> create(const std::vector<float>& buffer);

            virtual ~BufferGL();

            void bind() const;

            static void unbind();

            inline void delete_buffer() const;

        private:
            uint32_t buffer;
    };
}
