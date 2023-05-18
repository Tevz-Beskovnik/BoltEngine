#include <log.hpp>

namespace bolt
{
    #ifdef BOLT_DEBUG
    uint32_t LogUtil::raw_time = std::chrono::system_clock::now().time_since_epoch().count();
    std::string LogUtil::file_loc = std::string{BOLT_LOG_FILE} + "/log" + std::to_string(LogUtil::raw_time) + ".log";

    void LogUtil::initLogs()
    {
        auto start = std::chrono::system_clock::now();
        std::ifstream file;
        file.open(file_loc.c_str());
        file.close();
    }

    void LogUtil::error(std::string err)
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);

        FILE* f;
        f = fopen(file_loc.c_str(), "ab");
        std::string out = std::string(buffer) + " ERROR: " + err + '\n';
        fwrite(out.c_str(), 1, out.size()*sizeof(char), f);
        fclose(f);
    }

    void LogUtil::warning(std::string warning)
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);

        FILE* f;
        f = fopen(file_loc.c_str(), "ab");
        std::string out = std::string(buffer) + " WARNING: " + warning + '\n';
        fwrite(out.c_str(), 1, out.size()*sizeof(char), f);
        fclose(f);
    }

    void LogUtil::info(std::string info)
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);

        FILE* f;
        f = fopen(file_loc.c_str(), "ab");
        std::string out = std::string(buffer) + " INFO: " + info + '\n';
        fwrite(out.c_str(), 1, out.size()*sizeof(char), f);
        fclose(f);
    }
    #endif
}