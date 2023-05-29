#include <test_camera.hpp>

TestCamera::TestCamera(uint16_t w, uint16_t h)
{
    camera_conf config = {
        .id = 1,
        .position = {0.0, 0.0, -2.0},
        .pointing = {0.0, 0.0, 0.0},
        .width = w,
        .height = h,
        .f_far = 1000,
        .f_near = 0.1,
        .fov = 90,
    };

    CameraBase::set_config(config);
}

[[nodiscard]] ref_ptr<TestCamera> TestCamera::create(uint16_t w, uint16_t h)
{
    return create_ref<TestCamera>(w, h);
}

void TestCamera::update()
{
    pointing.y += Keyboard::is_key_held(Key::A)*-0.01 + Keyboard::is_key_held(Key::D)*0.01;
    pointing.x += Keyboard::is_key_held(Key::W)*0.01 + Keyboard::is_key_held(Key::S)*-0.01;

    position.x += Keyboard::is_key_held(Key::Left)*-0.01 + Keyboard::is_key_held(Key::Right)*0.01;
    position.z += Keyboard::is_key_held(Key::Down)*-0.01 + Keyboard::is_key_held(Key::Up)*0.01;

    CameraBase::update();
}