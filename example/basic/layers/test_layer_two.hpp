#pragma once

#include <bolt.hpp>
#include <object_generator.hpp>

using namespace bolt;

class TestLayerTwo final : public LayerInterface
{
    public:
        explicit TestLayerTwo(ref_ptr<Window> window);

        [[nodiscard]] static ref_ptr<TestLayerTwo> create(ref_ptr<Window> window);

        virtual ~TestLayerTwo() override = default;

        void frame() final;

        void bind_event_trigger(event_trigger trigger) final;

        void on_event(Event& e) const final;

        bool handle_mouse_position_event(MouseMoveEvent& event) const;

        bool handle_mouse_button_event(MouseClickEvent& event) const;

    private:
        setup_primitives;

        static vector_2 mouse_pos;

        static MouseButton pressed_button;
        static int32_t action;

        float ar;

        event_trigger trigger;
        ref_ptr<Window> window;
};