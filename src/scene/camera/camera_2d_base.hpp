#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <camera_events.hpp>
#include <camera_base.hpp>

namespace bolt
{
    struct camera_2d_conf
    {
        vector_2 position = { 0.0f, 0.0f };
        vector_2 size;
    };

    class Camera2dBase : public CameraBase
    {
        public:
            vector_2 position;

            vector_2 size;

            Camera2dBase();

            explicit Camera2dBase(const camera_2d_conf& config);

            void set_event_trigger(event_trigger trigger);

            void set_config(camera_2d_conf config);

            virtual void update();

            virtual void on_event(Event& e);

        protected:
            matrix_4 translation_matrix;

        private:
            event_trigger trigger;
    };
}
