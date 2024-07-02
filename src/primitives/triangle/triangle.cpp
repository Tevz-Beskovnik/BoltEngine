#include <triangle.hpp>

namespace bolt
{
    [[nodiscard]] uint32_t setup_triangle(triangle trig)
    {
        uint32_t buffer;

        glGenBuffers(1, &buffer);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data;

        add_triangle_to_buffer(data, trig);

        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        BOLT_LOG_INFO("Added triangle to primitives")

        return buffer;
    }

    [[nodiscard]] uint32_t create_triangle_vertex_array(uint32_t buffer)
    {
        uint32_t vertex_array;

        glGenVertexArrays(1, &vertex_array);

        glBindVertexArray(vertex_array);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        glVertexAttribPointer(
                0,
                2,
                GL_FLOAT,
                GL_FALSE,
                4 * sizeof(float),
                0
        );

        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
                1,
                2,
                GL_FLOAT,
                GL_FALSE,
                4 * sizeof(float),
                (void*)(2 * sizeof(float))
        );

        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vertex_array;
    }

    void add_triangle_to_buffer(std::vector<float>& buffer, triangle trig)
    {

        buffer.push_back(trig.vertecies[0].x);
        buffer.push_back(trig.vertecies[0].y);
        if(trig.noUV)
        {
            buffer.push_back(trig.UV[0].x);
            buffer.push_back(trig.UV[0].y);
        }
        else
        {
            buffer.push_back(0);
            buffer.push_back(0);
        }

        buffer.push_back(trig.vertecies[1].x);
        buffer.push_back(trig.vertecies[1].y);
        if(trig.noUV)
        {
            buffer.push_back(trig.UV[1].x);
            buffer.push_back(trig.UV[1].y);
        }
        else
        {
            buffer.push_back(0);
            buffer.push_back(1);
        }

        buffer.push_back(trig.vertecies[2].x);
        buffer.push_back(trig.vertecies[2].y);
        if(trig.noUV)
        {
            buffer.push_back(trig.UV[2].x);
            buffer.push_back(trig.UV[2].y);
        }
        else
        {
            buffer.push_back(1);
            buffer.push_back(1);
        }
    }

    [[nodiscard]] uint32_t setup_triangle_shaders(const RGB& color, const std::string& vert, const std::string& frag)
    {
        ASSERT_FILE_EXISTS(vert.c_str(), "File that contains vertex shader does not appear to exist");
        ASSERT_FILE_EXISTS(frag.c_str(), "File that contains fragment shader does not appear to exist");

        std::string vertex_shader_string;
        std::string line;
        std::ifstream file(vert);

        while(std::getline(file, line))
        {
            vertex_shader_string += line + '\n';
        }

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

        std::string fragment_shader_string;

        file.open(frag);

        while(std::getline(file, line))
        {
            fragment_shader_string += line + '\n';
        }

        char* frag_formated = new char[fragment_shader_string.size() + 50];

        sprintf(frag_formated, fragment_shader_string.c_str(), color.r_dec, color.g_dec, color.b_dec, color.a_dec);

        file.close();

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

    [[nodiscard]] uint32_t setup_triangle_texture(const std::string& file)
    {
        ASSERT_FILE_EXISTS(file.c_str(), "File that contains texture does not appear to exist");

        stbi_set_flip_vertically_on_load(true);

        int32_t width, height, BPP;
        uint32_t texture;
        uint8_t* texture_buffer = stbi_load(file.c_str(), &width, &height, &BPP, 0);

        BOLT_LOG_INFO("Reading texture_file file")

        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if(texture_buffer)
        {
            BOLT_LOG_INFO("Binding texture_file buffer to active binding and generating mipmaps")

            std::filesystem::path tex_file = file;
            if(tex_file.extension() == ".jpg")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
            else if(tex_file.extension() == ".png")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_buffer);
            else
                throw TextureException("Unknown file extension:", file.c_str());

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            throw TextureException("Failed to load image:", file.c_str());

        BOLT_LOG_INFO("Freeing loaded image from stb")

        return texture;
    }

    void add_to_trig_buffer(uint32_t offset, uint32_t buffer, triangle trig)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data;

        add_triangle_to_buffer(data, trig);

        glBufferSubData(GL_ARRAY_BUFFER, offset, 12 * sizeof(float), data.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}