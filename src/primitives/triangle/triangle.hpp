#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <primitives.hpp>
#include <renderer_exception.hpp>
#include <file_system.hpp>
#include <texture_exception.hpp>

namespace bolt
{
    #define create_triangles_i(trig, ...) buffers.push_back(setup_triangle(trig, __VA_ARGS__)); \
                                     draw_type.push_back(GL_TRIANGLES); \
                                     glBindBuffer(GL_ARRAY_BUFFER, buffers.back()); \
                                     glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size); \
                                     count.push_back(buffer_size/(sizeof(float)*4)); \
                                     vertex_arrays.push_back(create_triangle_vertex_array(buffers.back()));

    #define create_triangles_color(color, trig, ...) create_triangles_i(trig, __VA_ARGS__) \
                                                     shaders.push_back(setup_triangle_shaders(color, "../../src/primitives/triangle/shaders/vert.glsl", "../../src/primitives/triangle/shaders/fragColor.glsl")); \
                                                     textures.push_back(0);                \
                                                     glBindVertexArray(0);

    #define create_triangles_texture(tex, trig, ...) create_triangles_i(trig, __VA_ARGS__) \
                                                     shaders.push_back(setup_triangle_shaders(RGB(255.0f, 255.0f, 255.0f, 255.0f), "../../src/primitives/triangle/shaders/vert.glsl", "../../src/primitives/triangle/shaders/fragBoth.glsl")); \
                                                     textures.push_back(setup_triangle_texture(tex));                \
                                                     glBindVertexArray(0);

    #define create_triangles(tex, color, trig, ...) create_triangles_i(trig, __VA_ARGS__) \
                                                    shaders.push_back(setup_triangle_shaders(color, "../../src/primitives/triangle/shaders/vert.glsl", "../../src/primitives/triangle/shaders/fragBoth.glsl")); \
                                                    textures.push_back(setup_triangle_texture(tex));                \
                                                    glBindVertexArray(0);

    struct triangle
    {
        vector_2 vertecies[3];
        vector_2 UV[3];
        bool noUV = true;
    };

    [[nodiscard]] uint32_t setup_triangle(triangle trig);

    [[nodiscard]] uint32_t create_triangle_vertex_array(uint32_t buffer);

    void add_triangle_to_buffer(std::vector<float>& buffer, triangle trig);

    [[nodiscard]] uint32_t setup_triangle_shaders(const RGB& color, const std::string& vert, const std::string& frag);

    [[nodiscard]] uint32_t setup_triangle_texture(const std::string& file);

    void add_to_trig_buffer(uint32_t offset, uint32_t buffer, triangle trig);

    template<typename ...Args>
    void add_to_trig_buffer(uint32_t offset, uint32_t buffer, triangle trig, Args... args)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data;

        add_triangle_to_buffer(data, trig);

        glBufferSubData(GL_ARRAY_BUFFER, offset, 12 * sizeof(float), data.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        add_to_trig_buffer(offset + 12 * sizeof(float), buffer, args...);
    }

    template<typename ...Args>
    [[nodiscard]] uint32_t setup_triangle(triangle trig, Args... args)
    {
        uint32_t buffer;

        glGenBuffers(1, &buffer);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        constexpr std::size_t arg_num = sizeof...(Args); // number of args

        std::vector<float> data;

        add_triangle_to_buffer(data, trig);

        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float) + arg_num * 12 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        add_to_trig_buffer(12 * sizeof(float), buffer, args...);

        BOLT_LOG_INFO("Added triangle to primitives (VA args)")

        return buffer;
    }
};