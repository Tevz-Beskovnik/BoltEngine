#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <texture_gl.hpp>
#include <renderer_exception.hpp>

// TODO: add ability to instanciate this with depth or create update buffer with depth attachment

namespace bolt
{
    struct frame_buffer_conf
    {
        int32_t width;
        int32_t height;
        RGB background;
    };

    class FrameBufferGL
    {
        public:
            explicit FrameBufferGL(frame_buffer_conf config);

            virtual ~FrameBufferGL();

            static ref_ptr<FrameBufferGL> create(frame_buffer_conf config);

            void bind();

            static void unbind();

            [[nodiscard]] ref_ptr<CommonTextureGL> get_texture();

            void set_viewport(int32_t x, int32_t y, int32_t width, int32_t height);

            void delete_frame_buffer() const;
        private:
            uint32_t FBO;
            RGB background;
            uint32_t fbo_texture;
            int32_t texture_width, texture_height;
            int32_t viewport_width, viewport_height;
            int32_t viewport_x, viewport_y;
            bool new_viewport;
    };
}