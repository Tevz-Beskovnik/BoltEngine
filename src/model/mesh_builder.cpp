#include <mesh_builder.hpp>

namespace bolt
{
    MeshBuilder::MeshBuilder()
    {

    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_model(const_str file_path, model_standard file_standard)
    {
        if(!doesFileExist(file_path))
            BOLT_ERROR("File for model does not exist")

        switch(file_standard)
        {
            case model_standard::OBJ:
                return read_obj(file_path);
                break;
            case model_standard::COLLADA:
                return read_collada(file_path);
                break;
            case model_standard::STL:
                return read_stl(file_path);
                break;
            case model_standard::FBX:
                return read_fbx(file_path);
                break;
            default:
                BOLT_ERROR("Incorrect file standard specified")
                break;
        }
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_quad(const vector_2 corner, const vector_2 dimensions)
    {

    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_triangle(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3)
    {

    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_cube(const vector_2 center, const vector_3 dimensions)
    {

    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_sphere(const vector_2 center, const double radius)
    {

    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_obj(const_str  file_path)
    {

        std::ifstream file()
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_collada(const_str  file_path)
    {

    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_stl(const_str file_path)
    {

    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_fbx(const_str file_path)
    {

    }
}