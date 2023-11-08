#include "../net.h"

namespace net {
    enum class MsgTypes : uint32_t
    {
        ServerAccept,
        ServerDeny,
        ServerPing,
        MessageAll,
        ServerMessage,
        RequestScreenshot,
        RequestMouse,
        RequestKeyboard,
        Screenshot,
        Mouse,
        Keyboard
    };

}