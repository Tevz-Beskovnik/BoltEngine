#pragma once

#include <colors.hpp>
#include <log.hpp>
#include <cstddef>
#include <queue>
#include <type_traits>

#ifndef BOLT_POOL_DEFAULT_PRE_ALLOC
#define BOLT_POOL_DEFAULT_PRE_ALLOC 10
#endif

#include <cstdint>

namespace bolt
{
namespace pool
{
    template<typename T>
    concept PoolableObject = requires(T& a) // is this better then virtual abstraction? probably? A: Yes mostlikely since there is no common managed state
    {
        { a.reset() };
    };

    template<PoolableObject T>
    class ObjectPool 
    {
    using managed_object_ptr = T*;
    public:
        ObjectPool(uint32_t pre_alloc = BOLT_POOL_DEFAULT_PRE_ALLOC)
        {
            static_assert(std::is_trivially_constructible_v<T> == true);

            for(size_t i = 0; i < pre_alloc; i++)
                free_objects.push(new T());
        }

        ~ObjectPool()
        {
            while(!free_objects.empty())
            {
                delete free_objects.front();
                free_objects.pop();
            }
        }

        [[nodiscard]] managed_object_ptr obtain()
        {
            if(!free_objects.empty())
            {
                BOLT_MSG_DEBUG("Grabbing object from pool");
                auto front = free_objects.front();
                free_objects.pop();
                return front;
            }

            BOLT_MSG_DEBUG("Allocating new object");
            auto front = new T();
            return front;
        }

        void free(managed_object_ptr object)
        {
            object->reset();
            free_objects.push(object);
        }

    private:
        std::queue<managed_object_ptr> free_objects;
    };
}
}

