#pragma once

#include <bolt.hpp>

using namespace bolt;

class TestLayer : public LayerInterface {
    public:
        explicit TestLayer(ref_ptr<Window> window);

        [[nodiscard]] static ref_ptr<TestLayer> create(ref_ptr<Window> window);

        virtual ~TestLayer() override = default;

        void frame() const override;

        void bind_event_trigger(event_trigger trigger) override;

        void on_event(Event& e) const override;

        [[nodiscard]] bool handle_window_close(WindowCloseEvent& e) const;

        [[nodiscard]] bool handle_view_mat(class CameraUpdate& e) const;

    private:
        event_trigger trigger;
        ref_ptr<Window> window;
        ref_ptr<RendererGL> renderer;
};
