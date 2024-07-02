#pragma once

#include <core.hpp>

namespace bolt
{
    class Serializable
    {
        virtual Serializable deserialize() = 0;

        virtual std::string serialize() = 0;
    };
}