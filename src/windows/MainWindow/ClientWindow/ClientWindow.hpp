#pragma once
#include "ClientNetwork.hpp"
#include <wx/wx.h>
#include <wx/mstream.h>
#include "../../../utils/Logger/WindowLogger.hpp"
#include "ClientTextWindow.hpp"


#define DEV

class ClientWindow : public net::IClient<RemoteMessage>, public wxFrame
{
public:
    ClientWindow(const std::string& host, uint16_t port);

    virtual ~ClientWindow();

private:
    const int DELAY_MS = 1;
    bool CAPTURING = false;
    bool isWaitingForConnection = true;

    wxPanel* CapturePanel = nullptr;
    wxTextCtrl* textCtrl = nullptr;

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
    void ClientWindow::OnMouseClick(wxMouseEvent& event);
    void ClientWindow::OnMouseUnClick(wxMouseEvent& event);
    void ClientWindow::OnKeyDown(wxKeyEvent& event);
    void ClientWindow::OnKeyUp(wxKeyEvent& event);
    void ClientWindow::OnMouseDoubleClick(wxMouseEvent& event);
    void ClientWindow::OnMouseMove(wxMouseEvent& event);
    // void ClientWindow::OnMouseLeave(wxMouseEvent& event);
    // void ClientWindow::OnMouseEnter(wxMouseEvent& event);
    void ClientWindow::OnMouseWheel(wxMouseEvent& event);

    // std::unique_ptr<Logger> logger = std::make_unique<Logger>(this);
};
