#include "net_session.h"

namespace net
{
    template <typename T>
    session<T>::session(owner parent, asio::io_context &asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>> &qIn)
        : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn)
    {
        m_nOwnerType = parent;
    }

    template <typename T>
    virtual session<T>::~session()
    {
    }

    // Get session ID
    template <typename T>
    uint32_t session<T>::GetID() const
    {
        return id;
    }

    template <typename T>
    void session<T>::ConnectToClient(uint32_t uid)
    {
        if (m_nOwnerType == owner::server && m_socket.is_open())
        {
            id = uid;
            this->ReadHeader();
        }
    }

    template <typename T>
    void session<T>::ConnectToServer(const asio::ip::tcp::resolver::results_type &endpoints)
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

    template <typename T>
    void session<T>::Disconnect()
    {
        if (this->IsConnected())
            asio::post(m_asioContext, [this]()
                       { m_socket.close(); })
    }

    template <typename T>
    bool session<T>::IsConnected() const
    {
        return m_socket.is_open();
    }
}