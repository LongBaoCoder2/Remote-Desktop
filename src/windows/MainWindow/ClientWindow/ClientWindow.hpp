#pragma once
#include "ClientNetwork.hpp"
#include <wx/wx.h>
#include <wx/mstream.h>
#include <wx/overlay.h>
#include "../../../utils/Logger/WindowLogger.hpp"
#include "ClientTextWindow.hpp"


#define DEV

class ClientWindow : public net::IClient<RemoteMessage>, public wxFrame
{
public:
    ClientWindow(const std::string& host, uint16_t port);

    virtual ~ClientWindow();

private:
    const int DELAY_MS = 10;
    bool CAPTURING = false;
    bool isWaitingForConnection = true;

    wxPanel* CapturePanel = nullptr;
    wxPanel* MouseKeyPanel = nullptr;
    wxTextCtrl* textCtrl = nullptr;
    wxOverlay* overlay = nullptr;

    wxTimer* timer;
    wxTimer* secondTimer;
    wxScreenDC screenDC;
    wxBitmap screenshot;

    ClientTextWindow* clientTextWindow = nullptr;

    int imagesSentThisSecond = 0;

    void UpdatePanel();
    void ClearPanel();
    void OnUpdateWindow(wxTimerEvent&);
    void OnReceiveImage(net::message<RemoteMessage>& msg);
    void OnSecondTimer(wxTimerEvent& event);
    void OnMouseClick(wxMouseEvent& event);
    void OnMouseUnClick(wxMouseEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnMouseDoubleClick(wxMouseEvent& event);
    // void ClientWindow::OnMouseMove(wxMouseEvent& event);
    // void ClientWindow::OnMouseLeave(wxMouseEvent& event);
    // void ClientWindow::OnMouseEnter(wxMouseEvent& event);
    void OnMouseWheel(wxMouseEvent& event);

    // std::unique_ptr<Logger> logger = std::make_unique<Logger>(this);
};
