#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>

namespace bolt
{
    struct camera_conf {
        vector_3 positon = {0.0f, 0.0f, 0.0f};
        vector_3 pointing = {0.0f, 0.0f, 0.0f};
        uint16_t width;
        uint16_t height;
        float f_far;
        float f_near;
        float fov;
    };

    class Camera
    {
        public:
            vector_3 position;
            vector_3 pointing;

            Camera(camera_conf config);

            [[nodiscard]] static ref_ptr<Camera> create(camera_conf config);

            void update();

        private:
            vector_3 look_direction_side = {0.0f, 0.0f, 1.0f};
            vector_3 look_direction_forward = {1.0f, 0.0f, 0.0f};
            vector_3 look_direction_up = {0.0f, 1.0f, 0.0f};

            float forward = 0.0f;
            float sideways = 0.0f;
            float vertical = 0.0f;

            matrix_4 projection_mat;
            matrix_4 view_matrix;

            void create_projection_matrix(uint16_t width, uint16_t height, float f_far, float f_near, float fov);

            void update_view_matrix();
    };
}
