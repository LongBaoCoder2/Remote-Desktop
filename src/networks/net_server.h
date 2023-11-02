#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include "net_session.h"

namespace net
{
    template <typename T>
    class server_interface
    {
    public:
        server_interface(uint16_t port);
        virtual ~server_interface();

        bool Start();
        void Stop();
        void WaitForClientConnection();

        void MessageClient(std::shared_ptr<session<T>> client, const message<T> &msg);
        void MessageAllClients(const message<T> &msg, std::shared_ptr<session<T>> pIgnoreClient = nullptr);
        void Update(size_t nMaxMessages = -1, bool bWait = false);

    protected:
        virtual bool OnClientConnect(std::shared_ptr<session<T>> client);
        virtual void OnClientDisconnect(std::shared_ptr<session<T>> client);
        virtual void OnMessage(std::shared_ptr<session<T>> client, message<T> &msg);

    protected:
        tsqueue<owned_message<T>> m_qMessagesIn;
        std::deque<std::shared_ptr<session<T>>> m_deqConnections;

        asio::io_context m_asioContext;
        std::thread m_threadContext;
        asio::ip::tcp::acceptor m_asioAcceptor;
        uint32_t nIDCounter = 10000;
    };
}