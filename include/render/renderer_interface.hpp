#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>

namespace bolt
{
    class RenderInterface
    {
        public:
            [[nodiscard]] virtual void setMesh(const std::vector<polygon>& mesh) { ; };

            [[nodiscard]] virtual void addTexture(const std::string &path) { ; };

            [[nodiscard]] virtual void addShader(const std::string &path, shader_type type) { ; };

            virtual void render() const { ; };
    };
}