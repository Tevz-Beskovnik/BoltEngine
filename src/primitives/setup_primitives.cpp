#include <setup_primitives.hpp>

namespace bolt
{
    void draw_primitives_f(const std::vector<uint32_t>& vertex_arrays, const std::vector<uint32_t>& shaders, const std::vector<uint32_t>& draw_types, const std::vector<int32_t>& count, const std::vector<uint32_t>& textures)
    {
        for(uint32_t i = 0; i < vertex_arrays.size(); i++)
        {
            glBindVertexArray(vertex_arrays[i]);

            glUseProgram(shaders[i]);

            if(textures[i] != 0)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[i]);

                glUniform1f(glGetUniformLocation(shaders[i], "uTex"), GL_TEXTURE0);
            }

            glDrawArrays(draw_types[i], 0, (int)count[i]);
        }
    }
}

