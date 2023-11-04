#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include <asio.hpp>

namespace net
{

    template <typename T>
    class session : public std::enable_shared_from_this<session<T>>
    {

    public:
        enum class owner : uint16_t
        {
            server,
            client
        };

    public:
        session(owner parent, asio::io_context &asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>> &qIn);
        virtual ~session();

        uint32_t GetID() const;

    public:
        void ConnectToClient(uint32_t uid = 0);
        void ConnectToServer(const asio::ip::tcp::resolver::results_type &endpoints);
        void Disconnect();
        bool IsConnected() const;
        void StartListening();
        void Send(const message<T> &msg);

    private:
        void WriteHeader();
        void WriteBody();
        void ReadHeader();
        void ReadBody();
        void AddToIncomingMessageQueue();

    protected:
        asio::ip::tcp::socket m_socket;
        asio::io_context &m_asioContext;
        tsqueue<message<T>> m_qMessagesOut;
        tsqueue<owned_message<T>> &m_qMessagesIn;
        message<T> m_msgTemporaryIn;
        owner m_nOwnerType = owner::server;
        uint32_t id = 0;
    };
}
