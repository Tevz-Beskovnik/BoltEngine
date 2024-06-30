#include <2d_test_camera.hpp>

[[nodiscard]] ref_ptr<Camera2dTest> Camera2dTest::create(camera_2d_conf& config)
{
    return create_ref<Camera2dTest>(config);
}

void Camera2dTest::on_event(Event& event)
{
    EventDispatcher eventDispatcher(event);

    eventDispatcher.dispatch<class KeyEvent>(CAST_MEMBER_FUNCTION(Camera2dTest::handle_key_event));
}

bool Camera2dTest::handle_key_event(class KeyEvent& event)
{
    switch(event.key) {
        case Key::A:
        {
            position.x -= 0.1;
            break;
        }
        case Key::D:
        {
            position.x += 0.1;
            break;
        }
        case Key::W:
        {
            position.y += 0.1;
            break;
        }
        case Key::S:
        {
            position.y -= 0.1;
            break;
        }
    }

    return false;
}