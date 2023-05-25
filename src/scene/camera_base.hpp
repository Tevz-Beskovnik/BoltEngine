#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <camera_events.hpp>

namespace bolt
{
    struct camera_conf {
        uint32_t id;
        vector_3 positon = {0.0f, 0.0f, 0.0f};
        vector_3 pointing = {0.0f, 0.0f, 0.0f};
        uint16_t width;
        uint16_t height;
        float f_far;
        float f_near;
        float fov;
    };

    class CameraBase
    {
        public:
            vector_3 position;
            vector_3 pointing;

            CameraBase(camera_conf config);

            void set_event_trigger(event_trigger trigger);

            [[nodiscard]] static ref_ptr<CameraBase> create(camera_conf config);

            virtual void update();

            virtual void on_event(Event& e);

        private:
            uint32_t id;

            vector_3 look_direction_forward = {0.0f, 0.0f, 1.0f};
            vector_3 look_direction_side = {1.0f, 0.0f, 0.0f};
            vector_3 look_direction_up = {0.0f, 1.0f, 0.0f};

            float forward = 0.0f;
            float sideways = 0.0f;
            float vertical = 0.0f;

            matrix_4 projection_matrix;
            matrix_4 view_matrix;

            event_trigger trigger;

            void create_projection_matrix(uint16_t width, uint16_t height, float f_far, float f_near, float fov);

            void update_view_matrix();
    };
}
