#pragma once

#include "ServerNetwork.hpp"
#include <wx/wx.h>
#include <wx/mstream.h>
#include <atomic>

class ServerWindow : public net::IServer<RemoteMessage>, public wxFrame
{
public:
    ServerWindow();
    virtual ~ServerWindow();

protected:
    bool OnClientConnect(std::shared_ptr<net::session<RemoteMessage>> client) override;
    void OnClientDisconnect(std::shared_ptr<net::session<RemoteMessage>> client) override;
    void OnMessage(std::shared_ptr<net::session<RemoteMessage>> client, net::message<RemoteMessage>& msg) override;

private:
    void OnClientValidated(std::shared_ptr<net::session<RemoteMessage>> client);
    void takeScreenshot(int imgWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X), int imgHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y));
    void OnCaptureWindow(wxTimerEvent&);
    void OnClose(wxCloseEvent& event);
    void closeServer();
    

private:
    wxStaticText* text;
    wxRect frameRect;
    wxMemoryDC memDC;
    wxBitmap screenshot, oldscreenshot;
    wxTimer* timer;
    wxPanel* LogPanel;
    wxScreenDC screenDC;
    wxTextCtrl* textCtrl;
    std::atomic<bool> m_isRunning; // Biến kiểm soát việc lặp

private:
    const int DELAY_MS = 10;
    bool CAPTURING = false;
    size_t nCountUser = 0;
    int screenWidth;
    int screenHeight;
    double fx;
    double fy;
    int x, y;
    int button;
    int delta;

    std::thread m_updateMess;
};