#pragma once

#include <core.hpp>

namespace bolt
{
    #ifndef BOLT_LOG_FILE
        #define BOLT_LOG_FILE "/Users/tevz/Documents/programing/BoltEngine/log"
    #endif

    #define BOLT_LOG_ERROR(msg) LogUtil::log(LogType::ERROR, msg);

    #ifdef BOLT_DEBUG
        #define BOLT_MSG_DEBUG(bolt_msg_dbg) COLOR(GREEN_FG, BLACK_BG) std::cout << "DEBUG: " << bolt_msg_dbg << std::endl;
        #define BOLT_MSG_ERROR(bolt_msg_err) COLOR(RED_FG, BLACK_BG) std::cout << "ERROR: " << bolt_msg_err << std::endl;
        #define BOLT_ERROR(err) throw err;

        #define BOLT_LOG_WARNING(msg) LogUtil::log(LogType::WARNING, msg);
        #define BOLT_LOG_INFO(msg) LogUtil::log(LogType::INFO, msg);
    #else
        #define BOLT_MSG_DEBUG(string)
        #define BOLT_MSG_ERROR(bolt_msg_err)
        #define BOLT_ERROR(err)

        #define BOLT_LOG_WARNING(msg)
        #define BOLT_LOG_INFO(msg)
    #endif

    enum LogType
    {
        INFO,
        WARNING,
        ERROR
    };

    class LogUtil
    {
        public:
            LogUtil() = delete;
            LogUtil(const LogUtil&) = delete;

            static void initLogs();

            static void log(LogType, std::string, source_location s = source_location::current());

        public:
            static time_t raw_time;
            static std::string file_loc;
    };
}