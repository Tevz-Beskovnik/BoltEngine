#pragma once

#include <core.hpp>

namespace bolt
{
    #ifndef BOLT_LOG_FILE
        #define BOLT_LOG_FILE "/Users/tevz/Documents/programing/BoltEngine/log"
    #endif

    #ifdef BOLT_DEBUG
        #define BOLT_MSG_DEBUG(bolt_msg_dbg) COLOR(GREEN_FG, BLACK_BG) std::cout << "DEBUG: " << bolt_msg_dbg << std::endl;
        #define BOLT_MSG_ERROR(bolt_msg_err) COLOR(RED_FG, BLACK_BG) std::cout << "ERROR: " << bolt_msg_err << std::endl;
        #define BOLT_ERROR(err) throw std::runtime_error(err);

        #define BOLT_LOG_ERROR(msg) LogUtil::error(msg);
        #define BOLT_LOG_WARNING(msg) LogUtil::warning(msg);
        #define BOLT_LOG_INFO(msg) LogUtil::info(msg);

        class LogUtil
        {
            public:
                LogUtil() = delete;
                LogUtil(const LogUtil&) = delete;

                static void initLogs();

                static void error(std::string);

                static void warning(std::string);

                static void info(std::string);

            public:
                static uint32_t raw_time;
                static std::string file_loc;
        };
    #else
        #define BOLT_MSG_DEBUG(string)
        #define BOLT_MSG_LOG(bolt_msg_log)
        #define BOLT_MSG_ERROR(bolt_msg_err)
        #define BOLT_ERROR(err)

        #define BOLT_LOG_ERROR(msg)
        #define BOLT_LOG_WARNING(msg)
        #define BOLT_LOG_INFO(msg)
    #endif
}