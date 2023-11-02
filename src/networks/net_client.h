#pragma once

#include "net_common.h"
#include <string>
#include <thread>
#include <memory>
#include <asio.hpp>

namespace olc
{
    namespace net
    {
        template <typename T>
        class client_interface
        {
        public:
            client_interface();
            virtual ~client_interface();

            bool Connect(const std::string &host, const uint16_t port);
            void Disconnect();
            bool IsConnected();

            void Send(const message<T> &msg);
            tsqueue<owned_message<T>> &Incoming();

        protected:
            asio::io_context m_context;
            std::thread thrContext;
            std::unique_ptr<connection<T>> m_connection;

        private:
            tsqueue<owned_message<T>> m_qMessagesIn;
        };
    }
}
