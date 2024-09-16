#pragma once

#include <core.hpp>
#include <util.hpp>
#include <renderer_interface.hpp>
#include <frame_buffer_gl.hpp>
#include <common_texture.hpp>
#include <shader_gl.hpp>
#include <texture_gl.hpp>
#include <vertex_gl.hpp>
#include <file_system.hpp>
#include <structs.hpp>

// TODO: Remove framebuffer references from here framebuffer now resides in scenes

namespace bolt
{
    struct render_config_gl {
        std::vector<shader_config_gl> shader_config;
        std::vector<ref_ptr<CommonTextureGL>> texture_config;
        ref_ptr<ModelInterface> model;
        std::function<void(int32_t)> shader_bindings;
        uint32_t instances;
        uint32_t draw_type;
        uint32_t offset;
    };

    class RendererGL : public RenderInterface
    {
        public:
            explicit RendererGL(render_config_gl config);

            [[nodiscard]] static ref_ptr<RendererGL> create(render_config_gl config);

            bool set_instances(uint32_t instances) override;

            void set_draw_type(uint32_t draw_type) override;

            void set_viewport(vector_2 corner, vector_2 dimensions) override;

            void add_framebuffer(const ref_ptr<FrameBufferGL> framebuffer) final;

            void add_binding_func(std::function<void(uint32_t)> func) final;

            void add_texture(const ref_ptr<CommonTextureGL>) override;

            void add_model(const ref_ptr<ModelInterface>& model) override;

            void render() const override;

        private:

            uint32_t draw_type;
            uint32_t offset;
            uint32_t instances;
            std::function<void(uint32_t)> binding_function;

            ref_ptr<FrameBufferGL> framebuffer;
            ref_ptr<ModelInterface> model;
            ref_ptr<ShaderGL> shader;
            std::vector<ref_ptr<CommonTextureGL>> textures;
            ref_ptr<VertexGL> vertex;
    };
}