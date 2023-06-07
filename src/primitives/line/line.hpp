#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <renderer_exception.hpp>
#include <primitives.hpp>

namespace bolt
{
    #define SETUP_LINES(color, p1, p2) shaders.push_back(setup_line_shader(color));     \
                                       buffers.push_back(setup_line_buffer(p1, p2));    \
                                       draw_type.push_back(GL_LINES);                   \
                                       glBindBuffer(GL_ARRAY_BUFFER, buffers.back());   \
                                       glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size); \
                                       count.push_back(buffer_size/(sizeof(float)*3))

    uint32_t setup_line_shader(RGB color)
    {
        // vertex frag_shader
        std::string vertex_shader_string;
        std::string line;
        std::ifstream file("");

        while(std::getline(file, line))
        {
            vertex_shader_string += line + '\n';
        }
        vertex_shader_string += '\0';

        file.close();

        const_str c_str_vert = vertex_shader_string.c_str();

        uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER);

        BOLT_LOG_INFO("Compiling frag_shader:")
        BOLT_LOG_INFO(vertex_shader_string)

        glShaderSource(vert_shader, 1, &c_str_vert, NULL);
        glCompileShader(vert_shader);

        int32_t status;
        glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &status);

        if(status == GL_FALSE)
        {
            int32_t length;
            glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &length);

            auto message = new char[length];
            glGetShaderInfoLog(vert_shader, length, &length, message);

            glDeleteShader(vert_shader);

            BOLT_LOG_ERROR(message)
            BOLT_ERROR("Failed to compile frag_shader")
        }

        // fragment frag_shader
        std::string fragment_shader_string;

        file.open("");

        while(std::getline(file, line))
        {
            fragment_shader_string += line + '\n';
        }
        fragment_shader_string += '\0';

        file.close();

        const_str c_str_frag = fragment_shader_string.c_str();

        uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

        BOLT_LOG_INFO("Compiling frag_shader:")
        BOLT_LOG_INFO(fragment_shader_string)

        glShaderSource(frag_shader, 1, &c_str_frag, NULL);
        glCompileShader(frag_shader);

        glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &status);

        if(status == GL_FALSE)
        {
            int32_t length;
            glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &length);

            auto message = new char[length];
            glGetShaderInfoLog(frag_shader, length, &length, message);

            glDeleteShader(frag_shader);

            BOLT_LOG_ERROR(message)
            BOLT_ERROR("Failed to compile frag_shader")
        }

        BOLT_LOG_INFO("Shader compiled")

        uint32_t program = glCreateProgram();
        glAttachShader(program, vert_shader);
        glAttachShader(program, frag_shader);
        glLinkProgram(program);
        glValidateProgram(program);

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

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);

        return program;
    }

    template<typename ...Args>
    uint32_t add_to_buffer(uint32_t buffer, const vector_3& p1, const vector_3& p2, Args ...args)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        int32_t buffer_size;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);

        std::vector<float> data = {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z};

        glBufferSubData(buffer, buffer_size, 6 * sizeof(float), data.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        add_to_buffer(buffer, args...);
    }

    uint32_t add_to_buffer(uint32_t buffer, const vector_3& p1, const vector_3& p2)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        int32_t buffer_size;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);

        std::vector<float> data = {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z};

        glBufferSubData(buffer, buffer_size, 6 * sizeof(float), data.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    template<typename ...Args>
    uint32_t setup_line_buffer(Args ...args)
    {
        uint32_t buffer;

        glGenBuffers(1, &buffer);

        add_to_buffer(buffer, args...);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            3 * sizeof(float),
            0
            );

        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        add_to_buffer(buffer, args...);

        return buffer;
    }
}