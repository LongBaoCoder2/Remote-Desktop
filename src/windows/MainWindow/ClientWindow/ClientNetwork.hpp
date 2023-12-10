#pragma once

#include "../../../networks/net.h"

enum class RemoteMessage : uint32_t
{
    SERVER_ACCEPT,
    SERVER_DENY,
    SERVER_UPDATE,
    SERVER_DISCONNECT,
    CLIENT_ACCEPT,
    MouseClick,
    MouseUnClick,
    KeyPress,
    KeyRelease,
    DoubleClick,
    MouseMove,
    MouseLeave,
    MouseEnter,
    MouseWheel
};
