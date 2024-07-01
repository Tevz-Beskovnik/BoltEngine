//
// Created by tevz on 11.7.2023.
//
#define MOVEMENT_MODIFIER 5

#include <test_layer_two.hpp>

/**
 * TODO:
 * Screen coords are from -1 - 1 no 0 - 1 as I assumed (you already knew this you idiot
 * Anyway make sure it binds correctly
 * */

MouseButton TestLayerTwo::pressed_button = NONE;
int32_t TestLayerTwo::action = -1;
vector_2 TestLayerTwo::mouse_pos = {0, 0};
vector_2 TestLayerTwo::obj_pos = {800, 450};

static bool w_held;
static bool a_held;
static bool s_held;
static bool d_held;
static matrix_4 translation_matrix;

void binding_function(uint32_t program) {
    auto uTranslationMat = glGetUniformLocation(program, "uTranslation");

    translation_matrix.m[0][0] = TestLayerTwo::obj_pos.x/1600;
    translation_matrix.m[1][1] = TestLayerTwo::obj_pos.y/900;

    glUniformMatrix4fv(uTranslationMat, 1, GL_TRUE, &translation_matrix.m[0][0]);
}

TestLayerTwo::TestLayerTwo(ref_ptr<Window> window)
    :window(window), current_active(0)
{
    ObjectCreator::set_uniform_binding_func(binding_function);

    auto quad = ObjectCreator::quad({1.0f, 1.0f, 0.0f}, {0.05f, 0.05f * (1600.0f/900.0f)}, "../example/shaders/frag_tex.glsl", "../example/shaders/2d_player.vert");

    quad->add_texture("../example/textures/color-frame-bordo.png");

    scene.add_object(quad);
    //auto pos = scene.add_object(generate_3d_grid());

    /*uint16_t w, h;

    window->get_size(&w, &h);
    ar = static_cast<float>(w) / static_cast<float>(h);

    frames = {
        "../example/textures/color-frame-black.png",
        "../example/textures/color-frame-white.png",
        "../example/textures/color-frame-red.png",
        "../example/textures/color-frame-orange.png",
        "../example/textures/color-frame-vanilla.png",
        "../example/textures/color-frame-bordo.png",
        "../example/textures/color-frame-cyan.png",
        "../example/textures/color-frame-dark-blue.png",
        "../example/textures/color-frame-light-blue.png",
        "../example/textures/color-frame-dark-green.png",
        "../example/textures/color-frame-light-green.png",
        "../example/textures/color-frame-pinky.png",
        "../example/textures/color-frame-rose.png",
        "../example/textures/color-frame-brown.png"
    };

    create_frames(frame_objects, frames, collision_boxes, scene, ar);*/
}

[[nodiscard]] ref_ptr<TestLayerTwo> TestLayerTwo::create(ref_ptr<Window> window)
{
    return create_ref<TestLayerTwo>(window);
}

void TestLayerTwo::frame()
{
    scene.draw();
    /*scene.draw();

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
    }*/

    obj_pos.x += static_cast<float>(-MOVEMENT_MODIFIER*a_held) + static_cast<float>(MOVEMENT_MODIFIER*d_held);
    obj_pos.y += static_cast<float>(-MOVEMENT_MODIFIER*s_held) + static_cast<float>(MOVEMENT_MODIFIER*w_held);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        uint16_t height, width;
        window->get_size(&width, &height);

        ImGui::Begin("Mouse info");

        ImGui::Text("Camera position:");

        ImGui::Text("X: %f, Y: %f", obj_pos.x, obj_pos.y);

        ImGui::Text("Button clicked:");

        ImGui::Text("Button: %i, action: %i", pressed_button, action);

        ImGui::Text("Current active: %i,", current_active);

        ImGui::End();
    }

    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
    dispatcher.dispatch<WindowCloseEvent>(CAST_MEMBER_FUNCTION(handle_close_window_event));
    dispatcher.dispatch<class CameraUpdate>(CAST_MEMBER_FUNCTION(handle_camera_update));
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

bool TestLayerTwo::handle_camera_update(class CameraUpdate& event) const
{
    translation_matrix = event.get_view_matrix();

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
    switch(event.key) {
        case Key::A:
        {
            if(event.action == GLFW_PRESS) {
                a_held = true;
            } else if(event.action == GLFW_RELEASE) {
                a_held = false;
            }
            break;
        }
        case Key::D:
        {
            if(event.action == GLFW_PRESS) {
                d_held = true;
            } else if(event.action == GLFW_RELEASE) {
                d_held = false;
            }
            break;
        }
        case Key::W:
        {
            if(event.action == GLFW_PRESS) {
                w_held = true;
            } else if(event.action == GLFW_RELEASE) {
                w_held = false;
            }
            break;
        }
        case Key::S:
        {
            if(event.action == GLFW_PRESS) {
                s_held = true;
            } else if(event.action == GLFW_RELEASE) {
                s_held = false;
            }
            break;
        }
    }

    return false;
}

bool TestLayerTwo::handle_close_window_event(WindowCloseEvent& event) const
{
    StopAppEvent close_event;
    trigger(close_event);

    return true;
}