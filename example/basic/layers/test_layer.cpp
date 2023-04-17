//
// Created by Tevz on 17/04/2023.
//

#include <test_layer.hpp>

static RGB color(189, 240, 180);

void binding_func(uint32_t program)
{
    int uColor = glGetUniformLocation(program, "uColor");

    color.set_r(color.r+1);
    color.set_g(color.g+1);
    color.set_b(color.b+1);

    glUniform3f(uColor, color.r_dec, color.g_dec, color.b_dec);
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

    render_config_gl r_conf = {
        .shader_config = {s_vert, s_frag},
        .texture_config = {},
        .model = MeshBuilder::make_quad({-0.6f, -0.6f}, {0.5f, 0.5f})->add_model(MeshBuilder::make_quad({0.1f, 0.1f}, {0.5f, 0.5f})),//MeshBuilder::make_triangle(0.5f, -0.5f, -0.5f, -0.5f, 0.0f, 0.5f),
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

    dispatcher.dispatch<WindowCloseEvent>(CAST_MEMBER_FUNCTION(TestLayer::handle_window_close));
}

[[nodiscard]] bool TestLayer::handle_window_close(WindowCloseEvent& e) const
{
    std::cout << "Window is closing" << std::endl;

    StopAppEvent event;
    trigger(event);

    return true;
}
