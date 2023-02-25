#pragma once

#include <model.hpp>
#include <util.hpp>
#include <colors.hpp>
#include <primitives.hpp>
#include <file_system.hpp>

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
            MeshBuilder();

            [[nodiscard]] static ref_ptr<Model> read_model(const_str file_path, model_standard file_standard);

            [[nodiscard]] static ref_ptr<Model> make_quad(vector_2 corner, vector_2 dimensions);

            [[nodiscard]] static ref_ptr<Model> make_triangle(double x1, double y1, double x2, double y2, double x3, double y3);

            [[nodiscard]] static ref_ptr<Model> make_cube(vector_2 center, vector_3 dimensions);

            [[nodiscard]] static ref_ptr<Model> make_sphere(vector_2 center, double radius);

        private:
            [[nodiscard]] static ref_ptr<Model> read_obj(const_str file_path);

            [[nodiscard]] static ref_ptr<Model> read_collada(const_str file_path);

            [[nodiscard]] static ref_ptr<Model> read_stl(const_str file_path);

            [[nodiscard]] static ref_ptr<Model> read_fbx(const_str file_path);
    };
}