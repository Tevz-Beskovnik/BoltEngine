#include <line.hpp>

namespace bolt
{
    uint32_t setup_line_shader(RGB color, std::string vert_file, std::string frag_file)
    {
        // vertex frag_shader
        std::string vertex_shader_string;
        std::string line;
        std::ifstream file(vert_file);

        while(std::getline(file, line))
        {
            vertex_shader_string += line + '\n';
        }

        file.close();

        const_str c_str_vert = vertex_shader_string.c_str();

        uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER);

        BOLT_LOG_INFO("Compiling vert shader:")
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
        std::string fragment_shader_string = "#version 330 core\n"
                                             "\n"
                                             "out vec4 FragColor;\n"
                                             "\n"
                                             "void main()\n"
                                             "{\n"
                                             "    FragColor = vec4(%f, %f, %f, %f);\n"
                                             "}";

        char* frag_formated = new char[fragment_shader_string.size() + 40];

        sprintf(frag_formated, fragment_shader_string.c_str(), color.r_dec, color.g_dec, color.b_dec, color.a_dec);

        const_str c_str_frag = frag_formated;

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

        BOLT_LOG_INFO("Linking shader")

        glLinkProgram(program);

        BOLT_LOG_INFO("Validating program")

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

        BOLT_LOG_INFO("Shader validated")

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);

        delete[] frag_formated;

        BOLT_LOG_INFO("Shaders deleted")

        return program;
    }

    void add_to_buffer(uint32_t current_size, uint32_t buffer, const vector_3& p1, const vector_3& p2)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data = {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z};

        glBufferSubData(GL_ARRAY_BUFFER, current_size, 6 * sizeof(float), data.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    uint32_t setup_line_buffer(const vector_3& p1, const vector_3& p2)
    {
        uint32_t buffer;

        glGenBuffers(1, &buffer);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data = {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z};

        glBufferData(buffer, 6 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        BOLT_LOG_INFO("Added points to buffer")

        return buffer;
    }

    uint32_t create_line_vertex_arrays(uint32_t buffer)
    {
        uint32_t vertex_array;

        glGenVertexArrays(1, &vertex_array);

        glBindVertexArray(vertex_array);

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

        glBindVertexArray(0);

        return vertex_array;
    }

}