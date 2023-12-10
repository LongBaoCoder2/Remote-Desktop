#pragma once

#include <wx/wx.h>
#include <wx/statbmp.h>
#include "../../components/Button.hpp"
#include "../../constant.hpp"

wxDECLARE_EVENT(ConnectToUserEvent, wxCommandEvent);

class UserPanel : public wxPanel
{
public:
    UserPanel(wxWindow* parent, wxImage iconUser, std::string username, std::string ipAddress);

    ~UserPanel();

    void OnPaint(wxPaintEvent& event);


private:
    wxImage iconUser;
    std::string username;
    std::string IpAddress;

    void OnClick(wxMouseEvent& event);
};