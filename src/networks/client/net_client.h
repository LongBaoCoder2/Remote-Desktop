#pragma once

#include "../net_common.h"
#include "../net_message.h"
#include "../net_tsqueue.h"
#include "../net_session.h"

#include "../../windows/constant.hpp"

// WARNING: ALL TEMPLATE FUNCTION DEFINITIONS MUST BE IN SAME HPP FILE
// https://stackoverflow.com/a/495056
namespace net {
  template <typename T>
  class IClient {
  public:
    IClient();
    virtual ~IClient();

    bool ConnectToServer(const std::string& host);
    void Disconnect();
    bool IsConnected();

    void Send(const message<T>& msg);
    tsqueue<owned_message<T>>& Incoming();

  protected:
    asio::io_context m_context;
    std::thread thrContext;

    std::unique_ptr<session<T>> m_connectionImage;
    std::unique_ptr<session<T>> m_connectionEvent;

  private:
    tsqueue<owned_message<T>> m_qMessagesIn;
  };

  template <typename T>
  IClient<T>::IClient() {}

  template <typename T>
  IClient<T>::~IClient() {
    // If the client is destroyed, always try and disconnect from server
    Disconnect();
  }

  // Connect to server with hostname/ip-address and port
  template <typename T>
  bool IClient<T>::ConnectToServer(const std::string& host) {
    try {
      // Resolve hostname/ip-address into tangiable physical address
      asio::ip::tcp::resolver resolver(m_context);

      asio::ip::tcp::resolver::results_type endpoints =
        resolver.resolve(host, std::to_string(CONFIG_APP::IMAGE_PORT));

      // Create connection
      m_connectionImage = std::make_unique<session<T>>(
        session<T>::owner::client, m_context,
        asio::ip::tcp::socket(m_context), m_qMessagesIn);

      // Tell the connection object to connect to server
      m_connectionImage->ConnectToServer(endpoints);


      endpoints = resolver.resolve(host, std::to_string(CONFIG_APP::EVENT_PORT));

      // Create connection
      m_connectionEvent = std::make_unique<session<T>>(
        session<T>::owner::client, m_context,
        asio::ip::tcp::socket(m_context), m_qMessagesIn);

      // Tell the connection object to connect to server
      m_connectionEvent->ConnectToServer(endpoints);


      // Start Context Thread
      thrContext = std::thread([this]() { m_context.run(); });
    }
    catch (std::exception& e) {
      std::cerr << "Client Exception: " << e.what() << "\n";
      return false;
    }
    return true;
  }

  // Disconnect from server
  template <typename T>
  void IClient<T>::Disconnect() {
    // If connection exists, and it's connected then...
    if (IsConnected()) {
      // ...disconnect from server gracefully
      m_connectionEvent->Disconnect();
      m_connectionImage->Disconnect();
    }

    // Either way, we're also done with the asio context...
    m_context.stop();
    // ...and its thread
    if (thrContext.joinable()) thrContext.join();

    // Destroy the connection object
    m_connectionEvent.release();
    m_connectionImage.release();
  }

  // Check if client is actually connected to a server
  template <typename T>
  bool IClient<T>::IsConnected() {
    if (m_connectionEvent && m_connectionImage)
      return m_connectionEvent->IsConnected() && m_connectionImage->IsConnected();

    return false;
  }

  // Send message to server
  template <typename T>
  void IClient<T>::Send(const message<T>& msg) {
    if (IsConnected()) m_connectionEvent->Send(msg);
  }

  // Retrieve queue of messages from server
  template <typename T>
  tsqueue<owned_message<T>>& IClient<T>::Incoming() {
    return m_qMessagesIn;
  }
}  // namespace net
