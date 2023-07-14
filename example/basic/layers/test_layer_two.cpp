//
// Created by tevz on 11.7.2023.
//

#include <test_layer_two.hpp>

MouseButton TestLayerTwo::pressed_button = NONE;
int32_t TestLayerTwo::action = -1;
vector_2 TestLayerTwo::mouse_pos = {0, 0};

TestLayerTwo::TestLayerTwo(ref_ptr<Window> window)
    :window(window)
{
    uint32_t pos = scene.add_object(generate_3d_grid());

    uint16_t w, h;

    window->get_size(&w, &h);
    ar = static_cast<float>(w) / static_cast<float>(h);

    std::vector<std::string> frames = {
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

    for(uint8_t i = 0; i < 14; i+=2)
    {
        create_rectangles_texture(frames[i].c_str(), rectangle{
                .pos = {0.85f, (0.87f - i * 0.06f)},
                .dims = {0.05f, (0.05f * ar)}
        })

        create_rectangles_texture(frames[i+1].c_str(), rectangle{
                .pos = {0.92f, (0.87f - i * 0.06f)},
                .dims = {0.05f, (0.05f * ar)}
        })
    }
}

[[nodiscard]] ref_ptr<TestLayerTwo> TestLayerTwo::create(ref_ptr<Window> window)
{
    return create_ref<TestLayerTwo>(window);
}

void TestLayerTwo::frame()
{
    scene.draw();

    draw_primitives;

    {
        ImGui::Begin("Mouse info");

        ImGui::Text("Cursor position:");

        ImGui::Text("X: %f, Y: %f", mouse_pos.x, mouse_pos.y);

        ImGui::Text("Button clicked:");

        ImGui::Text("Button: %i, action: %i", pressed_button, action);

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
    mouse_pos.y = 2 - mouse_pos.y - 1;

    return false;
}

bool TestLayerTwo::handle_mouse_button_event(MouseClickEvent& event) const
{
    pressed_button = static_cast<MouseButton>(event.button);
    action = event.action;

    return false;
}