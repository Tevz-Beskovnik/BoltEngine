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
        std::vector<vector_3> vertices;
        std::vector<vector_2> UVs;
        std::vector<vector_3> normals;
        std::vector<uint32_t> indices;
    };

    class Model final : public ModelInterface
    {
        public:
            explicit Model(const model_config& config);

            ~Model() override;

            [[nodiscard]] static ref_ptr<Model> create(const model_config& config);

            [[nodiscard]] uint32_t vertices_count() const noexcept final;

            ref_ptr<ModelInterface> add_model(const ref_ptr<ModelInterface>& model) final;

            void move_model(const vector_3& position) noexcept final;

            void transform_model(const matrix_4& transformation) noexcept final;

            void rotate_model(vector_3 rotation_vector) noexcept final;

            void apply_lighting() final;

        private:
            ref_ptr<Model> instance;

            void recalculate_normals();

            void to_drawable_vector();

            void set_attribute_layout();

            [[nodiscard]] static vector_3 calculate_normal(vector_3 p1, vector_3 p2, vector_3 p3);
    };
}