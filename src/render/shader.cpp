#include <shader.hpp>

namespace bolt
{
    [[nodiscard]] Shader::Shader(const_str shader_location, shader_type type, render_framework framework_type)
    {

    }

    [[nodiscard]] ref_ptr<Shader> Shader::create(const_str shader_location, shader_type type, render_framework framework_type)
    {
        if(does_file_exist(shader_location))
            BOLT_ERROR("File does not work")

        return create_ref<Shader>(shader_location, type, framework_type);
    }

    void Shader::bind()
    {

    }

    void Shader::unbind()
    {

    }

    void Shader::destroy()
    {

    }
}