#include <setup_primitives.hpp>

namespace bolt
{
    uint32_t create_vertex_arrays(const std::vector<uint32_t>& buffer)
    {
        uint32_t vertex_array;

        glGenVertexArrays(1, &vertex_array);

        glBindVertexArray(vertex_array);

        glBindBuffer(GL_ARRAY_BUFFER, buffer.back());

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

    void draw_primitives_f(const std::vector<uint32_t>& vertex_arrays, const std::vector<uint32_t>& shaders, const std::vector<uint32_t>& draw_types, const std::vector<int32_t>& count)
    {
        for(uint32_t i = 0; i < vertex_arrays.size(); i++)
        {
            glBindVertexArray(vertex_arrays[i]);

            glUseProgram(shaders[i]);

            glDrawArrays(draw_types[i], 0, (int)count[i]);
        }
    }
}

