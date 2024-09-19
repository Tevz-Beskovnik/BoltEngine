#include <window.hpp>

// TODO: lack of mutex locks might cause crashing here :>

namespace bolt
{
    [[nodiscard]] Window::Window(const window_config& config)
        :background_color(new RGB()), background_color_owned(true), width(config.width), height(config.height), title((basic_str)config.title)
    {
        if (!glfwInit())
            BOLT_ERROR(SetupException("Failed to initialise GLFW"));

        BOLT_LOG_INFO("GLFW initialised")

        std::cout << "hello5" << std::endl;

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

        set_active();

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if(config.fullscreen)
            fullscreen();
    }

    Window::~Window()
    {
        delete caller;
    }

    [[nodiscard]] ref_ptr<Window> Window::create(const window_config& config)
    {
        ASSERT_NE(strlen(config.title), 0, "Title cannot be null len");
        ASSERT(!(config.height == 0 || config.width == 0), "Width and height cannot be 0");

        return create_ref<Window>(config);
    }

    void Window::resize_window(uint16_t width, uint16_t height)
    {
        this->width = width;
        this->height = height;
        BOLT_LOG_INFO("Resizing window");
        glfwSetWindowSize(window, width, height);
    }

    void Window::get_size(uint16_t *set_width, uint16_t *set_height)
    {
        lock();
        int s_width, s_height;
        glfwGetWindowSize(window, &s_width, &s_height);
        *set_width = s_width;
        *set_height = s_height;
        unlock();
    }

    void Window::fullscreen()
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

    void Window::windowed(uint16_t width, uint16_t height)
    {
        this->width = width;
        this->height = height;

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

    void Window::windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y)
    {
        this->width = width;
        this->height = height;

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

    void Window::frame_routine()
    {
        lock();

        glClearColor(background_color->r_dec, background_color->g_dec, background_color->b_dec, background_color->a_dec);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        unlock();
    }

    void Window::register_event_trigger(event_trigger trigger)
    {
        this->trigger = trigger;

        caller = new EventCaller(trigger);

        set_event_caller();
    }

    void Window::set_event_caller()
    {
        glfwSetWindowUserPointer(window, caller);

        // TODO decide what kind of input handeling to use direct or event based
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods); // if you overload the callback you also have to register the imgui impl callbacks
            static_cast<EventCaller*>(glfwGetWindowUserPointer(window))->call_keyboard_event(key, scancode, action, mods);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window){
            static_cast<EventCaller*>(glfwGetWindowUserPointer(window))->call_window_close_event();
        });

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height){
            static_cast<EventCaller*>(glfwGetWindowUserPointer(window))->call_window_resize_event(width, height);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods){
            ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
            static_cast<EventCaller*>(glfwGetWindowUserPointer(window))->call_mouse_event(button, action, mods);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x_pos, double y_pos){
            ImGui_ImplGlfw_CursorPosCallback(window, x_pos, y_pos);
            static_cast<EventCaller*>(glfwGetWindowUserPointer(window))->call_mouse_position_event(x_pos, y_pos);
        });
    }

    void Window::cleanup_routine()
    {
        lock();
        glfwSwapBuffers(window);
        unlock();
    }

    void Window::set_background_color(RGB* color)
    {
        lock();

        if(background_color_owned)
            delete background_color;

        background_color = color;
        background_color_owned = false;

        unlock();
    }

    void Window::hide_cursor()
    {
        lock();
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        unlock();
    }

    void Window::set_active()
    {
        lock();
        glfwMakeContextCurrent(window);
        unlock();

        BOLT_LOG_INFO("Set context to window")

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_FRONT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    [[nodiscard]] bool Window::is_window_open() const
    {
        return !glfwWindowShouldClose(window);
    }

    void Window::close()
    {
        glfwDestroyWindow(window);
    }

    void Window::lock()
    {
        use_lock.lock();
    }

    void Window::unlock()
    {
        use_lock.unlock();
    }
}