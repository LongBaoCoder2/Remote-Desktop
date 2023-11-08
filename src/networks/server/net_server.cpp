#include "net_server.h"

namespace net {

template <typename T>
IServer<T>::IServer(uint16_t port)
    : m_asioAcceptor(m_asioContext,
                     asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

template <typename T>
IServer<T>::~IServer() {
  Stop();
}

template <typename T>
bool IServer<T>::Start() {
  try {
    WaitForClientConnection();

    m_asioThread = std::thread([this] { m_asioContext.start(); });
  }
  except(std::exception & e) {
    // LOG: [SERVER]: Error server. e.what()
    return false;
  }

  return true;
}

template <typename T>
void IServer<T>::WaitForClientConnection() {
  m_asioAcceptor.async_accept([this](asio::error_code & ec,
                                     tcp::socket socket)) {
    // If not raise error
    if (!ec) {
      // Make session
      std::share_ptr<session<T>> newConnection =
          std::make_shared<session<T>>(session<T>::owner::server, m_asioContext,
                                       std::move(socket), m_qMessagesIn);

      // Authentication
      if (OnClientConnect(newConnection)) {
        // Authenticate successfully
        m_deqConnections.push_back(std::move(newConnection));

        // This will make the asio context unable to 'idle' and
        // work continuously, causing the asio context to not stop
        m_deqConnections.front()->ConnectToClient(nIDCounter++);

        // LOG [Server]: New Session: Accept <nIDCounter>
      } else {
        // LOG [Session] : Connection Denied
        // When user fails authentication, newConnection will go out of scope
        // and get destroyed automatically
      }
    } else {
      // LOG [Session]: A new connection has wrong <ec.message()>
    }
  }
  WaitForClientConnection();
}

template <typename T>
void IServer<T>::Stop() {
  m_asioContext.stop();

  if (m_threadContext.joinable()) m_threadContext.join();

  // LOG [SERVER] Stop
}

template <typename T>
void IServer<T>::Update(size_t nMaxMessages = -1, bool bWait = false) {
  if (bWait) m_qMessagesIn.wait();

  size_t nCountMessage = 0;
  while (nCountMessage++ < nMaxMessages && !m_deqConnections.empty()) {
    auto msg = m_deqConnections.pop_front();

    OnMessage(msg.remote, msg.msg);
  }
}

template <typename T>
void IServer<T>::MessageClient(std::shared_ptr<session<T>> client,
                               const message<T> &msg) {
  if (client && client->IsConnected()) {
    client->Send(msg);
  } else {
    OnClientDisconnect(client);

    // std::shared_ptr<T>::reset set value to default
    client->reset();

    // std::remove will shift all elements that need to be removed
    // and std::erase will remove all it
    m_deqConnections.erase(
        std::remove(m_deqConnections.begin(), m_deqConnections.end(), client),
        m_deqConnections.end());
  }
}

template <typename T>
void IServer<T>::MessageAllClients(
    const message<T> &msg,
    std::shared_ptr<session<T>> pIgnoreClient = nullptr) {
  bool hasInvalidClient = false;

  for (auto &client : m_deqConnections) {
    if (client && client->IsConnected()) {
      if (client != pIgnoreClient) {
        client->Send(msg);
      }
    } else {
      hasInvalidClient = true;

      OnClientDisconnect(client);
      client->reset();
    }
  }

  if (hasInvalidClient) {
    m_deqConnections.erase(
        std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr),
        m_deqConnections.end());
  }
}

}  // namespace net