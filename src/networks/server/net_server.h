#pragma once

#include "../net_common.h"
#include "../net_message.h"
#include "../net_session.h"
#include "../net_tsqueue.h"

// WARNING: ALL TEMPLATE FUNCTION DEFINITIONS MUST BE IN SAME HPP FILE
// https://stackoverflow.com/a/495056

namespace net
{
  template <typename T>
  class IServer
  {
  public:
    IServer(uint16_t port);
    virtual ~IServer();

    bool Start();
    void Stop();
    void WaitForClientConnection();

    void MessageClient(std::shared_ptr<session<T>> client, const message<T> &msg);
    void MessageAllClients(const message<T> &msg,
                           std::shared_ptr<session<T>> pIgnoreClient = nullptr);
    void Update(size_t nMaxMessages = -1, bool bWait = false);

  protected:
    virtual bool OnClientConnect(std::shared_ptr<session<T>> client) = 0;
    virtual void OnClientDisconnect(std::shared_ptr<session<T>> client) = 0;
    virtual void OnMessage(std::shared_ptr<session<T>> client, message<T> &msg) = 0;

  protected:
    tsqueue<owned_message<T>> m_qMessagesIn;
    std::deque<std::shared_ptr<session<T>>> m_deqConnections;

    asio::io_context m_asioContext;
    std::thread m_threadContext;
    asio::ip::tcp::acceptor m_asioAcceptor;
    uint32_t nIDCounter = 10000;
  };
  template <typename T>
  IServer<T>::IServer(uint16_t port)
      : m_asioAcceptor(m_asioContext,
                       asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

  template <typename T>
  IServer<T>::~IServer()
  {
    Stop();
  }

  template <typename T>
  bool IServer<T>::Start()
  {
    try
    {
      WaitForClientConnection();

      m_threadContext = std::thread([this]
                                    { m_asioContext.run(); });
    }
    catch (const std::exception &e)
    {
      std::cout << e.what() << std::endl;
      return false;
    }

    return true;
  }

  template <typename T>
  void IServer<T>::WaitForClientConnection()
  {
    m_asioAcceptor.async_accept([this](std::error_code ec,
                                       asio::ip::tcp::socket socket)
                                {
      // If not raise error
      if (!ec)
      {

        // Make session
        std::shared_ptr<session<T>> newConnection =
            std::make_shared<session<T>>(session<T>::owner::server, m_asioContext,
                                         std::move(socket), m_qMessagesIn);

        // Authentication
        if (OnClientConnect(newConnection))
        {
          // Authenticate successfully
          m_deqConnections.push_back(std::move(newConnection));

          // This will make the asio context unable to 'idle' and
          // work continuously, causing the asio context to not stop
          m_deqConnections.back()->ConnectToClient(nIDCounter++);

        }
        else
        {
          // When user fails authentication, newConnection will go out of scope
          // and get destroyed automatically
        }
      }
      else
      {
      }  
      WaitForClientConnection(); 
    });
  }

  template <typename T>
  void IServer<T>::Stop()
  {
    m_asioContext.stop();

    if (m_threadContext.joinable())
      m_threadContext.join();
  }

  template <typename T>
  void IServer<T>::Update(size_t nMaxMessages, bool bWait)
  {
    if (bWait)
      m_qMessagesIn.wait();

    size_t nCountMessage = 0;
    while (nCountMessage++ < nMaxMessages && !m_deqConnections.empty())
    {
      auto msg = m_deqConnections.pop_front();

      OnMessage(msg.remote, msg.msg);
    }
  }

  template <typename T>
  void IServer<T>::MessageClient(std::shared_ptr<session<T>> client,
                                 const message<T> &msg)
  {
    if (client && client->IsConnected())
    {
      client->Send(msg);
    }
    else
    {
      OnClientDisconnect(client);

      // std::shared_ptr<T>::reset set value to default
      client.reset();

      // std::remove will shift all elements that need to be removed
      // and std::erase will remove all it
      m_deqConnections.erase(
          std::remove(m_deqConnections.begin(), m_deqConnections.end(), client),
          m_deqConnections.end());
    }
  }

  template <typename T>
  void IServer<T>::MessageAllClients(const message<T> &msg, std::shared_ptr<session<T>> pIgnoreClients)
  {
    bool hasInvalidClient = false;

    for (auto &client : m_deqConnections)
    {
      if (client && client->IsConnected())
      {
        if (client != pIgnoreClients)
        {
          client->Send(msg);
        }
      }
      else
      {
        hasInvalidClient = true;

        OnClientDisconnect(client);
        client.reset();
      }
    }

    if (hasInvalidClient)
    {
      m_deqConnections.erase(
          std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr),
          m_deqConnections.end());
    }
  }

} // namespace net