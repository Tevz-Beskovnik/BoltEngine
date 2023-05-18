#include <window_gl.hpp>

namespace bolt 
{
    [[nodiscard]] WindowGL::WindowGL(uint16_t width, uint16_t height, const_str title = "[Untitled]")
        :background_color(new RGB()), background_color_owned(true)
    {
        if (!glfwInit())
            BOLT_ERROR(std::runtime_error("Failed to initialise GLFW"))

        BOLT_MSG_DEBUG("GLFW initialised")

        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        BOLT_MSG_DEBUG("Creating window")

        window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);

        if(window == NULL)
        {
            glfwTerminate();
            BOLT_ERROR("Failed to initialize window")
        }

        glfwMakeContextCurrent(window);

        BOLT_MSG_DEBUG("Set context to window")

        if(glewInit() != GLEW_OK)
            BOLT_ERROR("GLEW failed to init")


    }

    [[nodiscard]] single_ptr<WindowGL> WindowGL::create(uint16_t width, uint16_t height, const_str title)
    {
        BOLT_MSG_DEBUG("Creating window")
        return create_single<WindowGL>(width, height, title);
    }

    void WindowGL::resize_window(uint16_t width, uint16_t height)
    {
        BOLT_MSG_DEBUG("Resizing window")
        glfwSetWindowSize(window, width, height);
    }

    void WindowGL::fullscreen()
    {
        BOLT_MSG_DEBUG("Seting window to fullscreen")

        int width, height;

        glfwGetWindowSize(window , &width, &height);

        glfwSetWindowMonitor(
            window,
            glfwGetPrimaryMonitor(),
            0,
            0,
            width,
            height,
            GLFW_DONT_CARE
        );
    }

    void WindowGL::windowed(uint16_t width, uint16_t height)
    {
        BOLT_MSG_DEBUG("Seting window to windowed")
        glfwSetWindowMonitor(
            window,
            NULL,
            0,
            0,
            width,
            height,
            GLFW_DONT_CARE
        );
    }

    void WindowGL::windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y)
    {
        BOLT_MSG_DEBUG("Seting window to windowed")
        glfwSetWindowMonitor(
            window,
            NULL,
            x,
            y,
            width,
            height,
            GLFW_DONT_CARE
        );
    }

    void WindowGL::frame_routine()
    {
        glClearColor(background_color->r_dec, background_color->g_dec, background_color->b_dec, background_color->a_dec);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void WindowGL::cleanup_routine()
    {
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    void WindowGL::set_background_color(RGB* color)
    {
        if(background_color_owned)
            delete background_color;

        background_color = color;
        background_color_owned = false;
    }

    void WindowGL::set_active()
    {
        glfwMakeContextCurrent(window);

        BOLT_MSG_DEBUG("Set context to window")

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_FRONT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        BOLT_MSG_DEBUG("GLEW initialised")
    }

    [[nodiscard]] bool WindowGL::should_close()
    {
        return !glfwWindowShouldClose(window);
    }

    void WindowGL::close()
    {
        glfwDestroyWindow(window);
    }
}