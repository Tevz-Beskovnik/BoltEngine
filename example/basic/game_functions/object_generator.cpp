#include <object_generator.hpp>
#include <utility>

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

    return ObjectCreator::lines(mesh, RGB(255, 255, 255, 70), "../example/shaders/frag_lines.glsl", "../example/shaders/vert_lines.glsl");
}

void create_frames(std::vector<uint32_t>& object_frames, const std::vector<std::string>& frames, std::vector<rectangle>& collision_boxes, Scene& scene, float ar)
{
    for(uint8_t i = 0; i < 14; i+=2)
    {
        auto object_one = ObjectCreator::quad(vector_3{0.85f, (0.87f - i * 0.06f), 0.0f}, vector_2{0.05f, (0.05f * ar)}, "../example/shaders/frag_flat.glsl", "../example/shaders/vert_flat.glsl");

        object_one->add_binding_func([](uint32_t program){
            RGB color(255, 255, 255, 125); // TODO there has to be a better way of doing this but for now this is ok

            glUniform4f(glGetUniformLocation(program, "uCol"), color.r_dec, color.g_dec, color.b_dec, color.a_dec);
        });

        object_one->add_texture(frames[i]);

        object_frames.push_back(scene.add_object(object_one));

        collision_boxes.push_back(rectangle{
                .pos = vector_2{0.85, (0.87f - i * 0.06f)},
                .dims = vector_2{0.05f, (0.05f * ar)}
        });

        auto object_two = ObjectCreator::quad(vector_3{0.92f, (0.87f - i * 0.06f), 0.0f}, vector_2{0.05f, (0.05f * ar)}, "../example/shaders/frag_flat.glsl", "../example/shaders/vert_flat.glsl");

        object_two->add_binding_func([](uint32_t program){
            RGB color(255, 255, 255, 125); // TODO there has to be a better way of doing this but for now this is ok

            glUniform4f(glGetUniformLocation(program, "uCol"), color.r_dec, color.g_dec, color.b_dec, color.a_dec);
        });

        object_two->add_texture(frames[i+1]);

        object_frames.push_back(scene.add_object(object_two));

        collision_boxes.push_back(rectangle{
                .pos = vector_2{0.92f, (0.87f - i * 0.06f)},
                .dims = vector_2{0.05f, (0.05f * ar)}
        });
    }
}

uint32_t create_full_frame(const std::string& texture, const rectangle& rect, Scene& scene)
{
    auto full_frame = ObjectCreator::quad({rect.pos.x, rect.pos.y, 0.0f}, {rect.dims.x, rect.dims.y}, "../example/shaders/frag_flat.glsl", "../example/shaders/vert_flat.glsl");

    full_frame->add_texture(texture);

    full_frame->add_binding_func([](uint32_t program){
        RGB color(255, 255, 255, 255); // TODO there has to be a better way of doing this but for now this is ok

        glUniform4f(glGetUniformLocation(program, "uCol"), color.r_dec, color.g_dec, color.b_dec, color.a_dec);
    });

    return scene.add_object(full_frame);
}

uint32_t create_transparent_frame(const std::string& texture, const rectangle& rect, Scene& scene)
{
    auto full_frame = ObjectCreator::quad({rect.pos.x, rect.pos.y, 0.0f}, {rect.dims.x, rect.dims.y}, "../example/shaders/frag_flat.glsl", "../example/shaders/vert_flat.glsl");

    full_frame->add_texture(texture);

    full_frame->add_binding_func([](uint32_t program){
        RGB color(255, 255, 255, 125); // TODO there has to be a better way of doing this but for now this is ok

        glUniform4f(glGetUniformLocation(program, "uCol"), color.r_dec, color.g_dec, color.b_dec, color.a_dec);
    });

    auto itr = scene.add_object(full_frame);

    return itr;
}