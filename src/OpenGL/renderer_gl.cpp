#include <renderer_gl.hpp>

namespace bolt
{
    RendererGL::RendererGL()
    {

    }

    void RendererGL::addVertexLayout(Layout vertex_layout)
    {
        vertexLayouts.push_back(vertex_layout);
    }

    [[nodiscard]] void RendererGL::setMesh(const std::vector<polygon>& mesh)
    {
        ASSERT(!mesh.empty(), "Mesh cannot be an empty vector!");

        this->mesh = mesh;
    }

    [[nodiscard]] void RendererGL::addShader(const std::string &path, shader_type type)
    {
        ASSERT(!path.empty(), "Path cannot be a empty string");
        ASSERT_FILE_EXISTS(path.c_str());

        this->shaders.push_back(ShaderGL::create(path.c_str(), type));
    }

    [[nodiscard]] void RendererGL::addTexture(const std::string &path)
    {
        ASSERT(!path.empty(), "Path cannot be a empty string");
        ASSERT_FILE_EXISTS(path.c_str());

        this->textures.push_back(TextureGL::create()); // TODO: implement texture class
    }

    void RendererGL::render() const
    {

    }

    void RendererGL::convertMeshToVertex()
    {
        std::vector<float> attributes;

        for(const auto& polygon: mesh)
        {
            attributes.push_back(polygon.vert[0].x);
            attributes.push_back(polygon.vert[0].y);
            attributes.push_back(polygon.vert[0].z);

            attributes.push_back(polygon.vert[1].x);
            attributes.push_back(polygon.vert[1].y);
            attributes.push_back(polygon.vert[1].z);

            attributes.push_back(polygon.vert[2].x);
            attributes.push_back(polygon.vert[2].y);
            attributes.push_back(polygon.vert[2].z);

            
        }
    }
}