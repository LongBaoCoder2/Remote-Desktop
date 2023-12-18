#pragma once

#include "../../../../networks/net.h"
#include "ClientTextWindow.hpp"
#include "KeylogWindow.hpp"
#include "../../../constant.hpp"


enum class RemoteMessage : uint32_t
{
    SERVER_ACCEPT,
    SERVER_DENY,
    SERVER_UPDATE,
    SERVER_DISCONNECT,
    CLIENT_ACCEPT,
    CLIENT_DISCONNECT,
    MouseClick,
    MouseUnClick,
    KeyPress,
    KeyRelease,
    DoubleClick,
    MouseMove,
    MouseLeave,
    MouseEnter,
    MouseWheel,
    MetaData,
    CaptureRequest,
    CaptureSend
};
