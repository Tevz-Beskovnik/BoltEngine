#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <primitives.hpp>
#include <util.hpp>
#include <model_interface.hpp>

namespace bolt
{
    class Line final : public ModelInterface
    {
        public:
            Line(const std::vector<vector_3>& points, RGB color);

            ~Line() override;

            [[nodiscard]] static ref_ptr<Line> create(const std::vector<vector_3>& points, RGB color);

            [[nodiscard]] uint32_t vertices_count() const noexcept final;

            ref_ptr<ModelInterface> add_model(const ref_ptr<ModelInterface>& model) final;

            void move_model(const vector_3& position) noexcept final;

            void transform_model(const matrix_4& transformation) noexcept final;

            void rotate_model(vector_3 rotation_vector) noexcept final;

            void apply_lighting() final;

        private:
            std::vector<RGB> color;
            ref_ptr<Line> instance;

            void recalculate_normals();

            void to_drawable_vector();

            void set_attribute_layout();

            [[nodiscard]] static vector_3 calculate_normal(polygon triangle);
    };
}