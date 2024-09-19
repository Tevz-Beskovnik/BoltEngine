#pragma once

#include <core.hpp>
#include <util.hpp>
#include <renderer_interface.hpp>
#include <threadex.hpp>
#include <scene.hpp>
#include <colors.hpp>
#include <window.hpp>

namespace bolt
{
    class Renderer : public Thread {
    public:
        explicit Renderer(const ref_ptr<Window> window);

        void add_scene(const ref_ptr<Scene> scene);

        void set_window(const ref_ptr<Window> window);

        void execute() override;

    private:
        ref_ptr<Window> window;
        std::vector<ref_ptr<Scene>> scenes;
    };
}
