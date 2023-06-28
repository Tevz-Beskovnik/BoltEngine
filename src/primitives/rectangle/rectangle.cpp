#include <rectangle.hpp>

namespace bolt
{
    [[nodiscard]] std::pair<uint32_t, uint32_t> setup_rectangle_shader(RGB color)
    {
        std::string vertex_shader_string;
        std::string line;
        std::ifstream file("../../src/primitives/rectangle/shaders/vert.glsl");

        while(std::getline(file, line))
        {
            vertex_shader_string += line + '\n';
        }

        file.close();

        const_str c_str_vert = vertex_shader_string.c_str();

        uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER);

        BOLT_LOG_INFO("Compiling vert_shader:")
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
            BOLT_ERROR("Failed to compile vert_shader")
        }

        std::string fragment_shader_string;

        file.open("../../src/primitives/rectangle/shaders/fragColor.glsl");

        while(std::getline(file, line))
        {
            fragment_shader_string += line + '\n';
        }

        char* frag_formated = new char[fragment_shader_string.size() + 40];

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

        return { program, 0 };
    }

    [[nodiscard]] std::pair<uint32_t, uint32_t> setup_rectangle_shader(const std::string& texture_file)
    {
        ASSERT_FILE_EXISTS(texture_file.c_str(), "File that contains texture does not appear to exist");

        stbi_set_flip_vertically_on_load(true);

        int32_t width, height, BPP;
        uint32_t texture;
        uint8_t* texture_buffer = stbi_load(texture_file.c_str(), &width, &height, &BPP, 0);

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

            std::filesystem::path tex_file = texture_file;
            if(tex_file.extension() == ".jpg")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
            else if(tex_file.extension() == ".png")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_buffer);
            else
                throw TextureException("Unsuported file extension", texture_file);

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            throw TextureException("Failed to load image:", texture_file);

        BOLT_LOG_INFO("Freeing loaded image from stb")

        std::string vertex_shader_string;
        std::string line;
        std::ifstream file("../../src/primitives/rectangle/shaders/vert.glsl");

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

        file.open("../../src/primitives/rectangle/shaders/fragTexture.glsl");

        while(std::getline(file, line))
        {
            fragment_shader_string += line + '\n';
        }

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

        BOLT_LOG_INFO("Shaders deleted")

        return { program, texture };
    }

    [[nodiscard]] std::pair<uint32_t, uint32_t> setup_rectangle_shader(RGB color, const std::string& texture_file)
    {
        ASSERT_FILE_EXISTS(texture_file.c_str(), "File that contains texture does not appear to exist");

        stbi_set_flip_vertically_on_load(true);

        int32_t width, height, BPP;
        uint32_t texture;
        uint8_t* texture_buffer = stbi_load(texture_file.c_str(), &width, &height, &BPP, 0);

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

            std::filesystem::path tex_file = texture_file;
            if(tex_file.extension() == ".jpg")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
            else if(tex_file.extension() == ".png")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_buffer);
            else
                throw TextureException("Unknown file extension:", texture_file.c_str());

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            throw TextureException("Failed to load image:", texture_file);

        BOLT_LOG_INFO("Freeing loaded image from stb")

        std::string vertex_shader_string;
        std::string line;
        std::ifstream file("../../src/primitives/rectangle/shaders/vert.glsl");

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

        file.open("../../src/primitives/rectangle/shaders/fragBoth.glsl");

        while(std::getline(file, line))
        {
            fragment_shader_string += line + '\n';
        }

        char* frag_formated = new char[fragment_shader_string.size() + 50];

        sprintf(frag_formated, fragment_shader_string.c_str(), color.r_dec, color.g_dec, color.b_dec, color.a_dec);

        file.close();

        const_str c_str_frag = frag_formated;

        uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

        BOLT_LOG_INFO("Compiling frag_shader: ")
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

        BOLT_LOG_INFO("Shaders deleted")

        return { program, texture };
    }

    [[nodiscard]] std::pair<uint32_t, uint32_t> setup_rectangle_shader(RGB color, const std::string& texture_file, const std::string& vert, const std::string& frag)
    {
        ASSERT_FILE_EXISTS(texture_file.c_str(), "File that contains texture does not appear to exist");
        ASSERT_FILE_EXISTS(vert.c_str(), "File that contains vertex shader does not appear to exist");
        ASSERT_FILE_EXISTS(frag.c_str(), "File that contains fragment shader does not appear to exist");

        stbi_set_flip_vertically_on_load(true);

        int32_t width, height, BPP;
        uint32_t texture;
        uint8_t* texture_buffer = stbi_load(texture_file.c_str(), &width, &height, &BPP, 0);

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

            std::filesystem::path tex_file = texture_file;
            if(tex_file.extension() == ".jpg")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
            else if(tex_file.extension() == ".png")
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_buffer);
            else
                throw TextureException("Unknown file extension:", texture_file.c_str());

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
            throw TextureException("Failed to load image:", texture_file);

        BOLT_LOG_INFO("Freeing loaded image from stb")

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

        return { program, texture };
    }

    inline void add_rectangle_to_buffer(std::vector<float>& data, const rectangle& rect)
    {
        // poly 1
        data.push_back(rect.pos.x); // top left corner
        data.push_back(rect.pos.y);
        data.push_back(0);
        data.push_back(0);
        data.push_back(rect.pos.x); // bottom left corner
        data.push_back(rect.pos.y + rect.dims.y);
        data.push_back(0);
        data.push_back(1);
        data.push_back(rect.pos.x + rect.dims.x); // bottom right corner
        data.push_back(rect.pos.y + rect.dims.y);
        data.push_back(1);
        data.push_back(1);

        // poly 2
        data.push_back(rect.pos.x); // top left corner
        data.push_back(rect.pos.y);
        data.push_back(0);
        data.push_back(0);
        data.push_back(rect.pos.x + rect.dims.x); // bottom right corner
        data.push_back(rect.pos.y + rect.dims.y);
        data.push_back(1);
        data.push_back(1);
        data.push_back(rect.pos.x + rect.dims.x); // top right corner
        data.push_back(rect.pos.y);
        data.push_back(1);
        data.push_back(0);
    }

    void add_to_rect_buffer(uint32_t offset, uint32_t buffer, const rectangle& rect)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data;

        add_rectangle_to_buffer(data, rect);

        glBufferSubData(GL_ARRAY_BUFFER, offset, 24 * sizeof(float), data.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    [[nodiscard]] uint32_t setup_rectangle(const rectangle& rect)
    {
        uint32_t buffer;

        BOLT_LOG_INFO("Setup rectangle NO VA args")

        glGenBuffers(1, &buffer);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data;

        add_rectangle_to_buffer(data, rect);

        glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        BOLT_LOG_INFO("Added rectangle primitives")

        return buffer;
    }

    [[nodiscard]]
    uint32_t create_rect_vertex_arrays(uint32_t buffer)
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
}