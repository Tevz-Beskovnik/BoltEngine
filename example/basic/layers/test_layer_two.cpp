//
// Created by tevz on 11.7.2023.
//

#include <test_layer_two.hpp>

MouseButton TestLayerTwo::pressed_button = NONE;
int32_t TestLayerTwo::action = -1;
vector_2 TestLayerTwo::mouse_pos = {0, 0};

TestLayerTwo::TestLayerTwo(ref_ptr<Window> window)
    :window(window), current_active(0)
{
    auto pos = scene.add_object(generate_3d_grid());

    uint16_t w, h;

    window->get_size(&w, &h);
    ar = static_cast<float>(w) / static_cast<float>(h);

    frames = {
            "../../example/textures/color-frame-black.png",
            "../../example/textures/color-frame-white.png",
            "../../example/textures/color-frame-red.png",
            "../../example/textures/color-frame-orange.png",
            "../../example/textures/color-frame-vanilla.png",
            "../../example/textures/color-frame-bordo.png",
            "../../example/textures/color-frame-cyan.png",
            "../../example/textures/color-frame-dark-blue.png",
            "../../example/textures/color-frame-light-blue.png",
            "../../example/textures/color-frame-dark-green.png",
            "../../example/textures/color-frame-light-green.png",
            "../../example/textures/color-frame-pinky.png",
            "../../example/textures/color-frame-rose.png",
            "../../example/textures/color-frame-brown.png"
    };

    create_frames(frame_objects, frames, collision_boxes, scene, ar);
}

[[nodiscard]] ref_ptr<TestLayerTwo> TestLayerTwo::create(ref_ptr<Window> window)
{
    return create_ref<TestLayerTwo>(window);
}

void TestLayerTwo::frame()
{
    scene.draw();

    if(pressed_button == MouseButton::LEFT_BUTTON && action == 1)
    {
        if(int32_t new_active = intersects_rects(mouse_pos, collision_boxes); new_active != -1)
        {
            std::cout << "This was clicked" << std::endl;
            BOLT_LOG_INFO("Remove from scene the current active frame")
            scene.remove(frame_objects[current_active]);

            BOLT_LOG_INFO("Replace old active with transparent frame")
            frame_objects[current_active] = create_transparent_frame(frames[current_active], collision_boxes[current_active], scene);

            BOLT_LOG_INFO("Remove the to be active frame")
            scene.remove(frame_objects[new_active]);

            BOLT_LOG_INFO("Create the new active frame")
            frame_objects[new_active] = create_full_frame(frames[new_active], collision_boxes[new_active], scene);

            current_active = new_active;
        }
    }

    {
        uint16_t height, width;
        window->get_size(&width, &height);

        ImGui::Begin("Mouse info");

        ImGui::Text("Cursor position:");

        ImGui::Text("X: %f, Y: %f", mouse_pos.x, mouse_pos.y);

        ImGui::Text("Button clicked:");

        ImGui::Text("Button: %i, action: %i", pressed_button, action);

        ImGui::Text("Current active: %i,", current_active);

        ImGui::End();
    }

    ImGui::Render();
}

void TestLayerTwo::bind_event_trigger(event_trigger trigger)
{
    this->trigger = trigger;
}

void TestLayerTwo::on_event(Event& e) const
{
    EventDispatcher dispatcher(e);

    dispatcher.dispatch<MouseMoveEvent>(CAST_MEMBER_FUNCTION(handle_mouse_position_event));
    dispatcher.dispatch<MouseClickEvent>(CAST_MEMBER_FUNCTION(handle_mouse_button_event));
}

bool TestLayerTwo::handle_mouse_position_event(MouseMoveEvent& event) const
{
    uint16_t w, _;
    window->get_size(&w, &_);

    // clamp mouse position to the ranges of -1 to 1
    mouse_pos = event.pos;
    mouse_pos.y *= ar;
    mouse_pos /= (static_cast<float>(w)/2);

    mouse_pos.x -= 1;
    mouse_pos.y = 1 - mouse_pos.y;

    return false;
}

bool TestLayerTwo::handle_mouse_button_event(MouseClickEvent& event) const
{
    pressed_button = static_cast<MouseButton>(event.button);
    action = event.action;

    return false;
}