#include <mesh_builder.hpp>

namespace bolt
{
    MeshBuilder::MeshBuilder()
    {
        ;
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_model(const_str file_path, model_standard file_standard)
    {
        std::string error = "Model file: " + std::string(file_path) + " does not exist.";
        ASSERT_FILE_EXISTS(file_path, error);

        switch(file_standard)
        {
            case model_standard::OBJ:
                return read_obj(file_path);
            case model_standard::COLLADA:
                return read_collada(file_path);
            case model_standard::STL:
                return read_stl(file_path);
            case model_standard::FBX:
                return read_fbx(file_path);
            default:
                BOLT_ERROR(WrongFileExtensionException("Incorrect file standard specified"))
        }
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_quad(const vector_2 corner, const vector_2 dimensions)
    {
        std::vector<polygon> mesh;

        mesh.push_back(
            {
                .vert ={
                    { corner.x, corner.y, 0.0f },
                    { corner.x, corner.y + dimensions.y, 0.0f },
                    { corner.x + dimensions.x, corner.y, 0.0f }
                    },
                .UV = {
                    { 0.0f, 1.0f},
                    { 0.0f, 0.0f},
                    { 1.0f, 1.0f },
                }
            }
        );

        mesh.push_back(
            {
                .vert ={
                    { corner.x + dimensions.x, corner.y + dimensions.y, 0.0f },
                    { corner.x + dimensions.x, corner.y, 0.0f },
                    { corner.x, corner.y + dimensions.y, 0.0f }
                },
                .UV = {
                    { 1.0f, 1.0f },
                    { 1.0f, 0.0f },
                    { 0.0f, 0.0f }
                }
            }
        );

        BOLT_LOG_INFO("Mesh-builder poly count: " + std::to_string(mesh.size()))

        return Model::create({
            .mesh = mesh,
            .indices = {}
        });
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_triangle(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3)
    {
        std::vector<polygon> mesh;

        mesh.push_back(
            {
                .vert ={
                    { x1, y1, 0.0f },
                    { x2, y2, 0.0f },
                    { x3, y3, 0.0f }
                },
                .UV = {
                    { 1.0f, 1.0f },
                    { 1.0f, 0.0f},
                    { 0.0f, 0.0f},
                }
            }
        );

        return Model::create({
            .mesh = mesh,
            .indices = {}
        });
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_cube(const vector_3 center, const vector_3 dimensions)
    {


        return Model::create({{}, {}});
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_sphere(const vector_2 center, const double radius)
    {
        return Model::create({{}, {}});
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_obj(const_str file_path)
    {
        std::ifstream file(file_path);
        std::vector<polygon> mesh;

        ASSERT(file.is_open(), "Can't open file");

        std::vector<vector_3> verticies;
        std::vector<vector_3> normals;
        std::vector<vector_2> UVs;

        while (!file.eof())
        {
            char line[128];
            char junk;

            file.getline(line, 128);

            std::stringstream s;
            s << line;

            if (line[0] == 'v' && line[1] != 'n' && line[1] != 't')
            {
                vector_3 v;
                s >> junk >> v.x >> v.y >> v.z;
                verticies.push_back(v);
            }

            if (line[0] == 'v' && line[1] == 't')
            {
                float i, j;
                s >> junk >> junk >> i >> j;
                UVs.push_back({ (float)i, (float)j });
            }

            if (line[0] == 'v' && line[1] == 'n')
            {
                vector_3 n;
                s >> junk >> junk >> n.x >> n.y >> n.z;
                normals.push_back(n);
            }

            if (line[0] == 'f')
            {
                int f[3];
                int vn;
                int uv[3];
                if (UVs.empty() && normals.empty())
                {
                    s >> junk >> f[0] >> junk >> uv[0] >> junk >> vn >> f[1] >> junk >> uv[1] >> junk >> vn >> f[2] >> junk >> uv[2] >> junk >> vn;
                    mesh.push_back({{verticies[f[0] - 1], verticies[f[1] - 1], verticies[f[2] - 1] }, {UVs[uv[0] - 1], UVs[uv[1] - 1], UVs[uv[2] - 1] }, normals[vn - 1] });
                }
                else if(normals.empty())
                {
                    s >> junk >> f[0] >> junk >> junk >> vn >> f[1] >> junk >> junk >> vn >> f[2] >> junk >> junk >> vn;
                    mesh.push_back({{verticies[f[0] - 1], verticies[f[1] - 1], verticies[f[2] - 1] }, {0.0f }, normals[vn - 1] });
                }
                else
                {
                    s >> junk >> f[0] >> f[1] >> f[2];
                    mesh.push_back({{verticies[f[0] - 1], verticies[f[1] - 1], verticies[f[2] - 1] }, {0.0f }, 1.0f, 0.0f, 0.0f });
                }
            }
        }

        return Model::create({mesh, {}});
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_collada(const_str file_path) // TODO
    {
        return Model::create({{}, {}});
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_stl(const_str file_path) // TODO
    {
        return Model::create({{}, {}});
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_fbx(const_str file_path) // TODO
    {
        return Model::create({{}, {}});
    }
}