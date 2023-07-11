#pragma once

#include <model.hpp>
#include <util.hpp>
#include <colors.hpp>
#include <primitives.hpp>
#include <file_system.hpp>
#include <font.hpp>
#include <wrong_file_extension_exception.hpp>

namespace bolt
{
    enum model_standard{
        OBJ = 0,
        COLLADA = 1,
        STL = 2,
        FBX = 3,
    };

    class MeshBuilder
    {
        public:
            [[nodiscard]] static ref_ptr<Model> read_model(const_str file_path, model_standard file_standard);

            [[nodiscard]] static ref_ptr<Model> make_quad(vector_3 corner, vector_2 dimensions);

            [[nodiscard]] static ref_ptr<Model> make_triangle(float x1, float y1, float x2, float y2, float x3, float y3);

            [[nodiscard]] static ref_ptr<Model> make_cube(vector_3 dimensions);

            [[nodiscard]] static ref_ptr<Model> make_sphere(vector_2 center, float radius);

            [[nodiscard]] static ref_ptr<Model> make_text(const std::string& text, const ref_ptr<Font>& font);

        private:
            MeshBuilder();

            [[nodiscard]] static ref_ptr<Model> read_obj(const_str file_path);

            [[nodiscard]] static ref_ptr<Model> read_collada(const_str file_path);

            [[nodiscard]] static ref_ptr<Model> read_stl(const_str file_path);

            [[nodiscard]] static ref_ptr<Model> read_fbx(const_str file_path);
    };
}