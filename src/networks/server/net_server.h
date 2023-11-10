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

      m_threadContext = std::thread([this]()
                                    { m_asioContext.start(); });
    }
    catch (std::exception &e)
    {
      // LOG: [SERVER]: Error server. e.what()
      return false;
    }

    return true;
  }

  template <typename T>
  void IServer<T>::WaitForClientConnection()
  {
    m_asioAcceptor.async_accept([this](asio::error_code ec,
                                       tcp::socket socket))
    {
      // Prime context with an instruction to wait until a socket connects. This
      // is the purpose of an "acceptor" object. It will provide a unique socket
      // for each incoming connection attempt
      m_asioAcceptor.async_accept(
          [this](std::error_code ec, asio::ip::tcp::socket socket)
          {
            // Triggered by incoming connection request
            if (!ec)
            {
              // Display some useful(?) information
              std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << "\n";

              // Create a new connection to handle this client
              std::shared_ptr<connection<T>> newconn =
                  std::make_shared<connection<T>>(connection<T>::owner::server,
                                                  m_asioContext, std::move(socket), m_qMessagesIn);

              // Give the user server a chance to deny connection
              if (OnClientConnect(newconn))
              {
                // Connection allowed, so add to container of new connections
                m_deqConnections.push_back(std::move(newconn));

                // And very important! Issue a task to the connection's
                // asio context to sit and wait for bytes to arrive!
                m_deqConnections.back()->ConnectToClient(nIDCounter++);

                std::cout << "[" << m_deqConnections.back()->GetID() << "] Connection Approved\n";
              }
              else
              {
                std::cout << "[-----] Connection Denied\n";

                // Connection will go out of scope with no pending tasks, so will
                // get destroyed automagically due to the wonder of smart pointers
              }
            }
            else
            {
              // Error has occurred during acceptance
              std::cout << "[SERVER] New Connection Error: " << ec.message() << "\n";
            }

            // Prime the asio context with more work - again simply wait for
            // another connection...
            WaitForClientConnection();
          });
    }

    template <typename T>
    void IServer<T>::Stop()
    {
      m_asioContext.stop();

      if (m_threadContext.joinable())
        m_threadContext.join();

      // LOG [SERVER] Stop
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
      // Check client is legitimate...
      if (client && client->IsConnected())
      {
        // ...and post the message via the connection
        client->Send(msg);
      }
      else
      {
        // If we cant communicate with client then we may as
        // well remove the client - let the server know, it may
        // be tracking it somehow
        OnClientDisconnect(client);

        client.reset();

        // Then physically remove it from the container
        m_deqConnections.erase(
            std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
      }
    }

    template <typename T>
    void IServer<T>::MessageAllClients(
        const message<T> &msg,
        std::shared_ptr<session<T>> pIgnoreClient)
    {
      bool hasInvalidClient = false;

      for (auto &client : m_deqConnections)
      {
        if (client && client->IsConnected())
        {
          if (client != pIgnoreClient)
          {
            client->Send(msg);
          }
        }
        else
        {
          hasInvalidClient = true;

          OnClientDisconnect(client);
          client->reset();
        }
      }

      if (hasInvalidClient)
      {
        m_deqConnections.erase(
            std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr),
            m_deqConnections.end());
      }
    }
  }
}