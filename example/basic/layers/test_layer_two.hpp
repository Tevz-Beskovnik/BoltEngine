#pragma once

#include <bolt.hpp>
#include <collision.hpp>
#include <object_generator.hpp>

using namespace bolt;

class TestLayerTwo final : public LayerInterface
{
    public:
        static vector_2 obj_pos;

        explicit TestLayerTwo(ref_ptr<Window> window);

        [[nodiscard]] static ref_ptr<TestLayerTwo> create(ref_ptr<Window> window);

        virtual ~TestLayerTwo() override = default;

        void frame() final;

        void bind_event_trigger(event_trigger trigger) final;

        void on_event(Event& e) const final;

        bool handle_mouse_position_event(MouseMoveEvent& event) const;

        bool handle_mouse_button_event(MouseClickEvent& event) const;

        bool handle_close_window_event(WindowCloseEvent& event) const;

        bool handle_camera_update(class CameraUpdate& event) const;

        bool handle_keyboard_input(class KeyEvent& event) const;

    private:
        static vector_2 mouse_pos;

        static MouseButton pressed_button;
        static int32_t action;

        float ar;

        std::vector<rectangle> collision_boxes{};
        std::vector<std::string> frames;
        std::vector<uint32_t> frame_objects;
        uint32_t current_active;

        event_trigger trigger;
        ref_ptr<Window> window;
};