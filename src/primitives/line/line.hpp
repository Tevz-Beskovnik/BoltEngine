#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <renderer_exception.hpp>
#include <primitives.hpp>

namespace bolt
{

    #define create_lines(color, p1, p2, ...)  buffers.size(); \
                                              buffers.push_back(setup_line_buffer(p1, p2, __VA_ARGS__)); \
                                              draw_type.push_back(GL_LINES); \
                                              glBindBuffer(GL_ARRAY_BUFFER, buffers.back()); \
                                              glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size); \
                                              count.push_back(buffer_size/(sizeof(float)*3)); \
                                              vertex_arrays.push_back(create_line_vertex_arrays(buffers.back()));    \
                                              shaders.push_back(setup_line_shader(color)); \
                                              textures.push_back(0); \
                                              glBindVertexArray(0);

    #define create_lines_shaders(color, frag, vert, p1, p2, ...) buffers.size(); \
                                              buffers.push_back(setup_line_buffer(p1, p2, __VA_ARGS__)); \
                                              draw_type.push_back(GL_LINES); \
                                              glBindBuffer(GL_ARRAY_BUFFER, buffers.back()); \
                                              glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size); \
                                              count.push_back(buffer_size/(sizeof(float)*3)); \
                                              vertex_arrays.push_back(create_line_vertex_arrays(buffers.back()));    \
                                              shaders.push_back(setup_line_shader(color, frag, vert)); \
                                              textures.push_back(0); \
                                              glBindVertexArray(0);

    [[nodiscard]] uint32_t setup_line_shader(RGB color, std::string vert_file = "../src/primitives/line/shaders/vert.glsl", std::string frag_file = "../src/primitives/line/shaders/frag.glsl");

    void add_to_buffer(uint32_t current_size,uint32_t buffer, const vector_3& p1, const vector_3& p2);

    [[nodiscard]] uint32_t setup_line_buffer(const vector_3& p1, const vector_3& p2);

    [[nodiscard]] uint32_t create_line_vertex_arrays(uint32_t buffer);

    template<typename ...Args>
    void add_to_buffer(uint32_t current_size, uint32_t buffer, const vector_3& p1, const vector_3& p2, Args ...args)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data = {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z};

        glBufferSubData(GL_ARRAY_BUFFER, current_size, 6 * sizeof(float), data.data());

        //glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        add_to_buffer(current_size + 6 * sizeof(float), buffer, args...);
    }

    template<typename ...Args>
    [[nodiscard]] uint32_t setup_line_buffer(const vector_3& p1, const vector_3& p2, Args ...args)
    {
        uint32_t buffer;

        glGenBuffers(1, &buffer);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        constexpr std::size_t arg_num = sizeof...(Args); // number of args

        std::vector<float> data = {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z};

        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float) + arg_num * 3 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        add_to_buffer(6 * sizeof(float), buffer, args...);

        BOLT_LOG_INFO("Added points to buffer")

        return buffer;
    }
}