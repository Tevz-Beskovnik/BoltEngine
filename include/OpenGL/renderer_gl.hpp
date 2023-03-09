#pragma once

#include <core.hpp>
#include <util.hpp>
#include <renderer_interface.hpp>

namespace bolt
{
    struct Layout
    {
        unsigned int& program;
        unsigned int& buffer;
        std::string nameOfAttribute;
        int size;
        unsigned int type;
        unsigned int normalise;
        int totalSizeInBytes;
        ptrdiff_t offset;
    };

    class RendererGL : public RenderInterface
    {
        public:
            void setVertexLayout(Layout vertex_layout);

            [[nodiscard]] bool setMesh(std::vector<polygon> mesh) override;

            [[nodiscard]] bool setShader(std::string path) override;

            [[nodiscard]] bool setTexture(std::string path) override;

            void render() const override;
        private:
    };
}