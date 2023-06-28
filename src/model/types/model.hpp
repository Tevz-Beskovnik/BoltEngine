#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <model_interface.hpp>

namespace bolt
{
    struct model_config
    {
        std::vector<polygon> mesh;
        std::vector<uint32_t> indices;
    };

    class Model final : public ModelInterface
    {
        public:
            explicit Model(model_config config);

            ~Model() override;

            [[nodiscard]] static ref_ptr<Model> create(model_config config);

            void set_mesh(const std::vector<polygon>& mesh);

            [[nodiscard]] const std::vector<float>& get_drawable_vector() const noexcept final;

            [[nodiscard]] const std::vector<uint32_t>& get_index_buffer() const noexcept final;

            [[nodiscard]] const std::vector<AttributeLayout>& get_attribute_layout() const noexcept final;

            [[nodiscard]] const std::vector<polygon>& get_polygons() const noexcept final;

            [[nodiscard]] uint32_t polygon_count() const noexcept final;

            ref_ptr<ModelInterface> add_model(const ref_ptr<ModelInterface>& model) final;

            void move_model(const vector_3& position) noexcept final;

            void transform_model(const matrix_4& transformation) noexcept final;

            void rotate_model(vector_3 rotation_vector) noexcept final;

            void apply_lighting() final;

            void print() const;

        private:
            std::vector<polygon> mesh;
            std::vector<uint32_t> indices;
            std::vector<float> drawable_vector;
            std::vector<AttributeLayout> attribute_layout;
            ref_ptr<Model> instance;
            RGB color;

            void recalculate_normals();

            void to_drawable_vector();

            void set_attribute_layout();

            [[nodiscard]] static vector_3 calculate_normal(polygon triangle);
    };
}