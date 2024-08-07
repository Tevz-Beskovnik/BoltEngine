#pragma once

#include <core.hpp>
#include <util.hpp>
#include <renderer_interface.hpp>
#include <shader_gl.hpp>
#include <texture_gl.hpp>
#include <vertex_gl.hpp>
#include <file_system.hpp>
#include <structs.hpp>

namespace bolt
{
    struct render_config_gl {
        std::vector<shader_config_gl> shader_config;
        std::vector<texture_config_gl> texture_config;
        ref_ptr<ModelInterface> model;
        uniform_bindings shader_bindings;
        uint32_t instances;
        uint32_t draw_type;
        uint32_t offset;
    };

    class RendererGL : public RenderInterface
    {
        public:
            explicit RendererGL(render_config_gl config);

            [[nodiscard]] static ref_ptr<RendererGL> create(render_config_gl config);

            bool set_instances(uint32_t instances);

            void set_viewport(vector_2 corner, vector_2 dimensions) override;

            void add_binding_func(uniform_bindings func) final;

            void add_texture(const std::string &path) override;

            void add_model(const ref_ptr<ModelInterface>& model) override;

            void render() const override;

        private:

            uint32_t draw_type;
            uint32_t offset;
            uint32_t instances;
            uniform_bindings binding_function;

            ref_ptr<ModelInterface> model;
            ref_ptr<ShaderGL> shader;
            std::vector<ref_ptr<TextureGL>> textures;
            ref_ptr<VertexGL> vertex;
    };
}