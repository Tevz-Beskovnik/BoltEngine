#pragma once

#include "core.hpp"
#include "colors.hpp"
#include "util.hpp"
#include "primitives.hpp"

namespace bolt
{
    enum model_standard{
        OBJ = 0,
        COLLADA = 1,
        STL = 2,
        FBX = 3,
    };

    struct polygon
    {
        vector_3 vert[3];
        vector_2 UV[3];
        RGB color;
        vector_3 normal;
    };

    class Model
    {
        public:
            Model();

            [[nodiscard]] ref_ptr<Model> create(ref_ptr<std::vector<polygon>> mesh);

            void move_model(vector_3 position) noexcept;

            void transform_model(matrix_4 transformation) noexcept;

            void rotate_model(vector_3 rotation_vector) noexcept;

            void apply_lighting();
        private:
            void apply_transformation(matrix_4 *mat);

            ref_ptr<std::vector<polygon>> mesh;
    };
}