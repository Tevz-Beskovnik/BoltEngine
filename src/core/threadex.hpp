#pragma once

#include <core.hpp>
#include <util.hpp>

#if defined(WINDOWS) ||  defined(_WIN32)
#include <Windows.h>
#elif defined(__unix__ ) || defined(unix) || defined(__unix) || defined(__APPLE__)
#include <pthread.h>
#endif

namespace bolt {
    enum ThreadPriority {
        LOWEST,
        LOWER,
        LOW,
        NORMAL,
        HIGH,
        HIGHEST,
        REAL_TIME
    };

    class Thread {
    public:
        explicit Thread(ThreadPriority priority = NORMAL);

        void init();

        void set_thread_priority(ThreadPriority priority);

        void wait_for();

        std::thread::id get_thread_id();

    protected:
        virtual void execute() = 0;

    private:
        single_ptr<std::thread> thread_handle;
        ThreadPriority priority;
    };
}
