#pragma once

#include <bolt.hpp>

using namespace bolt;

class GuiLayer final : public LayerInterface {
    public:
        explicit GuiLayer(ref_ptr<Window> window);

        [[nodiscard]] static ref_ptr<GuiLayer> create(ref_ptr<Window> window);

        virtual ~GuiLayer() override = default;

        void frame() final;

        void bind_event_trigger(event_trigger trigger) final;

        void on_event(Event& e) const final;

        [[nodiscard]] bool handle_window_close(WindowCloseEvent& e) const;

        [[nodiscard]] bool handle_view_mat(class CameraUpdate& e) const;

    private:
        setup_primitives;

        bool pressed = false;

        float pitch;
        float yaw;

        event_trigger trigger;
        ref_ptr<Window> window;
        ref_ptr<RendererGL> renderer;
};
