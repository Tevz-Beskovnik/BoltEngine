#pragma once

#include <core.hpp>
#include <util.hpp>

#define REGISTER_ROOT_SERIALIZER(ClassName) \
    namespace bolt {                        \
        namespace serializer {              \
            ref_ptr<ClassName> try_deserialize(std::string input_file) \
            {                               \
                std::ifstream file(input_file); \
                make_ref<ClassName>(ClassName::try_deserialize(file)); \
            }                                    \
        }                                   \
    }

namespace bolt
{
    class Serializable;

    namespace serializer
    {
#ifndef SERIALIZER
        ref_ptr<Serializable> try_deserialize(std::string input_file)
        {
            throw std::runtime_error("Deserializer is not defined");
        }
#endif
    }

    class Serializable
    {
        virtual ref_ptr<Serializable> try_deserialize(std::ifstream input) = 0;

        virtual std::string serialize() = 0;
    };
}