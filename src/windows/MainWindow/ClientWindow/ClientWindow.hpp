#pragma once
#include "ClientNetwork.hpp"
#include <wx/wx.h>
#include <wx/mstream.h>
#include "../../../utils/Logger/WindowLogger.hpp"

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
    wxTextCtrl* textCtrl = nullptr;

    wxTimer *timer;
    wxScreenDC screenDC;
    wxBitmap screenshot;

    void UpdatePanel();
    void ClearPanel();
    void OnUpdateWindow(wxTimerEvent &);

    // std::unique_ptr<Logger> logger = std::make_unique<Logger>(this);
};
