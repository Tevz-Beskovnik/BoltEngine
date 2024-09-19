#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <model_interface.hpp>
#include <common_texture.hpp>
#include <frame_buffer_gl.hpp>

namespace bolt
{
    class RenderInterface
    {
        public:
            virtual ~RenderInterface() { ; };

            virtual bool set_instances(uint32_t instances) = 0;

            virtual void set_draw_type(uint32_t draw_type) = 0;

            virtual void add_texture(const ref_ptr<CommonTextureGL>) = 0;

            virtual void add_framebuffer(const ref_ptr<FrameBufferGL>) = 0;

            virtual void add_model(const ref_ptr<ModelInterface>& model) = 0;

            virtual void add_binding_func(std::function<void(uint32_t)> func) = 0;

            virtual void set_viewport(vector_2 corner, vector_2 dimensions) = 0;

            virtual void render() const = 0;
    };
}