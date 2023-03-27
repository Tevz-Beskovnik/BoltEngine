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
            void setModel(ref_ptr<ModelInterface> model) override;

            void addShader(const std::string &path, shader_type type) override;

            void addTexture(const std::string &path) override;

            void render() const override;

        private:
            ref_ptr<ModelInterface> model;
            ref_ptr<ShaderGL> shader;
            std::vector<ref_ptr<TextureGL>> textures;
            single_ptr<VertexGL> vertex;
    };
}