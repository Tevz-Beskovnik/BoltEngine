#include "mesh_builder.hpp"
#include "predef_shader_gl.hpp"
#include "renderer_gl.hpp"
#include "texture_gl.hpp"
#include "util.hpp"
#include <texture.hpp>


namespace bolt
{
    Texture::Texture(const_str name, const_str path, vector_2 pos, vector_2 dimensions)
        :texture({texture_type_gl::TEXTURE_2D, path, name}), position(pos), dimensions(dimensions)
    {
        renderer = RendererGL::create(render_config_gl{
        .shader = Shaders::get_texture_shaders(),
            .texture_config = {},
            .model = MeshBuilder::make_quad(pos, dimensions),
            .shader_bindings = ,
            .instances = 1,
            .draw_type = GL_TRIANGLES,
            .offset = 0
        });
    }

    ref_ptr<Texture> Texture::create(const_str name, const_str path, vector_2 pos, vector_2 dimensions)
    {
        return create_ref<Texture>(name, path, pos, dimensions);
    }

    ref_ptr<RenderInterface> Texture::get_renderer() const
    {
    }

    void Texture::binding_func(uint32_t program)
    {
        auto uTranslation = glGetUniformLocation(program, "uTranslation");
        
        glUniform2f(uTranslation, position.x, position.y);
    }
}

