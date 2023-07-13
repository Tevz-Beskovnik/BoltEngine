#include <test_camera.hpp>

TestCamera::TestCamera(uint16_t w, uint16_t h)
{
    camera_conf config = {
        .id = 1,
        .position = {6.0, 5.0, 6.0},
        .pointing = {-0.7, 2.37, 0},
        .width = w,
        .height = h,
        .f_far = 1000,
        .f_near = 0.1,
        .fov = 90,
    };

    last_cursor_position = Mouse::read_pos();

    CameraBase::set_config(config);
}

[[nodiscard]] ref_ptr<TestCamera> TestCamera::create(uint16_t w, uint16_t h)
{
    return create_ref<TestCamera>(w, h);
}

void TestCamera::update()
{
    /*vector_2 current = Mouse::read_pos();
    if(pointing.x + (last_cursor_position.y - current.y)*0.01 < PI/2 && pointing.x + (last_cursor_position.y - current.y)*0.01 > -PI/2)
        pointing.x += (last_cursor_position.y - current.y)*0.01;
    pointing.y += (last_cursor_position.x - current.x)*0.01;
    last_cursor_position = current;

    //pointing.y -= Keyboard::is_key_held(Key::Left)*-0.01 + Keyboard::is_key_held(Key::Right)*0.01;
    //pointing.x += Keyboard::is_key_held(Key::Down)*-0.01 + Keyboard::is_key_held(Key::Up)*0.01;

    sideways = Keyboard::is_key_held(Key::D)*0.07 + Keyboard::is_key_held(Key::A)*-0.07;
    position.y += Keyboard::is_key_held(Key::LeftShift)*-0.07 + Keyboard::is_key_held(Key::Space)*0.07;
    forward = Keyboard::is_key_held(Key::W)*0.07 + Keyboard::is_key_held(Key::S)*-0.07;*/

    CameraBase::update();
}

void TestCamera::update_view_matrix() {
    position = position + (look_direction_forward * forward) + (look_direction_side * sideways) + (look_direction_up * vertical);

    vector_3 target_f = {0.0f, 0.0f, 1.0f};

    matrix_4 camera_rotation = matrix_4::rotation_y(pointing.y);

    look_direction_forward = camera_rotation * target_f;
    look_direction_side = camera_rotation * vector_3{1.0f, 0.0f, 0.0f};
    look_direction_up = camera_rotation * vector_3{0.0f, 1.0f, 0.0f};

    target_f = position + look_direction_forward;

    view_matrix = matrix_4::view_matrix(projection_matrix, position, target_f, {0.0f, 1.0f, 0.0f}, {pointing.x, 0, 0});
}