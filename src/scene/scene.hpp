#pragma once

#include <core.hpp>
#include <renderer_interface.hpp>
#include <frame_buffer_gl.hpp>

namespace bolt
{
    typedef std::vector<ref_ptr<RenderInterface>>::iterator SceneIterator;

    class Scene
    {
        public:
            Scene();

            [[nodiscard]] const ref_ptr<RenderInterface>& get_object(uint32_t id);

            [[nodiscard]] uint32_t add_object(ref_ptr<RenderInterface> object);

            void set_framebuffer(ref_ptr<FrameBufferGL> framebuffer);

            void remove(uint32_t id);

            void draw();

            uint16_t get_id();

        private:
            ref_ptr<FrameBufferGL> framebuffer;
            std::vector<ref_ptr<RenderInterface>> objects;
            uint16_t id;

            static uint16_t id_count;
    };
}