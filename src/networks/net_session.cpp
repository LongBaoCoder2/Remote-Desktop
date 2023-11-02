#include "net_session.h"

namespace net {

template <typename T>
session<T>::session(owner parent, asio::io_context &asioContext,
                    asio::ip::tcp::socket socket,
                    tsqueue<owned_message<T>> &qIn)
    : m_asioContext(asioContext),
      m_socket(std::move(socket)),
      m_qMessagesIn(qIn) {
  m_nOwnerType = parent;
}

template <typename T>
session<T>::~session() {}

// Get session ID
uint32_t session::GetID() const { return id; }

template <typename T>
void session<T>::ConnectToClient(uint32_t uid) {
  if (m_nOwnerType == owner::server && m_socket.is_open()) {
    id = uid;
    this->ReadHeader();
  }
}

template <typename T>
void session<T>::ConnectToServer(
    const asio::ip::tcp::resolver::results_type &endpoints) {
  if (m_nOwnerType == owner::client) {
    asio::async_connect(
        m_socket, endpoints,
        [this](asio::error_code ec, asio::ip::tcp::endpoint endpoint) {
          if (!ec) this->ReadHead();
        })
  }
}

template <typename T>
void session<T>::Disconnect() {
  if (this->IsConnected())
    asio::post(m_asioContext, [this]() { m_socket.close(); })
}

template <typename T>
bool session<T>::IsConnected() const {
  return m_socket.is_open();
}

// ASYNC - Send a message, connections are one-to-one so no need to specifiy
// the target, for a client, the target is the server and vice versa
// session::Send - send message from a host to another host.
template <typename T>
void session<T>::Send(const message<T> &msg) {
  asio::post(m_asioContext, [ this, msg ]({
               // If the queue has a message in it, then we must
               // assume that it is in the process of asynchronously being
               // written. Either way add the message to the queue to be output.
               // If no messages
               // were available to be written, then start the process of
               // writing the message at the front of the queue.

               // Ve co ban thi bien bool nay giup chung ta biet duoc trong
               // queue co dang giu message nao hay khong Tai sao dieu nay lai
               // quan trong? Boi vi neu trong queue van con message thi ham
               // WriteHeader dang duoc goi o dau do Ma chung ta lai goi no o
               // day thi se dan den viec xung dot hoac thu tu goi tin gui qua
               // ben kia bi xao tron vi ta da goi ham WriteHeader khong dung
               // theo thu tu cac message
               bool bWritingMessage = m_qMessagesOut.empty();

               // Con dong nay thi chay binh thuong vi day chi don gian la bo
               // msg vao trong queue
               m_qMessagesOut.push_back(msg);

               // Neu khong con msg trong queue dang duoc xu li thi goi
               // WriteHeader de gui msg moi add vo queue
               if (!bWritingMessage) {
                 WriteHeader();
               }
             }));
}

// ASYNC - Prime context to write a message header
template <typename T>
void session<T>::WriteHeader() {
  // If this function is called, we know the outgoing message queue must have
  // at least one message to send. So allocate a transmission buffer to hold
  // the message, and issue the work - asio, send these bytes
  asio::async_write(
      m_socket,
      asio::buffer(&m_qMessagesOut.front().header, sizeof(message_header<T>)),
      [this](std::error_code ec, std::size_t length) {
        // asio has now sent the bytes - if there was a problem
        // an error would be available...
        if (!ec) {
          // ... no error, so check if the message header just sent also
          // has a message body...
          if (m_qMessagesOut.front().body.size() > 0) {
            // ...it does, so issue the task to write the body bytes
            WriteBody();
          } else {
            // ...it didnt, so we are done with this message. Remove it from
            // the outgoing message queue
            m_qMessagesOut.pop_front();

            // If the queue is not empty, there are more messages to send, so
            // make this happen by issuing the task to send the next header.
            if (!m_qMessagesOut.empty()) {
              WriteHeader();
            }
          }
        } else {
          // ...asio failed to write the message, we could analyse why but
          // for now simply assume the connection has died by closing the
          // socket. When a future attempt to write to this client fails due
          // to the closed socket, it will be tidied up.
          std::cout << "[" << id << "] Write Header Fail.\n";
          m_socket.close();
        }
      });
}

// ASYNC - Prime context to write a message body
template <typename T>
void session<T>::WriteBody() {
  // If this function is called, a header has just been sent, and that header
  // indicated a body existed for this message. Fill a transmission buffer
  // with the body data, and send it!
  asio::async_write(m_socket,
                    asio::buffer(m_qMessagesOut.front().body.data(),
                                 m_qMessagesOut.front().body.size()),
                    [this](std::error_code ec, std::size_t length) {
                      if (!ec) {
                        // Sending was successful, so we are done with the
                        // message and remove it from the queue
                        m_qMessagesOut.pop_front();

                        // If the queue still has messages in it, then issue the
                        // task to send the next messages' header.
                        if (!m_qMessagesOut.empty()) {
                          WriteHeader();
                        }
                      } else {
                        // Sending failed, see WriteHeader() equivalent for
                        // description :P
                        std::cout << "[" << id << "] Write Body Fail.\n";
                        m_socket.close();
                      }
                    });
}
}  // namespace net