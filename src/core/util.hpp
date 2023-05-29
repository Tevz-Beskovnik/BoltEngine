#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <assertion_exception.hpp>
#include <log.hpp>

namespace bolt
{
    // assertion definitions
    #ifndef ASSERT
    #define ASSERT(x, err) (x == true ? true : throw AssertionException(err))
    #endif

    #ifndef ASSERT_EQ
    #define ASSERT_EQ(left, right, err) (left == right ? true : throw AssertionException(err))
    #endif

    #ifndef ASSERT_NE
    #define ASSERT_NE(left, right, err) (left != right ? true : throw AssertionException(err))
    #endif

    #ifndef CAST_EVENT_FUNCTION
    #define CAST_MEMBER_FUNCTION(function) [this](auto&&... args) -> decltype(auto) { return this->function(std::forward<decltype(args)>(args)...); }
    #endif

    #ifndef TEST_EQUAL
    #define TEST_EQUAL(expression, err) static_assert(expression, err);
    #endif

    enum render_framework
    {
        OPEN_GL = 0,
        VULKAN = 1
    };

    typedef const char* const_str;
    typedef char* basic_str;

    template<typename T>
    using single_ptr = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr single_ptr<T> create_single (Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using ref_ptr = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr ref_ptr<T> create_ref (Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}