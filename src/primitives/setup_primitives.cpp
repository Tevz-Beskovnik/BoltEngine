#include <setup_primitives.hpp>

namespace bolt
{
    void draw_primitives(const std::vector<uint32_t>& vertex_arrays, const std::vector<uint32_t>& shaders, const std::vector<uint32_t>& draw_types, const std::vector<uint32_t>& count)
    {
        for(uint32_t i = 0; i < vertex_arrays.size(); i++)
        {
            glBindVertexArray(vertex_arrays[i]);

            glUseProgram(shaders[i]);

            glDrawArrays(draw_types[i], 0, (int)count[i]);
        }
    }
}

