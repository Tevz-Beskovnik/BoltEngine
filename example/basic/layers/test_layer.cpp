//
// Created by Tevz on 17/04/2023.
//

#include <test_layer.hpp>

static RGB color(189, 240, 180);

static matrix_4 view_mat;

void binding_func(uint32_t program)
{
    int uColor = glGetUniformLocation(program, "uColor");

    int uViewMat = glGetUniformLocation(program, "uViewMat");

    color.set_r(color.r+1);
    color.set_g(color.g+1);
    color.set_b(color.b+1);

    std::cout << view_mat.to_string() << std::endl;

    glUniform3f(uColor, color.r_dec, color.g_dec, color.b_dec);

    glUniformMatrix4dv(uViewMat, 1, GL_FALSE, &view_mat.m[0][0]);
}

TestLayer::TestLayer(ref_ptr<Window> window)
    :window(window)
{
    shader_config_gl s_vert {
        .shader_location = "/Users/tevz/Documents/programing/BoltEngine/example/shaders/vert.glsl",
        .type = GL_VERTEX_SHADER
    };

    shader_config_gl s_frag {
        .shader_location = "/Users/tevz/Documents/programing/BoltEngine/example/shaders/frag.glsl",
        .type = GL_FRAGMENT_SHADER
    };

    auto model = MeshBuilder::read_model("/Users/tevz/Documents/programing/BoltEngine/example/models/room1.obj", OBJ); // MeshBuilder::make_triangle(0.5f, -0.5f, -0.5f, -0.5f, 0.0f, 0.5f);
    model->move_model({0.0f, 0.0f, 3.0f});

    render_config_gl r_conf = {
        .shader_config = {s_vert, s_frag},
        .texture_config = {},
        .model = model, // , // MeshBuilder::make_quad({-0.6f, -0.6f}, {0.5f, 0.5f})->add_model(MeshBuilder::make_quad({0.1f, 0.1f}, {0.5f, 0.5f})),
        .shader_bindings = binding_func,
        .instances = 1,
        .draw_type = GL_TRIANGLES,
        .offset = 0
    };

    renderer = RendererGL::create(r_conf);
}

[[nodiscard]] ref_ptr<TestLayer> TestLayer::create(ref_ptr<Window> window)
{
    return create_ref<TestLayer>(window);
}

void TestLayer::frame() const
{
    window->window_frame_routine();

    renderer->render();

    window->window_cleanup_routine();
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
    //view_mat = e.get_view_matrix();
    view_mat = matrix_4{
        0.75, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1.0001, 1,
        0, -3, 7.90079, 8
    };

    return false;
}

[[nodiscard]] bool TestLayer::handle_window_close(WindowCloseEvent& e) const
{
    std::cout << "Window is closing" << std::endl;

    StopAppEvent event;
    trigger(event);

    return true;
}
