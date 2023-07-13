//
// Created by tevz on 11.7.2023.
//

#include <test_layer_two.hpp>

TestLayerTwo::TestLayerTwo(ref_ptr<Window> window)
    :window(window)
{
    uint32_t pos = scene.add_object(generate_3d_grid());
}

[[nodiscard]] ref_ptr<TestLayerTwo> TestLayerTwo::create(ref_ptr<Window> window)
{
    return create_ref<TestLayerTwo>(window);
}

void TestLayerTwo::frame()
{
    scene.draw();
}

void TestLayerTwo::bind_event_trigger(event_trigger trigger)
{
    this->trigger = trigger;
}

void TestLayerTwo::on_event(Event& e) const
{
    EventDispatcher dispatcher(e);
}
