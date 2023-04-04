#include <renderer_gl.hpp>

namespace bolt {
    RendererGL::RendererGL(render_config_gl config)
        :instances(config.instances == 0 ? 1 : config.instances), offset(config.offset), draw_type(config.draw_type), binding_function(config.shader_bindings), model(config.model)
    {
        this->shader = ShaderGL::create();

        for(const auto& shader : config.shader_config)
            this->shader->add_shader(shader);

        for(const auto& texture : config.texture_config)
            this->textures.push_back(TextureGL::create(texture));
    }

    ref_ptr<RendererGL> RendererGL::create(render_config_gl config)
    {
        return create_ref<RendererGL>();
    }

    bool RendererGL::set_instances(uint32_t instances)
    {
        if(instances == 0) return false;

        this->instances = instances;

        return true;
    }

    void RendererGL::set_model(ref_ptr<ModelInterface> model)
    {
        ASSERT(!model, "Model cannot be a null pointer");

        this->model = model;
    };

    void RendererGL::add_shader(const std::string &path, shader_type type) {
        ASSERT(!path.empty(), "Path cannot be a empty string");

        this->shader->add_shader({path.c_str(), type});
    }

    void RendererGL::add_texture(const std::string &path) {
        ASSERT(!path.empty(), "Path cannot be a empty string");
        ASSERT_FILE_EXISTS(path.c_str(), "Bad texture file");
        ASSERT((textures.size() < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS), "Max number of textures binded to renderer");

        this->textures.push_back(TextureGL::create({TEXTURE_2D, "neke", 0, 0})); // TODO: implement texture class
    }

    void RendererGL::render() const {
        vertex->bind();

        for(const auto& layout : model->get_attribute_layout()) {
            uint32_t attribIndex = glGetAttribLocation(shader->get_program(), layout.nameOfAttribute);

            glEnableVertexAttribArray(attribIndex);

            glVertexAttribPointer(
                attribIndex,
                layout.size,
                layout.type,
                layout.normalise,
                layout.totalSizeInBytes,
                (void *) layout.offset
            );
        }

        shader->bind();

        for(const auto& texture : textures) texture->bind();

        binding_function(shader->get_program());

        if(instances > 1)
            glDrawArrays(draw_type, static_cast<int>(offset), static_cast<int>(model->polygon_count()));
        else
            glDrawArraysInstanced(draw_type, static_cast<int>(offset), static_cast<int>(model->polygon_count()), static_cast<int>(instances));

        VertexGL::unbind();

        ShaderGL::unbind();

        for(const auto& texture : textures) texture->unbind();
    }
}