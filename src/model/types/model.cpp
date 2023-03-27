#include <model.hpp>

namespace bolt
{
    Model::Model()
    {

    }

    [[nodiscard]] Model::Model(const std::vector<polygon>& mesh)
        :mesh(mesh)
    {
        to_drawable_vector();
    }

    Model::~Model()
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

        to_drawable_vector();
    }

    [[nodiscard]] const std::vector<double>& Model::get_drawable_vector() noexcept
    {
        return drawable_vector;
    }

    [[nodiscard]] const std::vector<AttributeLayout>& Model::get_attribute_layout() noexcept
    {
        return attribute_layout;
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

    void Model::rotate_model(vector_3 rotation_vector) noexcept
    {
        // TODO: implement model rotation
    }

    void Model::apply_lighting()
    {
        // TODO: write a coherent lighting system
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

    void Model::to_drawable_vector()
    {
        drawable_vector.clear();

        for(const auto& polygon: mesh)
        {
            drawable_vector.push_back(polygon.vert[0].x);
            drawable_vector.push_back(polygon.vert[0].y);
            drawable_vector.push_back(polygon.vert[0].z);

            drawable_vector.push_back(polygon.normal.x);
            drawable_vector.push_back(polygon.normal.y);
            drawable_vector.push_back(polygon.normal.z);

            drawable_vector.push_back(polygon.UV[0].x);
            drawable_vector.push_back(polygon.UV[0].y);

            drawable_vector.push_back(polygon.vert[1].x);
            drawable_vector.push_back(polygon.vert[1].y);
            drawable_vector.push_back(polygon.vert[1].z);

            drawable_vector.push_back(polygon.normal.x);
            drawable_vector.push_back(polygon.normal.y);
            drawable_vector.push_back(polygon.normal.z);

            drawable_vector.push_back(polygon.UV[1].x);
            drawable_vector.push_back(polygon.UV[1].y);

            drawable_vector.push_back(polygon.vert[2].x);
            drawable_vector.push_back(polygon.vert[2].y);
            drawable_vector.push_back(polygon.vert[2].z);

            drawable_vector.push_back(polygon.normal.x);
            drawable_vector.push_back(polygon.normal.y);
            drawable_vector.push_back(polygon.normal.z);

            drawable_vector.push_back(polygon.UV[2].x);
            drawable_vector.push_back(polygon.UV[2].y);
        }
    }

    void Model::set_attribute_layout()
    {
        attribute_layout.push_back({
            "position",
            3,
            GL_DOUBLE,
            GL_FALSE,
            8 * sizeof(double),
            0
        });

        attribute_layout.push_back({
            "position",
            3,
            GL_DOUBLE,
            GL_FALSE,
            8 * sizeof(double),
            3 * sizeof(double)
        });

        attribute_layout.push_back({
            "position",
            3,
            GL_DOUBLE,
            GL_FALSE,
            8 * sizeof(double),
            6 * sizeof(double)
        });
    }
}