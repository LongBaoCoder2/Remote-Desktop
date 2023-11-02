#pragma once

#include "net_common.h"

namespace net
{
    template <typename T>
    class tsqueue
    {
    public:
        tsqueue() = default;
        tsqueue(const tsqueue<T> &) = delete;
        virtual ~tsqueue() { clear(); }

    public:
        const T &front();
        const T &back();
        T pop_front();
        T pop_back();
        void push_back(const T &item);
        void push_front(const T &item);
        bool empty();
        size_t count();
        void clear();
        void wait();

    protected:
        std::mutex muxQueue;
        std::deque<T> deqQueue;
        std::condition_variable cvBlocking;
        std::mutex muxBlocking;
    };
}