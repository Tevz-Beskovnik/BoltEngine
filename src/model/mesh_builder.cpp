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
        BOLT_LOG_INFO(std::string("Creating new model_from_file with mesh") + std::string(file_path))

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

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_quad(const vector_3 corner, const vector_2 dimensions)
    {
        BOLT_LOG_INFO("Creating a quad")

        std::vector<vector_3> verts;
        std::vector<vector_2> UVs;

        verts.push_back({corner.x, corner.y, corner.z});
        verts.push_back({corner.x, corner.y + dimensions.y, corner.z});
        verts.push_back({corner.x + dimensions.x, corner.y + dimensions.y, corner.z});
        verts.push_back({corner.x, corner.y, corner.z});
        verts.push_back({corner.x + dimensions.x, corner.y + dimensions.y, corner.z});
        verts.push_back({corner.x + dimensions.x, corner.y, corner.z});

        UVs.push_back({ 0.0f, 0.0f });
        UVs.push_back({ 0.0f, 1.0f});
        UVs.push_back({ 1.0f, 1.0f });
        UVs.push_back({ 0.0f, 0.0f});
        UVs.push_back({ 1.0f, 1.0f });
        UVs.push_back({ 1.0f, 0.0f });

        BOLT_LOG_INFO("Mesh-builder poly count: " + std::to_string(verts.size()/3))

        return Model::create({
            .vertices = verts,
            .UVs = UVs,
            .normals = std::vector<vector_3>(verts.size()/3),
            .indices = {}
        });
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_triangle(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3)
    {
        BOLT_LOG_INFO("Creating a triangle")

        std::vector<vector_3> verts;
        std::vector<vector_2> UVs;

        verts.push_back({ x1, y1, 0.0f });
        verts.push_back({ x2, y2, 0.0f });
        verts.push_back({ x3, y3, 0.0f });

        UVs.push_back({ 1.0f, 1.0f });
        UVs.push_back({ 1.0f, 0.0f});
        UVs.push_back({ 0.0f, 0.0f});

        return Model::create({
            .vertices = verts,
            .UVs = UVs,
            .normals = std::vector<vector_3>(verts.size()/3),
            .indices = {}
        });
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_cube(const vector_3 dimensions)
    {
        std::vector<polygon> mesh;

        BOLT_LOG_INFO("Creating a cube")

        std::vector<vector_3> verts;
        std::vector<vector_2> UVs;

        verts.push_back({0, 1*dimensions.y, 0});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 0});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({0, 0, 1*dimensions.z});
        verts.push_back({1*dimensions.x, 0, 1*dimensions.z});
        verts.push_back({0, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({0, 0, 0});
        verts.push_back({0, 0, 1*dimensions.z});
        verts.push_back({1*dimensions.x, 0, 0});
        verts.push_back({0, 0, 1*dimensions.z});
        verts.push_back({0, 0, 0});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 0});
        verts.push_back({1*dimensions.x, 0, 1*dimensions.z});
        verts.push_back({1*dimensions.x, 0, 0});
        verts.push_back({0, 1*dimensions.y, 0});
        verts.push_back({1*dimensions.x, 0, 0});
        verts.push_back({0, 0, 0});
        verts.push_back({0, 1*dimensions.y, 0});
        verts.push_back({0, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({0, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({0, 0, 1*dimensions.z});
        verts.push_back({0, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({0, 1*dimensions.y, 0});
        verts.push_back({0, 0, 0});
        verts.push_back({1*dimensions.x, 0, 0});
        verts.push_back({1*dimensions.x, 0, 1*dimensions.z});
        verts.push_back({0, 0, 1*dimensions.z});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 0});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 1*dimensions.z});
        verts.push_back({1*dimensions.x, 0, 1*dimensions.z});
        verts.push_back({0, 1*dimensions.y, 0});
        verts.push_back({1*dimensions.x, 1*dimensions.y, 0});
        verts.push_back({1*dimensions.x, 0, 0});

        UVs.push_back({1.000000, 0.500000});
        UVs.push_back({0.625000, 0.750000});
        UVs.push_back({0.625000, 0.500000});
        UVs.push_back({0.625000, 0.750000});
        UVs.push_back({0.375000, 1.000000});
        UVs.push_back({0.375000, 0.750000});
        UVs.push_back({0.625000, 0.000000});
        UVs.push_back({0.375000, 0.250000});
        UVs.push_back({0.375000, 0.000000});
        UVs.push_back({0.375000, 0.500000});
        UVs.push_back({0.125000, 0.750000});
        UVs.push_back({0.125000, 0.500000});
        UVs.push_back({0.625000, 0.500000});
        UVs.push_back({0.375000, 0.750000});
        UVs.push_back({0.375000, 0.500000});
        UVs.push_back({0.625000, 0.250000});
        UVs.push_back({0.375000, 0.500000});
        UVs.push_back({0.375000, 0.250000});
        UVs.push_back({1.000000, 0.500000});
        UVs.push_back({0.875000, 0.750000});
        UVs.push_back({0.625000, 0.750000});
        UVs.push_back({0.625000, 0.750000});
        UVs.push_back({0.625000, 1.000000});
        UVs.push_back({0.375000, 1.000000});
        UVs.push_back({0.625000, 0.000000});
        UVs.push_back({0.625000, 0.250000});
        UVs.push_back({0.375000, 0.250000});
        UVs.push_back({0.375000, 0.500000});
        UVs.push_back({0.375000, 0.750000});
        UVs.push_back({0.125000, 0.750000});
        UVs.push_back({0.625000, 0.500000});
        UVs.push_back({0.625000, 0.750000});
        UVs.push_back({0.375000, 0.750000});
        UVs.push_back({0.625000, 0.250000});
        UVs.push_back({0.625000, 0.500000});
        UVs.push_back({0.375000, 0.500000});

        return Model::create({verts, UVs, std::vector<vector_3>(verts.size()/3), {}});
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_sphere(const vector_2 center, const float radius)
    {
        return Model::create({{}, {}});
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::make_text(const std::string& text, const ref_ptr<Font>& font)
    {
        std::vector<polygon> mesh;
        std::vector<vector_3> verts;
        std::vector<vector_2> UVs;

        font->create_mesh(text, mesh);

        for(const auto& poly : mesh)
        {
            verts.push_back({poly.vert[0].x, poly.vert[0].y, poly.vert[0].z});
            verts.push_back({poly.vert[1].x, poly.vert[1].y, poly.vert[1].z});
            verts.push_back({poly.vert[2].x, poly.vert[2].y, poly.vert[2].z});

            UVs.push_back({poly.UV[0].x, poly.UV[0].y});
            UVs.push_back({poly.UV[1].x, poly.UV[1].y});
            UVs.push_back({poly.UV[2].x, poly.UV[2].y});
        }

        return Model::create({verts, UVs, std::vector<vector_3>(verts.size()/3), {}});
    }

    [[nodiscard]] ref_ptr<Model> MeshBuilder::read_obj(const_str file_path)
    {
        std::ifstream file(file_path);
        std::vector<polygon> mesh;

        ASSERT(file.is_open(), "Can't open file");

        // Local cache of verts
        std::vector<vector_3> verts;
        std::vector<vector_3> normals;
        std::vector<vector_2> UVs;

        while (!file.eof())
        {
            char line[128];
            file.getline(line, 128);

            std::stringstream s;
            s << line;

            char junk;

            if (line[0] == 'v' && line[1] != 'n' && line[1] != 't')
            {
                vector_3 v;
                s >> junk >> v.x >> v.y >> v.z;
                verts.push_back(v);
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
                if (UVs.empty() == false && normals.empty() == false)
                {
                    s >> junk >> f[0] >> junk >> uv[0] >> junk >> vn >> f[1] >> junk >> uv[1] >> junk >> vn >> f[2] >> junk >> uv[2] >> junk >> vn;
                    mesh.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { UVs[uv[0] - 1], UVs[uv[1] - 1], UVs[uv[2] - 1] }, normals[vn - 1] });
                }
                else if(normals.empty() == false)
                {
                    s >> junk >> f[0] >> junk >> junk >> vn >> f[1] >> junk >> junk >> vn >> f[2] >> junk >> junk >> vn;
                    mesh.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { 0.0f }, normals[vn-1] });
                }
                else
                {
                    s >> junk >> f[0] >> f[1] >> f[2];
                    mesh.push_back({ { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] }, { 0.0f }, 1.0f, 0.0f, 0.0f });
                }
            }
        }
        
        // TODO this is ugly make this preatier EWWWW ITS INNAFICIENT EWWWWW
        verts.clear();
        UVs.clear();
        normals.clear();

        for(const auto& poly : mesh)
        {
            verts.push_back({poly.vert[0].x, poly.vert[0].y, poly.vert[0].z});
            verts.push_back({poly.vert[1].x, poly.vert[1].y, poly.vert[1].z});
            verts.push_back({poly.vert[2].x, poly.vert[2].y, poly.vert[2].z});

            UVs.push_back({poly.UV[0].x, poly.UV[0].y});
            UVs.push_back({poly.UV[1].x, poly.UV[1].y});
            UVs.push_back({poly.UV[2].x, poly.UV[2].y});

            normals.push_back({poly.normal.x, poly.normal.y, poly.normal.z});
        }

        return Model::create({verts, UVs, normals, {}});
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