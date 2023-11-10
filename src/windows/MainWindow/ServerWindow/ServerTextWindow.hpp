#include "../../BasicTextWindow/BasicTextFrame.hpp"

class ServerTextWindow : public BasicTextFrame {
public:
    ServerTextWindow(const wxString& title = "Server Logger", const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(1920 / 4, 1080 / 2));
};