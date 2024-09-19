#include <renderer_gl.hpp>

namespace bolt {
    RendererGL::RendererGL(render_config_gl config)
        :instances(config.instances == 0 ? 1 : config.instances), offset(config.offset), draw_type(config.draw_type),
        binding_function(config.shader_bindings), model(config.model), textures(std::move(config.texture_config)),
        framebuffer(nullptr)
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

        this->vertex->unbind();
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

    void RendererGL::set_draw_type(uint32_t draw_type)
    {
        this->draw_type = draw_type;
    }

    void RendererGL::set_viewport(vector_2 corner, vector_2 dimensions)
    {
        glViewport(corner.x, corner.y, dimensions.x, dimensions.y);
    }

    void RendererGL::add_texture(const ref_ptr<CommonTextureGL> texture) {
        ASSERT((textures.size() < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS), "Max number of textures binded to renderer");
        // todo: slice string and determin file extension
        this->textures.push_back(texture); // TODO: implement texture class
    }

    void RendererGL::add_model(const ref_ptr<ModelInterface>& model)
    {
        this->model->add_model(model);

        this->vertex = VertexGL::create({
            .index_buffer = this->model->get_index_buffer().size() != 0
                ? IndexBufferGL::create(this->model->get_index_buffer())
                : nullptr,
            .verticies = this->model->get_drawable_vector(),
            .layouts = this->model->get_attribute_layout()
        });
    }

    void RendererGL::add_framebuffer(const ref_ptr<FrameBufferGL> framebuffer)
    {
        this->framebuffer = framebuffer;
    }

    void RendererGL::add_binding_func(std::function<void(uint32_t)> func)
    {
        this->binding_function = func;
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
                glDrawArrays(draw_type, offset, static_cast<int>(model->vertices_count()));
            else
                glDrawArraysInstanced(draw_type, offset, static_cast<int>(model->vertices_count()), static_cast<int>(instances));
        else
            if(instances == 1)
                glDrawElements(draw_type, static_cast<int>(model->vertices_count()), GL_UNSIGNED_INT, 0);
            else
                glDrawElementsInstanced(draw_type, static_cast<int>(model->vertices_count()), GL_UNSIGNED_INT, 0, static_cast<int>(instances));

        for(const auto& texture : textures)
            texture->unbind();
    }
}