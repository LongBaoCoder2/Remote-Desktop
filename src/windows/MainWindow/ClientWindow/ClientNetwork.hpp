#pragma once

#include "../../../networks/net.h"

enum class RemoteMessage : uint32_t
{
    SERVER_ACCEPT,
    SERVER_DENY,
    SERVER_UPDATE,
    CLIENT_ACCEPT
};