#include <model.hpp>

namespace bolt
{
    [[nodiscard]] Model::Model()
    = default;

    [[nodiscard]] Model::Model(const std::vector<polygon>& mesh)
        :mesh(mesh)
    {
        ;
    }

    [[nodiscard]] ref_ptr<Model> Model::create(const std::vector<polygon>& mesh)
    {
        return create_ref<Model>(mesh);
    }

    void Model::set_mesh(const std::vector<polygon>& new_mesh)
    {
        mesh = new_mesh;
    }

    void Model::transform_model(const matrix_4& mat) noexcept
    {
        #pragma omp parallel for
        for(uint64_t i = 0; i < mesh.size(); i++)
        {
            mesh[i].vert[0] = mat * mesh[i].vert[0];
            mesh[i].vert[1] = mat * mesh[i].vert[1];
            mesh[i].vert[2] = mat * mesh[i].vert[2];

            mesh[i].normal = Model::calculate_normal(mesh[i]);
        }
    }

    void Model::move_model(const vector_3& position) noexcept
    {
        matrix_4 translation_mat = matrix_4::translation(position);

        #pragma omp parallel for
        for(uint64_t i = 0; i < mesh.size(); i++)
        {
            mesh[i].vert[0] = translation_mat * mesh[i].vert[0];
            mesh[i].vert[1] = translation_mat * mesh[i].vert[1];
            mesh[i].vert[2] = translation_mat * mesh[i].vert[2];

            mesh[i].normal = Model::calculate_normal(mesh[i]);
        }
    }

    void Model::recalculate_normals()
    {
        #pragma omp parallel for
        for(uint64_t i = 0; i < mesh.size(); i++)
        {
            mesh[i].normal = Model::calculate_normal(mesh[i]);
        }
    }

    [[nodiscard]] vector_3 Model::calculate_normal(polygon triangle)
    {
        vector_3 U = triangle.vert[1] - triangle.vert[0];
        vector_3 V = triangle.vert[2] - triangle.vert[0];

        vector_3 normal = {
            U.y * V.z - U.z * V.y,
            U.z * V.x - U.x * V.z,
            U.x * V.y - U.y * V.x
        };

        return normal;
    }

}