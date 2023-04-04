#include <shader_gl.hpp>

namespace bolt
{
    [[nodiscard]] ShaderGL::ShaderGL()
        :shader(0)
    {
        program = glCreateProgram();

        glUseProgram(0);
    }

    ShaderGL::~ShaderGL()
    {
        if(glIsProgram(program) == GL_TRUE)
            glDeleteProgram(program);
    }

    [[nodiscard]] ref_ptr<ShaderGL> ShaderGL::create()
    {
        return create_ref<ShaderGL>();
    }

    void ShaderGL::add_shader(shader_config_gl config)
    {
        std::string error = "File: " + std::string(config.shader_location) + " does not exist.";
        ASSERT_FILE_EXISTS(config.shader_location, error);

        read_shader(config.shader_location);

        compile_shader(config.type);

        link_shader();
    }

    [[nodiscard]] uint32_t ShaderGL::get_program() const {
        return program;
    }

    void ShaderGL::bind() const
    {
        glUseProgram(program);
    }

    void ShaderGL::unbind()
    {
        glUseProgram(0);
    }

    void ShaderGL::destroy() const
    {
        glDeleteProgram(program);
    }

    void ShaderGL::read_shader(const_str shader_location)
    {
        shader_string = "";

        std::string line;
        std::ifstream file(shader_location);

        while(std::getline(file, line))
        {
            shader_string += line;
        }
    }

    void ShaderGL::compile_shader(shader_type type)
    {
        const_str c_str_shader = shader_string.c_str();

        switch(type)
        {
            case shader_type::VERTEX_SHADER:
                shader = glCreateShader(GL_VERTEX_SHADER);
                break;
            case shader_type::FRAGMENT_SHADER:
                shader = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            default:
                BOLT_ERROR("Unsupported shader type");
        }

        glShaderSource(shader, 1, &c_str_shader, nullptr);
        glCompileShader(shader);

        int32_t status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if(status == GL_FALSE)
        {
            int32_t length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            auto message = new char[length];
            glGetShaderInfoLog(shader, length, &length, message);

            glDeleteShader(shader);

            BOLT_ERROR(message)
        }
    }

    void ShaderGL::link_shader() const
    {
        glAttachShader(program, shader);

        glLinkProgram(program);

        int32_t status;
        glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

        if(status == GL_FALSE)
        {
            int32_t length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            auto message = new char[length];
            glGetProgramInfoLog(program, length, &length, message);

            glDeleteProgram(program);

            BOLT_ERROR(message)
        }

        glDeleteShader(shader);
    }
}