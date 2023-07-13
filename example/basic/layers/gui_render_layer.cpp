#include <gui_render_layer.hpp>

GuiRenderLayer::GuiRenderLayer(ref_ptr<Window> window)
    :window(window)
{
    ;
}

[[nodiscard]] ref_ptr<GuiRenderLayer> GuiRenderLayer::create(ref_ptr<Window> window)
{
    return create_ref<GuiRenderLayer>(window);
}

void GuiRenderLayer::frame()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiRenderLayer::bind_event_trigger(event_trigger trigger)
{
    this->trigger = trigger;
}

void GuiRenderLayer::on_event(Event& e) const
{
    EventDispatcher dispatcher(e);
}