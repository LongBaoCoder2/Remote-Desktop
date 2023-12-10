#include "../../../BasicTextWindow/BasicTextFrame.hpp"

class ClientTextWindow : public BasicTextFrame {
public:
    ClientTextWindow(const wxString& title = "Client Logger", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1920 / 4, 1080 / 2));
    void DisplayMessage(const wxString& message = "Default client message.");

private:
};