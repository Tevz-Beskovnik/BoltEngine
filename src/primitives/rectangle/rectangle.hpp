#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <renderer_exception.hpp>
#include <primitives.hpp>

namespace bolt
{
    struct rectangle {
        vector_3 corners[4];
    };

    inline void add_rectangle_to_buffer(std::vector<float>& data, const rectangle& rect);

    void add_to_rect_buffer(uint32_t offset, uint32_t buffer, const rectangle& rect);

    uint32_t setup_rectangle(const rectangle& rect);

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
    uint32_t setup_rectangle(const rectangle& rect, Args ...args)
    {
        uint32_t buffer;

        glGenBuffers(1, &buffer);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        constexpr std::size_t arg_num = sizeof...(Args); // number of args

        std::vector<float> data;

        add_rectangle_to_buffer(data, rect);

        glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float) + arg_num * 24 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        BOLT_LOG_INFO("Added rectangle primitives")

        add_to_rect_buffer(24 * sizeof(float), buffer, args...);

        return buffer;
    }
}