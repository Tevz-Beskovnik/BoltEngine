//
// Created by Tevz on 2. 9. 24.
//

#include <threadex.hpp>

namespace bolt {
    Thread::Thread(ThreadPriority priority)
        : priority(priority) {
        ;
    }

    void Thread::init() {
        if (thread_handle)
            throw std::runtime_error("Thread already started");

        thread_handle = create_single<std::thread>(&Thread::execute, this);
#if defined(WINDOWS) || defined(_WIN32)
#pragma message("Thread priorities aren't implemented for windows")
#elif defined(__unix__ ) || defined(unix) || defined(__unix) || defined(__APPLE__)
        struct sched_param param; // scheduler parameter
        int32_t scheduler_policy; // scheduler policy
        switch (priority) {
            case LOWEST:
                param.sched_priority = -20;
                scheduler_policy = SCHED_OTHER;
                break;
            case LOWER:
                param.sched_priority = -10;
                scheduler_policy = SCHED_OTHER;
                break;
            case LOW:
                param.sched_priority = -5;
                scheduler_policy = SCHED_OTHER;
                break;
            case NORMAL:
                param.sched_priority = 0;
                scheduler_policy = SCHED_OTHER;
                break;
            case HIGH:
                param.sched_priority = 10;
                scheduler_policy = SCHED_OTHER;
                break;
            case HIGHEST:
                param.sched_priority = 19;
                scheduler_policy = SCHED_OTHER;
                break;
            case REAL_TIME:
                param.sched_priority = 99;
                scheduler_policy = SCHED_FIFO;
                break;
            default: // default to normal
                param.sched_priority = 0;
                scheduler_policy = SCHED_OTHER;
                break;
        }

        pthread_setschedparam(thread_handle->native_handle(), scheduler_policy, &param);
#endif
    }

    void Thread::wait_for()
    {
        if(thread_handle)
        {
            if(thread_handle->joinable())
                thread_handle->join();
            thread_handle.reset();
        }
    }

    void Thread::set_thread_priority(ThreadPriority priority)
    {
        this->priority = priority;
    }

    std::thread::id Thread::get_thread_id()
    {
        return thread_handle->get_id();
    }
}
