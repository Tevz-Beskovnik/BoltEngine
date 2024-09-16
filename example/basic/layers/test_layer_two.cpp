//
// Created by tevz on 11.7.2023.
//
#define MOVEMENT_MODIFIER 1000

#include <test_layer_two.hpp>

/**
 * TODO:
 * Screen coords are from -1 - 1 not 0 - 1 as I assumed (you already knew this you idiot)
 * Anyway make sure it binds correctly
 * */

MouseButton TestLayerTwo::pressed_button = NONE;
int32_t TestLayerTwo::action = -1;
vector_2 TestLayerTwo::mouse_pos = {0, 0};

static bool w_held;
static bool a_held;
static bool s_held;
static bool d_held;
static vector_3 translationVector = {0.0f, 0.0f, 1.0f};
static double previous_time = 0;
static uint32_t frameCount = 0;

TestLayerTwo::TestLayerTwo(ref_ptr<Window> window)
    :window(window), current_active(0)
{
    platforms = {
        Platform::create({600, 300}, 6),
        Platform::create({312, 396}, 4),
        Platform::create({936, 444}, 5)
    };

    player = Player::create({800, 400});

    scene->add_object(player->get_render_interface());

    for (const auto& platform : platforms)
    {
        scene->add_object(platform->get_render_interface());
        player->add_hitbox(platform->get_hitbox());
    }
}

[[nodiscard]] ref_ptr<TestLayerTwo> TestLayerTwo::create(ref_ptr<Window> window)
{
    return create_ref<TestLayerTwo>(window);
}

void TestLayerTwo::update(double delta_time)
{
    player->compute(delta_time);

    /*ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        uint16_t height, width;
        window->get_size(&width, &height);

        ImGui::Begin("Mouse info");

        ImGui::Text("Camera position:");

        ImGui::Text("X: %f, Y: %f", (TestLayerTwo::obj_pos.x/1600)*2-1, (TestLayerTwo::obj_pos.y/900)*2-1);

        ImGui::Text("Button clicked:");

        ImGui::Text("Button: %i, action: %i", pressed_button, action);

        ImGui::Text("Current active: %i,", current_active);

        ImGui::End();
    }

    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
}

void TestLayerTwo::bind_event_trigger(event_trigger trigger)
{
    this->trigger = trigger;
}

void TestLayerTwo::on_event(Event& e) const // TODO: Bleh remove const from here its annoying af
{
    EventDispatcher dispatcher(e);

    dispatcher.dispatch<MouseMoveEvent>(CAST_MEMBER_FUNCTION(handle_mouse_position_event));
    dispatcher.dispatch<MouseClickEvent>(CAST_MEMBER_FUNCTION(handle_mouse_button_event));
    dispatcher.dispatch<WindowCloseEvent>(CAST_MEMBER_FUNCTION(handle_close_window_event));
    dispatcher.dispatch<class KeyEvent>(CAST_MEMBER_FUNCTION(handle_keyboard_input));
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

bool TestLayerTwo::handle_keyboard_input(class bolt::KeyEvent &event) const
{
    player->handle_keyboard_event(event);
    return false;
}

bool TestLayerTwo::handle_close_window_event(WindowCloseEvent& event) const
{
    StopAppEvent close_event;
    trigger(close_event);

    return true;
}