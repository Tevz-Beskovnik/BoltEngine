#include "renderer_gl.hpp"

namespace bolt {
    void RendererGL::setModel(ref_ptr<ModelInterface> model)
    {
        ASSERT(!model, "Model cannot be a null pointer");

        this->model = model;
    };

    void RendererGL::addShader(const std::string &path, shader_type type) {
        ASSERT(!path.empty(), "Path cannot be a empty string");

        this->shader->add_shader(path.c_str(), type);
    }

    void RendererGL::addTexture(const std::string &path) {
        ASSERT(!path.empty(), "Path cannot be a empty string");
        ASSERT_FILE_EXISTS(path.c_str(), "Bad texture file");

        this->textures.push_back(TextureGL::create()); // TODO: implement texture class
    }

    void RendererGL::render() const {
        vertex->bind();

        for(const auto& layout : model->get_attribute_layout())
        {
            uint32_t attribIndex = glGetAttribLocation(shader->get_program(), layout.nameOfAttribute);

            glEnableVertexAttribArray(attribIndex);

            glVertexAttribPointer(
                attribIndex,
                layout.size,
                layout.type,
                layout.normalise,
                layout.totalSizeInBytes,
                (void*)layout.offset
            );
        }
    }
}