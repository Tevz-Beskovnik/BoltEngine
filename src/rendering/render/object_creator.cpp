// TODO ADD HANDELING FOR VULKAN FRAMEWORK ASWELL

#include <object_creator.hpp>

namespace bolt
{
    render_framework ObjectCreator::framework = OPEN_GL;

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
            .shader_bindings = uniform_binding_func,
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
                .shader_bindings = uniform_binding_func,
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
                .shader_bindings = uniform_binding_func,
                .instances = 1,
                .draw_type = GL_TRIANGLES,
                .offset = 0
        });
    }

    void ObjectCreator::add_quad(vector_3 pos, vector_2 dims, const ref_ptr<RenderInterface>& renderer)
    {
        renderer->add_model(MeshBuilder::make_quad(pos, dims));
    }

    [[nodiscard]] ref_ptr<RenderInterface> ObjectCreator::model(const_str model_file, const_str frag_shader, const_str vert_shader)
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
                .shader_bindings = uniform_binding_func,
                .instances = 1,
                .draw_type = GL_TRIANGLES,
                .offset = 0
        });
    }

    void ObjectCreator::add_model(const_str model, const ref_ptr<RenderInterface>& renderer)
    {
        renderer->add_model(MeshBuilder::read_model(model, OBJ));
    }

    void ObjectCreator::set_uniform_binding_func(void (*uniform_binding_func)(uint32_t program))
    {
        ObjectCreator::uniform_binding_func = uniform_binding_func;
    }
}