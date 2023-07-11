#pragma once

#include <bolt.hpp>

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

    private:
        event_trigger trigger;
        ref_ptr<Window> window;
};