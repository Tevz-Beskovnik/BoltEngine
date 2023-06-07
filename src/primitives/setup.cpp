#include <setup.hpp>

void draw_primitives(const std::vector<uint32_t>& buffers, const std::vector<uint32_t>& shaders, const std::vector<uint32_t>& draw_types, const std::vector<uint32_t>& count)
{
    for(uint32_t i = 0; i < buffers.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);

        glUseProgram(shaders[i]);

        glDrawArrays(draw_types[i], 0, count[i]);
    }
}