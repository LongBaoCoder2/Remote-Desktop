#pragma once

#include "../net_common.h"
#include "../net_message.h"
#include "../net_tsqueue.h"
namespace net
{
    template <typename T>
    class IClient
    {
    public:
        IClient();
        virtual ~IClient();

        bool Connect(const std::string &host, const uint16_t port);
        void Disconnect();
        bool IsConnected();

        void Send(const message<T> &msg);
        tsqueue<owned_message<T>> &Incoming();

    protected:
        asio::io_context m_context;
        std::thread thrContext;
        std::unique_ptr<session<T>> m_connection;

    private:
        tsqueue<owned_message<T>> m_qMessagesIn;
    };
}
