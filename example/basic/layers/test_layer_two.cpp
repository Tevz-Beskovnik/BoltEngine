//
// Created by tevz on 11.7.2023.
//

#include <test_layer_two.hpp>

TestLayerTwo::TestLayerTwo(ref_ptr<Window> window)
    :window(window)
{
    std::vector<vector_3> bottom_grid;
    for(int32_t i = -4; i < 5; i++)
    {
        bottom_grid.push_back({static_cast<float>(i), -4, -4});
        bottom_grid.push_back({static_cast<float>(i), -4, 4});
    }

    for(int32_t i = -4; i < 5; i++)
    {
        bottom_grid.push_back({-4, -4, static_cast<float>(i)});
        bottom_grid.push_back({4, -4, static_cast<float>(i)});
    }

    uint32_t pos = scene.add_object(ObjectCreator::lines(bottom_grid, RGB(255, 255, 255, 255), "../../example/shaders/frag_lines.glsl", "../../example/shaders/vert_lines.glsl"));

    std::cout << pos << std::endl;
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
