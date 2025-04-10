#include "util.hpp"
#include <shader_gl.hpp>

namespace bolt
{
    ShaderGL::ShaderGL(shader_config_gl config)
    {
        std::string error = "File: " + std::string(config.shader_location) + " does not exist.";
        ASSERT_FILE_EXISTS(config.shader_location, error);

        std::string shader_string =  "";
        std::string line;
        std::ifstream file(config.shader_location);

        while(std::getline(file, line))
        {
            shader_string += line + '\n';
        }
        shader_string += '\0';

        const_str shader_str = shader_string.c_str();
        shader = glCreateShader(config.type);

        BOLT_LOG_INFO("Compiling shader:")
        BOLT_LOG_INFO(shader_str)

        glShaderSource(shader, 1, &shader_str, NULL);
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

            BOLT_LOG_INFO("Failed to compile shader")
            BOLT_LOG_ERROR(message)
            BOLT_ERROR(std::runtime_error("Shared failed to compiler"))
        }

        BOLT_LOG_INFO("Shader compiled")
    }

    ShaderGL::~ShaderGL()
    {
        glDeleteShader(shader);
    }

    ref_ptr<ShaderGL> ShaderGL::create(shader_config_gl config)
    {
        return create_ref<ShaderGL>(config);
    }

    uint32_t ShaderGL::get_shader() const
    {
        return shader;
    }

    [[nodiscard]] ProgramGL::ProgramGL(std::vector<ref_ptr<ShaderGL>> config)
    {
        BOLT_LOG_INFO("Creating shader program")

        BOLT_LOG_INFO("Linking shader")

        program = glCreateProgram();
        for(auto& shader : config)
            glAttachShader(program, shader->get_shader());
        glLinkProgram(program);
        glValidateProgram(program);

        int32_t status;
        glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

        if(status == GL_FALSE)
        {
            int32_t length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            auto message = new char[length];
            glGetProgramInfoLog(program, length, &length, message);

            glDeleteProgram(program);

            BOLT_LOG_ERROR(message)
            BOLT_ERROR(RendererException("Program failed to validate"))
        }

        BOLT_LOG_INFO("Linking finished");
    }

    ProgramGL::~ProgramGL()
    {
        BOLT_LOG_INFO("Deleting shader program")
        glDeleteProgram(program);
    }

    [[nodiscard]] ref_ptr<ProgramGL> ProgramGL::create(std::vector<ref_ptr<ShaderGL>> config)
    {
        return create_ref<ProgramGL>(config);
    }


    [[nodiscard]] uint32_t ProgramGL::get_program() const {
        return program;
    }

    void ProgramGL::bind() const
    {
        glUseProgram(program);
    }

    void ProgramGL::unbind()
    {
        glUseProgram(0);
    }

    void ProgramGL::destroy() const
    {
        glDeleteProgram(program);
    }
}
