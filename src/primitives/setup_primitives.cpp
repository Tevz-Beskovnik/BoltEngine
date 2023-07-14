#include <setup_primitives.hpp>

// TODO: store data about primitives in static variables in .cpp files so as to not pollute classes :))))))) (I AM SO PROUD I THOUGH OF THIS) AND ALSO SAVES A LOT OF HEDAICHES WHEN TRYING TO DRAW THING FROM CROSS CLASSES

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

    void cleanup_primitive(std::vector<uint32_t>& vertex_arrays, std::vector<uint32_t>& shaders, std::vector<uint32_t>& draw_types, std::vector<int32_t>& count, std::vector<uint32_t>& textures, std::vector<uint32_t>& buffers, uint32_t index)
    {
        BOLT_LOG_INFO(std::string("Cleaning up primative at index: ") + std::to_string(index))

        if(textures[index] != 0)
            glDeleteTextures(1, &textures[index]);

        glDeleteProgram(shaders[index]);
        glDeleteVertexArrays(1, &vertex_arrays[index]);
        glDeleteBuffers(1, &buffers[index]);

        shaders.erase(shaders.begin() + index);
        textures.erase(textures.begin() + index);
        vertex_arrays.erase(vertex_arrays.begin() + index);
        buffers.erase(buffers.begin() + index);
        draw_types.erase(draw_types.begin() + index);
        count.erase(count.begin() + index);
    }
}