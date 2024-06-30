//
// Created by Tevz on 17. 6. 24.
//

#include "camera_2d_base.hpp"

namespace bolt {
    Camera2dBase::Camera2dBase()
        : position({0, 0}), size({1600, 900})
    {
        ;
    }

    Camera2dBase::Camera2dBase(camera_2d_conf config)
        : position(config.position), size(config.size)
    {
        ;
    }

    void Camera2dBase::set_event_trigger(event_trigger trigger)
    {
        this->trigger = trigger;
    }

    void Camera2dBase::set_config(camera_2d_conf config)
    {
        this->size = config.size;
        this->position = config.position;
    }

    void Camera2dBase::update()
    {
        matrix_4 previous_translation_matrix = this->translation_matrix;

        this->translation_matrix = {
            this->position.x, 0.0f, 0.0f, 0.0f,
            0.0f, this->position.y, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        if(previous_translation_matrix != this->translation_matrix) {
            class CameraUpdate updateEvent(this->translation_matrix, 0);

            BOLT_LOG_INFO("Camera 2d update")
            trigger(updateEvent);
        }
    }

    void Camera2dBase::on_event(Event& e)
    {
        ;
    }
}