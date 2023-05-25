#include <shader_gl.hpp>

namespace bolt
{
    [[nodiscard]] ShaderGL::ShaderGL(std::vector<shader_config_gl> config)
    {
        BOLT_LOG_INFO("Creating shader program")

        for(auto& conf : config)
        {
            std::string error = "File: " + std::string(conf.shader_location) + " does not exist.";
            ASSERT_FILE_EXISTS(conf.shader_location, error);

            read_shader(conf.shader_location);

            compile_shader(conf.type);
        }

        BOLT_LOG_INFO("Linking shader")

        program = glCreateProgram();
        for(auto& shader : delete_queue)
            glAttachShader(program, shader);
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

        for(auto& shader : delete_queue)
            glDeleteShader(shader);

        BOLT_LOG_INFO("Linking finished");
    }

    ShaderGL::~ShaderGL()
    {
        BOLT_LOG_INFO("Deleting shader program")
        glDeleteProgram(program);
    }

    [[nodiscard]] ref_ptr<ShaderGL> ShaderGL::create(std::vector<shader_config_gl> config)
    {
        return create_ref<ShaderGL>(config);
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
            shader_string += line + '\n';
        }
        shader_string += '\0';
    }

    void ShaderGL::compile_shader(uint32_t type)
    {
        const_str c_str_shader = shader_string.c_str();
        uint32_t shader = glCreateShader(type);

        BOLT_LOG_INFO("Compiling shader:")
        BOLT_LOG_INFO(c_str_shader)

        glShaderSource(shader, 1, &c_str_shader, NULL);
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

            BOLT_LOG_ERROR(message)
            BOLT_ERROR("Failed to compile shader")
        }

        delete_queue.push_back(shader);

        BOLT_LOG_INFO("Shader compiled")
    }
}