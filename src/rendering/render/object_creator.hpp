#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <mesh_builder.hpp>
#include <model.hpp>
#include <line_model.hpp>
#include <renderer_interface.hpp>
#include <renderer_gl.hpp>
#include <renderer_vk.hpp>
#include <colors.hpp>
#include <structs.hpp>

namespace bolt
{
    class ObjectCreator
    {
        public:
            [[nodiscard]] static ref_ptr<RenderInterface> lines(const std::vector<vector_3>& points, RGB color, const_str frag_shader, const_str vert_shader);

            static void add_lines(const std::vector<vector_3>& points, RGB color, const ref_ptr<RenderInterface>& renderer);

            [[nodiscard]] static ref_ptr<RenderInterface> cube(vector_3 pos, vector_3 dims, const_str frag_shader, const_str vert_shader);

            static void add_cube(vector_3 pos, vector_3 dims, const ref_ptr<RenderInterface>& renderer);

            [[nodiscard]] static ref_ptr<RenderInterface> quad(vector_3 pos, vector_2 dims, const_str frag_shader, const_str vert_shader);

            static void add_quad(vector_3 pos, vector_2 dims, const ref_ptr<RenderInterface>& renderer);

            [[nodiscard]] static ref_ptr<RenderInterface> model(const_str model_file, const_str frag_shader, const_str vert_shader);

            static void add_model(const_str model, const ref_ptr<RenderInterface>& renderer);

            static void set_render_framework(render_framework framework);

            static void set_uniform_binding_func(uniform_bindings binding_func);

        private:
            static uniform_bindings binding_func;

            static render_framework framework;

            ObjectCreator();
    };
}
