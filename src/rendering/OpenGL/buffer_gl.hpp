#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    class BufferGL
    {
        public:
            template<typename T> /// IF YOU USE TEMPLATES IN CLASSES AND HEADER FILES DEFINITION MUST ALSO BE WRITTEN HERE
            explicit BufferGL(const std::vector<T>& buffer)
                : buffer(0)
            {
                BOLT_LOG_INFO("creating VBO")

                glGenBuffers(1, &this->buffer);
                bind();
                glBufferData(GL_ARRAY_BUFFER, buffer.size()*sizeof(T), buffer.data(), GL_DYNAMIC_DRAW);
                unbind();
                BOLT_LOG_INFO("created VBO")
            }

            template<typename T>
            static ref_ptr<BufferGL> create(const std::vector<T>& buffer)
            {
                return create_ref<BufferGL>(buffer);
            }

            virtual ~BufferGL();

            void bind() const;

            static void unbind();

            inline void delete_buffer() const;

        private:
            uint32_t buffer;
    };
}
