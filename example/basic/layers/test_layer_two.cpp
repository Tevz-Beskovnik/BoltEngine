//
// Created by tevz on 11.7.2023.
//

#include <test_layer_two.hpp>

TestLayerTwo::TestLayerTwo(ref_ptr<Window> window)
    :window(window)
{
    std::vector<vector_3> lines = {
        {-2.0, -2.0, -2.0},
        {-2.0, -2.0, 2.0},
        {-2.0, -2.0, 2.0},
        {2.0, -2.0, 2.0},
        {2.0, -2.0, 2.0},
        {2.0, -2.0, -2.0},
        {2.0, -2.0, -2.0},
        {-2.0, -2.0, -2.0}
    };

    scene.add_object(ObjectCreator::lines(lines, RGB(255, 255, 255, 125), "../../example/shaders/vert_lines.glsl", "../../example/shaders/frag_lines.glsl"));
}

[[nodiscard]] ref_ptr<TestLayerTwo> TestLayerTwo::create(ref_ptr<Window> window)
{
    return create_ref<TestLayerTwo>(window);
}

void TestLayerTwo::frame()
{

}

void TestLayerTwo::bind_event_trigger(event_trigger trigger)
{
    this->trigger = trigger;
}

void TestLayerTwo::on_event(Event& e) const
{
    EventDispatcher dispatcher(e);
}
