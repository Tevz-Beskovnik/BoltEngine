//
// Created by Tevz on 17/04/2023.
//

#include <test_layer.hpp>

static RGB color(189, 240, 180);

static matrix_4 view_mat;

static float u_time = 0.0;

static int _fpsCount = 0;
static int fps = 0; // this will store the final fps for the last second

static std::chrono::time_point<std::chrono::steady_clock> lastTime = std::chrono::steady_clock::now();

void binding_func(uint32_t program)
{
    int uColor = glGetUniformLocation(program, "uColor");

    int uTime = glGetUniformLocation(program, "uTime");

    int uViewMat = glGetUniformLocation(program, "uViewMat");

    u_time += 0.01;

    /*color.set_r(color.r+1);
    color.set_g(color.g+1);
    color.set_b(color.b+1);*/

    glUniform1f(uTime, u_time);

    glUniform3f(uColor, color.r_dec, color.g_dec, color.b_dec);

    glUniformMatrix4fv(uViewMat, 1, GL_TRUE, &view_mat.m[0][0]);
}

void CalculateFrameRate() {
    auto currentTime = std::chrono::steady_clock::now();

    const auto elapsedTime = duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
    ++_fpsCount;

    if (elapsedTime > 1000000000) {
        lastTime = currentTime;
        fps = _fpsCount;
        _fpsCount = 0;
    }
}

TestLayer::TestLayer(ref_ptr<Window> window)
    :window(window)
{
    shader_config_gl s_vert {
        .shader_location = "../../example/shaders/vert.glsl", // TODO localize all filepaths
        .type = GL_VERTEX_SHADER
    };

    shader_config_gl s_frag {
        .shader_location = "../../example/shaders/fragTex.glsl",
        .type = GL_FRAGMENT_SHADER
    };

    texture_config_gl town_tex {
        .type = bolt::TEXTURE_2D,
        .texture_location = "../../example/textures/TownColor.png"
    };

    auto model = MeshBuilder::make_cube({2,1,6});
    model->move_model({6.0f, 0.0f, 20.0f});

    render_config_gl r_conf = {
        .shader_config = {s_vert, s_frag},
        .texture_config = { town_tex },
        .model = model->add_model(MeshBuilder::read_model("../../example/models/town.obj", OBJ)), // , // MeshBuilder::make_quad({-0.6f, -0.6f}, {0.5f, 0.5f})->add_model(MeshBuilder::make_quad({0.1f, 0.1f}, {0.5f, 0.5f})),
        .shader_bindings = binding_func,
        .instances = 1,
        .draw_type = GL_TRIANGLES,
        .offset = 0
    };

    renderer = RendererGL::create(r_conf);

    create_lines(RGB(255.0f, 0, 255.0f, 255.0f), vector_3{0.5, 0.5, 0.0}, vector_3{0.5, -0.5, 0.0}, vector_3{-0.5, 0.5, 0.0}, vector_3{-0.5, -0.5, 0.0}, vector_3{0.5, -0.5, 0.0}, vector_3{-0.5, -0.5, 0.0})

    create_rect_shader(RGB(255.0f, 255.0f, 0.0f, 255.0f), "../../example/textures/wacky-code.png", rectangle{
        .pos = vector_2{-1, -1},
        .dims = vector_2{0.5, 1}
    })
    /*create_rects_c(RGB(255.0f, 255.0f, 0.0f, 255.0f), rectangle{
        .pos = vector_2{-1, -1},
        .dims = vector_2{0.5, 1}
    })*/
}

[[nodiscard]] ref_ptr<TestLayer> TestLayer::create(ref_ptr<Window> window)
{
    return create_ref<TestLayer>(window);
}

void TestLayer::frame() const
{
    window->cleanup_routine();
    window->frame_routine();

    renderer->render();

    draw_primitives;

    CalculateFrameRate();

    {
        ImGui::Begin("Box color editor");

        ImGui::Text("Adjust the color of the object");

        ImGui::Text("Fps: ");
        ImGui::SameLine();
        ImGui::Text("%s", std::to_string(fps).c_str());

        ImGui::SliderFloat("red", &color.r_dec, 0, 1);
        ImGui::SliderFloat("green", &color.g_dec, 0, 1);
        ImGui::SliderFloat("blue", &color.b_dec, 0, 1);

        ImGui::End();
    }

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void TestLayer::bind_event_trigger(bolt::event_trigger trigger)
{
    this->trigger = trigger;

    window->register_event_trigger(trigger); // TODO: This should be done somewhere inside of app somehow (reffer to context switching TODO)
}

void TestLayer::on_event(Event& e) const
{
    EventDispatcher dispatcher(e);

    dispatcher.dispatch<class CameraUpdate>(CAST_MEMBER_FUNCTION(TestLayer::handle_view_mat));
    dispatcher.dispatch<WindowCloseEvent>(CAST_MEMBER_FUNCTION(TestLayer::handle_window_close));
}

[[nodiscard]] bool TestLayer::handle_view_mat(class CameraUpdate& e) const
{
    view_mat = e.get_view_matrix();

    return false;
}

[[nodiscard]] bool TestLayer::handle_window_close(WindowCloseEvent& e) const
{
    std::cout << "Window is closing" << std::endl;

    StopAppEvent event;
    trigger(event);

    return true;
}
