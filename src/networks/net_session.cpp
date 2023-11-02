#include "net_session.h"

namespace net
{
    session::session(owner parent, asio::io_context &asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>> &qIn)
        : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn)
    {
        m_nOwnerType = parent;
    }

    virtual session::~session()
    {
    }

    // Get session ID
    uint32_t session::GetID() const
    {
        return id;
    }

    void session::ConnectToClient(uint32_t uid = 0)
    {
        if (m_nOwnerType == owner::server && m_socket.is_open())
        {
            id = uid;
            this->ReadHeader();
        }
    }

    void session::ConnectToServer(const asio::ip::tcp::resolver::results_type &endpoints)
    {
        if (m_nOwnerType == owner::client)
        {
            asio::async_connect(m_socket, endpoints,
                                [this](asio::error_code ec, asio::ip::tcp::endpoint endpoint)
                                {
                                    if (!ec)
                                        this->ReadHead();
                                })
        }
    }

    void session::Disconnect()
    {
        if (this->IsConnected())
            asio::post(m_asioContext, [this]()
                       { m_socket.close(); })
    }

    bool session::IsConnected() const
    {
        return m_socket.is_open();
    }
}