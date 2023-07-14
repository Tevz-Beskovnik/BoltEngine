#include <object_generator.hpp>

ref_ptr<RenderInterface> generate_3d_grid()
{
    std::vector<vector_3> mesh;

    for(int32_t i = -4; i < 5; i++)
    {
        mesh.push_back({static_cast<float>(i), -4, -4});
        mesh.push_back({static_cast<float>(i), -4, 4});
    }

    for(int32_t i = -4; i < 5; i++)
    {
        mesh.push_back({-4, -4, static_cast<float>(i)});
        mesh.push_back({4, -4, static_cast<float>(i)});
    }

    for(int32_t i = -4; i < 5; i++)
    {
        mesh.push_back({-4, static_cast<float>(i), -4});
        mesh.push_back({-4, static_cast<float>(i), 4});
    }

    for(int32_t i = -4; i < 5; i++)
    {
        mesh.push_back({-4, 4,static_cast<float>(i)});
        mesh.push_back({-4, -4,static_cast<float>(i)});
    }

    for(int32_t i = -4; i < 5; i++)
    {
        mesh.push_back({-4, static_cast<float>(i), -4});
        mesh.push_back({4, static_cast<float>(i), -4});
    }

    for(int32_t i = -4; i < 5; i++)
    {
        mesh.push_back({static_cast<float>(i), -4, -4});
        mesh.push_back({static_cast<float>(i), 4, -4});
    }

    return ObjectCreator::lines(mesh, RGB(255, 255, 255, 70), "../../example/shaders/frag_lines.glsl", "../../example/shaders/vert_lines.glsl");
}