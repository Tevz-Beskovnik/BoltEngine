#include <camera.hpp>

namespace bolt
{
    Camera::Camera(camera_conf config)
        : position(position), pointing(pointing)
    {
        create_projection_matrix(config.width, config.height, config.f_far, config.f_near, config.fov);
    }

    [[nodiscard]] ref_ptr<Camera> Camera::create(camera_conf config)
    {
        return create_ref<Camera>(config);
    }

    void Camera::update()
    {

    }

    void Camera::create_projection_matrix(uint16_t width, uint16_t height, float f_far, float f_near, float fov)
    {
        const float fov_rad = 1 / tanf(fov * 0.5f / 180.0f * (float)PI);

        const float aspect_ratio = static_cast<float>(height) / static_cast<float>(width);

        projection_mat = {
            aspect_ratio * fov_rad, 0.0f, 0.0f, 0.0f,
            0.0f, fov_rad, 0.0f, 0.0f,
            0.0f, 0.0f, f_far / (f_far - f_near), 1.0f,
            0.0f, 0.0f, (-f_far * f_near) / (f_far - f_near), 0.0f
        };
    }

    void Camera::update_view_matrix()
    {

    }
}