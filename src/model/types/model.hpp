#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <model_interface.hpp>

namespace bolt
{
    class Model : public ModelInterface
    {
        public:
            explicit Model(std::vector<polygon> mesh);

            ~Model() override;

            [[nodiscard]] static ref_ptr<Model> create(std::vector<polygon> mesh);

            void set_mesh(const std::vector<polygon>& mesh);

            [[nodiscard]] const std::vector<double>& get_drawable_vector() const noexcept override;

            [[nodiscard]] const std::vector<AttributeLayout>& get_attribute_layout() const noexcept override;

            [[nodiscard]] uint32_t polygon_count() const noexcept override;

            void move_model(const vector_3& position) noexcept override;

            void transform_model(const matrix_4& transformation) noexcept override;

            void rotate_model(vector_3 rotation_vector) noexcept override;

            void apply_lighting() override;

        private:
            std::vector<polygon> mesh;
            std::vector<double> drawable_vector;
            std::vector<AttributeLayout> attribute_layout;
            RGB color;

            void recalculate_normals();

            void to_drawable_vector();

            void set_attribute_layout();

            [[nodiscard]] static vector_3 calculate_normal(polygon triangle);
    };
}