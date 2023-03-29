#pragma once

#include <core.hpp>
#include <util.hpp>
#include <renderer_interface.hpp>
#include <shader_gl.hpp>
#include <texture_gl.hpp>
#include <vertex_gl.hpp>
#include <file_system.hpp>

namespace bolt
{
    class RendererGL : public RenderInterface
    {
        public:
            bool set_instances(uint32_t instances);

            void set_draw_type(uint32_t draw_type);

            void set_offset(uint32_t offset);

            void set_model(ref_ptr<ModelInterface> model) override;

            void add_shader(const std::string &path, shader_type type) override;

            void add_texture(const std::string &path) override;

            void render() const override;

        private:
            uint32_t draw_type;
            uint32_t offset;
            uint32_t instances;

            ref_ptr<ModelInterface> model;
            ref_ptr<ShaderGL> shader;
            std::vector<ref_ptr<TextureGL>> textures;
            single_ptr<VertexGL> vertex;
    };
}