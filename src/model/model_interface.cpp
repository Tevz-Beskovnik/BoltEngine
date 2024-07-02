#include <model_interface.hpp>

namespace bolt
{
    ModelInterface::ModelInterface(std::vector<vector_3> vertices, std::vector<vector_2> UVs, std::vector<vector_3> normals, std::vector<uint32_t> indices)
        :vertices(std::move(vertices)), UVs(std::move(UVs)), normals(std::move(normals)), indices(std::move(indices))
    {
        ;
    }

    [[nodiscard]] const std::vector<attribute_layout>& ModelInterface::get_attribute_layout() const noexcept
    {
        return attrib_layout;
    }

    [[nodiscard]] const std::vector<float>& ModelInterface::get_drawable_vector() const noexcept
    {
        return drawable_vector;
    }

    [[nodiscard]] const std::vector<uint32_t>& ModelInterface::get_index_buffer() const noexcept
    {
        return indices;
    }

    [[nodiscard]] const std::vector<vector_3>& ModelInterface::get_vertices() const noexcept
    {
        return vertices;
    }

    [[nodiscard]] const std::vector<vector_2>& ModelInterface::get_UVs() const noexcept
    {
        return UVs;
    }

    [[nodiscard]] const std::vector<vector_3>& ModelInterface::get_normals() const noexcept
    {
        return normals;
    }
}