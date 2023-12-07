#pragma once

#include <wx/wx.h>
#include <memory>
#include "../../constant.hpp"
#include "../../components/Button.hpp"
#include "../ClientWindow/ClientWindow.hpp"
#include "../ServerWindow/ServerWindow.hpp"

class ManageWindow : public wxPanel
{
public:

    ManageWindow(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~ManageWindow();
private:
    void OnServerConnectButton(wxMouseEvent& event);
    void OnClientConnectButton(wxMouseEvent& event);

private:
    std::unique_ptr<ClientWindow> clientWindow;
    std::unique_ptr<ServerWindow> serverWindow;

    wxTextCtrl* IPInput;
};