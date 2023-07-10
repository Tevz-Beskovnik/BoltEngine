#pragma once

#include <primitives.hpp>
#include <structs.hpp>

namespace bolt {
    class ModelInterface {
        public:
            virtual ~ModelInterface() { ; };

            virtual void move_model(const vector_3& position) noexcept = 0;

            virtual void transform_model(const matrix_4& transformation) noexcept = 0;

            virtual void rotate_model(vector_3 rotation_vector) noexcept = 0;

            virtual ref_ptr<ModelInterface> add_model(const ref_ptr<ModelInterface>& model) = 0;

            virtual void apply_lighting() = 0;

            [[nodiscard]] virtual uint32_t polygon_count() const noexcept = 0;

            [[nodiscard]] virtual const std::vector<AttributeLayout>& get_attribute_layout() const noexcept = 0;

            [[nodiscard]] virtual const std::vector<float>& get_drawable_vector() const noexcept = 0;

            [[nodiscard]] virtual const std::vector<uint32_t>& get_index_buffer() const noexcept = 0;

            [[nodiscard]] virtual const std::vector<polygon>& get_polygons() const noexcept = 0;
    };
}