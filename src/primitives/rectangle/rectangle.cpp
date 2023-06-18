#include <rectangle.hpp>

namespace bolt
{
    inline void add_rectangle_to_buffer(std::vector<float>& data, const rectangle& rect)
    {
        vector_3 U = rect.corners[1] - rect.corners[0];
        vector_3 V = rect.corners[2] - rect.corners[0];

        vector_3 normal1 {
            .x = (U.y * V.z) - (U.z * V.y),
            .y = (U.z * V.x) - (U.x - V.z),
            .z = (U.x * V.y) - (U.y - V.x)
        };

        V = rect.corners[2] - rect.corners[1];
        U = rect.corners[3] - rect.corners[1];

        vector_3 normal2 {
            .x = (U.y * V.z) - (U.z * V.y),
            .y = (U.z * V.x) - (U.x - V.z),
            .z = (U.x * V.y) - (U.y - V.x)
        };

        for(uint8_t i = 0; i < 3; i++)
        {
            data.push_back(rect.corners[i].x);
            data.push_back(rect.corners[i].y);
            data.push_back(rect.corners[i].z);

            data.push_back(normal1.x);
            data.push_back(normal1.y);
            data.push_back(normal1.z);
        }

        for(uint8_t i = 1; i < 4; i++)
        {
            data.push_back(rect.corners[i].x);
            data.push_back(rect.corners[i].y);
            data.push_back(rect.corners[i].z);

            data.push_back(normal2.x);
            data.push_back(normal2.y);
            data.push_back(normal2.z);
        }
    }

    void add_to_rect_buffer(uint32_t offset, uint32_t buffer, const rectangle& rect)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data;

        add_rectangle_to_buffer(data, rect);

        glBufferSubData(GL_ARRAY_BUFFER, offset, 24 * sizeof(float), data.data());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    uint32_t setup_rectangle(const rectangle& rect)
    {
        uint32_t buffer;

        glGenBuffers(1, &buffer);

        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        std::vector<float> data;

        add_rectangle_to_buffer(data, rect);

        glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        BOLT_LOG_INFO("Added rectangle primitives")

        return buffer;
    }
}