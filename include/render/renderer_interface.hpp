#pragma once

#include <core.hpp>
#include <primitives.hpp>

namespace bolt
{
    class RenderInterface
    {
        public:
            [[nodiscard]] virtual bool setMesh(std::vector<polygon>) { return false; };

            [[nodiscard]] virtual bool setTexture(std::string) { return false; };

            [[nodiscard]] virtual bool setShader(std::string) { return false; };

            virtual void render() const { ; };
    };
}