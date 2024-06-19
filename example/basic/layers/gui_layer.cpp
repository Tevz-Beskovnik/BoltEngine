//
// Created by Tevz on 17/04/2023.
//

#include <gui_layer.hpp>

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

GuiLayer::GuiLayer(ref_ptr<Window> window)
    :window(window)
{
    ObjectCreator::set_uniform_binding_func(binding_func);
}

[[nodiscard]] ref_ptr<GuiLayer> GuiLayer::create(ref_ptr<Window> window)
{
    return create_ref<GuiLayer>(window);
}

void GuiLayer::frame()
{

    /*CalculateFrameRate();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

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

    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
}

void GuiLayer::bind_event_trigger(bolt::event_trigger trigger)
{
    this->trigger = trigger;
}

void GuiLayer::on_event(Event& e) const
{
    EventDispatcher dispatcher(e);

    dispatcher.dispatch<class CameraUpdate>(CAST_MEMBER_FUNCTION(GuiLayer::handle_view_mat));
    dispatcher.dispatch<WindowCloseEvent>(CAST_MEMBER_FUNCTION(GuiLayer::handle_window_close));
}

[[nodiscard]] bool GuiLayer::handle_view_mat(class CameraUpdate& e) const
{
    view_mat = e.get_view_matrix();

    return false;
}

[[nodiscard]] bool GuiLayer::handle_window_close(WindowCloseEvent& e) const
{
    std::cout << "Window is closing" << std::endl;

    StopAppEvent event;
    trigger(event);

    return true;
}