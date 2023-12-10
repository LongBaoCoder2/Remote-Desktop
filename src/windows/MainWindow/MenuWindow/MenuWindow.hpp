#pragma once

#include <wx/wx.h>
#include "../../constant.hpp"
#include "../../components/Button.hpp"
#include "ListUserPanel.hpp"
#include "../../../models/IModel.hpp"
#include "../CaptureWindow/ClientWindow/ClientWindow.hpp"
#include "../CaptureWindow/ServerWindow/ServerWindow.hpp"

class MenuWindow : public wxPanel
{
public:
    MenuWindow(wxWindow* parent, std::shared_ptr<IModel>& _model, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~MenuWindow();

private:
    std::shared_ptr<IModel> model;

    ClientWindow* clientWindow = nullptr;
    ServerWindow* serverWindow = nullptr;
    wxTextCtrl* IPInput;

private:
    void CreateUserPanel();
    void CreateAdminPanel();

    // User
    void OnStartListening(wxMouseEvent&);

    void OnConnectToServer(wxCommandEvent& event);

    // Admin
    void ConnectToServer(std::string& host);

};