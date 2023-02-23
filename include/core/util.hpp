#pragma once

#include <core.hpp>
#include <colors.hpp>

namespace bolt
{
    #ifdef BOLT_DEBUG
        #define BOLT_MSG_DEBUG(bolt_msg_dbg) COLOR(GREEN_FG, BLACK_BG) std::cout << "DEBUG: " << bolt_msg_dbg << std::endl;
    #else
        #define BOLT_MSG_DEBUG(string)
    #endif
    // TODO: Wrap this all up to not be shown in prod
    #define BOLT_MSG_LOG(bolt_msg_log) COLOR(BLUE_FG, BLACK_BG) std::cout << "LOG: " << bolt_msg_log << std::endl;

    #define BOLT_MSG_ERROR(bolt_msg_err) COLOR(RED_FG, BLACK_BG) std::cout << "ERROR: " << bolt_msg_err << std::endl;

    #define BOLT_ERROR(err) throw err;
    //

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

    bool doesFileExist(const_str file)
    {
        std::fstream file_open(file);

        return file_open.is_open();
    }
}