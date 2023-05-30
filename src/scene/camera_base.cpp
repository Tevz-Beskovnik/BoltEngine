#include <camera_base.hpp>

namespace bolt
{
    CameraBase::CameraBase(camera_conf config)
        : position(config.position), pointing(config.pointing), id(config.id)
    {
        create_projection_matrix(config.width, config.height, config.f_far, config.f_near, config.fov);
    }

    void CameraBase::set_event_trigger(event_trigger trigger)
    {
        this->trigger = trigger;
    }

    void CameraBase::set_config(camera_conf config)
    {
        this->position = config.position;
        this->pointing = config.pointing;
        this->id = config.id;
        create_projection_matrix(config.width, config.height, config.f_far, config.f_near, config.fov);
    }

    void CameraBase::update()
    {
        matrix_4 previous_view_matrix = view_matrix;

        update_view_matrix();

        class CameraUpdate ev(view_matrix, id);

        if(previous_view_matrix != view_matrix) // if they are diffrent we want to dispatch a event to tell everyone to update
        {
            BOLT_LOG_INFO("Camera update")
            trigger(ev);
        }
    }

    void CameraBase::on_event(Event& e)
    {
        ;
    }

    void CameraBase::create_projection_matrix(uint16_t width, uint16_t height, float f_far, float f_near, float fov)
    {
        const float fov_rad = 1 / tanf(fov * 0.5f / 180.0f * (float)PI);

        const float aspect_ratio = static_cast<float>(height) / static_cast<float>(width);

        projection_matrix = {
            aspect_ratio * fov_rad, 0.0f, 0.0f, 0.0f,
            0.0f, fov_rad, 0.0f, 0.0f,
            0.0f, 0.0f, f_far / (f_far - f_near), 1.0f,
            0.0f, 0.0f, (-f_far * f_near) / (f_far - f_near), 0.0f
        };
    }
}