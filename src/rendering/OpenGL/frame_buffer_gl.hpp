#pragma once

#include <core.hpp>
#include <util.hpp>
#include <renderer_exception.hpp>

namespace bolt
{
    struct frame_buffer_conf
    {
        uint32_t width;
        uint32_t height;
    };

    class FrameBufferGL
    {
        public:
            FrameBufferGL(frame_buffer_conf config);

            virtual ~FrameBufferGL();

            static ref_ptr<FrameBufferGL> create(frame_buffer_conf config);

            void bind() const;

            static void unbind();

            void delete_frame_buffer() const;
        private:
            uint32_t FBO;
            uint32_t fbo_texture;
    };
}