//
// Created by tevz on 11.7.2023.
//

#include <line_model.hpp>

namespace bolt
{
    Line::Line(const std::vector<vector_3>& points, RGB color)
        : ModelInterface(points, {}, {}, {})
    {
        for(uint32_t i = 0; i < points.size(); i++)
            this->color.push_back(color);

        to_drawable_vector();

        set_attribute_layout();
    }

    Line::~Line()
    {
        ;
    }

    [[nodiscard]] ref_ptr<Line> Line::create(const std::vector<vector_3>& points, RGB color)
    {
        ref_ptr<Line> temp = create_ref<Line>(points, color);
        temp->instance = temp;
        return temp;
    }

    [[nodiscard]] uint32_t Line::vertices_count() const noexcept
    {
        return vertices.size();
    }

    void Line::transform_model(const matrix_4& mat) noexcept
    {
        #pragma omp parallel for
        for(auto& vert : vertices)
        {
            vert = mat * vert;
        }
    }

    ref_ptr<ModelInterface> Line::add_model(const ref_ptr<ModelInterface>& model)
    {
        for(const auto& vert : model->get_vertices())
            vertices.push_back(vert);

        for(const auto& UV : model->get_UVs())
            UVs.push_back(UV);

        for(const auto& normal : model->get_normals())
            normals.push_back(normal);

        for(const auto& index : model->get_index_buffer())
            indices.push_back(index);

        return instance;
    }

    void Line::move_model(const vector_3& position) noexcept
    {
        matrix_4 translation_mat = matrix_4::translation(position);

        transform_model(translation_mat);

        to_drawable_vector();
    }

    void Line::rotate_model(vector_3 rotation_vector) noexcept
    {
        // TODO: implement model_from_file rotation
    }

    void Line::apply_lighting()
    {
        // TODO: write a coherent lighting system
    }

    void Line::recalculate_normals()
    {
        ;
    }

    [[nodiscard]] vector_3 Line::calculate_normal(polygon triangle)
    {
        vector_3 U = triangle.vert[1] - triangle.vert[0];
        vector_3 V = triangle.vert[2] - triangle.vert[0];

        vector_3 normal = {
                U.y * V.z - U.z * V.y,
                U.z * V.x - U.x * V.z,
                U.x * V.y - U.y * V.x
        };

        return normal.normalize();
    }

    void Line::to_drawable_vector()
    {
        drawable_vector.clear();

        for(uint32_t i = 0; i < vertices.size(); i++)
        {
            drawable_vector.push_back(static_cast<float>(vertices[i].x));
            drawable_vector.push_back(static_cast<float>(vertices[i].y));
            drawable_vector.push_back(static_cast<float>(vertices[i].z));

            drawable_vector.push_back(static_cast<float>(color[i].r_dec));
            drawable_vector.push_back(static_cast<float>(color[i].g_dec));
            drawable_vector.push_back(static_cast<float>(color[i].b_dec));
            drawable_vector.push_back(static_cast<float>(color[i].a_dec));
        }
    }

    void Line::set_attribute_layout() {
        attrib_layout.push_back({
            3,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(float),
            0
        });

        attrib_layout.push_back({
            4,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(float),
            3 * sizeof(float)
        });
    }
}