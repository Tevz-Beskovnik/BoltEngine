// TODO ADD HANDELING FOR VULKAN FRAMEWORK ASWELL

#include <object_creator.hpp>

namespace bolt
{
    void trash(uint32_t) { ; }

    render_framework ObjectCreator::framework = OPEN_GL;

    std::function<void(uint32_t)> ObjectCreator::binding_func = trash;

    uint16_t ObjectCreator::width = 0;
    uint16_t ObjectCreator::height = 0;

    void ObjectCreator::set_render_framework(bolt::render_framework new_framework)
    {
        framework = new_framework;
    }

    ObjectCreator::ObjectCreator()
    {
        ;
    }

    [[nodiscard]] ref_ptr<RenderInterface> ObjectCreator::lines(const std::vector<vector_3>& points, RGB color, const_str frag_shader, const_str vert_shader)
    {
        return RendererGL::create(render_config_gl{
            .shader_config = {
                    shader_config_gl{
                        .shader_location = frag_shader,
                        .type = GL_FRAGMENT_SHADER
                    },
                    shader_config_gl{
                        .shader_location = vert_shader,
                        .type = GL_VERTEX_SHADER
                    }
                },
            .texture_config = {},
            .model = Line::create(points, color),
            .shader_bindings = ObjectCreator::binding_func,
            .instances = 1,
            .draw_type = GL_LINES,
            .offset = 0
        });
    }

    void ObjectCreator::add_lines(const std::vector<vector_3>& points, RGB color, const ref_ptr<RenderInterface>& renderer)
    {
        renderer->add_model(Line::create(points, color));
    }

    [[nodiscard]] ref_ptr<RenderInterface> ObjectCreator::cube(vector_3 pos, vector_3 dims, const_str frag_shader, const_str vert_shader)
    {
        auto model = MeshBuilder::make_cube(dims);

        model->move_model(pos);

        return RendererGL::create(render_config_gl{
                .shader_config = {
                        shader_config_gl{
                                .shader_location = frag_shader,
                                .type = GL_FRAGMENT_SHADER
                        },
                        shader_config_gl{
                                .shader_location = vert_shader,
                                .type = GL_VERTEX_SHADER
                        }
                },
                .texture_config = {},
                .model = model,
                .shader_bindings = ObjectCreator::binding_func,
                .instances = 1,
                .draw_type = GL_TRIANGLES,
                .offset = 0
        });
    }

    void ObjectCreator::add_cube(vector_3 pos, vector_3 dims, const ref_ptr<RenderInterface>& renderer)
    {
        auto model = MeshBuilder::make_cube(dims);

        model->move_model(pos);

        renderer->add_model(model);
    }

    [[nodiscard]] ref_ptr<RenderInterface> ObjectCreator::quad(vector_3 pos, vector_2 dims, const_str frag_shader, const_str vert_shader)
    {
        return RendererGL::create(render_config_gl{
                .shader_config = {
                        shader_config_gl{
                                .shader_location = frag_shader,
                                .type = GL_FRAGMENT_SHADER
                        },
                        shader_config_gl{
                                .shader_location = vert_shader,
                                .type = GL_VERTEX_SHADER
                        }
                },
                .texture_config = {},
                .model = MeshBuilder::make_quad(pos, dims),
                .shader_bindings = ObjectCreator::binding_func,
                .instances = 1,
                .draw_type = GL_TRIANGLES,
                .offset = 0
        });
    }

    void ObjectCreator::add_quad(vector_3 pos, vector_2 dims, const ref_ptr<RenderInterface>& renderer)
    {
        renderer->add_model(MeshBuilder::make_quad(pos, dims));
    }

    [[nodiscard]] ref_ptr<RenderInterface> ObjectCreator::model_from_file(const_str model_file, const_str frag_shader, const_str vert_shader)
    {
        return RendererGL::create(render_config_gl{
                .shader_config = {
                        shader_config_gl{
                                .shader_location = frag_shader,
                                .type = GL_FRAGMENT_SHADER
                        },
                        shader_config_gl{
                                .shader_location = vert_shader,
                                .type = GL_VERTEX_SHADER
                        }
                },
                .texture_config = {},
                .model = MeshBuilder::read_model(model_file, OBJ), // TODO check for file extension to determin what file type to add
                .shader_bindings = ObjectCreator::binding_func,
                .instances = 1,
                .draw_type = GL_TRIANGLES,
                .offset = 0
        });
    }

    void ObjectCreator::add_model_from_file(const_str model, const ref_ptr<RenderInterface>& renderer)
    {
        renderer->add_model(MeshBuilder::read_model(model, OBJ));
    }

    [[nodiscard]] ref_ptr<RenderInterface> ObjectCreator::model(ref_ptr<ModelInterface> model, const_str frag_shader, const_str vert_shader)
    {
        return RendererGL::create(render_config_gl{
            .shader_config = {
                shader_config_gl{
                    .shader_location = frag_shader,
                    .type = GL_FRAGMENT_SHADER
                },
                shader_config_gl{
                    .shader_location = vert_shader,
                    .type = GL_VERTEX_SHADER
                }
            },
            .texture_config = {},
            .model = model,
            .shader_bindings = ObjectCreator::binding_func,
            .instances = 1,
            .draw_type = GL_TRIANGLES,
            .offset = 0
        });
    }

    void ObjectCreator::add_model(ref_ptr<ModelInterface> model, ref_ptr<RenderInterface> interface)
    {
        interface->add_model(model);
    }

    void ObjectCreator::set_uniform_binding_func(std::function<void(uint32_t)> binding_func)
    {
        ObjectCreator::binding_func = binding_func;
    }

    void ObjectCreator::set_window_dims(uint16_t width, uint16_t height)
    {
        ObjectCreator::width = width;
        ObjectCreator::height = height;
    }
}