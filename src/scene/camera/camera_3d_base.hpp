#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <camera_events.hpp>
#include <camera_base.hpp>

namespace bolt
{
    struct camera_conf {
        uint32_t id;
        vector_3 position = {0.0f, 0.0f, 0.0f};
        vector_3 pointing = {0.0f, 0.0f, 0.0f};
        uint16_t width;
        uint16_t height;
        float f_far;
        float f_near;
        float fov;
    };

    class Camera3dBase : public CameraBase
    {
        public:
            vector_3 position;
            vector_3 pointing;

            float forward = 0.0f;
            float sideways = 0.0f;
            float vertical = 0.0f;

            Camera3dBase() = default;

            virtual ~Camera3dBase() = default;

            explicit Camera3dBase(camera_conf config);

            void set_event_trigger(event_trigger trigger);

            void set_config(camera_conf config);

            virtual void update();

            virtual void on_event(Event& e);

        protected:
            uint32_t id;

            vector_3 look_direction_forward = {0.0f, 0.0f, 1.0f};
            vector_3 look_direction_side = {1.0f, 0.0f, 0.0f};
            vector_3 look_direction_up = {0.0f, 1.0f, 0.0f};

            matrix_4 projection_matrix;
            matrix_4 view_matrix;

            virtual void update_view_matrix() = 0;

            void create_projection_matrix(uint16_t width, uint16_t height, float f_far, float f_near, float fov);

        private:

            event_trigger trigger;
    };
}
