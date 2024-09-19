#include <model.hpp>

namespace bolt
{
    [[nodiscard]] Model::Model(const model_config& config)
        : ModelInterface(config.vertices, config.UVs, config.normals, config.indices), instance(nullptr)
    {
        BOLT_LOG_INFO("Poly count: " + std::to_string(this->vertices.size()/3))

        to_drawable_vector();

        set_attribute_layout();
    }

    Model::~Model()
    {
        ;
    }

    [[nodiscard]] ref_ptr<Model> Model::create(const model_config& config)
    {
        ref_ptr<Model> temp = create_ref<Model>(config);
        temp->instance = temp;
        return temp;
    }

    [[nodiscard]] uint32_t Model::vertices_count() const noexcept
    {
        return vertices.size();
    }

    void Model::transform_model(const matrix_4& mat) noexcept
    {
        #pragma omp parallel for
        for(uint64_t i = 0; i < vertices.size(); i+=3)
        {
            vertices[i] = mat * vertices[i];
            vertices[i + 1] = mat * vertices[i + 1];
            vertices[i + 2] = mat * vertices[i + 2];

            normals[i/3] = Model::calculate_normal(vertices[i], vertices[i + 1], vertices[i + 2]);
        }
    }

    ref_ptr<ModelInterface> Model::add_model(const ref_ptr<ModelInterface>& model) // TODO have to combine index buffers too
    {
        for(const auto& vert : model->get_vertices())
            vertices.push_back(vert);

        for(const auto& UV : model->get_UVs())
            UVs.push_back(UV);

        for(const auto& normal : model->get_normals())
            normals.push_back(normal);

        for(const auto& index : model->get_index_buffer())
            indices.push_back(index);

        to_drawable_vector();

        return instance;
    }

    void Model::move_model(const vector_3& position) noexcept
    {
        matrix_4 translation_mat = matrix_4::translation(position);

        transform_model(translation_mat);

        to_drawable_vector();
    }

    void Model::rotate_model(vector_3 rotation_vector) noexcept
    {
        // TODO: implement model_from_file rotation
    }

    void Model::apply_lighting()
    {
        // TODO: write a coherent lighting system
    }

    void Model::recalculate_normals()
    {
        BOLT_LOG_INFO("Recalculating normals for model_from_file")

        #pragma omp parallel for
        for(uint64_t i = 0; i < vertices.size()-3; i+=3)
        {
            normals[i/3] = Model::calculate_normal(vertices[i], vertices[i + 1], vertices[i + 2]);
        }

        BOLT_LOG_INFO("Finished recalculating normals")
    }

    [[nodiscard]] vector_3 Model::calculate_normal(vector_3 p1, vector_3 p2, vector_3 p3)
    {
        vector_3 U = p2 - p1;
        vector_3 V = p3 - p1;

        vector_3 normal = {
            U.y * V.z - U.z * V.y,
            U.z * V.x - U.x * V.z,
            U.x * V.y - U.y * V.x
        };

        return normal.normalize();
    }

    void Model::to_drawable_vector()
    {
        BOLT_LOG_INFO("Creating drawable vector")
        drawable_vector.clear();

        for(uint32_t i = 0; i < vertices.size(); i+=3)
        {
            drawable_vector.push_back(static_cast<float>(vertices[i].x));
            drawable_vector.push_back(static_cast<float>(vertices[i].y));
            drawable_vector.push_back(static_cast<float>(vertices[i].z));

            drawable_vector.push_back(static_cast<float>(normals[i/3].x));
            drawable_vector.push_back(static_cast<float>(normals[i/3].y));
            drawable_vector.push_back(static_cast<float>(normals[i/3].z));

            drawable_vector.push_back(static_cast<float>(UVs[i].x));
            drawable_vector.push_back(static_cast<float>(UVs[i].y));

            drawable_vector.push_back(static_cast<float>(vertices[i+1].x));
            drawable_vector.push_back(static_cast<float>(vertices[i+1].y));
            drawable_vector.push_back(static_cast<float>(vertices[i+1].z));

            drawable_vector.push_back(static_cast<float>(normals[i/3].x));
            drawable_vector.push_back(static_cast<float>(normals[i/3].y));
            drawable_vector.push_back(static_cast<float>(normals[i/3].z));

            drawable_vector.push_back(static_cast<float>(UVs[i+1].x));
            drawable_vector.push_back(static_cast<float>(UVs[i+1].y));

            drawable_vector.push_back(static_cast<float>(vertices[i+2].x));
            drawable_vector.push_back(static_cast<float>(vertices[i+2].y));
            drawable_vector.push_back(static_cast<float>(vertices[i+2].z));

            drawable_vector.push_back(static_cast<float>(normals[i/3].x));
            drawable_vector.push_back(static_cast<float>(normals[i/3].y));
            drawable_vector.push_back(static_cast<float>(normals[i/3].z));

            drawable_vector.push_back(static_cast<float>(UVs[i+2].x));
            drawable_vector.push_back(static_cast<float>(UVs[i+2].y));
        }
    }

    void Model::set_attribute_layout()
    {
        attrib_layout.push_back({
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            0
        });

        attrib_layout.push_back({
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            3 * sizeof(float)
        });

        attrib_layout.push_back({
            2,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(float),
            6 * sizeof(float)
        });
    }
}