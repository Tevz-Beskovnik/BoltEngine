#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <renderer_exception.hpp>
#include <texture_exception.hpp>
#include <file_system.hpp>
#include <primitives.hpp>

namespace bolt
{
    #define create_rects_i(rect, ...)  buffers.push_back(setup_rectangle(rect, __VA_ARGS__)); \
                                     draw_type.push_back(GL_TRIANGLES); \
                                     glBindBuffer(GL_ARRAY_BUFFER, buffers.back()); \
                                     glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size); \
                                     count.push_back(buffer_size/(sizeof(float)*4)); \
                                     vertex_arrays.push_back(create_rect_vertex_arrays(buffers.back()));

    // TODO create abstractions for x, y, z & w, h
    // !!ATTENTION!! this sort of macros wizardry is efficient however this should NEVER EVER EVER be used in PRODUCTION CODE
    #define create_rectangles_color(color, rect, ...) create_rects_i(rect, __VA_ARGS__) \
                                             _shader_tex_pair = setup_rectangle_shader(color); \
                                             shaders.push_back(_shader_tex_pair.first); \
                                             textures.push_back(_shader_tex_pair.second);      \
                                             glBindVertexArray(0);

    #define create_rectangles_texture(tex, rect, ...) create_rects_i(rect, __VA_ARGS__) \
                                           _shader_tex_pair = setup_rectangle_shader(tex); \
                                           shaders.push_back(_shader_tex_pair.first);             \
                                           textures.push_back(_shader_tex_pair.second);    \
                                           glBindVertexArray(0);

    #define create_rectangles(color, tex, rect, ...) create_rects_i(rect, __VA_ARGS__) \
                                                      _shader_tex_pair = setup_rectangle_shader(color, tex); \
                                                      shaders.push_back(_shader_tex_pair.first);             \
                                                      textures.push_back(_shader_tex_pair.second);           \
                                                      glBindVertexArray(0);

    #define create_rect_shader_custom(color, tex, vert_file, frag_file, rect, ...) create_rects_i(rect, __VA_ARGS__) \
                                                                                   _shader_tex_pair = setup_rectangle_shader(color, tex); \
                                                                                   shaders.push_back(_shader_tex_pair.first);             \
                                                                                   textures.push_back(_shader_tex_pair.second); \
                                                                                   glBindVertexArray(0);

    struct rectangle {
        vector_2 pos;
        vector_2 dims;
    };

    [[nodiscard]] std::pair<uint32_t, uint32_t> setup_rectangle_shader(RGB color);

    [[nodiscard]] std::pair<uint32_t, uint32_t> setup_rectangle_shader(const std::string& texture_file);

    [[nodiscard]] std::pair<uint32_t, uint32_t> setup_rectangle_shader(RGB color, const std::string& texture);

    [[nodiscard]] std::pair<uint32_t, uint32_t> setup_rectangle_shader(RGB color, const std::string& texture, const std::string& vert, const std::string& frag);

    inline void add_rectangle_to_buffer(std::vector<float>& data, const rectangle& rect);

    void add_to_rect_buffer(uint32_t offset, uint32_t buffer, const rectangle& rect);

    [[nodiscard]] uint32_t create_rect_vertex_arrays(uint32_t buffer);

    [[nodiscard]] uint32_t setup_rectangle(const rectangle& rect);

    template <typename ...Args>
    void add_to_rect_buffer(uint32_t offset, uint32_t buffer, const rectangle& rect, Args ...args)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data;

        add_rectangle_to_buffer(data, rect);

        glBufferSubData(GL_ARRAY_BUFFER, offset, 24 * sizeof(float), data.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        add_to_rect_buffer(offset + 24 * sizeof(float), buffer, args...);
    }

    template <typename ...Args>
    [[nodiscard]] uint32_t setup_rectangle(const rectangle& rect, Args ...args)
    {
        uint32_t buffer;

        glGenBuffers(1, &buffer);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        constexpr std::size_t arg_num = sizeof...(Args); // number of args

        std::vector<float> data;

        add_rectangle_to_buffer(data, rect);

        glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float) + arg_num * 24 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        add_to_rect_buffer(24 * sizeof(float), buffer, args...);

        BOLT_LOG_INFO("Added rectangle primitives")

        return buffer;
    }
}