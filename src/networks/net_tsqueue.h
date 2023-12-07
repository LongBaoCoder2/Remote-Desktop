#pragma once

#include "net_common.h"

namespace net
{
    template <typename T>
    class tsqueue
    {
    public:
        tsqueue() = default;                  // using normal constructor. It means you can do this "tsqueue a;"
        tsqueue(const tsqueue<T>&) = delete; // not allowing copy
        virtual ~tsqueue() { clear(); }       // destructor, will call the clear() function, in order to clear the queue

    public:
        const T& front()
        {
            // std::scoped_lock lock(muxQueue); // it's a mutex lock which automatically unlock when out of scope
            std::scoped_lock lock(muxQueue);
            return deqQueue.front();
        }
        const T& back()
        {
            // std::scoped_lock lock(muxQueue);
            std::scoped_lock lock(muxQueue);
            return deqQueue.back();
        }
        T pop_front()
        {
            // std::scoped_lock lock(muxQueue);
            std::scoped_lock lock(muxQueue);
            auto t = deqQueue.front();
            deqQueue.pop_front();
            return t;
        }
        T pop_back()
        {
            // std::scoped_lock lock(muxQueue);
            std::scoped_lock lock(muxQueue);
            auto t = deqQueue.back();
            deqQueue.pop_back();
            return t;
        }
        void push_back(const T& item)
        {
            // std::scoped_lock lock(muxQueue);
            std::scoped_lock lock(muxQueue);
            deqQueue.emplace_back(item);

            std::unique_lock<std::mutex> ul(muxBlocking);
            cvBlocking.notify_one();
        }
        void push_front(const T& item)
        {
            // std::scoped_lock lock(muxQueue);
            std::scoped_lock  lock(muxQueue);
            deqQueue.emplace_front(std::move(item));

            std::unique_lock<std::mutex> ul(muxBlocking);
            cvBlocking.notify_one();
        }
        bool empty()
        {
            // std::scoped_lock lock(muxQueue);
            std::scoped_lock lock(muxQueue);
            return deqQueue.empty();
        }
        size_t count()
        {
            // std::scoped_lock lock(muxQueue);
            std::scoped_lock  lock(muxQueue);
            return deqQueue.size();
        }
        void clear()
        {
            // std::scoped_lock lock(muxQueue);
            std::scoped_lock lock(muxQueue);
            deqQueue.clear();
        }
        void wait()
        {
            while (empty())
            {
                std::unique_lock<std::mutex> ul(muxBlocking);
                /*
                    Because the push_front and push_back also need to lock the same mutex to add a message and send a signal,
                    it can't add a message to the queue between the wait's empty check and the condition_variable starting to wait.
                    If the queue is empty and the wait starts to wait, it will automatically release the mutex and
                    enter the waiting state. If the producer adds a message, it will lock the mutex, add the message, and
                    then send the signal. Since the mutex ensures exclusive access, the wait won't miss the signal.
                */
                cvBlocking.wait(ul, [this]
                    { return !empty(); }); // lambda function is kinda the double check, to prevent spurious wake-up
            }
        }

    protected:
        std::mutex muxQueue;
        std::deque<T> deqQueue;
        std::condition_variable cvBlocking;
        std::mutex muxBlocking;
    };
}