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
    void OnMessage(std::shared_ptr<net::session<RemoteMessage>> client, net::message<RemoteMessage> &msg) override;

private:
    const int DELAY_MS = 10000;
    bool CAPTURING = false;
    // bool hasUser = false;
    size_t nCountUser = 0;
    int screenWidth;
    int screenHeight;
    wxPanel *LogPanel;

    wxStaticText *text;
    wxBitmap screenshot;
    wxTimer *timer;
    wxScreenDC screenDC;
    // std::vector<uint32_t> garbageIDs;

    void OnClientValidated(std::shared_ptr<net::session<RemoteMessage>> client);

    void takeScreenShot(int imgWidth, int imgHeight);
    void takeScreenshot();
    void OnCaptureWindow(wxTimerEvent &);
};
