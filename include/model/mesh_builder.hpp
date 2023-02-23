#pragma once

#include <model.hpp>

namespace bolt
{
    class MeshBuilder
    {
    public:
        MeshBuilder();

        [[nodiscard]] static Model read_model(std::string file_path);

        [[nodiscard]] static Model make_quad(vector_2 corner, vector_2 dimensions);

        [[nodiscard]] static Model make_triangle(double x1, double y1, double x2, double y2, double x3, double y3);

        [[nodiscard]] static Model make_cube(vector_2 center, vector_3 dimensions);

        [[nodiscard]] static Model make_sphere(vector_2 center, double radius);

    private:
        [[nodiscard]] static Model read_obj(std::string file_path);

        [[nodiscard]] static Model read_collada(std::string file_path);

        [[nodiscard]] static Model read_stl(std::string file_path);

        [[nodiscard]] static Model read_fbx(std::string file_path);
    };
}