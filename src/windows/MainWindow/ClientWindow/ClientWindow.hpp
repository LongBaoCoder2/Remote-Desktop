#pragma once
#include "ClientNetwork.hpp"
#include <wx/wx.h>
#include "../../utils/Logger/WindowLogger.hpp"
#define DEV

class ClientWindow : public net::IClient<RemoteMessage>, public wxFrame
{
public:
    ClientWindow(const std::string &host, uint16_t port);

    virtual ~ClientWindow();

private:
    const int DELAY_MS = 6;
    bool CAPTURING = false;
    bool isWaitingForConnection = true;

    wxPanel *CapturePanel = nullptr;

    wxTimer *timer;
    wxScreenDC screenDC;
    wxBitmap screenshot;

    void UpdatePanel();
    void ClearPanel();
    void OnUpdateWindow(wxTimerEvent &);

#ifdef DEV
    std::unique_ptr<Logger> logger;
#endif

#ifdef DEV
    logger = std::make_unique<Logger>(this);
#endif
};
