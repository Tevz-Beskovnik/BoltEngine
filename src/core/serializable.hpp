#pragma once

#include <core.hpp>

namespace bolt
{
    class Serializable
    {
        virtual ref_ptr<Serializable> deserialize(std::string input) = 0;

        virtual std::string serialize() = 0;
    };
}