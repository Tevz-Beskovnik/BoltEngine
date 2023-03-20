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
    struct Layout
    {
        unsigned int& program;
        unsigned int& buffer;
        std::string nameOfAttribute;
        int size;
        unsigned int type;
        unsigned int normalise;
        int totalSizeInBytes;
        ptrdiff_t offset;
    };

    class RendererGL : public RenderInterface
    {
        public:
            RendererGL();

            void addVertexLayout(Layout vertex_layout);

            [[nodiscard]] void setMesh(const std::vector<polygon>& mesh) override;

            [[nodiscard]] void addShader(const std::string &path, shader_type type) override;

            [[nodiscard]] void addTexture(const std::string &path) override;

            void render() const override;
        private:
            void convertMeshToVertex();

            std::vector<Layout> vertexLayouts;
            std::vector<ref_ptr<ShaderGL>> shaders;
            std::vector<ref_ptr<TextureGL>> textures;
            single_ptr<VertexGL> vertex;

            std::vector<polygon> mesh;
    };
}