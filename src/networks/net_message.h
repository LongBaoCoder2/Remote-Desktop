#pragma once
#include "net_common.h"
#include "net_session.h"
#include <iostream>
#include <vector>
#include <memory>
#include <cstdint>

namespace net
{

    template <typename T>
    struct message_header;

    template <typename T>
    struct message;

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const message<T> &msg);

    template <typename T>
    struct owned_message;

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

        size_t size() const;

        friend std::ostream &operator<<(std::ostream &os, const message<T> &msg);

        template <typename DataType>
        friend message<T> &operator<<(message<T> &msg, const DataType &data);

        template <typename DataType>
        friend message<T> &operator>>(message<T> &msg, DataType &data);
    };

    template <typename T>
    class session;

    // Owned Message
    template <typename T>
    struct owned_message
    {
        std::shared_ptr<session<T>> remote = nullptr;
        message<T> msg;

        friend std::ostream &operator<<(std::ostream &os, const owned_message<T> &msg);
    };

}