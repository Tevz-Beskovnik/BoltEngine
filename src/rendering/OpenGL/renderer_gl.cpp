#include <renderer_gl.hpp>

namespace bolt {
    RendererGL::RendererGL(render_config_gl config)
        :instances(config.instances == 0 ? 1 : config.instances), offset(config.offset), draw_type(config.draw_type), binding_function(config.shader_bindings), model(config.model)
    {
        this->vertex = VertexGL::create({
            .index_buffer = model->get_index_buffer().size() != 0
                ? IndexBufferGL::create(model->get_index_buffer())
                : nullptr,
            .verticies = model->get_drawable_vector(),
            .layouts = config.model->get_attribute_layout()
        });

        this->vertex->bind();

        this->shader = ShaderGL::create(config.shader_config);

        for(const auto& texture : config.texture_config)
            this->textures.push_back(TextureGL::create(texture));
    }

    ref_ptr<RendererGL> RendererGL::create(render_config_gl config)
    {
        return create_ref<RendererGL>(config);
    }

    bool RendererGL::set_instances(uint32_t instances)
    {
        if(instances == 0) return false;

        this->instances = instances;

        return true;
    }

    void RendererGL::set_viewport(vector_2 corner, vector_2 dimensions)
    {
        glViewport(corner.x, corner.y, dimensions.x, dimensions.y);
    }

    void RendererGL::add_texture(const std::string &path) {
        ASSERT(!path.empty(), "Path cannot be a empty string");
        ASSERT_FILE_EXISTS(path.c_str(), "Bad texture file");
        ASSERT((textures.size() < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS), "Max number of textures binded to renderer");
        // todo: slice string and determin file extension
        this->textures.push_back(TextureGL::create({TEXTURE_2D, path.c_str()})); // TODO: implement texture class
    }

    void RendererGL::render() const {
        shader->bind();

        vertex->bind();

        for(const auto& texture : textures)
        {
            texture->bind();

            texture->bind_uniform(shader->get_program());
        }

        if(binding_function != nullptr)
            binding_function(shader->get_program());

        if(!vertex->has_index())
            if(instances == 1)
                glDrawArrays(draw_type, offset, static_cast<int>(3*model->polygon_count()));
            else
                glDrawArraysInstanced(draw_type, offset, static_cast<int>(3*model->polygon_count()), static_cast<int>(instances));
        else
            if(instances == 1)
                glDrawElements(draw_type, static_cast<int>(3*model->polygon_count()), GL_UNSIGNED_INT, 0);
            else
                glDrawElementsInstanced(draw_type, static_cast<int>(3*model->polygon_count()), GL_UNSIGNED_INT, 0, static_cast<int>(instances));

        for(const auto& texture : textures)
            texture->unbind();
    }
}