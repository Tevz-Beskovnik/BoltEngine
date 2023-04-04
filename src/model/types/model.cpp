#include <model.hpp>

namespace bolt
{
    [[nodiscard]] Model::Model(std::vector<polygon> mesh)
        :mesh(std::move(mesh))
    {
        to_drawable_vector();
    }

    Model::~Model()
    {
        ;
    }

    [[nodiscard]] ref_ptr<Model> Model::create(std::vector<polygon> mesh)
    {
        return create_ref<Model>(mesh);
    }

    void Model::set_mesh(const std::vector<polygon>& new_mesh)
    {
        mesh = new_mesh;

        to_drawable_vector();
    }

    [[nodiscard]] const std::vector<float>& Model::get_drawable_vector() const noexcept
    {
        return drawable_vector;
    }

    [[nodiscard]] const std::vector<AttributeLayout>& Model::get_attribute_layout() const noexcept
    {
        return attribute_layout;
    }

    [[nodiscard]] uint32_t Model::polygon_count() const noexcept
    {
        return mesh.size();
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
            drawable_vector.push_back(static_cast<float>(polygon.vert[0].x));
            drawable_vector.push_back(static_cast<float>(polygon.vert[0].y));
            drawable_vector.push_back(static_cast<float>(polygon.vert[0].z));

            drawable_vector.push_back(static_cast<float>(polygon.normal.x));
            drawable_vector.push_back(static_cast<float>(polygon.normal.y));
            drawable_vector.push_back(static_cast<float>(polygon.normal.z));

            drawable_vector.push_back(static_cast<float>(polygon.UV[0].x));
            drawable_vector.push_back(static_cast<float>(polygon.UV[0].y));

            drawable_vector.push_back(static_cast<float>(polygon.vert[1].x));
            drawable_vector.push_back(static_cast<float>(polygon.vert[1].y));
            drawable_vector.push_back(static_cast<float>(polygon.vert[1].z));

            drawable_vector.push_back(static_cast<float>(polygon.normal.x));
            drawable_vector.push_back(static_cast<float>(polygon.normal.y));
            drawable_vector.push_back(static_cast<float>(polygon.normal.z));

            drawable_vector.push_back(static_cast<float>(polygon.UV[1].x));
            drawable_vector.push_back(static_cast<float>(polygon.UV[1].y));

            drawable_vector.push_back(static_cast<float>(polygon.vert[2].x));
            drawable_vector.push_back(static_cast<float>(polygon.vert[2].y));
            drawable_vector.push_back(static_cast<float>(polygon.vert[2].z));

            drawable_vector.push_back(static_cast<float>(polygon.normal.x));
            drawable_vector.push_back(static_cast<float>(polygon.normal.y));
            drawable_vector.push_back(static_cast<float>(polygon.normal.z));

            drawable_vector.push_back(static_cast<float>(polygon.UV[2].x));
            drawable_vector.push_back(static_cast<float>(polygon.UV[2].y));
        }
    }

    void Model::set_attribute_layout()
    {
        attribute_layout.push_back({
            "iPosition",
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            0
        });

        attribute_layout.push_back({
            "iNormals",
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            3 * sizeof(float)
        });

        attribute_layout.push_back({
            "iUV",
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            6 * sizeof(float)
        });
    }
}