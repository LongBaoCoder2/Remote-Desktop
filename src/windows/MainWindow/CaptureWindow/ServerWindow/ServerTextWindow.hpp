#include "../../../BasicTextWindow/BasicTextFrame.hpp"

class ServerTextWindow : public BasicTextFrame {
public:
    ServerTextWindow(const wxString& title = "Server Logger", const wxPoint& pos = wxDefaultPosition, const wxSize& size = CONFIG_UI::VERY_SMALL_WINDOW);
};