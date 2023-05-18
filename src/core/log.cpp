#include <log.hpp>

namespace bolt
{
    uint32_t LogUtil::time = std::chrono::system_clock::now().time_since_epoch().count();
    std::string LogUtil::file_loc = std::string{BOLT_LOG_FILE} + "/log" + std::to_string(LogUtil::time) + ".txt";

    void LogUtil::initLogs()
    {
        auto start = std::chrono::system_clock::now();
        std::ifstream file;
        file.open(file_loc.c_str());
        file.close();
    }

    void LogUtil::error(std::string err)
    {
        FILE* f;
        f = fopen(file_loc.c_str(), "wb");
        std::string out = "ERROR: " + err;
        fwrite(out.c_str(), 1, out.size()*sizeof(char), f);
        fclose(f);
    }

    void LogUtil::warning(std::string warning)
    {
        FILE* f;
        f = fopen(file_loc.c_str(), "wb");
        std::string out = "WARNING: " + warning;
        fwrite(out.c_str(), 1, out.size()*sizeof(char), f);
        fclose(f);
    }

    void LogUtil::info(std::string info)
    {
        FILE* f;
        f = fopen(file_loc.c_str(), "wb");
        std::string out = "INFO: " + info;
        fwrite(out.c_str(), 1, out.size()*sizeof(char), f);
        fclose(f);
    }
}