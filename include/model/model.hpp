#pragma once

#include "core.hpp"
#include "colors.hpp"
#include "util.hpp"
#include "primitives.hpp"

namespace bolt
{
    struct polygon
    {
        vector_3 vert[3];
        vector_2 UV[3];
        vector_3 normal;
    };

    class Model
    {
        public:
            [[nodiscard]] Model(const std::vector<polygon>& mesh);

            [[nodiscard]] static ref_ptr<Model> create(const std::vector<polygon>& mesh);

            void move_model(vector_3 position) noexcept;

            void transform_model(matrix_4 transformation) noexcept;

            void rotate_model(vector_3 rotation_vector) noexcept;

            void apply_lighting();
        private:
            void apply_transformation(matrix_4 *mat);

            void recalculate_normals();

            [[nodiscard]] static vector_3 calculate_normal(polygon triangle);

            std::vector<polygon> mesh;
            RGB color;
    };
}