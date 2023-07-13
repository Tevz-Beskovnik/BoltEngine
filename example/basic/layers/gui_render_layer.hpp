#include <bolt.hpp>

using namespace bolt;

class GuiRenderLayer final : public LayerInterface {
    public:
        explicit GuiRenderLayer(ref_ptr<Window> window);

        [[nodiscard]] static ref_ptr<GuiRenderLayer> create(ref_ptr<Window> window);

        virtual ~GuiRenderLayer() override = default;

        void frame() final;

        void bind_event_trigger(event_trigger trigger) final;

        void on_event(Event& e) const final;

    private:
        event_trigger trigger;
        ref_ptr<Window> window;
};
