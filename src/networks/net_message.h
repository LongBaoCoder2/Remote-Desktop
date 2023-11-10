#pragma once
#include "net_common.h"

namespace net
{

    // Message Header
    template <typename T>
    struct message_header
    {
        T id{};
        uint32_t size = 0;
    };

    // Message Body
    template <typename T>
    struct message
    {
        message_header<T> header{};
        std::vector<uint8_t> body;

        size_t size() const
        {
            // Return entire message size
            return body.size();
        }

        friend std::ostream &operator<<(std::ostream &os, const message<T> &msg)
        {
            os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
            return os;
        }

        template <typename DataType>
        friend message<T> &operator<<(message<T> &msg, const DataType &data)
        {
            size_t i = msg.body.size();

            msg.body.resize(msg.body.size() + sizeof(DataType));

            std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

            msg.header.size = msg.size();

            return msg;
        }

        template <typename DataType>
        friend message<T> &operator>>(message<T> &msg, DataType &data)
        {
            size_t i = msg.body.size() - sizeof(DataType);

            std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

            msg.body.resize(i);

            msg.header.size = msg.size();

            return msg;
        }

        // template <typename DataType>
        // friend message<T> &operator<<(message<T> &msg, const vector<DataType> &data)
        // {
        //     size_t i = 0;

        //     msg.body.resize(i + data.size());

        //     std::memcpy(msg.body.data(), data.data(), data.size());

        //     msg.header.size = msg.size();

        //     return msg;
        // }

        // template <typename DataType>
        // friend message<T> &operator>>(message<T> &msg, vector<DataType> &data)
        // {
        //     size_t sizeOfMsg = msg.body.size();

        //     std::memcpy(data.data(), msg.body.data(), sizeOfMsg);

        //     msg.body.resize(0);

        //     msg.header.size = msg.size();

        //     return msg;
        // }
    };

    template <typename T>
    class session;

    // Owned Message
    template <typename T>
    struct owned_message
    {
        std::shared_ptr<session<T>> remote;
        message<T> msg;

        // Again, a friendly string maker
        friend std::ostream &operator<<(std::ostream &os, const owned_message<T> &msg)
        {
            os << msg.msg;
            return os;
        }
    };
}