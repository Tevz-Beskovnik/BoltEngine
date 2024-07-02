#pragma once

#include <primitives.hpp>
#include <structs.hpp>

namespace bolt {
    class ModelInterface {
        public:
            ModelInterface(std::vector<vector_3> vertices, std::vector<vector_2> UVs, std::vector<vector_3> normals, std::vector<uint32_t> indices);

            virtual ~ModelInterface() { ; };

            virtual void move_model(const vector_3& position) noexcept = 0;

            virtual void transform_model(const matrix_4& transformation) noexcept = 0;

            virtual void rotate_model(vector_3 rotation_vector) noexcept = 0;

            virtual ref_ptr<ModelInterface> add_model(const ref_ptr<ModelInterface>& model) = 0;

            virtual void apply_lighting() = 0;

            [[nodiscard]] virtual uint32_t vertices_count() const noexcept = 0;

            [[nodiscard]] const std::vector<attribute_layout>& get_attribute_layout() const noexcept;

            [[nodiscard]] const std::vector<float>& get_drawable_vector() const noexcept;

            [[nodiscard]] const std::vector<uint32_t>& get_index_buffer() const noexcept;

            [[nodiscard]] const std::vector<vector_3>& get_vertices() const noexcept;

            [[nodiscard]] const std::vector<vector_2>& get_UVs() const noexcept;

            [[nodiscard]] const std::vector<vector_3>& get_normals() const noexcept;

        protected:
            std::vector<vector_3> vertices;
            std::vector<vector_2> UVs;
            std::vector<vector_3> normals;
            std::vector<uint32_t> indices;
            std::vector<float> drawable_vector;
            std::vector<attribute_layout> attrib_layout;
    };
}