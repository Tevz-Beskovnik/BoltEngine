#pragma once

#include "core.hpp"
#include "colors.hpp"
#include "util.hpp"
#include "primitives.hpp"

namespace bolt
{
    class Model
    {
        public:
            [[nodiscard]] Model();

            [[nodiscard]] explicit Model(const std::vector<polygon>& mesh);

            [[nodiscard]] static ref_ptr<Model> create(const std::vector<polygon>& mesh);

            void set_mesh(const std::vector<polygon>& mesh);

            void move_model(const vector_3& position) noexcept;

            void transform_model(const matrix_4& transformation) noexcept;

            void rotate_model(vector_3 rotation_vector) noexcept;

            void apply_lighting();
    private:
            void recalculate_normals();

            [[nodiscard]] static vector_3 calculate_normal(polygon triangle);

            std::vector<polygon> mesh;
            RGB color;
    };
}