#include <log.hpp>

namespace bolt
{
    time_t LogUtil::raw_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string LogUtil::file_loc = std::string{BOLT_LOG_FILE} + "/log" + std::to_string(LogUtil::raw_time) + ".log";

    const char* log_type_strings[] = {
        ENUM_TO_STRING(INFO),
        ENUM_TO_STRING(WARNING),
        ENUM_TO_STRING(ERROR)
    };

    void LogUtil::initLogs()
    {
        auto start = std::chrono::system_clock::now();
        std::ifstream file;
        file.open(file_loc.c_str());
        file.close();
    }

    void LogUtil::log(LogType t, const std::string& err, source_location s)
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);

        FILE* f;
        f = fopen(file_loc.c_str(), "ab");
        std::string out = std::string(buffer) + " " +
            log_type_strings[t] +
            " [" + s.function_name() + "#" + std::to_string(s.line()) + "] " +
            err +
            '\n';
        fwrite(out.c_str(), 1, out.size()*sizeof(char), f);
        fclose(f);
    }
}