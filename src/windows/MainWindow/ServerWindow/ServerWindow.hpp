#pragma once

#include "ServerNetwork.hpp"
#include <wx/wx.h>
#include <wx/mstream.h>

class ServerWindow : public net::IServer<RemoteMessage>, public wxFrame
{
public:
    ServerWindow(uint16_t port);
    virtual ~ServerWindow();

protected:
    bool OnClientConnect(std::shared_ptr<net::session<RemoteMessage>> client) override;
    void OnClientDisconnect(std::shared_ptr<net::session<RemoteMessage>> client) override;
    void OnMessage(std::shared_ptr<net::session<RemoteMessage>> client, net::message<RemoteMessage>& msg) override;

private:
    const int DELAY_MS = 1;
    bool CAPTURING = false;
    // bool hasUser = false;
    size_t nCountUser = 0;
    int screenWidth;
    int screenHeight;
    double fx;
    double fy;
    int x, y;
    int button;
    int delta;

    wxStaticText *text;
    wxRect frameRect;
    wxMemoryDC memDC;
    wxBitmap screenshot, oldscreenshot;
    wxTimer *timer;
    wxTimer* secondTimer;
    wxTimer* QueueTimer;
    wxPanel* LogPanel;
    wxScreenDC screenDC;
    wxTextCtrl* textCtrl;
    
    std::thread m_updateMess;

    int imagesSentThisSecond = 0;
    // std::vector<uint32_t> garbageIDs;


    void OnUpdateWindow(wxTimerEvent& event);
    void OnClientValidated(std::shared_ptr<net::session<RemoteMessage>> client);
    void OnSecondTimer(wxTimerEvent& event);
    void takeScreenshot(int imgWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X), int imgHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y));
    void OnCaptureWindow(wxTimerEvent &);
    // void CaptureAndSend();
};
