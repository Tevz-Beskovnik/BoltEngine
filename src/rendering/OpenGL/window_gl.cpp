#include <window_gl.hpp>

namespace bolt 
{
    [[nodiscard]] WindowGL::WindowGL(uint16_t width, uint16_t height, const_str title = "[Untitled]")
        :background_color(new RGB()), background_color_owned(true)
    {
        if (!glfwInit())
            BOLT_ERROR(SetupException("Failed to initialise GLFW"))

        BOLT_LOG_INFO("GLFW initialised")

        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        BOLT_LOG_INFO("Creating window")

        window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);

        Keyboard::set_window(window);
        Mouse::set_window(window);

        if(window == NULL)
        {
            glfwTerminate();
            BOLT_ERROR(SetupException("Failed to initialize window"))
        }

        glfwMakeContextCurrent(window);

        BOLT_LOG_INFO("Set context to window")

        if(glewInit() != GLEW_OK)
            BOLT_ERROR(SetupException("GLEW failed to init"))

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 150");
    }

    [[nodiscard]] single_ptr<WindowGL> WindowGL::create(uint16_t width, uint16_t height, const_str title)
    {
        BOLT_LOG_INFO("Creating window")
        return create_single<WindowGL>(width, height, title);
    }

    void WindowGL::resize_window(uint16_t width, uint16_t height)
    {
        BOLT_LOG_INFO("Resizing window")
        glfwSetWindowSize(window, width, height);
    }

    void WindowGL::fullscreen()
    {
        BOLT_LOG_INFO("Seting window to fullscreen")

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
        BOLT_LOG_INFO("Seting window to windowed")
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
        BOLT_LOG_INFO("Seting window to windowed")
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
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(background_color->r_dec, background_color->g_dec, background_color->b_dec, background_color->a_dec);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void WindowGL::set_event_caller(EventCallerManagedPtr caller)
    {
        this->caller = caller;

        glfwSetWindowUserPointer(window, caller);

        // TODO decide what kind of input handeling to use direct or event based
        /*glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            static_cast<EventCallerManagedPtr>(glfwGetWindowUserPointer(window))->call_keyboard_event(key, scancode, action, mods);
        });*/

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window){
            static_cast<EventCallerManagedPtr>(glfwGetWindowUserPointer(window))->call_window_close_event();
        });

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height){
            static_cast<EventCallerManagedPtr>(glfwGetWindowUserPointer(window))->call_window_resize_event(width, height);
        });
    }

    void WindowGL::cleanup_routine()
    {
        glfwSwapBuffers(window);
    }

    void WindowGL::set_background_color(RGB* color)
    {
        if(background_color_owned)
            delete background_color;

        background_color = color;
        background_color_owned = false;
    }

    void WindowGL::hide_cursor() const
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void WindowGL::set_active()
    {
        glfwMakeContextCurrent(window);

        BOLT_LOG_INFO("Set context to window")

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_FRONT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        BOLT_LOG_INFO("GLEW initialised")
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