#include <camera.hpp>

namespace bolt
{
    Camera::Camera(camera_conf config)
        : position(config.positon), pointing(config.pointing)
    {
        create_projection_matrix(config.width, config.height, config.f_far, config.f_near, config.fov);
    }

    [[nodiscard]] ref_ptr<Camera> Camera::create(camera_conf config)
    {
        return create_ref<Camera>(config);
    }

    void Camera::update()
    {
        update_view_matrix();
    }

    void Camera::create_projection_matrix(uint16_t width, uint16_t height, float f_far, float f_near, float fov)
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

    void Camera::update_view_matrix()
    {
        position = position + (look_direction_forward * forward) + (look_direction_side * sideways) + (look_direction_up * vertical);

        vector_3 target_f = {0.0f, 0.0f, 1.0f};

        matrix_4 camera_rotation = matrix_4::rotation_y(pointing.y);

        look_direction_forward = camera_rotation * target_f;
        look_direction_side = camera_rotation * vector_3{1.0f, 0.0f, 0.0f};
        look_direction_up = camera_rotation * vector_3{0.0f, 1.0f, 0.0f};

        view_matrix = matrix_4::view_matrix(projection_matrix, position, target_f, {0.0f, 1.0f, 0.0f}, pointing);
    }
}