#include <model.hpp>

namespace bolt
{
    [[nodiscard]] Model::Model(const std::vector<polygon>& mesh)
        :mesh(mesh)
    {
        ;
    }

    [[nodiscard]] ref_ptr<Model> Model::create(const std::vector<polygon>& mesh)
    {
        return create_ref<Model>(mesh);
    }

    void Model::apply_transformation(matrix_4 *mat)
    {

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